# This file is part of MUST (Marmot Umpire Scalable Tool)
#
# Copyright (C)
#   2011-2015 ZIH, Technische Universitaet Dresden, Federal Republic of Germany
#   2011-2015 Lawrence Livermore National Laboratories, United States of America
#   2013-2015 RWTH Aachen University, Federal Republic of Germany
#
# See the file LICENSE.txt in the package base directory for details

# @file CMakeLists.cmake
#       CMake file for modules/openSHMEM.
#
# @author Tobias Hilbrich
# @author Joachim Protze
# @date 20.05.2015
#

INSTALL(FILES 
            OpenShmemCollApi.h
        DESTINATION include)

#Install headers
#ADD_SUBDIRECTORY (MemoryAccessChecks)
#ADD_SUBDIRECTORY (TextuallyAlignedColls)