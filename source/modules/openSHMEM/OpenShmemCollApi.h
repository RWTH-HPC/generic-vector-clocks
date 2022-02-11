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
 * @file OpenShmemCollApi.h
 *      P call definition for MUST internal OpenShmem events.
 *
 * @author Tobias Hilbrich
 * @date 15.06.2015
 */

#include "MustEnums.h"
#include "MustTypes.h"

#ifndef OPENSHMEMCOLLAPI_H
#define OPENSHMEMCOLLAPI_H

/**
 * Enumeration to differentiate collective types in OpenSHMEM.
 * @note this might also migrate to a header that has a proper name, but its good here for the time being.
 */
enum OpenShmemCollectiveType
{
    OPEN_SHMEM_COLL_BARRIER = 0,
    OPEN_SHMEM_COLL_BARRIER_ALL,

    OPEN_SHMEM_COLL_BROADCAST4,
    OPEN_SHMEM_COLL_BROADCAST8,
    OPEN_SHMEM_COLL_BROADCAST32,
    OPEN_SHMEM_COLL_BROADCAST64,

    OPEN_SHMEM_COLL_COLLECT4,
    OPEN_SHMEM_COLL_COLLECT8,
    OPEN_SHMEM_COLL_COLLECT32,
    OPEN_SHMEM_COLL_COLLECT64,

    OPEN_SHMEM_COLL_FCOLLECT4,
    OPEN_SHMEM_COLL_FCOLLECT8,
    OPEN_SHMEM_COLL_FCOLLECT32,
    OPEN_SHMEM_COLL_FCOLLECT64,

    OPEN_SHMEM_COLL_INT_AND_TO_ALL,
    OPEN_SHMEM_COLL_INT4_AND_TO_ALL,
    OPEN_SHMEM_COLL_INT8_AND_TO_ALL,
    OPEN_SHMEM_COLL_LONG_AND_TO_ALL,
    OPEN_SHMEM_COLL_LONGLONG_AND_TO_ALL,
    OPEN_SHMEM_COLL_SHORT_AND_TO_ALL,

    OPEN_SHMEM_COLL_INT_OR_TO_ALL,
    OPEN_SHMEM_COLL_INT4_OR_TO_ALL,
    OPEN_SHMEM_COLL_INT8_OR_TO_ALL,
    OPEN_SHMEM_COLL_LONG_OR_TO_ALL,
    OPEN_SHMEM_COLL_LONGLONG_OR_TO_ALL,
    OPEN_SHMEM_COLL_SHORT_OR_TO_ALL,

    OPEN_SHMEM_COLL_INT_XOR_TO_ALL,
    OPEN_SHMEM_COLL_INT4_XOR_TO_ALL,
    OPEN_SHMEM_COLL_INT8_XOR_TO_ALL,
    OPEN_SHMEM_COLL_LONG_XOR_TO_ALL,
    OPEN_SHMEM_COLL_LONGLONG_XOR_TO_ALL,
    OPEN_SHMEM_COLL_SHORT_XOR_TO_ALL,

    OPEN_SHMEM_COLL_DOUBLE_MAX_TO_ALL,
    OPEN_SHMEM_COLL_FLOAT_MAX_TO_ALL,
    OPEN_SHMEM_COLL_INT_MAX_TO_ALL,
    OPEN_SHMEM_COLL_INT4_MAX_TO_ALL,
    OPEN_SHMEM_COLL_INT8_MAX_TO_ALL,
    OPEN_SHMEM_COLL_LONG_MAX_TO_ALL,
    OPEN_SHMEM_COLL_LONGDOUBLE_MAX_TO_ALL,
    OPEN_SHMEM_COLL_LONGLONG_MAX_TO_ALL,
    OPEN_SHMEM_COLL_SHORT_MAX_TO_ALL,
    OPEN_SHMEM_COLL_REAL4_MAX_TO_ALL,
    OPEN_SHMEM_COLL_REAL8_MAX_TO_ALL,
    OPEN_SHMEM_COLL_REAL16_MAX_TO_ALL,

    OPEN_SHMEM_COLL_DOUBLE_MIN_TO_ALL,
    OPEN_SHMEM_COLL_FLOAT_MIN_TO_ALL,
    OPEN_SHMEM_COLL_INT_MIN_TO_ALL,
    OPEN_SHMEM_COLL_INT4_MIN_TO_ALL,
    OPEN_SHMEM_COLL_INT8_MIN_TO_ALL,
    OPEN_SHMEM_COLL_LONG_MIN_TO_ALL,
    OPEN_SHMEM_COLL_LONGDOUBLE_MIN_TO_ALL,
    OPEN_SHMEM_COLL_LONGLONG_MIN_TO_ALL,
    OPEN_SHMEM_COLL_SHORT_MIN_TO_ALL,
    OPEN_SHMEM_COLL_REAL4_MIN_TO_ALL,
    OPEN_SHMEM_COLL_REAL8_MIN_TO_ALL,
    OPEN_SHMEM_COLL_REAL16_MIN_TO_ALL,

    OPEN_SHMEM_COLL_DOUBLE_SUM_TO_ALL,
    OPEN_SHMEM_COLL_FLOAT_SUM_TO_ALL,
    OPEN_SHMEM_COLL_INT_SUM_TO_ALL,
    OPEN_SHMEM_COLL_INT4_SUM_TO_ALL,
    OPEN_SHMEM_COLL_INT8_SUM_TO_ALL,
    OPEN_SHMEM_COLL_LONG_SUM_TO_ALL,
    OPEN_SHMEM_COLL_LONGDOUBLE_SUM_TO_ALL,
    OPEN_SHMEM_COLL_LONGLONG_SUM_TO_ALL,
    OPEN_SHMEM_COLL_SHORT_SUM_TO_ALL,
    OPEN_SHMEM_COLL_REAL4_SUM_TO_ALL,
    OPEN_SHMEM_COLL_REAL8_SUM_TO_ALL,
    OPEN_SHMEM_COLL_REAL16_SUM_TO_ALL,
    OPEN_SHMEM_COLL_COMPLEXD_SUM_TO_ALL,
    OPEN_SHMEM_COLL_COMPLEXF_SUM_TO_ALL,
    OPEN_SHMEM_COLL_COMP4_SUM_TO_ALL,
    OPEN_SHMEM_COLL_COMP8_SUM_TO_ALL,

    OPEN_SHMEM_COLL_DOUBLE_PROD_TO_ALL,
    OPEN_SHMEM_COLL_FLOAT_PROD_TO_ALL,
    OPEN_SHMEM_COLL_INT_PROD_TO_ALL,
    OPEN_SHMEM_COLL_INT4_PROD_TO_ALL,
    OPEN_SHMEM_COLL_INT8_PROD_TO_ALL,
    OPEN_SHMEM_COLL_LONG_PROD_TO_ALL,
    OPEN_SHMEM_COLL_LONGDOUBLE_PROD_TO_ALL,
    OPEN_SHMEM_COLL_LONGLONG_PROD_TO_ALL,
    OPEN_SHMEM_COLL_SHORT_PROD_TO_ALL,
    OPEN_SHMEM_COLL_REAL4_PROD_TO_ALL,
    OPEN_SHMEM_COLL_REAL8_PROD_TO_ALL,
    OPEN_SHMEM_COLL_REAL16_PROD_TO_ALL,
    OPEN_SHMEM_COLL_COMPLEXD_PROD_TO_ALL,
    OPEN_SHMEM_COLL_COMPLEXF_PROD_TO_ALL,
    OPEN_SHMEM_COLL_COMP4_PROD_TO_ALL,
    OPEN_SHMEM_COLL_COMP8_PROD_TO_ALL
};

//==Function used for generate basic collectives.
inline int PMust_OpenShmem_Coll_Basic (
        MustParallelId pId,
        MustLocationId lId,
        int PE_start,
        int logPE_stride,
        int PE_size,
        int collType,
        int numTasks)  {return 0;}

typedef int (*Must_OpenShmem_Coll_BasicP) (
        MustParallelId pId,
        MustLocationId lId,
        int PE_start,
        int logPE_stride,
        int PE_size,
        int collType,
        int numTasks);

//==Function used for generate rooted collectives.
inline int PMust_OpenShmem_Coll_Root (
        MustParallelId pId,
        MustLocationId lId,
        int PE_start,
        int logPE_stride,
        int PE_size,
        int PE_root,
        int collType,
        int numTasks)  {return 0;}

typedef int (*Must_OpenShmem_Coll_RootP) (
        MustParallelId pId,
        MustLocationId lId,
        int PE_start,
        int logPE_stride,
        int PE_size,
        int PE_root,
        int collType,
        int numTasks);

//==Function used to generate collectives that include a number that must be equal across all PEs.
inline int PMust_OpenShmem_Coll_EqualNum (
        MustParallelId pId,
        MustLocationId lId,
        int PE_start,
        int logPE_stride,
        int PE_size,
        int nelems,
        int collType,
        int numTasks)  {return 0;}

typedef int (*Must_OpenShmem_Coll_EqualNumP) (
        MustParallelId pId,
        MustLocationId lId,
        int PE_start,
        int logPE_stride,
        int PE_size,
        int nelems,
        int collType,
        int numTasks);

//==Function used to generate collectives that include a number that must be equal across all PEs (as a size_t).
inline int PMust_OpenShmem_Coll_EqualNumSizeT (
        MustParallelId pId,
        MustLocationId lId,
        int PE_start,
        int logPE_stride,
        int PE_size,
        size_t nelems,
        int collType,
        int numTasks)  {return 0;}

typedef int (*Must_OpenShemem_Coll_EqualNumSizeTP) (
        MustParallelId pId,
        MustLocationId lId,
        int PE_start,
        int logPE_stride,
        int PE_size,
        size_t nelems,
        int collType,
        int numTasks);


#endif /* OPENSHMEMCOLLAPI_H */
