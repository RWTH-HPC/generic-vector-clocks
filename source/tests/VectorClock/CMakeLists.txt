# Part of the MUST Project, under BSD-3-Clause Licensg
# See https://hpc.rwth-aachen.de/must/LICENSE for license information.
# SPDX-License-Identifier: BSD-3-Clause

# @file CMakeLists.txt
#  CMake file for vector clock tests
#
# @author Felix Tomski
# @date 29.06.2021
#

# Modified version of configureTest in MTHelperMacros.cmake
FUNCTION (configureVectorClockTest 
        outLayoutSpecName  #Filepath of layout specification to generate
        l0Mods                      #List of modules on layer 0, format: "<Mod0Name>:<Mod0Group>;<Mod1Name>:<Mod1Group>;..."
        l1Mods                      #List of modules on layer 1
        numPlaces               #Number of processes used for process 0
        model # programming model
        )

        SET (outLayoutSpecName ${outLayoutSpecName})
        SET (l0Mods ${l0Mods})
        SET (l1Mods ${l1Mods})
        SET (numApps ${numApps})

        #Calculate important variables for the run script
        MATH (EXPR totalProcs  "${numPlaces} * 1")
        
        #Calculate variables for layout spec
        SET(levels "0" "1")
        FOREACH (level ${levels})
            SET (level${level}ModString "")
            FOREACH (module ${l${level}Mods})
                STRING (REGEX MATCH "^[^:]*" modName ${module})
                STRING (REGEX MATCH "[^:]*$" modGroup ${module})
            
                SET (level${level}ModString "${level${level}ModString} \n<analysis name=\"${modName}\" group=\"${modGroup}\"></analysis>")    
            ENDFOREACH (module)
        ENDFOREACH (level)
        
        #Configure the layout specification
        IF (model STREQUAL "MPI")
            CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/layout.template.xml ${outLayoutSpecName})
        ELSEIF(model STREQUAL "OpenSHMEM")
            CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/layout-shmem.template.xml ${outLayoutSpecName})
        ENDIF()
ENDFUNCTION (configureVectorClockTest)


FUNCTION (addVectorClockTest
        familyName
        srcName
        numPlaces
        l0Mods
        l1Mods
        regex
        model
        )

    GET_FILENAME_COMPONENT(testName "${familyName}/${srcName}" NAME_WE)
    

    IF (model STREQUAL "OpenSHMEM")
        ADD_EXECUTABLE (${testName} "${familyName}/${srcName}")
        TARGET_LINK_LIBRARIES(${testName} ${OSHMEM_LIBRARY}) # add "-loshmem" to link OpenSHMEM library (for OpenMPI)
        TARGET_LINK_LIBRARIES(${testName} ${PnSHMEM_C_LIBRARIES})
    ELSE()
        addTestExecutable (${testName} "${familyName}/${srcName}")
    ENDIF()
    
    configureVectorClockTest (
        ${CMAKE_CURRENT_BINARY_DIR}/${testName}Layout.xml
        "${l0Mods}"
        "${l1Mods}"
        ${numPlaces}
        ${model}
        )
    
    ADD_TEST(NAME ${testName} COMMAND
        bash ${MUSTRUN} 
            --must:timeout ${MUSTRUN_TIMEOUT}
            --must:np ${MPIEXEC_NUMPROC_FLAG} 
            --must:mpiexec mpiexec.hydra
            --must:layout ${CMAKE_CURRENT_BINARY_DIR}/${testName}Layout.xml 
            ${MPIEXEC_NUMPROC_FLAG} ${numPlaces} $<TARGET_FILE:${testName}> 
    )


    SET_TESTS_PROPERTIES (${testName} PROPERTIES PASS_REGULAR_EXPRESSION ${regex})
    
ENDFUNCTION (addVectorClockTest)

addVectorClockTest("PointToPoint" "VCP2PMixed.cpp" 3 "" "" "shutdown" "MPI")
addVectorClockTest("PointToPoint" "VCP2PBlockingSync.cpp" 2 "" "" "shutdown" "MPI")
addVectorClockTest("PointToPoint" "VCP2PBlockingAsync.cpp" 2 "" "" "shutdown" "MPI")
addVectorClockTest("PointToPoint" "VCP2PNonblockingAsync.cpp" 2 "" "" "shutdown" "MPI")

addVectorClockTest("Collective" "VCCollBlockingAllToOne.cpp" 12 "" "" "shutdown" "MPI")
addVectorClockTest("Collective" "VCCollNonblockingAllToOne.cpp" 4 "" "" "shutdown" "MPI")
addVectorClockTest("Collective" "VCCollBlockingOneToAll.cpp" 12 "" "" "shutdown" "MPI")
addVectorClockTest("Collective" "VCCollBlockingAllToAll.cpp" 12 "" "" "shutdown" "MPI")
addVectorClockTest("Collective" "VCCollNonblockingAllToAll.cpp" 4 "" "" "shutdown" "MPI")

addVectorClockTest("RMA" "VCRMALockUnlock.cpp" 2 "" "" "shutdown" "MPI")
addVectorClockTest("RMA" "VCRMAFence.cpp" 4 "" "" "shutdown" "MPI")
addVectorClockTest("RMA" "VCRMAGeneralActiveTarget.cpp" 3 "" "" "shutdown" "MPI")
addVectorClockTest("RMA" "VCRMAGeneralActiveTargetMultiple.cpp" 5 "" "" "shutdown" "MPI")

addVectorClockTest("Annotations" "VCAnnotateTick.cpp" 3 "" "" "shutdown" "MPI")
addVectorClockTest("Annotations" "VCAnnotateProcessSignalWait.cpp" 3 "" "" "shutdown" "MPI")
addVectorClockTest("Annotations" "VCAnnotateProcessSignalWaitTransitive.cpp" 3 "" "" "shutdown" "MPI")
addVectorClockTest("Annotations" "VCAnnotateResourceSignalWait.cpp" 3 "" "" "shutdown" "MPI")

IF (ENABLE_OPENSHMEM)
    addVectorClockTest("OpenSHMEM" "VCBarrier.cpp" 4 "" "" "shutdown" "OpenSHMEM")
    addVectorClockTest("OpenSHMEM" "VCBarrierAll.cpp" 4 "" "" "shutdown" "OpenSHMEM")
    addVectorClockTest("OpenSHMEM" "VCBroadcast.cpp" 4 "" "" "shutdown" "OpenSHMEM")
    addVectorClockTest("OpenSHMEM" "VCAllocFree.cpp" 3 "" "" "shutdown" "OpenSHMEM")
    addVectorClockTest("OpenSHMEM" "VCLock.cpp" 3 "" "" "shutdown" "OpenSHMEM")
    addVectorClockTest("OpenSHMEM" "VCAnnotateLock.cpp" 3 "" "" "shutdown" "OpenSHMEM")
    addVectorClockTest("OpenSHMEM" "VCWaitUntil.cpp" 4 "" "" "shutdown" "OpenSHMEM")
ENDIF()