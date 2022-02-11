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
// RUN: %builddir/tests/VectorClock/VCAnnotateLockLayout.xml \
// RUN: %must-bin-dir/VCAnnotateLock 2>&1 \
// RUN: | FileCheck %s

// CHECK-DAG: shutdown(0){{.*}}clk=(1, 1, 1)
// CHECK-DAG: shutdown(1){{.*}}clk=(1, 3, 1)
// CHECK-DAG: shutdown(2){{.*}}clk=(1, 3, 3)

#include <mpi.h>
#include <shmem.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <GTI_Annotations.h>

int main(int argc, char **argv) {
    static long lock = 0;
    MPI_Init(&argc, &argv);
    shmem_init();

    int mype = shmem_my_pe();
    int npes = shmem_n_pes();

    shmem_barrier_all();

    if (mype == 1) {
        GTI_AnnotateTick();
        GTI_AnnotateResourceWait((uint64_t)&lock, 2);
        // shmem_set_lock(&lock);

        // shmem_clear_lock(&lock);
        GTI_AnnotateTick();
        GTI_AnnotateResourceSignal((uint64_t)&lock, 2);
    } else if (mype == 2) {
        sleep(1); // PE 2 should lock after PE 1 to have a reproducible VC
        GTI_AnnotateTick();
        GTI_AnnotateResourceWait((uint64_t)&lock, 2);
        // shmem_set_lock(&lock);

        // shmem_clear_lock(&lock);
        GTI_AnnotateTick();
        GTI_AnnotateResourceSignal((uint64_t)&lock, 2);
    }

    MPI_Finalize();
}
