/* Part of the MUST Project, under BSD-3-Clause License
 * See https://hpc.rwth-aachen.de/must/LICENSE for license information.
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 *  @file VCAllocFree.cpp
 *
 *  @date 12.03.2022
 *  @author Simon Schwitanski
 */

// RUN: %must-run --must:layout \
// RUN: %builddir/tests/VectorClock/VCAllocFreeLayout.xml \
// RUN: %must-bin-dir/VCAllocFree 2>&1 \
// RUN: | FileCheck %s

// CHECK-DAG: shutdown(0){{.*}}clk=(3, 3, 3)
// CHECK-DAG: shutdown(1){{.*}}clk=(3, 3, 3)
// CHECK-DAG: shutdown(2){{.*}}clk=(3, 3, 3)

#include <mpi.h>
#include <shmem.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);
    shmem_init();

    int mype = shmem_my_pe();
    int npes = shmem_n_pes();

    int *val = (int *)shmem_malloc(4);

    // each PE sends its own PE number to neighoring "right" rank
    shmem_int32_put(val, &mype, 1, (mype + 1) % npes);

    shmem_sync_all();
    printf("I am rank %d and my value is %d\n", mype, *val);

    shmem_free(val);

    MPI_Finalize();
}
