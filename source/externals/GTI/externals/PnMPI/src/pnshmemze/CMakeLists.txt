# This file is part of P^nMPI.
#
# Copyright (c)
#  2008-2019 Lawrence Livermore National Laboratories, United States of America
#  2011-2016 ZIH, Technische Universitaet Dresden, Federal Republic of Germany
#  2013-2019 RWTH Aachen University, Federal Republic of Germany
#
#
# P^nMPI is free software; you can redistribute it and/or modify it under the
# terms of the GNU Lesser General Public License as published by the Free
# Software Foundation version 2.1 dated February 1999.
#
# P^nMPI is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
# A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
# details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with P^nMPI; if not, write to the
#
#   Free Software Foundation, Inc.
#   51 Franklin St, Fifth Floor
#   Boston, MA 02110, USA
#
#
# Written by Martin Schulz, schulzm@llnl.gov.
#
# LLNL-CODE-402774

# PnMPIze should be build by default. However, some platforms (like BlueGene/Q)
# do not support switching the process with system calls like 'execvp', so the
# PnMPIze tool can't be used at these platforms and may be disabled.
option(ENABLE_PNSHMEMZE "Build the Pnshmemze invocation tool." on)
if (NOT ENABLE_PNSHMEMZE)
  return()
endif ()


include(GNUInstallDirs)

find_package(argp REQUIRED)
find_package(help2man)
find_package(C99)

if (C99_FOUND)
  add_definitions(${C99_FLAGS})
endif ()

# Set the PnMPI search paths for mac OS.
#
# DYLD_INSERT_LIBRARIES works with paths only, so PnMPIze will search for the
# PnMPI library to preload. By default these path's are the following ones, but
# the install path should be appended to these.
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(PNSHMEMZE_SEARCH_PATHS
    ${CMAKE_INSTALL_FULL_LIBDIR}
    "/usr/local/lib"
    "/lib"
    "/usr/lib")

  # If PnMPI is installed in a default install directory, this duplicated path
  # should be stripped from the list.
  list(REMOVE_DUPLICATES PNSHMEMZE_SEARCH_PATHS)

  # Convert the list to a search-path list.
  string(REPLACE ";" ":" PNSHMEMZE_SEARCH_PATHS "${PNSHMEMZE_SEARCH_PATHS}")
endif ()

configure_file(config.h.in config.h)


# Include all required directories.
include_directories(${CMAKE_CURRENT_BINARY_DIR})


# Build and install PnMPIze.
add_executable(pnshmemze pnshmemze.c)
add_coverage(pnshmemze)
add_sanitizers(pnshmemze)

target_link_libraries(pnshmemze ${ARGP_LIBRARIES})
set_target_properties(pnshmemze PROPERTIES OUTPUT_NAME pnshmemze)

install(TARGETS pnshmemze EXPORT pnshmemze DESTINATION ${CMAKE_INSTALL_BINDIR})
install(EXPORT pnshmemze DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake/PnMPI)

# If help2man could be found, generate a man page for pnshmemze. The help2man
# command will install this man page, too.
if (HELP2MAN_FOUND)
  help2man(pnshmemze-man TARGET pnshmemze NOINFO INSTALL RENAME pnshmemze.1)
endif()
