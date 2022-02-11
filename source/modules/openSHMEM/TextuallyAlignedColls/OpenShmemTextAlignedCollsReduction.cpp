/* This file is part of MUST (Marmot Umpire Scalable Tool)
 *
 * Copyright (C)
 *  2011-2015 ZIH, Technische Universitaet Dresden, Federal Republic of Germany
 *  2011-2015 Lawrence Livermore National Laboratories, United States of America
 *  2013-2015 RWTH Aachen University, Federal Republic of Germany
 *
 * See the file LICENSE.txt in the package base directory for details
 */

/**
 * @file OpenShmemTextAlignedCollsReduction.cpp
 *       @see must::OpenShmemTextAlignedCollsReduction.
 *
 *  @date 15.06.2015
 *  @author Tobias Hilbrich
 */

#include "GtiMacros.h"
#include "MustEnums.h"

#include "OpenShmemTextAlignedCollsReduction.h"

#include <sstream>
#include <assert.h>

using namespace must;

mGET_INSTANCE_FUNCTION(OpenShmemTextAlignedCollsReduction);
mFREE_INSTANCE_FUNCTION(OpenShmemTextAlignedCollsReduction);
mPNMPI_REGISTRATIONPOINT_FUNCTION(OpenShmemTextAlignedCollsReduction);

//=============================
// OpenShmemCollInfo -- Constructor
//=============================
OpenShmemCollInfo::OpenShmemCollInfo (
        MustParallelId pId,
        MustLocationId lId,
        int PE_start,
        int logPE_stride,
        int PE_size,
        OpenShmemCollectiveType collType,
        int numTasks,
        bool hasRoot,
        int PE_root,
        bool hasNelems,
        size_t nelems,
        bool hasNreduces,
        int nreduces,
        int fromChannel)
 : pId (pId),
   lId (lId),
   PE_start (PE_start),
   logPE_stride (logPE_stride),
   PE_size (PE_size),
   collType (collType),
   numTasks (numTasks),
   hasRoot (hasRoot),
   PE_root (PE_root),
   hasNelems (hasNelems),
   nelems (nelems),
   hasNreduces (hasNreduces),
   nreduces (nreduces),
   fromChannel (fromChannel)
{
    //Nothing to do
}

//=============================
// OpenShmemCollInfo -- Destructor
//=============================
OpenShmemCollInfo::~OpenShmemCollInfo ()
{
    //Nothing to do
}

//=============================
// OpenShmemCollWave -- Constructor
//=============================
OpenShmemCollWave::OpenShmemCollWave (
        int numReachableRanks)
 : myNumReachableRanks (numReachableRanks),
   myNumJoinedRanks (0),
   myCompletion (NULL),
   myOps (),
   myChannels (),
   myTimedOut (false)
{

}

//=============================
// OpenShmemCollWave -- Destructor
//=============================
OpenShmemCollWave::~OpenShmemCollWave ()
{
    if (myCompletion)
        delete myCompletion;

    std::list<OpenShmemCollInfo*>::iterator itA;
    for (itA = myOps.begin(); itA != myOps.end(); itA++)
    {
        if (*itA)
            delete (*itA);
    }
    myOps.clear();

    std::list<I_ChannelId*>::iterator itB;
    for (itB = myChannels.begin(); itB != myChannels.end(); itB++)
    {
        if (*itB)
            delete (*itB);
    }
    myChannels.clear();
}

//=============================
// OpenShmemCollWave -- belongsToWave
//=============================
bool OpenShmemCollWave::belongsToWave (gti::I_ChannelId* cId)
{
    //Initialize completion tree if needed
    if (!myCompletion && cId)
        myCompletion = new CompletionTree (
                cId->getNumUsedSubIds()-1,
                cId->getSubIdNumChannels(cId->getNumUsedSubIds()-1));

    //Do we actually have a cId?
    if (!cId)
    {
        assert (0); //This should't happen in fact
        return false;
    }

    /*
     * Question is am I waiting for this new operation?
     */
    if (!myCompletion->wasCompleted(cId))
        return true;

    return false;
}

//=============================
// OpenShmemCollWave -- abort
//=============================
bool OpenShmemCollWave::abort (std::list<gti::I_ChannelId*> *outFinishedChannels)
{
    assert (outFinishedChannels);

    if (outFinishedChannels)
    {
        outFinishedChannels->splice (outFinishedChannels->begin(), myChannels);
    }

    return timeout ();
}

//=============================
// OpenShmemCollWave -- timeout
//=============================
bool OpenShmemCollWave::timeout (void)
{
    //Store that we timed out, drop all channel lists
    myTimedOut = true;
    //Simply clear, if I recall correctly the memory in there will be freed by someone else
    myChannels.clear();

    return true;
}

//=============================
// OpenShmemCollWave -- isCompleted
//=============================
bool OpenShmemCollWave::isCompleted (void)
{
    if (myNumReachableRanks == myNumJoinedRanks)
        return true;
    return false;
}

//=============================
// OpenShmemPEGroupInfo -- Constructor
//=============================
OpenShmemPEGroupInfo::OpenShmemPEGroupInfo (
        int reachableBegin,
        int reachableEnd,
        int PE_start,
        int logPE_stride,
        int PE_size)
 : myActiveWaves (),
   myTimedOutWaves (),
   myNumReachableRanks (0),
   myPE_start (PE_start),
   myLogPE_stride (logPE_stride),
   myPE_size (PE_size)
{
    /**
     * @todo This is a VERY silly implementation, there is a constant time
     *       approach to do this.
     */
    //Determine how many ranks of our connected ranks we can reach
    int stride = 1;
    if (myLogPE_stride)
        stride = stride << myLogPE_stride; //bit shift left gives us the right power of 2
    for (int count = 0; count < myPE_size; count++)
    {
        int pe = myPE_start + count * stride;
        if (reachableBegin <= pe &&
            pe <= reachableEnd)
            myNumReachableRanks++;
    }

#ifdef MUST_OSH_COLL_DEBUG
    std::cout << getpid () << ": I created a group for (start=" << PE_start << ", logStride=" << logPE_stride << ", count=" << PE_size << ") of those PEs I can reach " << myNumReachableRanks << " PEs" << std::endl;
#endif /*MUST_OSH_COLL_DEBUG*/
}

//=============================
// OpenShmemPEGroupInfo -- Destructor
//=============================
OpenShmemPEGroupInfo::~OpenShmemPEGroupInfo (void)
{
    std::list<OpenShmemCollWave*>::iterator iter;
    for (iter = myActiveWaves.begin(); iter != myActiveWaves.end(); iter++)
    {
        if (*iter)
            delete (*iter);
    }
    myActiveWaves.clear();

    for (iter = myTimedOutWaves.begin(); iter != myTimedOutWaves.end(); iter++)
    {
        if (*iter)
            delete (*iter);
    }
    myTimedOutWaves.clear();
}

//=============================
// OpenShmemPEGroupInfo -- comparePEGroup
//=============================
bool OpenShmemPEGroupInfo::comparePEGroup (
        int PE_start,
        int logPE_stride,
        int PE_size,
        bool *partialOverlap,
        int *PE_overlap)
{
    //Simple: equality
    if (myPE_start == PE_start &&
        myLogPE_stride == logPE_stride &&
        myPE_size == PE_size)
    {
        if (partialOverlap) *partialOverlap = false;
        if (PE_overlap) *PE_overlap = -1;
        return true;
    }

    //Easy: They are not equal ...
    //More tricky: Do they overlap
    /**
     * @todo There must be a constant time approach to find out whether the two
     *       stride expressions overlap, I choose a VERY silly implementation
     *       for the moment.
     */
    if (partialOverlap) *partialOverlap = false;
    if (PE_overlap) *PE_overlap = -1;

    int stride = 1, strideOther = 1;
    if (myLogPE_stride)
        stride = stride << myLogPE_stride; //bit shift left gives us the right power of 2
    if (logPE_stride)
        strideOther = strideOther << logPE_stride;

    int count = 0, countOther = 0;
    int pe = myPE_start, peOther = PE_start;

    //Simple overlap in the initial PEs?
    if (pe == peOther)
    {
        if (partialOverlap) *partialOverlap = true;
        if (PE_overlap) *PE_overlap = pe;
        return false;
    }

    //Loop over all the PEs that we hit with the given strides
    do
    {
        //We increment the smaller of the PEs
        if (pe < peOther)
        {
            pe += stride;
            count++;
        }
        else
        {
            peOther += strideOther;
            countOther++;
        }

        //Did we catch an overlap?
        if (pe == peOther)
        {
            if (partialOverlap) *partialOverlap = true;
            if (PE_overlap) *PE_overlap = pe;
            break;
        }

    //We abort the loop once either count is reached
    } while (count < myPE_size && countOther < PE_size);

    return false;
}

//=============================
// OpenShmemPEGroupInfo -- hasOpenWaveWithPE
//=============================
bool OpenShmemPEGroupInfo::hasOpenWaveWithPE (
        int PE_overlap,
        OpenShmemCollInfo **pOutConflictOp)
{
    std::list<OpenShmemCollWave*>::iterator iter;

    for (int i = 0; i < 2; i++)
    {
        std::list<OpenShmemCollWave*> *pList = &myActiveWaves;
        if (i == 1)
            pList = &myTimedOutWaves;
        for (iter = pList->begin(); iter != pList->end();iter++)
        {
            assert (*iter); //wave must be allocated, there should not be nulls in here
            //If there is no completion tree yet, then the given cID is not present, so it belongs to the wave

            std::list<OpenShmemCollInfo*>::iterator opIter;
            for (opIter = (*iter)->myOps.begin(); opIter != (*iter)->myOps.end(); opIter++)
            {
                /**
                 * @todo use rank instead of pId here!
                 *       The operation must get a rank value that we initialize in its constructor for that!
                 */
                if ((*opIter)->pId == PE_overlap)
                {
                    if (pOutConflictOp) *pOutConflictOp = (*opIter);
                    return true;
                }
            }
        }
    }

    if (pOutConflictOp) *pOutConflictOp = NULL;
    return false;
}

//=============================
// OpenShmemPEGroupInfo -- timeout
//=============================
bool OpenShmemPEGroupInfo::timeout (void)
{
    std::list<OpenShmemCollWave*>::iterator iter;

    std::list<OpenShmemCollWave*> *pList = &myActiveWaves;
    for (iter = pList->begin(); iter != pList->end();iter++)
    {
        assert (*iter); //wave must be allocated, there should not be nulls in here
        if (!(*iter)->timeout())
            return false;
        myTimedOutWaves.push_back (*iter);
    }
    myActiveWaves.clear();

    return true;
}

//=============================
// Constructor
//=============================
OpenShmemTextAlignedCollsReduction::OpenShmemTextAlignedCollsReduction (const char* instanceName)
    : gti::ModuleBase<OpenShmemTextAlignedCollsReduction, I_OpenShmemTextAlignedColls> (instanceName),
      myReachableBegin (-1),
      myReachableEnd (-1),
      myHadSubset (false),
      myHadWeakAlignment (false),
      myHadWeakViolation (false),
      myIsActive (true),
      myPEGroups ()
{
    //create sub modules
    std::vector<I_Module*> subModInstances;
    subModInstances = createSubModuleInstances ();

    //handle sub modules
#define NUM_SUBS 3
    if (subModInstances.size() < NUM_SUBS)
    {
        std::cerr << "Module has not enough sub modules, check its analysis specification! (" << __FILE__ << "@" << __LINE__ << ")" << std::endl;
        assert (0);
    }
    if (subModInstances.size() > NUM_SUBS)
    {
        for (int i = NUM_SUBS; i < subModInstances.size(); i++)
            destroySubModuleInstance (subModInstances[i]);
    }

    myPIdMod = (I_ParallelIdAnalysis*) subModInstances[0];
    myLIdMod = (I_LocationAnalysis*) subModInstances[1];
    myLogger = (I_CreateMessage*) subModInstances[2];

    //Initialize module data
    /*Nothing to do yet*/
    this->getWrapperFunction ("Must_OpenShmem_Coll_Basic", (GTI_Fct_t*)&myCollBasicFct);
    this->getWrapperFunction ("Must_OpenShmem_Coll_Root", (GTI_Fct_t*)&myCollRootFct);
    this->getWrapperFunction ("Must_OpenShmem_Coll_EqualNum", (GTI_Fct_t*)&myCollEqualNumFct);
    this->getWrapperFunction ("Must_OpenShmem_Coll_EqualNumSizeT", (GTI_Fct_t*)&myCollEqualNumSizeTFct);
}

//=============================
// Destructor
//=============================
OpenShmemTextAlignedCollsReduction::~OpenShmemTextAlignedCollsReduction ()
{
    /*Free own things*/
    std::list<OpenShmemPEGroupInfo*>::iterator iter;
    for (iter = myPEGroups.begin(); iter != myPEGroups.end(); iter++)
    {
        if (*iter)
            delete (*iter);
    }
    myPEGroups.clear();

    /*Free sub-modules*/
	if (myPIdMod)
		destroySubModuleInstance ((I_Module*) myPIdMod);
	myPIdMod = NULL;

	if (myLIdMod)
	    destroySubModuleInstance ((I_Module*) myLIdMod);
	myLIdMod = NULL;

	if (myLogger)
		destroySubModuleInstance ((I_Module*) myLogger);
	myLogger = NULL;


}

//=============================
// collBasic
//=============================
GTI_ANALYSIS_RETURN OpenShmemTextAlignedCollsReduction::collBasic (
        MustParallelId pId,
        MustLocationId lId,
        int PE_start,
        int logPE_stride,
        int PE_size,
        int collType,
        int numTasks,
        gti::I_ChannelId *cId,
        std::list<gti::I_ChannelId*> *outFinishedChannels)
{
    if (!myIsActive)
        return GTI_ANALYSIS_SUCCESS; //If we reported an error before, we stop aggregation

    //Calculate a from channel, we use it to decide whether we run and report checks or not, as to avoid redundant reports
    int fromChannel = -1;
    if (cId)
        fromChannel = cId->getSubId(cId->getNumUsedSubIds()-1);
    if (cId->getNumUsedSubIds() == 1)
        fromChannel = -1; //Special rule, as reduction does not runs on application directly we must not avoid any checks on the first TBON layer!

    //Create op
    OpenShmemCollInfo* newOp = new OpenShmemCollInfo (
            pId,
            lId,
            PE_start,
            logPE_stride,
            PE_size,
            (OpenShmemCollectiveType) collType,
            numTasks,
            false,
            -1,
            false,
            0,
            false,
            -1,
            fromChannel);

    //== 2) Process or Queue ?
    return handleNewOp (pId, cId, outFinishedChannels, newOp);
}

//=============================
// collRoot
//=============================
GTI_ANALYSIS_RETURN OpenShmemTextAlignedCollsReduction::collRoot (
        MustParallelId pId,
        MustLocationId lId,
        int PE_start,
        int logPE_stride,
        int PE_size,
        int PE_root,
        int collType,
        int numTasks,
        gti::I_ChannelId *cId,
        std::list<gti::I_ChannelId*> *outFinishedChannels)
{
    if (!myIsActive)
        return GTI_ANALYSIS_SUCCESS; //If we reported an error before, we stop aggregation

    //Calculate a from channel, we use it to decide whether we run and report checks or not, as to avoid redundant reports
    int fromChannel = -1;
    if (cId)
        fromChannel = cId->getSubId(cId->getNumUsedSubIds()-1);
    if (cId->getNumUsedSubIds() == 1)
        fromChannel = -1; //Special rule, as reduction does not runs on application directly we must not avoid any checks on the first TBON layer!

    //Create op
    OpenShmemCollInfo* newOp = new OpenShmemCollInfo (
            pId,
            lId,
            PE_start,
            logPE_stride,
            PE_size,
            (OpenShmemCollectiveType) collType,
            numTasks,
            true,
            PE_root,
            false,
            0,
            false,
            -1,
            fromChannel);

    //== 2) Process or Queue ?
    return handleNewOp (pId, cId, outFinishedChannels, newOp);
}

//=============================
// collEqualNum
//=============================
GTI_ANALYSIS_RETURN OpenShmemTextAlignedCollsReduction::collEqualNum (
        MustParallelId pId,
        MustLocationId lId,
        int PE_start,
        int logPE_stride,
        int PE_size,
        int nelems,
        int collType,
        int numTasks,
        gti::I_ChannelId *cId,
        std::list<gti::I_ChannelId*> *outFinishedChannels)
{
    if (!myIsActive)
        return GTI_ANALYSIS_SUCCESS; //If we reported an error before, we stop aggregation

    //Calculate a from channel, we use it to decide whether we run and report checks or not, as to avoid redundant reports
    int fromChannel = -1;
    if (cId)
        fromChannel = cId->getSubId(cId->getNumUsedSubIds()-1);
    if (cId->getNumUsedSubIds() == 1)
        fromChannel = -1; //Special rule, as reduction does not runs on application directly we must not avoid any checks on the first TBON layer!

    //Create op
    OpenShmemCollInfo* newOp = new OpenShmemCollInfo (
            pId,
            lId,
            PE_start,
            logPE_stride,
            PE_size,
            (OpenShmemCollectiveType) collType,
            numTasks,
            false,
            -1,
            false,
            0,
            true,
            nelems,
            fromChannel);

    //== 2) Process or Queue ?
    return handleNewOp (pId, cId, outFinishedChannels, newOp);
}

//=============================
// collEqualNumSizeT
//=============================
GTI_ANALYSIS_RETURN OpenShmemTextAlignedCollsReduction::collEqualNumSizeT (
        MustParallelId pId,
        MustLocationId lId,
        int PE_start,
        int logPE_stride,
        int PE_size,
        size_t nelems,
        int collType,
        int numTasks,
        gti::I_ChannelId *cId,
        std::list<gti::I_ChannelId*> *outFinishedChannels)
{
    if (!myIsActive)
        return GTI_ANALYSIS_SUCCESS; //If we reported an error before, we stop aggregation

    //Calculate a from channel, we use it to decide whether we run and report checks or not, as to avoid redundant reports
    int fromChannel = -1;
    if (cId)
        fromChannel = cId->getSubId(cId->getNumUsedSubIds()-1);
    if (cId->getNumUsedSubIds() == 1)
        fromChannel = -1; //Special rule, as reduction does not runs on application directly we must not avoid any checks on the first TBON layer!

    //Create op
    OpenShmemCollInfo* newOp = new OpenShmemCollInfo (
            pId,
            lId,
            PE_start,
            logPE_stride,
            PE_size,
            (OpenShmemCollectiveType) collType,
            numTasks,
            false,
            -1,
            true,
            nelems,
            false,
            -1,
            fromChannel);

    //== 2) Process or Queue ?
    return handleNewOp (pId, cId, outFinishedChannels, newOp);
}

//=============================
// handleNewOp
//=============================
GTI_ANALYSIS_RETURN OpenShmemTextAlignedCollsReduction::handleNewOp (
        MustParallelId pId,
        I_ChannelId* cId,
        std::list<gti::I_ChannelId*> *outFinishedChannels,
        OpenShmemCollInfo* newOp)
{
    GTI_ANALYSIS_RETURN ret;

    //Get a rank for the given pId
    int rank = myPIdMod->getInfoForId(pId).rank;

    //Access information on reachable ranks
    if (myReachableBegin < 0)
    {
        this->getReachableRanks(
                &myReachableBegin,
                &myReachableEnd,
                rank);

#ifdef MUST_OSH_COLL_DEBUG
        std::cout << getpid () << ": OpenShmem Reduce Module -> Can reach: " << myReachableBegin << "-" << myReachableEnd << std::endl;
#endif /*MUST_OSH_COLL_DEBUG*/
    }

    //Store whether we saw any subset collective (one that does not includes all PEs)
    if (newOp->PE_start != 0 || newOp->logPE_stride != 0 || newOp->PE_size < myReachableEnd)
    {
        //Note this triggers on the tool process that receives events of the highest most PE only;
        //=> newOp->PE_size < myReachableEnd
        //But that should be good enough
        myHadSubset = true;
    }

    //Search for the PE group info for this op
    std::list<OpenShmemPEGroupInfo*>::iterator iter;
    OpenShmemPEGroupInfo* groupInfo = NULL;
    std::list<OpenShmemCollWave*> overlapWaves;
    bool hadError = false;

    for (iter = myPEGroups.begin(); iter != myPEGroups.end(); iter++)
    {
        assert (*iter); //There must be something

        //Compare PE group in the op with this group
        bool partialOverlap = false;
        int PE_overlap;
        if ((*iter)->comparePEGroup(newOp->PE_start, newOp->logPE_stride, newOp->PE_size, &partialOverlap, &PE_overlap))
        {
            //We found it
            groupInfo = *iter;
            break; //see note/todo below this is a part in it: We continue with the search, as to find overlapping PE groups
            //continue;
        }

        //If we have a partial overlap, we can check whether the two groups block
        //each other (group A waits for a PE active in group B and vice versa)
        /**
         * @note
         *  The check is more part of a deadlock detection and not complete, i.e., it will not always succeed.
         *  Also note: The recursive scheme can make this catch fewer errors even.
         */
        /**
         * @todo This is disabled for the moment, we would need to compare two PE groups
         *       and check whether they include any pair of active ops with PEs that
         *       are required by the other group and vice versa.
         */
        /*OpenShmemCollInfo *conflictOp;
        if (    partialOverlap &&
                PE_overlap != myPIdMod->getInfoForId(newOp->pId).rank &&
                (*iter)->hasOpenWaveWithPE (PE_overlap, &conflictOp))
        {
            reportCollsWithOverlappingGroups (
                    newOp,
                    conflictOp,
                    PE_overlap);
            hadError = true;
            break;
        }*/
    }

    //Do we need a new Info?
    if (!groupInfo && !hadError)
    {
        groupInfo = new OpenShmemPEGroupInfo (
                myReachableBegin,
                myReachableEnd,
                newOp->PE_start,
                newOp->logPE_stride,
                newOp->PE_size);
        myPEGroups.push_back(groupInfo);
    }

    //Apply the new op to the PE group info
    if (groupInfo)
    {
        ret = addOpToGroup (
                groupInfo,
                cId,
                outFinishedChannels,
                newOp);
    }

#ifdef MUST_OSH_COLL_DEBUG
    printAsDot ();
#endif /*MUST_OSH_COLL_DEBUG*/

    //If there was an error we stop processing
    if (hadError || ret == GTI_ANALYSIS_FAILURE)
    {
        //We had an error here, delete the op here (we didn't add it to the wave then)
        delete newOp;

        /**
         * @todo we should time out all active waves at this point and put their
         *       waiting cIds into outFinishedChannels!
         */

        myIsActive = false;
        ret = GTI_ANALYSIS_IRREDUCIBLE;
    }

    return ret;
}

//=============================
// addOpToGroup
//=============================
GTI_ANALYSIS_RETURN OpenShmemTextAlignedCollsReduction::addOpToGroup (
        OpenShmemPEGroupInfo *groupInfo,
        I_ChannelId* cId,
        std::list<gti::I_ChannelId*> *outFinishedChannels,
        OpenShmemCollInfo* newOp)
{
    GTI_ANALYSIS_RETURN ret;

    OpenShmemCollWave* wave = NULL;
    std::list<OpenShmemCollWave*> *waves = NULL;
    std::list<OpenShmemCollWave*>::iterator waveIter;

    //1) Search through all existing waves to see whether it belongs there
    for (int i = 0; i < 2; i++)
    {
        waves = &(groupInfo->myActiveWaves);
        bool isActive = true;
        if (i == 1)
        {
            waves = &(groupInfo->myTimedOutWaves);
            isActive = false;
        }

        //loop over all waves we have
        for (waveIter = waves->begin(); waveIter != waves->end(); waveIter++)
        {
            assert (*waveIter);
            if ( (*waveIter)->belongsToWave(cId))
            {
                wave = *waveIter;
                break;
            }
        }

        if (wave)
            break;
    }

    //2) If we don't have an existing wave, then create a new one
    if (!wave)
    {
        wave = new OpenShmemCollWave (groupInfo->myNumReachableRanks);
        groupInfo->myActiveWaves.push_back(wave);
        waveIter = groupInfo->myActiveWaves.end();
        waveIter--;
        waves = &(groupInfo->myActiveWaves);
    }

    //3) Apply to the wave
    ret = addOpToWave (wave, cId, outFinishedChannels, newOp);

    //4) Did we have an error, if so abort all active waves
    if (ret == GTI_ANALYSIS_FAILURE)
    {
        for (waveIter = groupInfo->myActiveWaves.begin(); waveIter != groupInfo->myActiveWaves.end(); waveIter++)
            (*waveIter)->abort (outFinishedChannels);
    }

    //6) Was the wave completed?
    if (ret != GTI_ANALYSIS_FAILURE && wave->isCompleted())
    {
        //Remove from current list
        waves->erase(waveIter);
        delete (wave);
    }

    return ret;
}

//=============================
// addOpToWave
//=============================
GTI_ANALYSIS_RETURN OpenShmemTextAlignedCollsReduction::addOpToWave (
                    OpenShmemCollWave *wave,
                    I_ChannelId* cId,
                    std::list<gti::I_ChannelId*> *outFinishedChannels,
                    OpenShmemCollInfo* newOp)
{
#ifdef MUST_OSH_COLL_DEBUG
    std::cout << getpid() << "coll with ID " << newOp->collType << " from " << newOp->pId << " with lId=" << newOp->lId << "..." << std::endl;
#endif /*MUST_OSH_COLL_DEBUG*/

    //Initialize completion tree if needed
    if (!wave->myCompletion && cId)
        wave->myCompletion = new CompletionTree (
                cId->getNumUsedSubIds()-1,
                cId->getSubIdNumChannels(cId->getNumUsedSubIds()-1));

    //==0) First op?
    OpenShmemCollInfo* headOp = NULL;
    if (wave->myNumJoinedRanks != 0)
    {
        assert (!wave->myOps.empty());
        headOp = wave->myOps.front();
    }

    //1) We can ignore checks for this op if its something our ancestors already check
    bool needToCheckThisOp = true;

    if (cId && wave->myCompletion)
    {
        if (!wave->myCompletion->createsNewChild(cId))
        {
            needToCheckThisOp = false;

#ifdef MUST_OSH_COLL_DEBUG
            std::cout << getpid() << "Not checking this op since it is checked by an ancestor of mine" << std::endl;
#endif /*MUST_OSH_COLL_DEBUG*/
        }
    }

    //==2) OpenSHMEM standard consistency checks
    if (headOp && needToCheckThisOp)
    {
        //A) Is the collective-id right?
        if (newOp->collType != headOp->collType)
        {
            //Report
            reportCollTypeMismatch (newOp, headOp);

            //We should also open all our outFinishedChannels
            wave->abort (outFinishedChannels);

            return GTI_ANALYSIS_FAILURE;
        }

        //B) Root must match
        if (newOp->hasRoot && newOp->PE_root != headOp->PE_root)
        {
            assert (headOp->hasRoot); //If the new op has a root and the collective type is similar as checked above, then the head op must also have a root

            //Report
            reportRootMismatch (newOp, headOp);

            //We should also open all our outFinishedChannels
            wave->abort (outFinishedChannels);

            return GTI_ANALYSIS_FAILURE;
        }

        //C) Nelems must match
        if (newOp->hasNelems && newOp->nelems != headOp->nelems)
        {
            assert (headOp->hasNelems); //If the new op has a root and the collective type is similar as checked above, then the head op must also have a root

            //Report
            reportNelemsMismatch (newOp, headOp);

            //We should also open all our outFinishedChannels
            wave->abort (outFinishedChannels);

            return GTI_ANALYSIS_FAILURE;
        }

        //D) nreduces must match
        if (newOp->hasNreduces && newOp->nreduces != headOp->nreduces)
        {
            assert (headOp->hasNreduces); //If the new op has a root and the collective type is similar as checked above, then the head op must also have a root

            //Report
            reportNreducesMismatch (newOp, headOp);

            //We should also open all our outFinishedChannels
            wave->abort (outFinishedChannels);

            return GTI_ANALYSIS_FAILURE;
        }

        //E) Textual alignment checks
#ifdef USE_CALLPATH
        LocationInfo &refA = myLIdMod->getInfoForId (newOp->pId, newOp->lId);
        LocationInfo &refB = myLIdMod->getInfoForId (headOp->pId, headOp->lId);

        //1) Totally equal stacks?
        bool equalStacks = true;
        bool equalCallers = true;
        std::string callerA = "", callerB = "";
        bool hadCallerA = false, hadCallerB = false;

        std::list<MustStackLevelInfo>::iterator stackIterA, stackIterB;
        stackIterA = refA.stack.begin();
        stackIterB = refB.stack.begin();
        while (stackIterA != refA.stack.end() || stackIterB != refB.stack.end())
        {
            //Handling of full equality
            if ( stackIterA == refB.stack.end() || stackIterB == refB.stack.end())
            {
                //If the one stack is longer than the other, its no full equality
                equalStacks = false;
            }
            else if (equalStacks)
            {
                //If we have a stack for both ops we check whether we see difference in them
                if (stackIterA->symName != stackIterB->symName ||
                    stackIterA->fileModule != stackIterB->fileModule ||
                    stackIterA->lineOffset != stackIterB->lineOffset)
                    equalStacks = false;
            }

            //For "same function" equality we must fiddle out the calling function of the shmem call
            //We do that by using the last symName before a symName that includes the name of the shmem call
            /**
             * @todo this must be matched up with future stack gathering and stack pruning,
             *       in the current prototype we get a stack with lots of MUST internal things.
             *       Thus the thing we wanna use is not the bottom of the stack.
             */
            if (stackIterA != refA.stack.end())
            {
                if (hadCallerA)
                {
                    callerA = stackIterA->symName;
                    hadCallerA = false;
                }
                if (stackIterA->symName.find (refA.callName) != std::string::npos)
                    hadCallerA = true;
            }

            if (stackIterB != refB.stack.end())
            {
                if (hadCallerB)
                {
                    callerB = stackIterB->symName;
                    hadCallerB = false;
                }
                if (stackIterB->symName.find (refB.callName) != std::string::npos)
                    hadCallerB = true;
            }

            //Next
            if (stackIterA != refA.stack.end())
                stackIterA++;
            if (stackIterB != refB.stack.end())
                stackIterB++;
        }

        //See todo above on getting the caller of the function, this checks that we did things more or less correct
        assert (callerA != "" && callerB != "");

        if (callerA != callerB)
            equalCallers = false;

        if (!equalStacks && equalCallers)
        {
            reportWeakAlignedColl (newOp, headOp);
        }
        else if (!equalStacks && !equalCallers)
        {
            reportUnalignedColl (newOp, headOp);
        }
#endif
    }//End Do we need to check anything for this op?

    //=4) Add the op
    GTI_ANALYSIS_RETURN ret;

    if (needToCheckThisOp)
        wave->myOps.push_back(newOp);

    if (cId)
        wave->myCompletion->addCompletion(cId);
    wave->myNumJoinedRanks += newOp->numTasks;

    assert (wave->myNumJoinedRanks <= wave->myNumReachableRanks); //Make sure nothing weird happens, we should have never more than we can reach

    /*
     * We can create a reduced record if:
     * - we are not timed out
     * - we have a list of outFinishedChannels
     */
    if (!wave->myTimedOut && outFinishedChannels)
    {
        if (wave->myNumJoinedRanks == wave->myNumReachableRanks)
        {
#ifdef MUST_OSH_COLL_DEBUG
            std::cout << getpid() << "Completed a wave, now adding a representative event" << std::endl;
#endif /*MUST_OSH_COLL_DEBUG*/

            //This is complete
            ret = GTI_ANALYSIS_SUCCESS;

            outFinishedChannels->splice(outFinishedChannels->end(), wave->myChannels);
            createReducedRecord(newOp, wave->myNumReachableRanks);
        }
        else
        {
#ifdef MUST_OSH_COLL_DEBUG
            std::cout << getpid() << "Wave not finished yet, we have " << wave->myNumJoinedRanks << " out of " << wave->myNumReachableRanks << " reachable PEs." << std::endl;
#endif /*MUST_OSH_COLL_DEBUG*/

            //If not complete we return that we are waiting and also add the channel id of the op to the list in the wave
            ret = GTI_ANALYSIS_WAITING;

            if (cId)
                wave->myChannels.push_back(cId);
        }
    }
    else
    {
#ifdef MUST_OSH_COLL_DEBUG
            std::cout << getpid() << "Not aggregating for this op since its wave timed out." << std::endl;
#endif /*MUST_OSH_COLL_DEBUG*/

        ret = GTI_ANALYSIS_IRREDUCIBLE;
    }

    //== If we did not add this op to our op lists, we must now free it
    if (!needToCheckThisOp && ret != GTI_ANALYSIS_FAILURE)
        delete newOp;

    return ret;
}

//=============================
// timeout
//=============================
void OpenShmemTextAlignedCollsReduction::timeout ()
{
    std::list<OpenShmemPEGroupInfo*>::iterator iter;

    //Timeout all waves in all PE group infos
    for (iter = myPEGroups.begin(); iter != myPEGroups.end(); iter++)
    {
        if (!*iter)
            continue;

        (*iter)->timeout ();
    }

#ifdef MUST_OSH_COLL_DEBUG
    std::cout << getpid () << ": had a timeout" << std::endl;
    printAsDot ();
#endif /*MUST_OSH_COLL_DEBUG*/
}

//=============================
// reportCollsWithOverlappingGroups
//=============================
bool OpenShmemTextAlignedCollsReduction::reportCollsWithOverlappingGroups (
        OpenShmemCollInfo *opA,
        OpenShmemCollInfo *opB)
{
    //Ignore if already checked by ancestor in TBON
    if (    opA->fromChannel >= 0 &&
            opA->fromChannel >= 0 &&
            opA->fromChannel == opB->fromChannel)
        return true;

    std::list <std::pair <MustParallelId, MustLocationId> > references;
    std::stringstream stream;

    stream
        << "Detected two active collectives that each include a PE that is missing in the active set of the other collective, deadlock is likely. "
        << "A correct OpenSHMEM application must execute consistent collectives within groups of PEs. "
        << "The first collective (A) uses the active set (start="<<opA->PE_start<<", logStride="<<opA->logPE_stride<<", count="<<opA->PE_size<<") and the second "
        << "collective (B) uses the active set  (start="<<opB->PE_start<<", logStride="<<opB->logPE_stride<<", count="<<opB->PE_size<<"). "
        << "PE " << myPIdMod->getInfoForId(opA->pId).rank << " activated an operation for collective A, but is also part of collective B. "
        << "Its active operation is detailed in the source location for this error message. "
        << "PE " << myPIdMod->getInfoForId(opB->pId).rank << " activated an operation for collective B, but is also part of collective A. "
        << "Its active operation is detailed as reference 1 (rightmost column). "
        << "Note that the MUST error messages will not include all pairs of overlapping collectives pairs (for performance reasons), but rather just a single or a few representative cases of the error. ";
    references.push_back(std::make_pair (opB->pId, opB->lId));

    stream << std::endl << "Note that collective matching was disabled as a result, collectives won't be analyzed for their correctness or blocking state anymore (Since the outcome of this would be undefined past a first error). You should solve this issue and rerun your application with MUST.";

    myLogger->createMessage (
            MUST_ERROR_OPENSHMEM_COLLECTIVE_PE_GROUP_LOCK,
            opA->pId,
            opA->lId,
            MustErrorMessage,
            stream.str(),
            references);

    return true;
}

//=============================
// reportCollTypeMismatch
//=============================
bool OpenShmemTextAlignedCollsReduction::reportCollTypeMismatch (
                    OpenShmemCollInfo *opA,
                    OpenShmemCollInfo *opB)
{
    //Ignore if already checked by ancestor in TBON
    if (    opA->fromChannel >= 0 &&
            opA->fromChannel >= 0 &&
            opA->fromChannel == opB->fromChannel)
        return true;

    std::list <std::pair <MustParallelId, MustLocationId> > references;
    std::stringstream stream;

    stream
    << "Detected a collective mismatch. "
    << "The application issued collectives of distinct names that use the same group of PEs and match. "
    << "The PE group is (start="<<opA->PE_start<<", logStride="<<opA->logPE_stride<<", count="<<opA->PE_size<<"). "
    << "The first collective (A) is detailed in the source location for this error message. "
    << "The second collective (B) is detailed as reference 1 (rightmost column). "
    << "A correct OpenSHMEM application must use the same collective for A and B. "
    << "Note that the MUST error messages will not include all collective operation pairs (for performance reasons), but rather just a single or a few representative cases of the error. ";
    references.push_back(std::make_pair (opB->pId, opB->lId));

    stream << std::endl << "Note that collective matching was disabled as a result, collectives won't be analyzed for their correctness or blocking state anymore (Since the outcome of this would be undefined past a first error). You should solve this issue and rerun your application with MUST.";

    myLogger->createMessage (
            MUST_ERROR_OPENSHMEM_COLLECTIVE_TYPE_MISMATCH,
            opA->pId,
            opA->lId,
            MustErrorMessage,
            stream.str(),
            references);

    return true;
}

//=============================
// reportRootMismatch
//=============================
bool OpenShmemTextAlignedCollsReduction::reportRootMismatch (
                    OpenShmemCollInfo *opA,
                    OpenShmemCollInfo *opB)
{
    //Ignore if already checked by ancestor in TBON
    if (    opA->fromChannel >= 0 &&
            opA->fromChannel >= 0 &&
            opA->fromChannel == opB->fromChannel)
        return true;

    std::list <std::pair <MustParallelId, MustLocationId> > references;
    std::stringstream stream;

    stream
    << "Collectives that use a root PE identify mismatching roots. "
    << "The PE group is (start="<<opA->PE_start<<", logStride="<<opA->logPE_stride<<", count="<<opA->PE_size<<"). "
    << "The first collective (A) uses root=" << opA->PE_root << " and is detailed in the source location for this error message. "
    << "The second collective (B) uses root=" << opB->PE_root << " and is detailed as reference 1 (rightmost column). "
    << "A correct OpenSHMEM application must use the an equal root for all collectives that will match at runtime. "
    << "Note that the MUST error messages will not include all collective operation pairs (for performance reasons), but rather just a single or a few representative cases of the error. ";
    references.push_back(std::make_pair (opB->pId, opB->lId));

    stream << std::endl << "Note that collective matching was disabled as a result, collectives won't be analyzed for their correctness or blocking state anymore (Since the outcome of this would be undefined past a first error). You should solve this issue and rerun your application with MUST.";

    myLogger->createMessage (
            MUST_ERROR_OPENSHMEM_COLLECTIVE_ROOT_MISMATCH,
            opA->pId,
            opA->lId,
            MustErrorMessage,
            stream.str(),
            references);

    return true;
}

//=============================
// reportNelemsMismatch
//=============================
bool OpenShmemTextAlignedCollsReduction::reportNelemsMismatch (
                    OpenShmemCollInfo *opA,
                    OpenShmemCollInfo *opB)
{
    //Ignore if already checked by ancestor in TBON
    if (    opA->fromChannel >= 0 &&
            opA->fromChannel >= 0 &&
            opA->fromChannel == opB->fromChannel)
        return true;

    std::list <std::pair <MustParallelId, MustLocationId> > references;
    std::stringstream stream;

    stream
    << "Collectives that use an \"nelems\" count identify mismatching counts. "
    << "The PE group is (start="<<opA->PE_start<<", logStride="<<opA->logPE_stride<<", count="<<opA->PE_size<<"). "
    << "The first collective (A) uses nelems=" << opA->nelems << " and is detailed in the source location for this error message. "
    << "The second collective (B) uses nelems=" << opB->nelems << " and is detailed as reference 1 (rightmost column). "
    << "A correct OpenSHMEM application must use an equal count for \"nelems\" on all PEs of a collective. "
    << "Note that the MUST error messages will not include all collective operation pairs (for performance reasons), but rather just a single or a few representative cases of the error. ";
    references.push_back(std::make_pair (opB->pId, opB->lId));

    stream << std::endl << "Note that collective matching was disabled as a result, collectives won't be analyzed for their correctness or blocking state anymore (Since the outcome of this would be undefined past a first error). You should solve this issue and rerun your application with MUST.";

    myLogger->createMessage (
            MUST_ERROR_OPENSHMEM_COLLECTIVE_NELEMS_MISMATCH,
            opA->pId,
            opA->lId,
            MustErrorMessage,
            stream.str(),
            references);

    return true;
}

//=============================
// reportNreducesMismatch
//=============================
bool OpenShmemTextAlignedCollsReduction::reportNreducesMismatch (
                    OpenShmemCollInfo *opA,
                    OpenShmemCollInfo *opB)
{
    //Ignore if already checked by ancestor in TBON
    if (    opA->fromChannel >= 0 &&
            opA->fromChannel >= 0 &&
            opA->fromChannel == opB->fromChannel)
        return true;

    std::list <std::pair <MustParallelId, MustLocationId> > references;
    std::stringstream stream;

    stream
    << "Collectives that use an \"nreduces\" count identify mismatching counts. "
    << "The PE group is (start="<<opA->PE_start<<", logStride="<<opA->logPE_stride<<", count="<<opA->PE_size<<"). "
    << "The first collective (A) uses nreduces=" << opA->nreduces << " and is detailed in the source location for this error message. "
    << "The second collective (B) uses nreduces=" << opB->nreduces << " and is detailed as reference 1 (rightmost column). "
    << "A correct OpenSHMEM application must use an equal count for \"nreduces\" on all PEs of a reduction. "
    << "Note that the MUST error messages will not include all collective operation pairs (for performance reasons), but rather just a single or a few representative cases of the error. ";
    references.push_back(std::make_pair (opB->pId, opB->lId));

    stream << std::endl << "Note that collective matching was disabled as a result, collectives won't be analyzed for their correctness or blocking state anymore (Since the outcome of this would be undefined past a first error). You should solve this issue and rerun your application with MUST.";

    myLogger->createMessage (
            MUST_ERROR_OPENSHMEM_COLLECTIVE_NREDUCES_MISMATCH,
            opA->pId,
            opA->lId,
            MustErrorMessage,
            stream.str(),
            references);

    return true;
}

//=============================
// reportWeakAlignedColl
//=============================
bool OpenShmemTextAlignedCollsReduction::reportWeakAlignedColl (
                    OpenShmemCollInfo *opA,
                    OpenShmemCollInfo *opB)
{
    //Remember that we had a weak alignment
    myHadWeakAlignment = true;

    //Ignore if already checked by ancestor in TBON
    if (    opA->fromChannel >= 0 &&
            opA->fromChannel >= 0 &&
            opA->fromChannel == opB->fromChannel)
        return true;

    std::list <std::pair <MustParallelId, MustLocationId> > references;
    std::stringstream stream;

    stream
    << "An OpenSHMEM collective uses a weak textual alignment. "
    << "This happens if the call stacks that issue matching collective operations differ, but still result from the same program function. "
    << "The OpenSHMEM standard allows this behavior, but it may highlight a defect if you did not intend this behavior. "
    << "The PE group of the collective is (start="<<opA->PE_start<<", logStride="<<opA->logPE_stride<<", count="<<opA->PE_size<<"). "
    << "The first collective (A) and its call stack is detailed in the source location for this error message. "
    << "The second collective (B) and its call stack is detailed as reference 1 (rightmost column).";
    references.push_back(std::make_pair (opB->pId, opB->lId));

    myLogger->createMessage (
            MUST_WARNING_OPENSHMEM_COLLECTIVE_WEAK_ALIGNMENT,
            opA->pId,
            opA->lId,
            MustWarningMessage,
            stream.str(),
            references);

    return true;
}

//=============================
// reportUnalignedColl
//=============================
bool OpenShmemTextAlignedCollsReduction::reportUnalignedColl (
                    OpenShmemCollInfo *opA,
                    OpenShmemCollInfo *opB)
{
    //Remember that we had an unaligned collective
    myHadWeakViolation = true;

    //Ignore if already checked by ancestor in TBON
    if (    opA->fromChannel >= 0 &&
            opA->fromChannel >= 0 &&
            opA->fromChannel == opB->fromChannel)
        return true;

    std::list <std::pair <MustParallelId, MustLocationId> > references;
    std::stringstream stream;

    stream
    << "An OpenSHMEM collective is textually unaligned. "
    << "This happens if the call stacks that issue matching collective operations differ, and not even result from the same program function. "
    << "The OpenSHMEM standard allows this behavior, but it may highlight a defect if you did not intend this behavior. "
    << "The PE group of the collective is (start="<<opA->PE_start<<", logStride="<<opA->logPE_stride<<", count="<<opA->PE_size<<"). "
    << "The first collective (A) and its call stack is detailed in the source location for this error message. "
    << "The second collective (B) and its call stack is detailed as reference 1 (rightmost column).";
    references.push_back(std::make_pair (opB->pId, opB->lId));

    myLogger->createMessage (
            MUST_WARNING_OPENSHMEM_COLLECTIVE_UNALIGNED,
            opA->pId,
            opA->lId,
            MustWarningMessage,
            stream.str(),
            references);

    return true;
}

//=============================
// createReducedRecord
//=============================
bool OpenShmemTextAlignedCollsReduction::createReducedRecord(
        OpenShmemCollInfo *op,
        int numTasks)
{
    if (op->hasRoot)
    {
        //Collective with root
        assert (myCollRootFct);
        (*myCollRootFct) (
                op->pId,
                op->lId,
                op->PE_start,
                op->logPE_stride,
                op->PE_size,
                op->PE_root,
                op->collType,
                numTasks
            );
    }
    else if (op->hasNelems)
    {
        //Collective with nelems
        assert (myCollEqualNumSizeTFct);
        (*myCollEqualNumSizeTFct) (
                op->pId,
                op->lId,
                op->PE_start,
                op->logPE_stride,
                op->PE_size,
                op->nelems,
                op->collType,
                numTasks
            );
    }
    else if (op->hasNreduces)
    {
        //Collective with nreduces
        assert (myCollEqualNumFct);
        (*myCollEqualNumFct) (
                op->pId,
                op->lId,
                op->PE_start,
                op->logPE_stride,
                op->PE_size,
                op->nreduces,
                op->collType,
                numTasks
            );
    }
    else
    {
        //Basic collective
        assert (myCollBasicFct);
        (*myCollBasicFct) (
                op->pId,
                op->lId,
                op->PE_start,
                op->logPE_stride,
                op->PE_size,
                op->collType,
                numTasks
            );
    }

    return true;
}


//=============================
// printAsDot
//=============================
bool OpenShmemTextAlignedCollsReduction::printAsDot (void)
{
    //todo
    return true;
}

/*EOF*/
