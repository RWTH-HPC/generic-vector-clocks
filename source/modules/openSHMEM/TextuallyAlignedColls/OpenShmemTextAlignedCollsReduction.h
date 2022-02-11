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
 * @file OpenShmemTextAlignedCollsReduction.h
 *       @see must::OpenShmemTextAlignedCollsReduction.
 *
 *  @date 15.06.2015
 *  @author Tobias Hilbrich
 */

#include "ModuleBase.h"
#include "I_ParallelIdAnalysis.h"
#include "I_LocationAnalysis.h"
#include "I_CreateMessage.h"
#include "OpenShmemCollApi.h"
#include "CompletionTree.h"

#include "I_OpenShmemTextAlignedColls.h"

#include <string>

#ifndef OPENSHMEMTEXTALIGNEDCOLLSREDUCTION_H
#define OPENSHMEMTEXTALIGNEDCOLLSREDUCTION_H

using namespace gti;

namespace must
{
    /**
     * Container to store information on a collective operation.
     */
    class OpenShmemCollInfo
    {
        public:
            OpenShmemCollInfo (
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
                    int fromChannel);

            virtual ~OpenShmemCollInfo (void);

            MustParallelId pId;
            MustLocationId lId;
            int PE_start;
            int logPE_stride;
            int PE_size;
            OpenShmemCollectiveType collType;
            int numTasks;

            bool hasRoot;
            int PE_root;
            bool hasNelems;
            size_t nelems;
            bool hasNreduces;
            int nreduces;

            int fromChannel;
    };

    /**
     * Information for a collective wave.
     */
    class OpenShmemCollWave
    {
        public:
            OpenShmemCollWave (
                    int numReachableRanks);

            ~OpenShmemCollWave (void);

            /**
             * Tests whether the given channel identifier belongs to this wave.
             * If so the function returns true.
             * Assumes that the operation for the channel identifier has an equal group
             * as the PE group associated with this wave.
             * @param cId channel identifier to test.
             * @return true if argument identifies an operation that belongs to the wave.
             */
            bool belongsToWave (gti::I_ChannelId* cId);

            /**
             * Aborts aggregation for this wave and pushes cIds of all operations for which
             * we have a pending aggregation into the given list.
             * Memory management of the cIds is then transferred to the caller.
             * @param outFinishedChannels return value things for gti::I_Reduction.
             * @return true iff successful.
             */
            bool abort (std::list<gti::I_ChannelId*> *outFinishedChannels);

            /**
             * Times our this wave.
             */
            bool timeout (void);

            /**
             * Returns true iff completed.
             * @return true iff completed.
             */
            bool isCompleted (void);

            int myNumReachableRanks;
            int myNumJoinedRanks;

            CompletionTree *myCompletion;

            std::list<OpenShmemCollInfo*> myOps;
            std::list<I_ChannelId*> myChannels;

            bool myTimedOut;
    };

    /**
     * Information for a PE group expression.
     */
    class OpenShmemPEGroupInfo
    {
        public:
            /**
             * Constructor
             * @param reachableBegin first PE that can send events to this place
             * @param reachableEnd last PE that can send events to this place
             * @param PE_start start PE for this PE group
             * @param logPE_stride stride as exponent of 2 that this group uses
             * @param PE_size count of PEs in this group
             */
            OpenShmemPEGroupInfo (
                    int reachableBegin,
                    int reachableEnd,
                    int PE_start,
                    int logPE_stride,
                    int PE_size);

            /**
             * Destructor.
             */
            ~OpenShmemPEGroupInfo (void);

            /**
             * Compares this PE group with the given group and returns true if both groups
             * are similar.
             * @param PE_start to compare against
             * @param logPE_stride to compare against
             * @param PE_size to compare against
             * @param pointer to storage for a bool or NULL, is set to true if there is a partial overlap and to false otherwise.
             * @param pointer to storage for an int or NULL, is set to the first PE that is in both groups if there is an overlap.
             */
            bool comparePEGroup (
                    int PE_start,
                    int logPE_stride,
                    int PE_size,
                    bool *partialOverlap,
                    int *PE_overlap);

            /**
             * Returns true iff this wave has an uncompleted wave
             * that does not yet includes the given channel identifier.
             * (Irrespective of whether its aggregation can still
             * succeed or not).
             * @param PE_overlap a PE to test whether its op is active in some wave in this coll group.
             * @param pOutConflictOp pointer to storage for an op, will point to an op of that is active in this group and has the given PE.
             * @return true or false.
             */
            bool hasOpenWaveWithPE (
                    int PE_overlap, OpenShmemCollInfo **pOutConflictOp);

            /**
             * Times out all waves.
             */
            bool timeout (void);

            std::list<OpenShmemCollWave*> myActiveWaves; /**< Currently active waves.*/
            std::list<OpenShmemCollWave*> myTimedOutWaves; /**< Waves that timed out.*/

            int myNumReachableRanks;
            int myPE_start;
            int myLogPE_stride;
            int myPE_size;
    };

    /**
     * Implementaion of I_OpenShmemTextAlignedColls.
     * This implementation serves as the reduction module.
     */
    class OpenShmemTextAlignedCollsReduction : public gti::ModuleBase<OpenShmemTextAlignedCollsReduction, I_OpenShmemTextAlignedColls>
    {
        public:
            /**
             * Constructor.
             * @param instanceName name of this module instance.
             */
            OpenShmemTextAlignedCollsReduction (const char* instanceName);

    		/**
    		 * Destructor.
    		 */
    		virtual ~OpenShmemTextAlignedCollsReduction (void);

    		/**
    		 * @see I_OpenShmemTextAlignedColls::collBasic.
    		 */
    		GTI_ANALYSIS_RETURN collBasic (
    		        MustParallelId pId,
    		        MustLocationId lId,
    		        int PE_start,
    		        int logPE_stride,
    		        int PE_size,
    		        int collType,
    		        int numTasks,
    		        gti::I_ChannelId *cId,
    		        std::list<gti::I_ChannelId*> *outFinishedChannels);

    		/**
    		 * @see I_OpenShmemTextAlignedColls::collRoot.
    		 */
    		GTI_ANALYSIS_RETURN collRoot (
    		        MustParallelId pId,
    		        MustLocationId lId,
    		        int PE_start,
    		        int logPE_stride,
    		        int PE_size,
    		        int PE_root,
    		        int collType,
    		        int numTasks,
                    gti::I_ChannelId *cId,
                    std::list<gti::I_ChannelId*> *outFinishedChannels);

    		/**
    		 * @see I_OpenShmemTextAlignedColls::collEqualNum.
    		 */
    		GTI_ANALYSIS_RETURN collEqualNum (
    		        MustParallelId pId,
    		        MustLocationId lId,
    		        int PE_start,
    		        int logPE_stride,
    		        int PE_size,
    		        int nelems,
    		        int collType,
    		        int numTasks,
                    gti::I_ChannelId *cId,
                    std::list<gti::I_ChannelId*> *outFinishedChannels);

    		/**
    		 * @see I_OpenShmemTextAlignedColls::collEqualNum.
    		 */
    		GTI_ANALYSIS_RETURN collEqualNumSizeT (
    		        MustParallelId pId,
    		        MustLocationId lId,
    		        int PE_start,
    		        int logPE_stride,
    		        int PE_size,
    		        size_t nelems,
    		        int collType,
    		        int numTasks,
                    gti::I_ChannelId *cId,
                    std::list<gti::I_ChannelId*> *outFinishedChannels);

    		/**
    		 * @see gti::I_Reduction
    		 */
    		virtual void timeout (void);

        protected:
    		I_ParallelIdAnalysis* myPIdMod;
    	    I_CreateMessage* myLogger;
    	    I_LocationAnalysis* myLIdMod;

    	    Must_OpenShmem_Coll_BasicP myCollBasicFct;
    	    Must_OpenShmem_Coll_RootP myCollRootFct;
    	    Must_OpenShmem_Coll_EqualNumP myCollEqualNumFct;
    	    Must_OpenShemem_Coll_EqualNumSizeTP myCollEqualNumSizeTFct;

    	    int myReachableBegin, myReachableEnd;

    	    bool myHadSubset;
    	    bool myHadWeakAlignment;
    	    bool myHadWeakViolation;

    	    bool myIsActive; /**< Allows us to switch aggregation and checks off after reporting the first error.*/

    	    std::list<OpenShmemPEGroupInfo*> myPEGroups; /**< List of infos for all the differnt types of PE groups we have.*/

    	    /**
    	     * Handles a newly created operation.
    	     * @param pId of the new op.
    	     * @param cId channel identifier for the op.
    	     * @param outFinishedChannels return value things for gti::I_Reduction.
    	     * @param newOp the new op.
    	     * @return @see gti::I_Reduction
    	     */
    	    GTI_ANALYSIS_RETURN handleNewOp (
    	            MustParallelId pId,
    	            I_ChannelId* cId,
    	            std::list<gti::I_ChannelId*> *outFinishedChannels,
    	            OpenShmemCollInfo* newOp);

    	    /**
    	     * Tries to add the new op to a wave of this PE group.
    	     * If an incompatibility occurs, the function returns GTI_ANALYIS_FAILURE.
    	     * Memory of the op goes back to the caller then. If
    	     * it succeeds it returns waiting/success and manages
    	     * the return values. Memory for the op is then passed
    	     * to this function.
    	     * @param groupInfo PE group to add to.
    	     * @param cId channel identifier of the new op.
    	     * @param outFinishedChannels return value things for gti::I_Reduction.
             * @param newOp the new op.
             * @return @see gti::I_Reduction
    	     */
    	    GTI_ANALYSIS_RETURN addOpToGroup (
    	            OpenShmemPEGroupInfo *groupInfo,
    	            I_ChannelId* cId,
    	            std::list<gti::I_ChannelId*> *outFinishedChannels,
    	            OpenShmemCollInfo* newOp);

    	    /**
    	     * Add the given (new) op to the given wave.
    	     * If an incompatibility occurs, the function returns GTI_ANALYIS_FAILURE.
    	     * Memory of the op goes back to the caller then. If
    	     * it succeeds it returns waiting/success and manages
    	     * the return values. Memory for the op is then passed
    	     * to this function.
    	     * @param wave to add to.
    	     * @param cId channel identifier of the new op.
    	     * @param outFinishedChannels return value things for gti::I_Reduction.
    	     * @param newOp the new op.
    	     * @return @see gti::I_Reduction
    	     */
    	    GTI_ANALYSIS_RETURN addOpToWave (
    	            OpenShmemCollWave *wave,
    	            I_ChannelId* cId,
    	            std::list<gti::I_ChannelId*> *outFinishedChannels,
    	            OpenShmemCollInfo* newOp);

    	    /**
    	     * Reports a collectives that block each other such that they can't both complete.
    	     * @param opA first operation.
    	     * @param opB second operation.
    	     * @return true iff successful.
    	     */
    	    bool reportCollsWithOverlappingGroups (
    	            OpenShmemCollInfo *opA,
    	            OpenShmemCollInfo *opB);

    	    /**
    	     * Reports a collective type mismatch.
    	     * @param opA first operation.
    	     * @param opB second operation.
    	     * @return true iff successful.
    	     */
    	    bool reportCollTypeMismatch (
    	            OpenShmemCollInfo *opA,
    	            OpenShmemCollInfo *opB);

    	    /**
    	     * Reports a root PE mismatch.
    	     * @param opA first operation.
    	     * @param opB second operation.
    	     * @return true iff successful.
    	     */
    	    bool reportRootMismatch (
    	            OpenShmemCollInfo *opA,
    	            OpenShmemCollInfo *opB);

    	    /**
    	     * Reports a root PE mismatch.
    	     * @param opA first operation.
    	     * @param opB second operation.
    	     * @return true iff successful.
    	     */
    	    bool reportNelemsMismatch (
    	            OpenShmemCollInfo *opA,
    	            OpenShmemCollInfo *opB);

    	    /**
    	     * Reports a root PE mismatch.
    	     * @param opA first operation.
    	     * @param opB second operation.
    	     * @return true iff successful.
    	     */
    	    bool reportNreducesMismatch (
    	            OpenShmemCollInfo *opA,
    	            OpenShmemCollInfo *opB);

    	    /**
    	     * Reports that a collective only has a weak alignment.
    	     * @param opA first operation.
    	     * @param opB second operation.
    	     * @return true iff successful.
    	     */
    	    bool reportWeakAlignedColl (
    	            OpenShmemCollInfo *opA,
    	            OpenShmemCollInfo *opB);

    	    /**
    	     * Reports a completly unaligned collective.
    	     * @param opA first operation.
    	     * @param opB second operation.
    	     * @return true iff successful.
    	     */
    	    bool reportUnalignedColl (
    	            OpenShmemCollInfo *opA,
    	            OpenShmemCollInfo *opB);

    	    /**
    	     * Creates a reduced event record for the given operation as a
    	     * representative of a completed wave.
    	     * @param op for which we create a reduced record.
    	     * @param numTasks number of PEs that the representative op will represent.
    	     * @return true iff successful.
    	     */
    	    bool createReducedRecord(
    	            OpenShmemCollInfo *op,
    	            int numTasks);

    	    /**
    	     * Serves for debugging prints information to a named DOT file.
    	     */
    	    bool printAsDot (void);
    };
} /*namespace MUST*/

#endif /*OPENSHMEMTEXTALIGNEDCOLLSREDUCTION_H*/
