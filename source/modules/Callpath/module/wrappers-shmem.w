/// -*- c++ -*-
/// Wrappers for the PnMPI callpath module.  These take a stacktrace 
/// at each PnMPI call so that it can be exposed for other modules.
#include <mpi.h>
#include <pshmem.h>
#include "Callpath.h"
#include "CallpathRuntime.h"
#include "callpath_internal.h"
using namespace std;


/// Runtime used to take stack traces.
extern CallpathRuntime *runtime;

{{forallfn fn_name start_pes}}
_EXTERN_C_ {{ret_type}} {{sub {{fn_name}} '^sh' NQsh}}({{formals}});
{{endforallfn}}

/**
 * @todo The shmem excludes below require correction in osh_wrap.py, the 
 *       complex gets messed up in the return value part.
 */
{{fnall fn_name start_pes MPI_Init MPI_Init_thread MPI_Finalize MPI_Pcontrol MPI_Comm_Rank MPI_Comm_size MPI_Initialized shmem_complexd_sum_to_all shmem_complexf_prod_to_all shmem_complexd_prod_to_all shmem_complexf_sum_to_all}} {
  {{ret_var_decl}}

  PNMPIMOD_Callpath_callpath = runtime->doStackwalk();
  {{ret_var_assign}}NQ{{fn_name}}({{args}});
  {{return}}
} {{endfnall}}
