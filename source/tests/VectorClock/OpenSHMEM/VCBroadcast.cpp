/* Part of the MUST Project, under BSD-3-Clause License
 * See https://hpc.rwth-aachen.de/must/LICENSE for license information.
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 *  @file VCBroadcast.cpp
 *
 *  @date 12.03.2022
 *  @author Simon Schwitanski
 */

// RUN: %must-run --must:layout \
// RUN: %builddir/tests/VectorClock/VCBroadcastLayout.xml \
// RUN: %must-bin-dir/VCBroadcast 2>&1 \
// RUN: | FileCheck %s

// CHECK-DAG: shutdown(0){{.*}}clk=(2, 1, 1, 1)
// CHECK-DAG: shutdown(1){{.*}}clk=(2, 2, 1, 1)
// CHECK-DAG: shutdown(2){{.*}}clk=(2, 1, 2, 1)
// CHECK-DAG: shutdown(3){{.*}}clk=(2, 1, 1, 2)

#include <mpi.h>
#include <shmem.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

long pSync[_SHMEM_BCAST_SYNC_SIZE];

int main(int argc, char **argv) {
    static int val = 42;
    static int test = 0;

    MPI_Init(&argc, &argv);
    shmem_init();

    int mype = shmem_my_pe();
    int npes = shmem_n_pes();

    // VC_AnnotateSignal(NULL);
    for (int i = 0; i < _SHMEM_BCAST_SYNC_SIZE; i += 1)
        pSync[i] = _SHMEM_SYNC_VALUE;

    shmem_barrier_all();
    if (mype == 0) {
        test = 42;
        shmem_broadcast32(&val, &test, 1, 0, 0, 0, npes, pSync);
    } else {
        shmem_broadcast32(&val, &test, 1, 0, 0, 0, npes, pSync);
    }

    MPI_Finalize();
}
