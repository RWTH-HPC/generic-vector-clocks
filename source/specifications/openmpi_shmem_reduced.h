/*
 * Initialization routines
 */
void shmem_init (void);
int shmem_init_thread (int requested, int* provided);
void shmem_finalize (void);
void shmem_global_exit (int status);

/*
 * Query routines
 */
int shmem_n_pes (void);
int shmem_my_pe (void);
void shmem_query_thread (int* provided);

/*
 * Info routines
 */
void shmem_info_get_version (int* major, int* minor);
void shmem_info_get_name (char* name);

/*
 * Accessability routines
 */
int shmem_pe_accessible (int pe);
int shmem_addr_accessible (const void* addr, int pe);

/*
 * Symmetric heap routines
 */
void* shmem_malloc (size_t size);
void* shmem_calloc (size_t count, size_t size);
void* shmem_align (size_t align, size_t size);
void* shmem_realloc (void* ptr, size_t size);
void shmem_free (void* ptr);

/*
 * Remote pointer operations
 */
void* shmem_ptr (const void* ptr, int pe);

/*
 * Communication context operations
 */

typedef struct { int dummy; } * shmem_ctx_t;

#define SHMEM_CTX_DEFAULT oshmem_ctx_default

extern shmem_ctx_t oshmem_ctx_default;

int shmem_ctx_create (long options, shmem_ctx_t* ctx);
void shmem_ctx_destroy (shmem_ctx_t ctx);


/*
 * Lock functions
 */
void shmem_set_lock ( long* lock);
void shmem_clear_lock ( long* lock);
int shmem_test_lock ( long* lock);

/*
 * P2P sync routines
 */
void shmem_short_wait ( short* addr, short value);
void shmem_int_wait ( int* addr, int value);
void shmem_long_wait ( long* addr, long value);
void shmem_longlong_wait ( long long* addr, long long value);
void shmem_wait ( long* addr, long value);

void shmem_short_wait_until ( short* addr, int cmp, short value);
void shmem_int_wait_until ( int* addr, int cmp, int value);
void shmem_long_wait_until ( long* addr, int cmp, long value);
void shmem_longlong_wait_until ( long long* addr, int cmp, long long value);
void shmem_ushort_wait_until ( unsigned short* addr, int cmp, unsigned short value);
void shmem_uint_wait_until ( unsigned int* addr, int cmp, unsigned int value);
void shmem_ulong_wait_until ( unsigned long* addr, int cmp, unsigned long value);
void shmem_ulonglong_wait_until ( unsigned long long* addr, int cmp, unsigned long long value);
void shmem_int32_wait_until ( int32_t* addr, int cmp, int32_t value);
void shmem_int64_wait_until ( int64_t* addr, int cmp, int64_t value);
void shmem_uint32_wait_until ( uint32_t* addr, int cmp, uint32_t value);
void shmem_uint64_wait_until ( uint64_t* addr, int cmp, uint64_t value);
void shmem_size_wait_until ( size_t* addr, int cmp, size_t value);
void shmem_ptrdiff_wait_until ( ptrdiff_t* addr, int cmp, ptrdiff_t value);

int shmem_short_test ( short* addr, int cmp, short value);
int shmem_int_test ( int* addr, int cmp, int value);
int shmem_long_test ( long* addr, int cmp, long value);
int shmem_longlong_test ( long long* addr, int cmp, long long value);
int shmem_ushort_test ( unsigned short* addr, int cmp, unsigned short value);
int shmem_uint_test ( unsigned int* addr, int cmp, unsigned int value);
int shmem_ulong_test ( unsigned long* addr, int cmp, unsigned long value);
int shmem_ulonglong_test ( unsigned long long* addr, int cmp, unsigned long long value);
int shmem_int32_test ( int32_t* addr, int cmp, int32_t value);
int shmem_int64_test ( int64_t* addr, int cmp, int64_t value);
int shmem_uint32_test ( uint32_t* addr, int cmp, uint32_t value);
int shmem_uint64_test ( uint64_t* addr, int cmp, uint64_t value);
int shmem_size_test ( size_t* addr, int cmp, size_t value);
int shmem_ptrdiff_test ( ptrdiff_t* addr, int cmp, ptrdiff_t value);
/*
 * Barrier sync routines
 */
void shmem_barrier (int PE_start, int logPE_stride, int PE_size, long* pSync);
void shmem_barrier_all (void);
void shmem_sync (int PE_start, int logPE_stride, int PE_size, long* pSync);
void shmem_sync_all (void);
void shmem_fence (void);
void shmem_ctx_fence (shmem_ctx_t ctx);
void shmem_quiet (void);
void shmem_ctx_quiet (shmem_ctx_t ctx);

/*
 * Collective routines
 */
void shmem_broadcast32 (void* target, const void* source, size_t nlong, int PE_root, int PE_start, int logPE_stride, int PE_size, long* pSync);
void shmem_broadcast64 (void* target, const void* source, size_t nlong, int PE_root, int PE_start, int logPE_stride, int PE_size, long* pSync);
void shmem_broadcast (void* target, const void* source, size_t nlong, int PE_root, int PE_start, int logPE_stride, int PE_size, long* pSync);
void shmem_collect32 (void* target, const void* source, size_t nlong, int PE_start, int logPE_stride, int PE_size, long* pSync);
void shmem_collect64 (void* target, const void* source, size_t nlong, int PE_start, int logPE_stride, int PE_size, long* pSync);
void shmem_fcollect32 (void* target, const void* source, size_t nlong, int PE_start, int logPE_stride, int PE_size, long* pSync);
void shmem_fcollect64 (void* target, const void* source, size_t nlong, int PE_start, int logPE_stride, int PE_size, long* pSync);
void shmem_alltoall32 (void* target, const void* source, size_t nelems, int PE_start, int logPE_stride, int PE_size, long* pSync);
void shmem_alltoall64 (void* target, const void* source, size_t nelems, int PE_start, int logPE_stride, int PE_size, long* pSync);
void shmem_alltoalls32 (void* target, const void* source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems, int PE_start, int logPE_stride, int PE_size, long* pSync);
void shmem_alltoalls64 (void* target, const void* source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems, int PE_start, int logPE_stride, int PE_size, long* pSync);


/*
 * Reduction routines
 */
void shmem_short_and_to_all (short* target, const short* source, int nreduce, int PE_start, int logPE_stride, int PE_size, short* pWrk, long* pSync);
void shmem_int_and_to_all (int* target, const int* source, int nreduce, int PE_start, int logPE_stride, int PE_size, int* pWrk, long* pSync);
void shmem_long_and_to_all (long* target, const long* source, int nreduce, int PE_start, int logPE_stride, int PE_size, long* pWrk, long* pSync);
void shmem_longlong_and_to_all (long long* target, const long long* source, int nreduce, int PE_start, int logPE_stride, int PE_size, long long* pWrk, long* pSync);

void shmem_short_or_to_all (short* target, const short* source, int nreduce, int PE_start, int logPE_stride, int PE_size, short* pWrk, long* pSync);
void shmem_int_or_to_all (int* target, const int* source, int nreduce, int PE_start, int logPE_stride, int PE_size, int* pWrk, long* pSync);
void shmem_long_or_to_all (long* target, const long* source, int nreduce, int PE_start, int logPE_stride, int PE_size, long* pWrk, long* pSync);
void shmem_longlong_or_to_all (long long* target, const long long* source, int nreduce, int PE_start, int logPE_stride, int PE_size, long long* pWrk, long* pSync);

void shmem_short_xor_to_all (short* target, const short* source, int nreduce, int PE_start, int logPE_stride, int PE_size, short* pWrk, long* pSync);
void shmem_int_xor_to_all (int* target, const int* source, int nreduce, int PE_start, int logPE_stride, int PE_size, int* pWrk, long* pSync);
void shmem_long_xor_to_all (long* target, const long* source, int nreduce, int PE_start, int logPE_stride, int PE_size, long* pWrk, long* pSync);
void shmem_longlong_xor_to_all (long long* target, const long long* source, int nreduce, int PE_start, int logPE_stride, int PE_size, long long* pWrk, long* pSync);

void shmem_short_max_to_all (short* target, const short* source, int nreduce, int PE_start, int logPE_stride, int PE_size, short* pWrk, long* pSync);
void shmem_int_max_to_all (int* target, const int* source, int nreduce, int PE_start, int logPE_stride, int PE_size, int* pWrk, long* pSync);
void shmem_long_max_to_all (long* target, const long* source, int nreduce, int PE_start, int logPE_stride, int PE_size, long* pWrk, long* pSync);
void shmem_longlong_max_to_all (long long* target, const long long* source, int nreduce, int PE_start, int logPE_stride, int PE_size, long long* pWrk, long* pSync);
void shmem_float_max_to_all (float* target, const float* source, int nreduce, int PE_start, int logPE_stride, int PE_size, float* pWrk, long* pSync);
void shmem_double_max_to_all (double* target, const double* source, int nreduce, int PE_start, int logPE_stride, int PE_size, double* pWrk, long* pSync);
void shmem_longdouble_max_to_all (long double* target, const long double* source, int nreduce, int PE_start, int logPE_stride, int PE_size, long double* pWrk, long* pSync);

void shmem_short_min_to_all (short* target, const short* source, int nreduce, int PE_start, int logPE_stride, int PE_size, short* pWrk, long* pSync);
void shmem_int_min_to_all (int* target, const int* source, int nreduce, int PE_start, int logPE_stride, int PE_size, int* pWrk, long* pSync);
void shmem_long_min_to_all (long* target, const long* source, int nreduce, int PE_start, int logPE_stride, int PE_size, long* pWrk, long* pSync);
void shmem_longlong_min_to_all (long long* target, const long long* source, int nreduce, int PE_start, int logPE_stride, int PE_size, long long* pWrk, long* pSync);
void shmem_float_min_to_all (float* target, const float* source, int nreduce, int PE_start, int logPE_stride, int PE_size, float* pWrk, long* pSync);
void shmem_double_min_to_all (double* target, const double* source, int nreduce, int PE_start, int logPE_stride, int PE_size, double* pWrk, long* pSync);
void shmem_longdouble_min_to_all (long double* target, const long double* source, int nreduce, int PE_start, int logPE_stride, int PE_size, long double* pWrk, long* pSync);

void shmem_short_sum_to_all (short* target, const short* source, int nreduce, int PE_start, int logPE_stride, int PE_size, short* pWrk, long* pSync);
void shmem_int_sum_to_all (int* target, const int* source, int nreduce, int PE_start, int logPE_stride, int PE_size, int* pWrk, long* pSync);
void shmem_long_sum_to_all (long* target, const long* source, int nreduce, int PE_start, int logPE_stride, int PE_size, long* pWrk, long* pSync);
void shmem_longlong_sum_to_all (long long* target, const long long* source, int nreduce, int PE_start, int logPE_stride, int PE_size, long long* pWrk, long* pSync);
void shmem_float_sum_to_all (float* target, const float* source, int nreduce, int PE_start, int logPE_stride, int PE_size, float* pWrk, long* pSync);
void shmem_double_sum_to_all (double* target, const double* source, int nreduce, int PE_start, int logPE_stride, int PE_size, double* pWrk, long* pSync);
void shmem_longdouble_sum_to_all (long double* target, const long double* source, int nreduce, int PE_start, int logPE_stride, int PE_size, long double* pWrk, long* pSync);

void shmem_short_prod_to_all (short* target, const short* source, int nreduce, int PE_start, int logPE_stride, int PE_size, short* pWrk, long* pSync);
void shmem_int_prod_to_all (int* target, const int* source, int nreduce, int PE_start, int logPE_stride, int PE_size, int* pWrk, long* pSync);
void shmem_long_prod_to_all (long* target, const long* source, int nreduce, int PE_start, int logPE_stride, int PE_size, long* pWrk, long* pSync);
void shmem_longlong_prod_to_all (long long* target, const long long* source, int nreduce, int PE_start, int logPE_stride, int PE_size, long long* pWrk, long* pSync);
void shmem_float_prod_to_all (float* target, const float* source, int nreduce, int PE_start, int logPE_stride, int PE_size, float* pWrk, long* pSync);
void shmem_double_prod_to_all (double* target, const double* source, int nreduce, int PE_start, int logPE_stride, int PE_size, double* pWrk, long* pSync);
void shmem_longdouble_prod_to_all (long double* target, const long double* source, int nreduce, int PE_start, int logPE_stride, int PE_size, long double* pWrk, long* pSync);

/*
 * Platform specific cache management routines
 */
void shmem_udcflush (void);
void shmem_udcflush_line (void* target);
void shmem_set_cache_inv (void);
void shmem_set_cache_line_inv (void* target);
void shmem_clear_cache_inv (void);
void shmem_clear_cache_line_inv (void* target);
