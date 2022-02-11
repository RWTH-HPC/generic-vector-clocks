#!/usr/local_rwth/bin/zsh

START_TIMESTAMP=$(date +"%Y-%m-%d_%H-%M-%S")
EVAL_RESULT_DIR=`pwd`/"eval_results"/$START_TIMESTAMP
mkdir -p $EVAL_RESULT_DIR

OUTPUT_DIR=`pwd`/"outputs"
mkdir -p $OUTPUT_DIR

### read config
MUST_EXE=`grep ^must ../config | cut -d ' ' -f 2`
SPEC_DIR=`grep ^spec ../config | cut -d ' ' -f 2`
ACCOUNT=`grep ^account ../config | cut -d ' ' -f 2`
OUTPUT_ROOT_DIR=`grep ^output_root ../config | cut -d ' ' -f 2`

ACCOUNT_ARG=""
if [ ! -z "$ACCOUNT" ]; then
  ACCOUNT_ARG="--account=${ACCOUNT}"
fi

SPEC_RESULT_DIR=$OUTPUT_ROOT_DIR/"result"
SPEC_CONFIG_DIR=$SPEC_DIR/"config"
SPEC_DEFAULT_SIZE="L"
SPEC_FALLBACK_SIZE="m"

mkdir -p $SPEC_RESULT_DIR


### make sure the spec result directory is empty
if [ -d $SPEC_RESULT_DIR ]; then
    mv $SPEC_RESULT_DIR/ "${SPEC_RESULT_DIR}_${START_TIMESTAMP}.bak"
    echo "The old spec result directory has been moved to ${SPEC_RESULT_DIR}_${START_TIMESTAMP}.bak"
fi



TARGETS="104"
ITERATIONS="3"
DATASET_SUFFIX="ref"
COMM_STRAT="mpi"
COLL_STRATS_CONFIG="naive binomial mpi"
MUST_MODES="plain vc"
COLL_STRATS="raw plain naive binomial mpi"

TASKS_PER_NODE="24"
NODES="1 2 4"

BIND="_bind"

while getopts t:n:s:c:i:d:b:pm flag; do
    case "${flag}" in
        t) TARGETS=${OPTARG};;
        n) NODES=${OPTARG};;
        s) COMM_STRAT=${OPTARG};;
        c) COLL_STRATS=${OPTARG};;
        i) ITERATIONS=${OPTARG};;
        d) DATASET_SUFFIX=${OPTARG};;
        b) TASKS_PER_NODE=${OPTARG};;
        p) BIND="";;
        m) SPEC_DEFAULT_SIZE="M" && SPEC_FALLBACK_SIZE="l";;
    esac
done

SPEC_SIZE_FILE=$SPEC_DIR/"benchspec/MPI2007/MPI${SPEC_DEFAULT_SIZE}2007.bset"
MUST_TEMP_BASE_DIR=`pwd`/"../preparation/temp${TASKS_PER_NODE}"

echo "targets ${TARGETS}" > $EVAL_RESULT_DIR/info
echo "coll_strats ${COLL_STRATS}" >> $EVAL_RESULT_DIR/info
echo "comm_strat ${COMM_STRAT}" >> $EVAL_RESULT_DIR/info
echo "nodes ${NODES}" >> $EVAL_RESULT_DIR/info
echo "iterations ${ITERATIONS}" >> $EVAL_RESULT_DIR/info
echo "dataset ${DATASET_SUFFIX}" >> $EVAL_RESULT_DIR/info

CSV_HEADER="bench_id,dataset,iterations,comm_strat,tasks_per_node,nodes"
for COLL_STRAT in ${COLL_STRATS}; do
    CSV_HEADER=${CSV_HEADER},${COLL_STRAT}
done
for NUM_NODES in ${NODES}; do
    echo $CSV_HEADER > $EVAL_RESULT_DIR/"node-${NUM_NODES}.csv"
done

### prepare spec configs
JOB_SCRIPT="job-script-mpi2007.sh"

CONFIG_SUFFIX=""
if [[ $BIND = "_bind" ]]; then
    CONFIG_SUFFIX=".in"
    echo "bind 1" >> $EVAL_RESULT_DIR/info
else
    echo "bind 0" >> $EVAL_RESULT_DIR/info
fi
SPEC_CONFIG_TEMPLATE_RAW="mpi2007_clx18_raw${BIND}.cfg.in"
SPEC_CONFIG_TEMPLATE_PLAIN="mpi2007_clx18_plain${BIND}.cfg.in"
SPEC_CONFIG_TEMPLATE_VC="mpi2007_clx18_vc${BIND}.cfg.in"
cp $SPEC_CONFIG_TEMPLATE_RAW $SPEC_CONFIG_DIR
sed -e 's@\#OUTPUT_ROOT_DIR\#'@"$OUTPUT_ROOT_DIR@"'' $SPEC_CONFIG_TEMPLATE_RAW > $SPEC_CONFIG_DIR/"mpi2007_clx18_raw${BIND}.cfg${CONFIG_SUFFIX}"
sed -e 's@\#MUST_EXE\#'@"$MUST_EXE@"'' -e 's@\#MUST_TEMP_DIR\#'@"$MUST_TEMP_BASE_DIR@"'' -e 's@\#COMM_STRAT\#'@"$COMM_STRAT@"'' -e 's@\#OUTPUT_ROOT_DIR\#'@"$OUTPUT_ROOT_DIR@"'' $SPEC_CONFIG_TEMPLATE_PLAIN > $SPEC_CONFIG_DIR/"mpi2007_clx18_plain${BIND}.cfg${CONFIG_SUFFIX}"
for COLL_STRAT in ${COLL_STRATS_CONFIG}; do
    sed -e 's@\#COLL_STRAT\#'@"$COLL_STRAT@"'g' -e 's@\#MUST_EXE\#'@"$MUST_EXE@"'' -e 's@\#MUST_TEMP_DIR\#'@"$MUST_TEMP_BASE_DIR@"'' -e 's@\#COMM_STRAT\#'@"$COMM_STRAT@"'' -e 's@\#OUTPUT_ROOT_DIR\#'@"$OUTPUT_ROOT_DIR@"'' $SPEC_CONFIG_TEMPLATE_VC > $SPEC_CONFIG_DIR/"mpi2007_clx18_${COLL_STRAT}${BIND}.cfg${CONFIG_SUFFIX}"
done

### SUBMIT JOBS
# postprocessing happens in job script as we do not wait here for a job to finish
# run different coll strats for same number of nodes and same target in same job script to use the exact same nodes
PREV_JOB_ID=""
DEPENDENCY_ARG=""

for TARGET in ${TARGETS}; do
    # check if medium or only large data set is available
    DATASET=`echo $SPEC_DEFAULT_SIZE | tr A-Z a-z`
    if ! grep -q $TARGET $SPEC_SIZE_FILE; then
        DATASET=$SPEC_FALLBACK_SIZE
    fi
    DATASET="${DATASET}${DATASET_SUFFIX}"

    mkdir $EVAL_RESULT_DIR/$TARGET

    echo $CSV_HEADER > $EVAL_RESULT_DIR/"bench-${TARGET}.csv"

    ### pre-build spec applications (saves time on nodes, but takes longer on frontend)
    cd $SPEC_DIR
    source shrc
    for COLL_STRAT in ${COLL_STRATS}; do
        runspec --action setup --config=mpi2007_clx18_${COLL_STRAT}${BIND}.cfg${CONFIG_SUFFIX} --noreportable --size=${DATASET} -I --tune=base ${TARGET}
    done
    cd -
    source ~/.zshrc

    for NUM_NODES in ${NODES}; do
        mkdir $EVAL_RESULT_DIR/$TARGET/$NUM_NODES
        echo "submitting target=${TARGET} on nodes=${NUM_NODES} dep_arg=${DEPENDENCY_ARG} coll_strats=${COLL_STRATS}, spec_dir=${SPEC_DIR}, dataset=${DATASET}"
        PREV_JOB_ID=`sbatch $DEPENDENCY_ARG --ntasks-per-node=$TASKS_PER_NODE --nodes=$NUM_NODES --chdir=$SPEC_DIR --job-name=SPEC-${TARGET}-${NUM_NODES} --time=10 --output="${OUTPUT_DIR}/slurm-bind.%J.out" $ACCOUNT_ARG \
                    --export=ALL,SPEC_RESULT_DIR=$SPEC_RESULT_DIR,EVAL_RESULT_DIR=$EVAL_RESULT_DIR,TASKS_PER_NODE=$TASKS_PER_NODE,NUM_NODES=$NUM_NODES,SPEC_TARGET=$TARGET,COLL_STRATS="${COLL_STRATS}",COMM_STRAT=$COMM_STRAT,ITERATIONS=$ITERATIONS,DATASET=$DATASET,BIND="${BIND}" $JOB_SCRIPT`
        DEPENDENCY_ARG="--dependency=afterany:${PREV_JOB_ID##* }"
    done
done
