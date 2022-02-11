#!/usr/local_rwth/bin/zsh

##SBATCH --cpus-per-task=1
#SBATCH --overcommit

#SBATCH -v
#SBATCH --partition=c18m
#SBATCH --exclusive
#SBATCH --switches=1


# Load gcc/7 to have working libstdc++ and gfortran for MUST module, then load intel again
module unload intel
module load gcc/7
module load intel/2021.4.0
module load cmake/3.16.4

source shrc
TOTAL_RANKS=$(($TASKS_PER_NODE * $NUM_NODES))
NEW_TARGET_ROW=${SPEC_TARGET},${DATASET},${ITERATIONS},${COMM_STRAT},${TASKS_PER_NODE},${NUM_NODES}

EXPANDED_NODELIST=`scontrol show hostname $SLURM_JOB_NODELIST | paste -d, -s | tr -s ',' ' '`

sleep $((5+2*$NUM_NODES))

for COLL_STRAT in ${COLL_STRATS}; do
    if (( $TASKS_PER_NODE == 24)); then
#        for tool threads
#        CPU_MAPPING_STR=$(eval echo {0..$((48 - 1))..2} | tr -s ' ' ',' | tr -s -d '\n' '')

#        for tool processes
        CPU_MAPPING_STR=$(eval echo {0..$(($TASKS_PER_NODE/2 - 1))} | tr -s ' ' ',' | tr -s -d '\n' '')
        CPU_MAPPING_STR=$CPU_MAPPING_STR,$(eval echo {$(($TASKS_PER_NODE))..$(($TASKS_PER_NODE + $TASKS_PER_NODE/2 - 1))} | tr -s ' ' ',' | tr -s -d '\n' '')
        if [[ $COLL_STRAT != "raw" ]]; then
            CPU_MAPPING_STR=$CPU_MAPPING_STR,$(eval echo {$(($TASKS_PER_NODE/2))..$(($TASKS_PER_NODE - 1))} | tr -s ' ' ',' | tr -s -d '\n' '')
            CPU_MAPPING_STR=$CPU_MAPPING_STR,$(eval echo {$(($TASKS_PER_NODE + $TASKS_PER_NODE/2))..$(($TASKS_PER_NODE*2 - 1))} | tr -s ' ' ',' | tr -s -d '\n' '')
        fi
    elif (( $TASKS_PER_NODE == 48 )); then
        CPU_MAPPING_STR=$(eval echo {0..$(($TASKS_PER_NODE - 1))} | tr -s ' ' ',' | tr -s -d '\n' '')

#        CPU_MAPPING_STR=$(eval echo {0..$(($TASKS_PER_NODE/4 - 1))} | tr -s ' ' ',' | tr -s -d '\n' '')
#        CPU_MAPPING_STR=$CPU_MAPPING_STR,$(eval echo {$(($TASKS_PER_NODE/2))..$(($TASKS_PER_NODE/2 + $TASKS_PER_NODE/4 - 1))} | tr -s ' ' ',' | tr -s -d '\n' '')
#        CPU_MAPPING_STR=$CPU_MAPPING_STR,$(eval echo {$(($TASKS_PER_NODE/4))..$(($TASKS_PER_NODE/2 - 1))} | tr -s ' ' ',' | tr -s -d '\n' '')
#        CPU_MAPPING_STR=$CPU_MAPPING_STR,$(eval echo {$(($TASKS_PER_NODE*3/4))..$(($TASKS_PER_NODE - 1))} | tr -s ' ' ',' | tr -s -d '\n' '')
    fi

    GENERATED_MACHINEFILE=$EVAL_RESULT_DIR/$SPEC_TARGET/$NUM_NODES/machinefile
    echo "#jobid: $SLURM_JOB_ID" > $GENERATED_MACHINEFILE
    echo "#launch_node: $SLURMD_NODENAME" >> $GENERATED_MACHINEFILE
    for NODE_NAME in $EXPANDED_NODELIST; do
        echo $NODE_NAME:$TASKS_PER_NODE >> $GENERATED_MACHINEFILE
    done
    if [[ $COLL_STRAT != "raw" ]]; then
        for NODE_NAME in $EXPANDED_NODELIST; do
            echo $NODE_NAME:$TASKS_PER_NODE >> $GENERATED_MACHINEFILE
        done
    fi

    if [[ $BIND = "_bind" ]]; then
        sed -e 's@\#INTEL_BINDING_LIST\#'@"$CPU_MAPPING_STR@"'' -e 's@\#MACHINEFILE\#'@"$GENERATED_MACHINEFILE@"'' config/mpi2007_clx18_${COLL_STRAT}_bind.cfg.in > config/mpi2007_clx18_${COLL_STRAT}_bind.cfg
    fi

    runspec --nobuild --action validate --config=mpi2007_clx18_${COLL_STRAT}${BIND} --noreportable --iterations=${ITERATIONS} --output_format=csv --ranks=${TOTAL_RANKS} --size=${DATASET} -I --tune=base ${SPEC_TARGET}

    SPEC_COLL_OUTPUT_DIR=$EVAL_RESULT_DIR/$SPEC_TARGET/$NUM_NODES/$COLL_STRAT
    mv $SPEC_RESULT_DIR $SPEC_COLL_OUTPUT_DIR

    NEW_TARGET_ROW=$NEW_TARGET_ROW,`grep -m$(($ITERATIONS+1)) "${SPEC_TARGET}" ${SPEC_COLL_OUTPUT_DIR}/*.csv | tail -n1 | cut -d ',' -f 3`
done

echo $NEW_TARGET_ROW >> $EVAL_RESULT_DIR/"bench-${SPEC_TARGET}.csv"
echo $NEW_TARGET_ROW >> $EVAL_RESULT_DIR/"node-${NUM_NODES}.csv"

