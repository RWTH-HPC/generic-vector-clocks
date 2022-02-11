/* This file is part of MUST (Marmot Umpire Scalable Tool)
 *
 * Copyright (C)
 *  2011-2014 ZIH, Technische Universitaet Dresden, Federal Republic of Germany
 *  2011-2014 Lawrence Livermore National Laboratories, United States of America
 *  2013-2014 RWTH Aachen University, Federal Republic of Germany
 *
 * See the file LICENSE.txt in the package base directory for details
 */

/**
 * @file openSHMEMMemoryAccessChecks.h
 *       @see openSHMEMMemoryAccessChecks.
 *
 *  @date 22.10.2014
 *  @author Tobias Hilbrich, Joachim Protze
 */

#include "ModuleBase.h"
#include "I_ParallelIdAnalysis.h"
#include "I_ArgumentAnalysis.h"
#include "I_CreateMessage.h"

#include "I_openSHMEMMemoryAccessChecks.h"

#include <string>
#include <map>

#ifndef OPENSHMEMMEMORYACCESSCHECKS_H
#define OPENSHMEMMEMORYACCESSCHECKS_H

using namespace gti;

namespace must
{
    /**
     * Implementation of I_openSHMEMMemoryAccessChecks.
     * @see I_openSHMEMMemoryAccessChecks
     */
    class openSHMEMMemoryAccessChecks : public gti::ModuleBase<openSHMEMMemoryAccessChecks, I_openSHMEMMemoryAccessChecks>
    {
    public:
        /**
         * Constructor.
         * @param instanceName name of this module instance.
         */
        openSHMEMMemoryAccessChecks (const char* instanceName);

            /**
             * Destructor.
             */
            virtual ~openSHMEMMemoryAccessChecks (void);

            /**
             * @see I_openSHMEMMemoryAccessChecks::checkOpenSHMEMValidMemoryAccess.
             */
            GTI_ANALYSIS_RETURN checkOpenSHMEMValidMemoryAccess (MustParallelId pId, MustLocationId lId, int aId, void* devicePtr, size_t size);
            

            /**
             * @see I_openSHMEMMemoryAccessChecks::openSHMEMalloc.
             */
            GTI_ANALYSIS_RETURN openSHMEMalloc (MustParallelId pId, MustLocationId lId, void* devicePtr, size_t size);
            
             /**
             * @see I_openSHMEMMemoryAccessChecks::openSHMEMfree.
             */
            GTI_ANALYSIS_RETURN openSHMEMfree (MustParallelId pId, MustLocationId lId, void* devicePtr);

    protected:
            I_ParallelIdAnalysis* myPIdMod;
            I_CreateMessage* myLogger;
            I_ArgumentAnalysis* myArgMod;

            std::map<MustAddressType, MustAddressType> allocatedBlocks;
    };
} /*namespace MUST*/

#endif /*OPENSHMEMMEMORYACCESSCHECKS_H*/
