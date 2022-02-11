#!/usr/local_rwth/bin/zsh

tasks_per_node=24
nodes="1 2 4"
comm_strats="mpi thread"
coll_strats="naive binomial mpi"
must_modes="plain vc"

must=`grep must ../config | cut -d ' ' -f 2`
path_layout_dest=`pwd`/"concrete_layouts"
path_layout_src="layouts"

while getopts t:n:s:c:l: flag; do
    case "${flag}" in
        t) tasks_per_node=${OPTARG};; 
        n) nodes=${OPTARG};; 
        s) comm_strats=${OPTARG};; 
        c) coll_strats=${OPTARG};; 
    esac
done

places_per_node=$tasks_per_node

# necessary for tool threads?
#if [ "${comm_strat}" = "thread" ]
#then
#    places_per_node=$(($places_per_node * 2))
#fi

app_comm_protocol="CProtMpiSplited"
app_comm_strat="CStratSimpleUp"
tool_comm_strat="CStratPRecvIntra"
tool_comm_protocol="CProtMpiSplited"

set -e

if [ ! -d $path_layout_dest ]; then
    mkdir -p $path_layout_dest
fi

total_ranks=0
module load cmake/3.16.4

for n in ${nodes}; do
    total_ranks=$(($tasks_per_node * $n))
    for mmode in ${must_modes}; do
        for comm_strat in ${comm_strats}; do
            if [ "${comm_strat}" = "thread" ]; then
                app_comm_protocol="CProtSharedMemory"
            fi

            if [ "${mmode}" = "vc" ]; then
                for coll_strat in ${coll_strats}; do
                    sed -e 's@\#COMM_STRAT_NAME\#'@"${comm_strat}@"'' -e 's@\#APP_COMM_PROT\#'@"${app_comm_protocol}@"'' -e 's@\#APP_COMM_STRAT\#'@"${app_comm_strat}@"'' -e 's@\#TOOL_COMM_PROT\#'@"${tool_comm_protocol}@"'' -e 's@\#TOOL_COMM_STRAT\#'@"${tool_comm_strat}@"'' -e 's@\#NUM_APPS\#'@"$(($n * places_per_node))@"'' -e 's@\#NUM_PLACES\#'@"$total_ranks@"'' ${path_layout_src}/layout_${mmode}.xml.in > ${path_layout_dest}/layout_${comm_strat}_${mmode}_${total_ranks}.xml
                    ${must} --must:mode prepare --must:temp temp${tasks_per_node}/temp_${comm_strat}_${mmode}_${coll_strat}_${total_ranks} --must:layout ${path_layout_dest}/layout_${comm_strat}_${mmode}_${total_ranks}.xml
                done
            else
                    sed -e 's@\#COMM_STRAT_NAME\#'@"${comm_strat}@"'' -e 's@\#APP_COMM_PROT\#'@"${app_comm_protocol}@"'' -e 's@\#APP_COMM_STRAT\#'@"${app_comm_strat}@"'' -e 's@\#TOOL_COMM_PROT\#'@"${tool_comm_protocol}@"'' -e 's@\#TOOL_COMM_STRAT\#'@"${tool_comm_strat}@"'' -e 's@\#NUM_APPS\#'@"$(($n * places_per_node))@"'' -e 's@\#NUM_PLACES\#'@"$total_ranks@"'' ${path_layout_src}/layout_${mmode}.xml.in > ${path_layout_dest}/layout_${comm_strat}_${mmode}_${total_ranks}.xml
                    ${must} --must:mode prepare --must:temp temp${tasks_per_node}/temp_${comm_strat}_${mmode}_${total_ranks} --must:layout ${path_layout_dest}/layout_${comm_strat}_${mmode}_${total_ranks}.xml
            fi
        done
    done
done

