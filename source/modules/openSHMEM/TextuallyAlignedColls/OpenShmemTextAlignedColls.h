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
 * @file OpenShmemTextAlignedColls.h
 *       @see must::OpenShmemTextAlignedColls.
 *
 *  @date 12.06.2015
 *  @author Tobias Hilbrich
 */

#include "ModuleBase.h"
#include "I_ParallelIdAnalysis.h"
#include "I_LocationAnalysis.h"
#include "I_CreateMessage.h"

#include "I_OpenShmemTextAlignedColls.h"

#include <string>

#ifndef OPENSHMEMTEXTALIGNEDCOLLS_H
#define OPENSHMEMTEXTALIGNEDCOLLS_H

using namespace gti;

namespace must
{
    /**
     * Implementaion of I_OpenShmemTextAlignedColls.
     * This implementation serves as the module that executes on the TBON root.
     * It doesn't needs to implement anything at all in fact.
     */
    class OpenShmemTextAlignedColls : public gti::ModuleBase<OpenShmemTextAlignedColls, I_OpenShmemTextAlignedColls>
    {
    public:
            /**
             * Constructor.
             * @param instanceName name of this module instance.
             */
            OpenShmemTextAlignedColls (const char* instanceName);

    		/**
    		 * Destructor.
    		 */
    		virtual ~OpenShmemTextAlignedColls (void);

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
    		 *
    		 * This is not really necessary for this module, as it is not a reduction.
    		 * But the dummy we implement here avoids the need of an interface
    		 * differentiation between the regular and the reduction module.
    		 */
    		virtual void timeout (void);

    protected:

    };
} /*namespace MUST*/

#endif /*OPENSHMEMTEXTALIGNEDCOLLS_H*/
