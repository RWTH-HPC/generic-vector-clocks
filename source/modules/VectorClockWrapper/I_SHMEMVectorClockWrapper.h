/* Part of the MUST Project, under BSD-3-Clause License
 * See https://hpc.rwth-aachen.de/must/LICENSE for license information.
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**
 * @file I_SHMEMVectorClockWrapper.h
 *       Vector clock analysis module.
 *
 *  @date 29.06.2021
 *  @author Felix Tomski
 */

#include "MustTypes.h"
#include "BaseIds.h"
#include "GtiEnums.h"
#include "I_Module.h"

#ifndef I_SHMEMVECTORCLOCKWRAPPER_H
#define I_SHMEMVECTORCLOCKWRAPPER_H

/**
 * Wrapper for the GTI VectorClock module.
 *
 * Dependencies (order as listed):
 * - X
 *
 */
class I_SHMEMVectorClockWrapper : public gti::I_Module {
  public:
    virtual gti::GTI_ANALYSIS_RETURN init() = 0;
    virtual gti::GTI_ANALYSIS_RETURN tick() = 0;

    // collectives
    virtual gti::GTI_ANALYSIS_RETURN oneToAllProcs(MustParallelId pId, int PE_root, int PE_start, int logPE_stride, int PE_size) = 0;
    virtual gti::GTI_ANALYSIS_RETURN allToAllProcs(MustParallelId pId, int PE_start, int logPE_stride, int PE_size) = 0;
    virtual gti::GTI_ANALYSIS_RETURN allToAll(MustParallelId pId) = 0;

    // allocations
    virtual gti::GTI_ANALYSIS_RETURN mallocSegment(MustParallelId pId, size_t size) = 0;
    virtual gti::GTI_ANALYSIS_RETURN freeSegment(MustParallelId pId, MustAddressType ptr) = 0;

    // locking
    virtual gti::GTI_ANALYSIS_RETURN lock(MustParallelId pid, MustAddressType lockAddr) = 0;
    virtual gti::GTI_ANALYSIS_RETURN unlock(MustParallelId, MustAddressType lockAddr) = 0;
}; /*class I_SHMEMVectorClockWrapper*/

#endif /*I_SHMEMVECTORCLOCKWRAPPER_H */
