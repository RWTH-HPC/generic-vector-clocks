/* Part of the MUST Project, under BSD-3-Clause License
 * See https://hpc.rwth-aachen.de/must/LICENSE for license information.
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file SHMEMVectorClockWrapper.h
 *       @see I_SHMEMVectorClockWrapper.h.
 *
 *  @date 29.06.2021
 *  @author Felix Tomski
 */

#include "I_CommTrack.h"
#include "I_ParallelIdAnalysis.h"
#include "I_VectorClock.h"
#include "I_WinTrack.h"
#include "ModuleBase.h"

#include "I_SHMEMVectorClockWrapper.h"
#include <vector>

#ifndef SHMEMVECTORCLOCKWRAPPER_H
#define SHMEMVECTORCLOCKWRAPPER_H

using namespace gti;

namespace must {
class SHMEMVectorClockWrapper : public gti::ModuleBase<SHMEMVectorClockWrapper, I_SHMEMVectorClockWrapper> {
  public:
    /**
     * Constructor.
     */
    SHMEMVectorClockWrapper(const char* instanceName);

    /**
     * Destructor.
     */
    virtual ~SHMEMVectorClockWrapper(void);

    GTI_ANALYSIS_RETURN init();
    GTI_ANALYSIS_RETURN tick();

    GTI_ANALYSIS_RETURN oneToAllProcs(MustParallelId pId, int PE_root, int PE_start, int logPE_stride, int PE_size);
    GTI_ANALYSIS_RETURN allToAllProcs(MustParallelId pId, int PE_start, int logPE_stride, int PE_size);
    GTI_ANALYSIS_RETURN allToAll(MustParallelId pId);
    GTI_ANALYSIS_RETURN mallocSegment(MustParallelId pId, size_t size);
    GTI_ANALYSIS_RETURN freeSegment(MustParallelId pId, MustAddressType ptr);

    GTI_ANALYSIS_RETURN lock(MustParallelId pId, MustAddressType lockAddr);
    GTI_ANALYSIS_RETURN unlock(MustParallelId pId, MustAddressType lockAddr);

  protected:
    I_VectorClock* myVectorClockMod;

  private:
    int myNumPEs;
    int myPEId;
    int generateContextId(int PE_start, int logPE_stride, int PE_size);
    std::vector<int> translateToGroupRanks(int PE_start, int logPE_stride, int PE_size);
    int translateToLocalRank(int globalRank, int PE_start, int logPE_stride, int PE_size);

}; /*class SHMEMVectorClockWrapper*/
} /*namespace must*/

#endif /*SHMEMVECTORCLOCKWRAPPER_H*/
