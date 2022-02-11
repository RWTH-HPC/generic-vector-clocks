# This file is part of MUST (Marmot Umpire Scalable Tool)
#
# Copyright (C)
#   2011-2015 ZIH, Technische Universitaet Dresden, Federal Republic of Germany
#   2011-2015 Lawrence Livermore National Laboratories, United States of America
#   2013-2015 RWTH Aachen University, Federal Republic of Germany
#
# See the file LICENSE.txt in the package base directory for details

# @file CMakeLists.cmake
#       CMake file for modules/TextuallyAlignedColls.
#
# @author Tobias Hilbrich
# @date 12.06.2015
#

#Install headers
INSTALL(FILES 
            I_OpenShmemTextAlignedColls.h
            OpenShmemCollApi.h 
        DESTINATION include)

#Build and install modules 
GTI_MAC_ADD_MODULE (openShmemTextAlignedColls "OpenShmemTextAlignedColls.cpp;${BASE_SOURCES}" "CXX")
GTI_MAC_ADD_MODULE (openShmemTextAlignedCollsReduction "OpenShmemTextAlignedCollsReduction.cpp;${GTI_SRC_DIR}/CompletionTree.cpp;${BASE_SOURCES}" "CXX")
