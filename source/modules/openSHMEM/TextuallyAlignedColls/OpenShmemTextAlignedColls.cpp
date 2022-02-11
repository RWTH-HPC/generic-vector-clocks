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
 * @file OpenShmemTextAlignedColls.cpp
 *       @see must::OpenShmemTextAlignedColls.
 *
 *  @date 12.06.2015
 *  @author Tobias Hilbrich
 */

#include "GtiMacros.h"
#include "MustEnums.h"

#include "OpenShmemTextAlignedColls.h"

#include <sstream>
#include <assert.h>

using namespace must;

mGET_INSTANCE_FUNCTION(OpenShmemTextAlignedColls);
mFREE_INSTANCE_FUNCTION(OpenShmemTextAlignedColls);
mPNMPI_REGISTRATIONPOINT_FUNCTION(OpenShmemTextAlignedColls);

//=============================
// Constructor
//=============================
OpenShmemTextAlignedColls::OpenShmemTextAlignedColls (const char* instanceName)
    : gti::ModuleBase<OpenShmemTextAlignedColls, I_OpenShmemTextAlignedColls> (instanceName)
{
    //create sub modules
    std::vector<I_Module*> subModInstances;
    subModInstances = createSubModuleInstances ();

    //handle sub modules
#define NUM_SUBS 0
    if (subModInstances.size() > NUM_SUBS)
    {
        for (int i = NUM_SUBS; i < subModInstances.size(); i++)
            destroySubModuleInstance (subModInstances[i]);
    }

    //Initialize module data
    /*Nothing to do yet*/
}

//=============================
// Destructor
//=============================
OpenShmemTextAlignedColls::~OpenShmemTextAlignedColls ()
{
	/*Nothing else to free yet*/
}

//=============================
// collBasic
//=============================
GTI_ANALYSIS_RETURN OpenShmemTextAlignedColls::collBasic (
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
	return GTI_ANALYSIS_SUCCESS;
}

//=============================
// collRoot
//=============================
GTI_ANALYSIS_RETURN OpenShmemTextAlignedColls::collRoot (
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
    return GTI_ANALYSIS_SUCCESS;
}

//=============================
// collEqualNum
//=============================
GTI_ANALYSIS_RETURN OpenShmemTextAlignedColls::collEqualNum (
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
    return GTI_ANALYSIS_SUCCESS;
}

//=============================
// collEqualNumSizeT
//=============================
GTI_ANALYSIS_RETURN OpenShmemTextAlignedColls::collEqualNumSizeT (
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
    return GTI_ANALYSIS_SUCCESS;
}

//=============================
// timeout
//=============================
void OpenShmemTextAlignedColls::timeout ()
{
    //Nothing to do, this is just a dummy
}

/*EOF*/
