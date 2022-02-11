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
 * @file openSHMEMMemoryAccessChecks.cpp
 *       @see openSHMEMMemoryAccessChecks.
 *
 *  @date 22.10.2014
 *  @author Tobias Hilbrich, Joachim Protze
 */

#include "GtiMacros.h"
#include "MustEnums.h"

#include "openSHMEMMemoryAccessChecks.h"

#include <sstream>

using namespace must;

mGET_INSTANCE_FUNCTION(openSHMEMMemoryAccessChecks);
mFREE_INSTANCE_FUNCTION(openSHMEMMemoryAccessChecks);
mPNMPI_REGISTRATIONPOINT_FUNCTION(openSHMEMMemoryAccessChecks);

//=============================
// Constructor
//=============================
openSHMEMMemoryAccessChecks::openSHMEMMemoryAccessChecks (const char* instanceName)
    : gti::ModuleBase<openSHMEMMemoryAccessChecks, I_openSHMEMMemoryAccessChecks> (instanceName),
    allocatedBlocks()
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
    myLogger = (I_CreateMessage*) subModInstances[1];
    myArgMod = (I_ArgumentAnalysis*) subModInstances[2];

    //Initialize module data
    /*TODO*/
}

//=============================
// Destructor
//=============================
openSHMEMMemoryAccessChecks::~openSHMEMMemoryAccessChecks ()
{
    if (myPIdMod)
        destroySubModuleInstance ((I_Module*) myPIdMod);
    myPIdMod = NULL;

    if (myLogger)
        destroySubModuleInstance ((I_Module*) myLogger);
    myLogger = NULL;

    if (myArgMod)
        destroySubModuleInstance ((I_Module*) myArgMod);
    myArgMod = NULL;

    /*TODO Free other modules data*/
}

//=============================
// checkOpenSHMEMValidMemoryAccess
//=============================
GTI_ANALYSIS_RETURN openSHMEMMemoryAccessChecks::checkOpenSHMEMValidMemoryAccess (
        MustParallelId pId,
        MustLocationId lId,
        int aId,
        void* devicePtr,
        size_t size)
{
    std::cout << "accessing " << size << " Bytes at " << devicePtr << std::endl;
    
        bool valid = false;
        bool match = false;
        MustAddressType range;
        std::map<MustAddressType, MustAddressType>::iterator it;
        MustAddressType matDevicePtr = (MustAddressType)devicePtr;
        MustAddressType matSize = (MustAddressType)size;
        for ( it = allocatedBlocks.begin() ; it != allocatedBlocks.end(); it++ ) {
           // found a valid allocation
            if ( (it->first <= matDevicePtr) && ((it->first)+(it->second) >= matDevicePtr + matSize) ) {
                valid = true;
                break;
            }
           // found a allocation, that overlaps - but cannot hold the transfer - ERROR!
            if ( ((it->first)+(it->second) >= matDevicePtr) || (it->first <= matDevicePtr + matSize) ) {
                match = true;
                range = it->second;
                break;
            }
        }
        
        if ( valid == false )
        {
          if ( match == false )
          {
              std::stringstream stream;
              stream
                  <<  "The data transfer is invalid. It is outside any allocated memory.";

              myLogger->createMessage(
                      MUST_ERROR_ZERO_ALLOCATION,
                      pId,
                      lId,
                      MustErrorMessage,
                      stream.str()
              );
              return GTI_ANALYSIS_FAILURE;
          }else{
              std::stringstream stream;
              stream
                  <<  "The data transfer is invalid. It exceeds the allocated memory. Argument " << myArgMod->getIndex(aId)
                  << " (" << myArgMod->getArgName(aId) << ") specifies a size of " << size << " bytes, where the target region can hold up to "
                  << range << " bytes.";

              myLogger->createMessage(
                      MUST_ERROR_ZERO_ALLOCATION,
                      pId,
                      lId,
                      MustErrorMessage,
                      stream.str()
              );
              return GTI_ANALYSIS_FAILURE;
          }
        }

    return GTI_ANALYSIS_SUCCESS;
}

//=============================
// openSHMEMalloc
//=============================
GTI_ANALYSIS_RETURN openSHMEMMemoryAccessChecks::openSHMEMalloc (MustParallelId pId, MustLocationId lId, void* devicePtr, size_t size)
{
    allocatedBlocks.insert(std::make_pair<MustAddressType, MustAddressType>((MustAddressType)devicePtr,(MustAddressType)size));
    std::cout << "allocated " << allocatedBlocks[(MustAddressType)devicePtr] << " Bytes at " << devicePtr << std::endl;
    return GTI_ANALYSIS_SUCCESS;
}

//=============================
// openSHMEMfree
//=============================
GTI_ANALYSIS_RETURN openSHMEMMemoryAccessChecks::openSHMEMfree (MustParallelId pId, MustLocationId lId, void* devicePtr)
{
  if (allocatedBlocks.erase((MustAddressType)devicePtr) == 0)
  {
            std::stringstream stream;
            stream
                <<  "The pointer to be freed is invalid. The pointer that was not allocated or already freed.";

            myLogger->createMessage(
                    MUST_ERROR_ZERO_ALLOCATION,
                    pId,
                    lId,
                    MustErrorMessage,
                    stream.str()
            );
            return GTI_ANALYSIS_FAILURE;
  }
    
  return GTI_ANALYSIS_SUCCESS;
}

/*EOF*/
