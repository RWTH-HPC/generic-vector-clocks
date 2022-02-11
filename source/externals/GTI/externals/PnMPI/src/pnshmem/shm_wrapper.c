/* This file is part of P^nMPI.
 *
 * Copyright (c)
 *  2008-2019 Lawrence Livermore National Laboratories, United States of America
 *  2011-2016 ZIH, Technische Universitaet Dresden, Federal Republic of Germany
 *  2013-2019 RWTH Aachen University, Federal Republic of Germany
 *
 *
 * P^nMPI is free software; you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation version 2.1 dated February 1999.
 *
 * P^nMPI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with P^nMPI; if not, write to the
 *
 *   Free Software Foundation, Inc.
 *   51 Franklin St, Fifth Floor
 *   Boston, MA 02110, USA
 *
 *
 * Written by Martin Schulz, schulzm@llnl.gov.
 *
 * LLNL-CODE-402774
 */

#include <stdarg.h>

#include "core.h"
#include "pnmpi-config.h"
#include <shmem.h>
#include <pnmpi/debug_io.h>
#include <pnmpi/private/force_link.h>
#include <pnmpi/private/function_address.h>
#include <pnmpi/private/initialization.h>
#include <pnmpi/private/modules.h>
#include <pnmpi/private/mpi_interface.h>
#include <pnmpi/private/mpi_reentry.h>
#include <pnmpi/private/pmpi.h>
#include <pnmpi/private/pmpi_assert.h>
#include <pnmpi/private/return_address.h>
#include <pnmpi/private/tls.h>

/* Special wrappers not covered by the generator */
#ifdef EXPERIMENTAL_UNWIND
#define UNW_LOCAL_ONLY
#include <libunwind.h>
#endif


/* Map the old debug macros to the new debug functions and macros.
 *
 * WARNING:
 * - These macros are not portable to non-GCC compatible compilers, as
 *   ##__VA_ARGS__ is a GNU extension.
 * - These macros are for legacy support only. Use the functions and macros
 *   defined in debug_io.h for new code!
 */
#define WARNPRINT(format, ...) PNMPI_Warning(format "\n", ##__VA_ARGS__);
#define DBGPRINT3(format, ...) \
  PNMPI_Debug(PNMPI_DEBUG_CALL, format "\n", ##__VA_ARGS__);

/* Enable all debug levels, as checking the debug level to print is part of
 * pnmpi_debug now. */
#define DBGLEVEL


extern void *MPIR_ToPointer(int idx);


/*-------------------------------------------------------------------*/
/* shmem_init */
void shmem_init() {
    /**
     * We call MPI_Init (if not already initialized) here in a way
     * in which we wrap it by ourselves. This is crucial as we use
     * that call to initialize ourselves.
     */
    int initialized = 0;
    MPI_Initialized(&initialized);

    if (!initialized)
      MPI_Init(NULL, NULL);

    // call real init function
    //pshmem_init();
}


/*-------------------------------------------------------------------*/
/* The End. */

//#ifdef COMPILE_FOR_FORTRAN
//#include "wrapper_cf.c"
//#else
#include "shm_wrapper_c.c"
//#endif
