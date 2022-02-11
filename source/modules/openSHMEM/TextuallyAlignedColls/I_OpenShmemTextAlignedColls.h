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
 * @file I_OpenShmemTextAlignedColls.h
 *       @see OpenShmemTextAlignedColls.
 *
 *  @date 12.06.2015
 *  @author Tobias Hilbrich
 */

#include "I_Module.h"
#include "I_Reduction.h"
#include "GtiEnums.h"
#include "BaseIds.h"

#ifndef I_OPENSHMEMTEXTALIGNEDCOLLS_H
#define I_OPENSHMEMTEXTALIGNEDCOLLS_H

/**
 * Checks that apply to OpenSHMEM collectives to analyze them for mismatches
 * and textual alignment issues.
 *
 * Dependencies (order as listed):
 * = Root module:
 *   - NONE
 * = Reduction module:
 *   - ParallelIdAnalysis
 *   - LocationIdAnalysis
 *   - CreateMessage
 *
 * Interface for both the root and the reduction version of modules
 * that check OpenShmem collectives. For the regular module that operates
 * on the root, the I_Reduction inheritance is superfluous, but doesn't
 * really hurts, since it only requires us to implement a dummy timeout
 * function there. The actual interface function use default arguments
 * for the channel identifiers and finished channel lists as to support
 * the arguments of both modules.
 *
 */
class I_OpenShmemTextAlignedColls : public gti::I_Module, public gti::I_Reduction
{
public:

	/**
	 * Notifies the module of a collective that only
	 * uses the usual PE description without any further
	 * additional consistency requirements.
	 * This is:
	 *  - barrier
	 *  - barrier_all
	 *  - collect
	 *
	 * @param pId parallel Id of the call site.
	 * @param lId location Id of the call site.
	 * @param PE_start see OpenSHMEM spec.
	 * @param logPE_stride see OpenSHMEM spec.
	 * @param PE_size see OpenSHMEM spec.
	 * @param collType entry in OpenShmemCollectiveType (cast to int) to specify the type of collective.
	 * @param numTasks counter for event aggregation.
	 * @param cId @see gti::I_Reduction
	 * @param outFinishedChannels @see gti::I_Reduction
	 * @return see gti::GTI_ANALYSIS_RETURN.
	 */
    virtual gti::GTI_ANALYSIS_RETURN collBasic (
            MustParallelId pId,
            MustLocationId lId,
            int PE_start,
            int logPE_stride,
            int PE_size,
            int collType,
            int numTasks,
            gti::I_ChannelId *cId = NULL,
            std::list<gti::I_ChannelId*> *outFinishedChannels = NULL) = 0;

    /**
     * Notifies the module of collective that uses a root.
     * This is:
     *  - broadcast
     *
     * @param pId parallel Id of the call site.
     * @param lId location Id of the call site.
     * @param PE_start see OpenSHMEM spec.
     * @param logPE_stride see OpenSHMEM spec.
     * @param PE_size see OpenSHMEM spec.
     * @param PE_root see OpenSHMEM spec.
     * @param collType entry in OpenShmemCollectiveType (cast to int) to specify the type of collective.
     * @param numTasks counter for event aggregation.
     * @param cId @see gti::I_Reduction
     * @param outFinishedChannels @see gti::I_Reduction
     * @return see gti::GTI_ANALYSIS_RETURN.
     */
    virtual gti::GTI_ANALYSIS_RETURN collRoot (
            MustParallelId pId,
            MustLocationId lId,
            int PE_start,
            int logPE_stride,
            int PE_size,
            int PE_root,
            int collType,
            int numTasks,
            gti::I_ChannelId *cId = NULL,
            std::list<gti::I_ChannelId*> *outFinishedChannels = NULL) = 0;

    /**
     * Notifies the module of a collective that includes
     * an int that must be equal between all PEs.
     * This is:
     *  - all reductions
     *
     * @param pId parallel Id of the call site.
     * @param lId location Id of the call site.
     * @param PE_start see OpenSHMEM spec.
     * @param logPE_stride see OpenSHMEM spec.
     * @param PE_size see OpenSHMEM spec.
     * @param nelems  see OpenSHMEM spec (this must be equal between all PEs).
     * @param collType entry in OpenShmemCollectiveType (cast to int) to specify the type of collective.
     * @param numTasks counter for event aggregation.
     * @param cId @see gti::I_Reduction
     * @param outFinishedChannels @see gti::I_Reduction
     * @return see gti::GTI_ANALYSIS_RETURN.
     */
    virtual gti::GTI_ANALYSIS_RETURN collEqualNum (
            MustParallelId pId,
            MustLocationId lId,
            int PE_start,
            int logPE_stride,
            int PE_size,
            int nelems,
            int collType,
            int numTasks,
            gti::I_ChannelId *cId = NULL,
            std::list<gti::I_ChannelId*> *outFinishedChannels = NULL) = 0;

    /**
     * Notifies the module of a collective that includes
     * a size_t that must be equal between all PEs.
     * This is:
     *  - fcollect
     *
     * @param pId parallel Id of the call site.
     * @param lId location Id of the call site.
     * @param PE_start see OpenSHMEM spec.
     * @param logPE_stride see OpenSHMEM spec.
     * @param PE_size see OpenSHMEM spec.
     * @param nelems  see OpenSHMEM spec (this must be equal between all PEs).
     * @param collType entry in OpenShmemCollectiveType (cast to int) to specify the type of collective.
     * @param numTasks counter for event aggregation.
     * @param cId @see gti::I_Reduction
     * @param outFinishedChannels @see gti::I_Reduction
     * @return see gti::GTI_ANALYSIS_RETURN.
     */
    virtual gti::GTI_ANALYSIS_RETURN collEqualNumSizeT (
            MustParallelId pId,
            MustLocationId lId,
            int PE_start,
            int logPE_stride,
            int PE_size,
            size_t nelems,
            int collType,
            int numTasks,
            gti::I_ChannelId *cId = NULL,
            std::list<gti::I_ChannelId*> *outFinishedChannels = NULL) = 0;

};/*class I_OpenShmemTextAlignedColls*/

#endif /*I_OPENSHMEMTEXTALIGNEDCOLLS_H*/
