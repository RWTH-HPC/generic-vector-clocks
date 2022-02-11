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
 * @file I_openSHMEMMemoryAccessChecks.h
 *       @see I_openSHMEMMemoryAccessChecks.
 *
 *  @date 22.10.2014
 *  @author Tobias Hilbrich, Joachim Protze
 */

#include "I_Module.h"
#include "GtiEnums.h"
#include "BaseIds.h"

#ifndef I_OPENSHMEMMEMORYACCESSCHECKS_H
#define I_OPENSHMEMMEMORYACCESSCHECKS_H

/**
 * Checks for openSHMEM memory transfers and allocations.
 *
 * Dependencies (order as listed):
 * - ParallelIdAnalysis
 * - CreateMessage
 * - ArgumentAnalysis
 *
 */
class I_openSHMEMMemoryAccessChecks : public gti::I_Module
{
public:

    /**
     * Checks whether the size of data to copy does not exceed the allocation size of openSHMEMalloc.
     *
     * @param pId parallel Id of the call site.
     * @param lId location Id of the call site.
     * @param aId argument Id of the value to check.
     * @param devicePtr address for allocated region on the device.
     * @param size to check.
     * @return see gti::GTI_ANALYSIS_RETURN.
     */
    virtual gti::GTI_ANALYSIS_RETURN checkOpenSHMEMValidMemoryAccess (
            MustParallelId pId,
            MustLocationId lId,
            int aId,
            void* devicePtr,
            size_t size) = 0;
            
            
    /**
     * Notifies the module that a new allocation took place.
     *
     * @param pId parallel Id of the call site.
     * @param lId location Id of the call site.
     * @param devicePtr address for allocated region on the device.
     * @param size of allocated region.
     * @return see gti::GTI_ANALYSIS_RETURN.
     */
    virtual gti::GTI_ANALYSIS_RETURN openSHMEMalloc (
            MustParallelId pId,
            MustLocationId lId,
            void* devicePtr,
            size_t size) = 0;
            
            
     /**
     * Notifies the module that a deallocation took place.
     *
     * @param pId parallel Id of the call site.
     * @param lId location Id of the call site.
     * @param devicePtr address for allocated region on the device.
     * @param size of allocated region.
     * @return see gti::GTI_ANALYSIS_RETURN.
     */
    virtual gti::GTI_ANALYSIS_RETURN openSHMEMfree (
            MustParallelId pId,
            MustLocationId lId,
            void* devicePtr) = 0;
};/*class I_openSHMEMMemoryAccessChecks*/

#endif /*I_OPENSHMEMMEMORYACCESSCHECKS_H*/
