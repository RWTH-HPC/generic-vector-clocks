/* Part of the MUST Project, under BSD-3-Clause License
 * See https://hpc.rwth-aachen.de/must/LICENSE for license information.
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 *  @file VCBarrierAll.cpp
 *
 *  @date 12.03.2022
 *  @author Simon Schwitanski
 */

// RUN: %must-run --must:layout \
// RUN: %builddir/tests/VectorClock/VCBarrierAllLayout.xml \
// RUN: %must-bin-dir/VCBarrierAll 2>&1 \
// RUN: | FileCheck %s

// CHECK-DAG: shutdown(0){{.*}}clk=(1, 1, 1, 1)
// CHECK-DAG: shutdown(1){{.*}}clk=(1, 1, 1, 1)
// CHECK-DAG: shutdown(2){{.*}}clk=(1, 1, 1, 1)

#include <mpi.h>
#include <shmem.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int numprocs, myid, i;

    MPI_Init(&argc, &argv);
    shmem_init();

    shmem_barrier_all();

    MPI_Finalize();
}
