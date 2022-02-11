#! @BASH@
#@@
#
# MUST (Marmot Umpire Scalable Tool)
# Copyright (C) ZIH, Technische Universitaet Dresden, Federal Republic of Germany, 2011-2013
# Copyright (C) Lawrence Livermore National Laboratories, United States of America, 2011-2013
#
# See the file LICENSE.txt in the package base directory for details
#
# pnmpize - tool to ld-preload applications with the pnmpi library
#

language=$1
shift

if [ "x$language" == "xfortran" ]
then
    lib_name="@PNMPI_Fortran_LIB_NAME@"
    libraries="@PnMPI_Fortran_LIBRARIES@"
else
    lib_name="libpnshmem.so.1.4.0"
    libraries="@PnMPI_LIBRARY_DIR@/libpnshmem.so.1.4.0"
fi

#Linux
export LD_PRELOAD=$libraries:$LD_PRELOAD

#Mac ``` Unclear magic happens here ```
export DYLD_FORCE_FLAT_NAMESPACE=yes
export DYLD_INSERT_LIBRARIES=$libraries

$@
