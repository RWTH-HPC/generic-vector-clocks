/* Part of the MUST Project, under BSD-3-Clause License
 * See https://hpc.rwth-aachen.de/must/LICENSE for license information.
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 *  @file VCBarrier.cpp
 *
 *  @date 12.03.2022
 *  @author Simon Schwitanski
 */

// RUN: %must-run --must:layout \
// RUN: %builddir/tests/VectorClock/VCBarrierLayout.xml \
// RUN: %must-bin-dir/VCBarrier 2>&1 \
// RUN: | FileCheck %s

// CHECK-DAG: shutdown(0){{.*}}clk=(1, 1, 1, 1)
// CHECK-DAG: shutdown(1){{.*}}clk=(1, 1, 1, 1)
// CHECK-DAG: shutdown(2){{.*}}clk=(1, 1, 2, 2)
// CHECK-DAG: shutdown(3){{.*}}clk=(1, 1, 2, 2)

#include <mpi.h>
#include <shmem.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

long pSync[_SHMEM_BCAST_SYNC_SIZE];

int main(int argc, char **argv) {
    int numprocs, mype, i;

    MPI_Init(&argc, &argv);
    shmem_init();

    mype = shmem_my_pe();

    for (i = 0; i < _SHMEM_BCAST_SYNC_SIZE; i += 1)
        pSync[i] = _SHMEM_SYNC_VALUE;

    shmem_barrier(0, 0, shmem_n_pes(), pSync);

    if (mype == 2 || mype == 3) // ranks 2 and 3 perform a barrier
    {
        shmem_barrier(2, 0, 2, pSync);
    }

    MPI_Finalize();
}
