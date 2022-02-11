/* Part of the MUST Project, under BSD-3-Clause License
 * See https://hpc.rwth-aachen.de/must/LICENSE for license information.
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file SHMEMVectorClockWrapper.cpp
 *       @see I_SHMEMVectorClockWrapper.h.
 *
 *  @date 29.06.2021
 *  @author Felix Tomski
 */

#include "SHMEMVectorClockWrapper.h"
#include "GtiMacros.h"
#include <cmath>
#include <pshmem.h>

using namespace must;

mGET_INSTANCE_FUNCTION(SHMEMVectorClockWrapper)
mFREE_INSTANCE_FUNCTION(SHMEMVectorClockWrapper)
mPNMPI_REGISTRATIONPOINT_FUNCTION(SHMEMVectorClockWrapper)

//=============================
// Constructor
//=============================
SHMEMVectorClockWrapper::SHMEMVectorClockWrapper(const char *instanceName)
    : gti::ModuleBase<SHMEMVectorClockWrapper, I_SHMEMVectorClockWrapper>(
          instanceName) {
    // create sub modules
    std::vector<I_Module *> subModInstances;
    subModInstances = createSubModuleInstances();

    // handle sub modules
#define NUM_SUBMODULES 1
    if (subModInstances.size() < NUM_SUBMODULES) {
        std::cerr << "Module has not enough sub modules, check its analysis "
                     "specification! ("
                  << __FILE__ << "@" << __LINE__ << ")" << std::endl;
        assert(0);
    }
    if (subModInstances.size() > NUM_SUBMODULES) {
        for (std::vector<I_Module *>::size_type i = NUM_SUBMODULES;
             i < subModInstances.size(); i++)
            destroySubModuleInstance(subModInstances[i]);
    }

    myVectorClockMod = (I_VectorClock *)subModInstances[0];

    // Initialize module data
    /*None needed*/
}

//=============================
// Destructor
//=============================
SHMEMVectorClockWrapper::~SHMEMVectorClockWrapper() {
    if (myVectorClockMod)
        destroySubModuleInstance((I_Module *)myVectorClockMod);
    myVectorClockMod = NULL;

    // assert(sharedLocks.empty());
}

//=============================
// tick
//=============================
GTI_ANALYSIS_RETURN SHMEMVectorClockWrapper::tick() {
    return myVectorClockMod->tick();
}

//=============================
// init
//=============================
GTI_ANALYSIS_RETURN SHMEMVectorClockWrapper::init() {
    // Get number of PEs
    // TODO: This has to be implemented in a separate CommTracking module later.
    myNumPEs = pshmem_n_pes();
    myPEId = pshmem_my_pe();
}

//=============================
// oneToAll
//=============================
GTI_ANALYSIS_RETURN SHMEMVectorClockWrapper::oneToAllProcs(MustParallelId pId,
                                                           int PE_root,
                                                           int PE_start,
                                                           int logPE_stride,
                                                           int PE_size) {
    std::vector<int> groupRanks =
        translateToGroupRanks(PE_start, logPE_stride, PE_size);
    int localRank =
        translateToLocalRank(myPEId, PE_start, logPE_stride, PE_size);
    int localRoot =
        translateToLocalRank(PE_root, PE_start, logPE_stride, PE_size);

    // Generate hash for given combination of PE_start, logPE_stride and PE_size
    // TODO: Fix VC implementation to work without communication contexts.
    int hash = generateContextId(PE_start, logPE_stride, PE_size);

    return myVectorClockMod->oneToAll(localRank, localRoot, PE_root, groupRanks,
                                      hash);
}

//=============================
// allToAll
//=============================
GTI_ANALYSIS_RETURN SHMEMVectorClockWrapper::allToAll(MustParallelId pId) {
    return allToAllProcs(pId, 0, 0, myNumPEs); // synchronize with all processes
}

//=============================
// allToAllProcs
//=============================
GTI_ANALYSIS_RETURN SHMEMVectorClockWrapper::allToAllProcs(MustParallelId pId,
                                                           int PE_start,
                                                           int logPE_stride,
                                                           int PE_size) {
    std::vector<int> groupRanks =
        translateToGroupRanks(PE_start, logPE_stride, PE_size);
    int localRank =
        translateToLocalRank(myPEId, PE_start, logPE_stride, PE_size);

    // Generate hash for given combination of PE_start, logPE_stride and PE_size
    // TODO: Fix VC implementation to work without communication contexts.
    int hash = generateContextId(PE_start, logPE_stride, PE_size);

    return myVectorClockMod->allToAll(
        groupRanks,
        hash, // use unique hash for each communication context in SHMEM
        localRank, 0, myPEId);
}

//=============================
// mallocSegment
//=============================
GTI_ANALYSIS_RETURN SHMEMVectorClockWrapper::mallocSegment(MustParallelId pId,
                                                           size_t size) {
    // only synchronizes when size > 0 according to specification
    if (size > 0)
        return allToAllProcs(pId, 0, 0,
                             myNumPEs); // synchronize with all processes
    else
        return GTI_ANALYSIS_SUCCESS;
}

//=============================
// freeSegment
//=============================
GTI_ANALYSIS_RETURN SHMEMVectorClockWrapper::freeSegment(MustParallelId pId,
                                                         MustAddressType ptr) {
    // only synchronizes when ptr != NULL according to specification
    if (ptr != 0)
        return allToAllProcs(pId, 0, 0,
                             myNumPEs); // synchronize with all processes
    else
        return GTI_ANALYSIS_SUCCESS;
}

//=============================
// lock
//=============================
GTI_ANALYSIS_RETURN SHMEMVectorClockWrapper::lock(MustParallelId pId, MustAddressType lockAddr) {
    return myVectorClockMod->lock(lockAddr, 0); // we use PE 0 as central deposition rank
}

//=============================
// unlock
//=============================
GTI_ANALYSIS_RETURN SHMEMVectorClockWrapper::unlock(MustParallelId pId, MustAddressType lockAddr) {
    return myVectorClockMod->unlock(lockAddr, 0); // we use PE 0 as central deposition rank
}

//=============================
// translateGroupRanks
//=============================
std::vector<int>
SHMEMVectorClockWrapper::translateToGroupRanks(int PE_start, int logPE_stride,
                                               int PE_size) {
    int stride = (int)std::pow(2, logPE_stride);
    std::vector<int> groupRanks;
    int count = 0;
    int localRank; // We have to translate the process group (P1, P2, ...) to
                   // (0, 1, ...) to make it work with the VC module
    for (int i = PE_start; i < myNumPEs; i += stride) {
        groupRanks.push_back(i);
        if (i == myPEId)
            localRank = count;
        count++;
    }

    return groupRanks;
}

//=============================
// translateToLocalRank
//=============================
int SHMEMVectorClockWrapper::translateToLocalRank(int globalRank, int PE_start,
                                                  int logPE_stride,
                                                  int PE_size) {
    int stride = (int)std::pow(2, logPE_stride);
    int count = 0;
    int localRank;
    for (int i = PE_start; i < myNumPEs; i += stride) {
        if (i == globalRank)
            return count;
        count++;
    }

    assert(false);
    return -1;
}

//=============================
// generateContextId
//=============================
int SHMEMVectorClockWrapper::generateContextId(int PE_start, int logPE_stride,
                                               int PE_size) {
    // use unique hash for each communication context in SHMEM
    return (PE_size * 31 + logPE_stride) * 17 + PE_start;
}
