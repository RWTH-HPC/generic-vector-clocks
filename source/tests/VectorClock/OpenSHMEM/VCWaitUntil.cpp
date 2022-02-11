/* Part of the MUST Project, under BSD-3-Clause License
 * See https://hpc.rwth-aachen.de/must/LICENSE for license information.
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 *  @file VCWaitUntil.cpp
 *
 *  @date 12.03.2022
 *  @author Simon Schwitanski
 */

// RUN: %must-run --must:layout \
// RUN: %builddir/tests/VectorClock/VCWaitUntilLayout.xml \
// RUN: %must-bin-dir/VCWaitUntil 2>&1 \
// RUN: | FileCheck %s

// CHECK-DAG: shutdown(0){{.*}}clk=(3, 3, 2, 2)
// CHECK-DAG: shutdown(1){{.*}}clk=(3, 3, 2, 2)
// CHECK-DAG: shutdown(2){{.*}}clk=(3, 3, 2, 2)
// CHECK-DAG: shutdown(3){{.*}}clk=(3, 3, 2, 2)

#include <mpi.h>
#include <shmem.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <GTI_Annotations.h>

long pSync[_SHMEM_BCAST_SYNC_SIZE];

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);
    shmem_init();

    int mype = shmem_my_pe();
    int npes = shmem_n_pes();

    int *val = (int *)shmem_malloc(4);
    *val = 0;

    if (mype == 0) {
        // each PE0 signals to PE1
        int flag = 1;
        // shmem_int32_put(val, &flag, 1, 1);
        GTI_AnnotateTick();
        GTI_AnnotateResourceSignal((uint64_t)&val, 1);
    } else if (mype == 1) {
        // shmem_int32_wait_until(val, SHMEM_CMP_NE, 0);
        GTI_AnnotateTick();
        GTI_AnnotateResourceWait((uint64_t)&val, 1);
    }

    shmem_free(val);

    MPI_Finalize();
}
