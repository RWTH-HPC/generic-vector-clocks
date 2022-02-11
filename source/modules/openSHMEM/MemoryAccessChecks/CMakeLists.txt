# This file is part of MUST (Marmot Umpire Scalable Tool)
#
# Copyright (C)
#   2011-2014 ZIH, Technische Universitaet Dresden, Federal Republic of Germany
#   2011-2014 Lawrence Livermore National Laboratories, United States of America
#   2013-2014 RWTH Aachen University, Federal Republic of Germany
#
# See the file LICENSE.txt in the package base directory for details

# @file CMakeLists.cmake
#       CMake file for modules/openSHMEM/MemoryAccessChecks.
#
# @author Tobias Hilbrich
# @author Joachim Protze
# @date 22.10.2014
#

#Install headers
INSTALL(FILES I_openSHMEMMemoryAccessChecks.h DESTINATION include)

#Build and install modules 
GTI_MAC_ADD_MODULE (openSHMEMMemoryAccessChecks "openSHMEMMemoryAccessChecks.cpp;${BASE_SOURCES}" "CXX")
