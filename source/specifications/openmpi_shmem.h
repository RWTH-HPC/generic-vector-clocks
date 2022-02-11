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
 * Elemental put routines
 */
void shmem_ctx_char_p (shmem_ctx_t ctx, char* addr, char value, int pe);
void shmem_ctx_short_p (shmem_ctx_t ctx, short* addr, short value, int pe);
void shmem_ctx_int_p (shmem_ctx_t ctx, int* addr, int value, int pe);
void shmem_ctx_long_p (shmem_ctx_t ctx, long* addr, long value, int pe);
void shmem_ctx_float_p (shmem_ctx_t ctx, float* addr, float value, int pe);
void shmem_ctx_double_p (shmem_ctx_t ctx, double* addr, double value, int pe);
void shmem_ctx_longlong_p (shmem_ctx_t ctx, long long* addr, long long value, int pe);
void shmem_ctx_schar_p (shmem_ctx_t ctx, signed char* addr, signed char value, int pe);
void shmem_ctx_uchar_p (shmem_ctx_t ctx, unsigned char* addr, unsigned char value, int pe);
void shmem_ctx_ushort_p (shmem_ctx_t ctx, unsigned short* addr, unsigned short value, int pe);
void shmem_ctx_uint_p (shmem_ctx_t ctx, unsigned int* addr, unsigned int value, int pe);
void shmem_ctx_ulong_p (shmem_ctx_t ctx, unsigned long* addr, unsigned long value, int pe);
void shmem_ctx_ulonglong_p (shmem_ctx_t ctx, unsigned long long* addr, unsigned long long value, int pe);
void shmem_ctx_longdouble_p (shmem_ctx_t ctx, long double* addr, long double value, int pe);
void shmem_ctx_int8_p (shmem_ctx_t ctx, int8_t* addr, int8_t value, int pe);
void shmem_ctx_int16_p (shmem_ctx_t ctx, int16_t* addr, int16_t value, int pe);
void shmem_ctx_int32_p (shmem_ctx_t ctx, int32_t* addr, int32_t value, int pe);
void shmem_ctx_int64_p (shmem_ctx_t ctx, int64_t* addr, int64_t value, int pe);
void shmem_ctx_uint8_p (shmem_ctx_t ctx, uint8_t* addr, uint8_t value, int pe);
void shmem_ctx_uint16_p (shmem_ctx_t ctx, uint16_t* addr, uint16_t value, int pe);
void shmem_ctx_uint32_p (shmem_ctx_t ctx, uint32_t* addr, uint32_t value, int pe);
void shmem_ctx_uint64_p (shmem_ctx_t ctx, uint64_t* addr, uint64_t value, int pe);
void shmem_ctx_size_p (shmem_ctx_t ctx, size_t* addr, size_t value, int pe);
void shmem_ctx_ptrdiff_p (shmem_ctx_t ctx, ptrdiff_t* addr, ptrdiff_t value, int pe);

void shmem_char_p (char* addr, char value, int pe);
void shmem_short_p (short* addr, short value, int pe);
void shmem_int_p (int* addr, int value, int pe);
void shmem_long_p (long* addr, long value, int pe);
void shmem_float_p (float* addr, float value, int pe);
void shmem_double_p (double* addr, double value, int pe);
void shmem_longlong_p (long long* addr, long long value, int pe);
void shmem_schar_p (signed char* addr, signed char value, int pe);
void shmem_uchar_p (unsigned char* addr, unsigned char value, int pe);
void shmem_ushort_p (unsigned short* addr, unsigned short value, int pe);
void shmem_uint_p (unsigned int* addr, unsigned int value, int pe);
void shmem_ulong_p (unsigned long* addr, unsigned long value, int pe);
void shmem_ulonglong_p (unsigned long long* addr, unsigned long long value, int pe);
void shmem_longdouble_p (long double* addr, long double value, int pe);
void shmem_int8_p (int8_t* addr, int8_t value, int pe);
void shmem_int16_p (int16_t* addr, int16_t value, int pe);
void shmem_int32_p (int32_t* addr, int32_t value, int pe);
void shmem_int64_p (int64_t* addr, int64_t value, int pe);
void shmem_uint8_p (uint8_t* addr, uint8_t value, int pe);
void shmem_uint16_p (uint16_t* addr, uint16_t value, int pe);
void shmem_uint32_p (uint32_t* addr, uint32_t value, int pe);
void shmem_uint64_p (uint64_t* addr, uint64_t value, int pe);
void shmem_size_p (size_t* addr, size_t value, int pe);
void shmem_ptrdiff_p (ptrdiff_t* addr, ptrdiff_t value, int pe);

/*
 * Block data put routines
 */
void shmem_ctx_char_put (shmem_ctx_t ctx, char* target, const char* source, size_t len, int pe);
void shmem_ctx_short_put (shmem_ctx_t ctx, short* target, const short* source, size_t len, int pe);
void shmem_ctx_int_put (shmem_ctx_t ctx, int* target, const int* source, size_t len, int pe);
void shmem_ctx_long_put (shmem_ctx_t ctx, long* target, const long* source, size_t len, int pe);
void shmem_ctx_float_put (shmem_ctx_t ctx, float* target, const float* source, size_t len, int pe);
void shmem_ctx_double_put (shmem_ctx_t ctx, double* target, const double* source, size_t len, int pe);
void shmem_ctx_longlong_put (shmem_ctx_t ctx, long long* target, const long long* source, size_t len, int pe);
void shmem_ctx_schar_put (shmem_ctx_t ctx, signed char* target, const signed char* source, size_t len, int pe);
void shmem_ctx_uchar_put (shmem_ctx_t ctx, unsigned char* target, const unsigned char* source, size_t len, int pe);
void shmem_ctx_ushort_put (shmem_ctx_t ctx, unsigned short* target, const unsigned short* source, size_t len, int pe);
void shmem_ctx_uint_put (shmem_ctx_t ctx, unsigned int* target, const unsigned int* source, size_t len, int pe);
void shmem_ctx_ulong_put (shmem_ctx_t ctx, unsigned long* target, const unsigned long* source, size_t len, int pe);
void shmem_ctx_ulonglong_put (shmem_ctx_t ctx, unsigned long long* target, const unsigned long long* source, size_t len, int pe);
void shmem_ctx_longdouble_put (shmem_ctx_t ctx, long double* target, const long double* source, size_t len, int pe);
void shmem_ctx_int8_put (shmem_ctx_t ctx, int8_t* target, const int8_t* source, size_t len, int pe);
void shmem_ctx_int16_put (shmem_ctx_t ctx, int16_t* target, const int16_t* source, size_t len, int pe);
void shmem_ctx_int32_put (shmem_ctx_t ctx, int32_t* target, const int32_t* source, size_t len, int pe);
void shmem_ctx_int64_put (shmem_ctx_t ctx, int64_t* target, const int64_t* source, size_t len, int pe);
void shmem_ctx_uint8_put (shmem_ctx_t ctx, uint8_t* target, const uint8_t* source, size_t len, int pe);
void shmem_ctx_uint16_put (shmem_ctx_t ctx, uint16_t* target, const uint16_t* source, size_t len, int pe);
void shmem_ctx_uint32_put (shmem_ctx_t ctx, uint32_t* target, const uint32_t* source, size_t len, int pe);
void shmem_ctx_uint64_put (shmem_ctx_t ctx, uint64_t* target, const uint64_t* source, size_t len, int pe);
void shmem_ctx_size_put (shmem_ctx_t ctx, size_t* target, const size_t* source, size_t len, int pe);
void shmem_ctx_ptrdiff_put (shmem_ctx_t ctx, ptrdiff_t* target, const ptrdiff_t* source, size_t len, int pe);

void shmem_char_put (char* target, const char* source, size_t len, int pe);
void shmem_short_put (short* target, const short* source, size_t len, int pe);
void shmem_int_put (int* target, const int* source, size_t len, int pe);
void shmem_long_put (long* target, const long* source, size_t len, int pe);
void shmem_float_put (float* target, const float* source, size_t len, int pe);
void shmem_double_put (double* target, const double* source, size_t len, int pe);
void shmem_longlong_put (long long* target, const long long* source, size_t len, int pe);
void shmem_schar_put (signed char* target, const signed char* source, size_t len, int pe);
void shmem_uchar_put (unsigned char* target, const unsigned char* source, size_t len, int pe);
void shmem_ushort_put (unsigned short* target, const unsigned short* source, size_t len, int pe);
void shmem_uint_put (unsigned int* target, const unsigned int* source, size_t len, int pe);
void shmem_ulong_put (unsigned long* target, const unsigned long* source, size_t len, int pe);
void shmem_ulonglong_put (unsigned long long* target, const unsigned long long* source, size_t len, int pe);
void shmem_longdouble_put (long double* target, const long double* source, size_t len, int pe);
void shmem_int8_put (int8_t* target, const int8_t* source, size_t len, int pe);
void shmem_int16_put (int16_t* target, const int16_t* source, size_t len, int pe);
void shmem_int32_put (int32_t* target, const int32_t* source, size_t len, int pe);
void shmem_int64_put (int64_t* target, const int64_t* source, size_t len, int pe);
void shmem_uint8_put (uint8_t* target, const uint8_t* source, size_t len, int pe);
void shmem_uint16_put (uint16_t* target, const uint16_t* source, size_t len, int pe);
void shmem_uint32_put (uint32_t* target, const uint32_t* source, size_t len, int pe);
void shmem_uint64_put (uint64_t* target, const uint64_t* source, size_t len, int pe);
void shmem_size_put (size_t* target, const size_t* source, size_t len, int pe);
void shmem_ptrdiff_put (ptrdiff_t* target, const ptrdiff_t* source, size_t len, int pe);

void shmem_ctx_put8 (shmem_ctx_t ctx, void* target, const void* source, size_t len, int pe);
void shmem_ctx_put16 (shmem_ctx_t ctx, void* target, const void* source, size_t len, int pe);
void shmem_ctx_put32 (shmem_ctx_t ctx, void* target, const void* source, size_t len, int pe);
void shmem_ctx_put64 (shmem_ctx_t ctx, void* target, const void* source, size_t len, int pe);
void shmem_ctx_put128 (shmem_ctx_t ctx, void* target, const void* source, size_t len, int pe);
void shmem_ctx_putmem (shmem_ctx_t ctx, void* target, const void* source, size_t len, int pe);

void shmem_put8 (void* target, const void* source, size_t len, int pe);
void shmem_put16 (void* target, const void* source, size_t len, int pe);
void shmem_put32 (void* target, const void* source, size_t len, int pe);
void shmem_put64 (void* target, const void* source, size_t len, int pe);
void shmem_put128 (void* target, const void* source, size_t len, int pe);
void shmem_putmem (void* target, const void* source, size_t len, int pe);


/*
 * Strided put routines
 */
void shmem_ctx_char_iput (shmem_ctx_t ctx, char* target, const char* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_ctx_short_iput (shmem_ctx_t ctx, short* target, const short* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_ctx_int_iput (shmem_ctx_t ctx, int* target, const int* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_ctx_long_iput (shmem_ctx_t ctx, long* target, const long* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_ctx_float_iput (shmem_ctx_t ctx, float* target, const float* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_ctx_double_iput (shmem_ctx_t ctx, double* target, const double* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_ctx_longlong_iput (shmem_ctx_t ctx, long long* target, const long long* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_ctx_schar_iput (shmem_ctx_t ctx, signed char* target, const signed char* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_ctx_uchar_iput (shmem_ctx_t ctx, unsigned char* target, const unsigned char* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_ctx_ushort_iput (shmem_ctx_t ctx, unsigned short* target, const unsigned short* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_ctx_uint_iput (shmem_ctx_t ctx, unsigned int* target, const unsigned int* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_ctx_ulong_iput (shmem_ctx_t ctx, unsigned long* target, const unsigned long* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_ctx_ulonglong_iput (shmem_ctx_t ctx, unsigned long long* target, const unsigned long long* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_ctx_longdouble_iput (shmem_ctx_t ctx, long double* target, const long double* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_ctx_int8_iput (shmem_ctx_t ctx, int8_t* target, const int8_t* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_ctx_int16_iput (shmem_ctx_t ctx, int16_t* target, const int16_t* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_ctx_int32_iput (shmem_ctx_t ctx, int32_t* target, const int32_t* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_ctx_int64_iput (shmem_ctx_t ctx, int64_t* target, const int64_t* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_ctx_uint8_iput (shmem_ctx_t ctx, uint8_t* target, const uint8_t* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_ctx_uint16_iput (shmem_ctx_t ctx, uint16_t* target, const uint16_t* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_ctx_uint32_iput (shmem_ctx_t ctx, uint32_t* target, const uint32_t* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_ctx_uint64_iput (shmem_ctx_t ctx, uint64_t* target, const uint64_t* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_ctx_size_iput (shmem_ctx_t ctx, size_t* target, const size_t* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_ctx_ptrdiff_iput (shmem_ctx_t ctx, ptrdiff_t* target, const ptrdiff_t* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);

void shmem_char_iput (char* target, const char* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_short_iput (short* target, const short* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_int_iput (int* target, const int* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_long_iput (long* target, const long* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_float_iput (float* target, const float* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_double_iput (double* target, const double* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_longlong_iput (long long* target, const long long* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_schar_iput (signed char* target, const signed char* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_uchar_iput (unsigned char* target, const unsigned char* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_ushort_iput (unsigned short* target, const unsigned short* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_uint_iput (unsigned int* target, const unsigned int* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_ulong_iput (unsigned long* target, const unsigned long* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_ulonglong_iput (unsigned long long* target, const unsigned long long* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_longdouble_iput (long double* target, const long double* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_int8_iput (int8_t* target, const int8_t* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_int16_iput (int16_t* target, const int16_t* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_int32_iput (int32_t* target, const int32_t* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_int64_iput (int64_t* target, const int64_t* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_uint8_iput (uint8_t* target, const uint8_t* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_uint16_iput (uint16_t* target, const uint16_t* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_uint32_iput (uint32_t* target, const uint32_t* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_uint64_iput (uint64_t* target, const uint64_t* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_size_iput (size_t* target, const size_t* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_ptrdiff_iput (ptrdiff_t* target, const ptrdiff_t* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);

void shmem_ctx_iput8 (shmem_ctx_t ctx, void* target, const void* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_ctx_iput16 (shmem_ctx_t ctx, void* target, const void* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_ctx_iput32 (shmem_ctx_t ctx, void* target, const void* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_ctx_iput64 (shmem_ctx_t ctx, void* target, const void* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_ctx_iput128 (shmem_ctx_t ctx, void* target, const void* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);

void shmem_iput8 (void* target, const void* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_iput16 (void* target, const void* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_iput32 (void* target, const void* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_iput64 (void* target, const void* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_iput128 (void* target, const void* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);

/*
 * Nonblocking put routines
 */
void shmem_ctx_char_put_nbi (shmem_ctx_t ctx, char* target, const char* source, size_t len, int pe);
void shmem_ctx_short_put_nbi (shmem_ctx_t ctx, short* target, const short* source, size_t len, int pe);
void shmem_ctx_int_put_nbi (shmem_ctx_t ctx, int* target, const int* source, size_t len, int pe);
void shmem_ctx_long_put_nbi (shmem_ctx_t ctx, long* target, const long* source, size_t len, int pe);
void shmem_ctx_float_put_nbi (shmem_ctx_t ctx, float* target, const float* source, size_t len, int pe);
void shmem_ctx_double_put_nbi (shmem_ctx_t ctx, double* target, const double* source, size_t len, int pe);
void shmem_ctx_longlong_put_nbi (shmem_ctx_t ctx, long long* target, const long long* source, size_t len, int pe);
void shmem_ctx_schar_put_nbi (shmem_ctx_t ctx, signed char* target, const signed char* source, size_t len, int pe);
void shmem_ctx_uchar_put_nbi (shmem_ctx_t ctx, unsigned char* target, const unsigned char* source, size_t len, int pe);
void shmem_ctx_ushort_put_nbi (shmem_ctx_t ctx, unsigned short* target, const unsigned short* source, size_t len, int pe);
void shmem_ctx_uint_put_nbi (shmem_ctx_t ctx, unsigned int* target, const unsigned int* source, size_t len, int pe);
void shmem_ctx_ulong_put_nbi (shmem_ctx_t ctx, unsigned long* target, const unsigned long* source, size_t len, int pe);
void shmem_ctx_ulonglong_put_nbi (shmem_ctx_t ctx, unsigned long long* target, const unsigned long long* source, size_t len, int pe);
void shmem_ctx_longdouble_put_nbi (shmem_ctx_t ctx, long double* target, const long double* source, size_t len, int pe);
void shmem_ctx_int8_put_nbi (shmem_ctx_t ctx, int8_t* target, const int8_t* source, size_t len, int pe);
void shmem_ctx_int16_put_nbi (shmem_ctx_t ctx, int16_t* target, const int16_t* source, size_t len, int pe);
void shmem_ctx_int32_put_nbi (shmem_ctx_t ctx, int32_t* target, const int32_t* source, size_t len, int pe);
void shmem_ctx_int64_put_nbi (shmem_ctx_t ctx, int64_t* target, const int64_t* source, size_t len, int pe);
void shmem_ctx_uint8_put_nbi (shmem_ctx_t ctx, uint8_t* target, const uint8_t* source, size_t len, int pe);
void shmem_ctx_uint16_put_nbi (shmem_ctx_t ctx, uint16_t* target, const uint16_t* source, size_t len, int pe);
void shmem_ctx_uint32_put_nbi (shmem_ctx_t ctx, uint32_t* target, const uint32_t* source, size_t len, int pe);
void shmem_ctx_uint64_put_nbi (shmem_ctx_t ctx, uint64_t* target, const uint64_t* source, size_t len, int pe);
void shmem_ctx_size_put_nbi (shmem_ctx_t ctx, size_t* target, const size_t* source, size_t len, int pe);
void shmem_ctx_ptrdiff_put_nbi (shmem_ctx_t ctx, ptrdiff_t* target, const ptrdiff_t* source, size_t len, int pe);

void shmem_char_put_nbi (char* target, const char* source, size_t len, int pe);
void shmem_short_put_nbi (short* target, const short* source, size_t len, int pe);
void shmem_int_put_nbi (int* target, const int* source, size_t len, int pe);
void shmem_long_put_nbi (long* target, const long* source, size_t len, int pe);
void shmem_float_put_nbi (float* target, const float* source, size_t len, int pe);
void shmem_double_put_nbi (double* target, const double* source, size_t len, int pe);
void shmem_longlong_put_nbi (long long* target, const long long* source, size_t len, int pe);
void shmem_schar_put_nbi (signed char* target, const signed char* source, size_t len, int pe);
void shmem_uchar_put_nbi (unsigned char* target, const unsigned char* source, size_t len, int pe);
void shmem_ushort_put_nbi (unsigned short* target, const unsigned short* source, size_t len, int pe);
void shmem_uint_put_nbi (unsigned int* target, const unsigned int* source, size_t len, int pe);
void shmem_ulong_put_nbi (unsigned long* target, const unsigned long* source, size_t len, int pe);
void shmem_ulonglong_put_nbi (unsigned long long* target, const unsigned long long* source, size_t len, int pe);
void shmem_longdouble_put_nbi (long double* target, const long double* source, size_t len, int pe);
void shmem_int8_put_nbi (int8_t* target, const int8_t* source, size_t len, int pe);
void shmem_int16_put_nbi (int16_t* target, const int16_t* source, size_t len, int pe);
void shmem_int32_put_nbi (int32_t* target, const int32_t* source, size_t len, int pe);
void shmem_int64_put_nbi (int64_t* target, const int64_t* source, size_t len, int pe);
void shmem_uint8_put_nbi (uint8_t* target, const uint8_t* source, size_t len, int pe);
void shmem_uint16_put_nbi (uint16_t* target, const uint16_t* source, size_t len, int pe);
void shmem_uint32_put_nbi (uint32_t* target, const uint32_t* source, size_t len, int pe);
void shmem_uint64_put_nbi (uint64_t* target, const uint64_t* source, size_t len, int pe);
void shmem_size_put_nbi (size_t* target, const size_t* source, size_t len, int pe);
void shmem_ptrdiff_put_nbi (ptrdiff_t* target, const ptrdiff_t* source, size_t len, int pe);

void shmem_ctx_put8_nbi (shmem_ctx_t ctx, void* target, const void* source, size_t len, int pe);
void shmem_ctx_put16_nbi (shmem_ctx_t ctx, void* target, const void* source, size_t len, int pe);
void shmem_ctx_put32_nbi (shmem_ctx_t ctx, void* target, const void* source, size_t len, int pe);
void shmem_ctx_put64_nbi (shmem_ctx_t ctx, void* target, const void* source, size_t len, int pe);
void shmem_ctx_put128_nbi (shmem_ctx_t ctx, void* target, const void* source, size_t len, int pe);
void shmem_ctx_putmem_nbi (shmem_ctx_t ctx, void* target, const void* source, size_t len, int pe);

void shmem_put8_nbi (void* target, const void* source, size_t len, int pe);
void shmem_put16_nbi (void* target, const void* source, size_t len, int pe);
void shmem_put32_nbi (void* target, const void* source, size_t len, int pe);
void shmem_put64_nbi (void* target, const void* source, size_t len, int pe);
void shmem_put128_nbi (void* target, const void* source, size_t len, int pe);
void shmem_putmem_nbi (void* target, const void* source, size_t len, int pe);

/*
 * Elemental get routines
 */
char shmem_ctx_char_g (shmem_ctx_t ctx, const char* addr, int pe);
short shmem_ctx_short_g (shmem_ctx_t ctx, const short* addr, int pe);
int shmem_ctx_int_g (shmem_ctx_t ctx, const int* addr, int pe);
long shmem_ctx_long_g (shmem_ctx_t ctx, const long* addr, int pe);
float shmem_ctx_float_g (shmem_ctx_t ctx, const float* addr, int pe);
double shmem_ctx_double_g (shmem_ctx_t ctx, const double* addr, int pe);
long long shmem_ctx_longlong_g (shmem_ctx_t ctx, const long long* addr, int pe);
long double shmem_ctx_longdouble_g (shmem_ctx_t ctx, const long double* addr, int pe);
signed char shmem_ctx_schar_g (shmem_ctx_t ctx, const signed char* addr, int pe);
unsigned char shmem_ctx_uchar_g (shmem_ctx_t ctx, const unsigned char* addr, int pe);
unsigned short shmem_ctx_ushort_g (shmem_ctx_t ctx, const unsigned short* addr, int pe);
unsigned int shmem_ctx_uint_g (shmem_ctx_t ctx, const unsigned int* addr, int pe);
unsigned long shmem_ctx_ulong_g (shmem_ctx_t ctx, const unsigned long* addr, int pe);
unsigned long long shmem_ctx_ulonglong_g (shmem_ctx_t ctx, const unsigned long long* addr, int pe);
int8_t shmem_ctx_int8_g (shmem_ctx_t ctx, const int8_t* addr, int pe);
int16_t shmem_ctx_int16_g (shmem_ctx_t ctx, const int16_t* addr, int pe);
int32_t shmem_ctx_int32_g (shmem_ctx_t ctx, const int32_t* addr, int pe);
int64_t shmem_ctx_int64_g (shmem_ctx_t ctx, const int64_t* addr, int pe);
uint8_t shmem_ctx_uint8_g (shmem_ctx_t ctx, const uint8_t* addr, int pe);
uint16_t shmem_ctx_uint16_g (shmem_ctx_t ctx, const uint16_t* addr, int pe);
uint32_t shmem_ctx_uint32_g (shmem_ctx_t ctx, const uint32_t* addr, int pe);
uint64_t shmem_ctx_uint64_g (shmem_ctx_t ctx, const uint64_t* addr, int pe);
size_t shmem_ctx_size_g (shmem_ctx_t ctx, const size_t* addr, int pe);
ptrdiff_t shmem_ctx_ptrdiff_g (shmem_ctx_t ctx, const ptrdiff_t* addr, int pe);

char shmem_char_g (const char* addr, int pe);
short shmem_short_g (const short* addr, int pe);
int shmem_int_g (const int* addr, int pe);
long shmem_long_g (const long* addr, int pe);
float shmem_float_g (const float* addr, int pe);
double shmem_double_g (const double* addr, int pe);
long long shmem_longlong_g (const long long* addr, int pe);
long double shmem_longdouble_g (const long double* addr, int pe);
signed char shmem_schar_g (const signed char* addr, int pe);
unsigned char shmem_uchar_g (const unsigned char* addr, int pe);
unsigned short shmem_ushort_g (const unsigned short* addr, int pe);
unsigned int shmem_uint_g (const unsigned int* addr, int pe);
unsigned long shmem_ulong_g (const unsigned long* addr, int pe);
unsigned long long shmem_ulonglong_g (const unsigned long long* addr, int pe);
int8_t shmem_int8_g (const int8_t* addr, int pe);
int16_t shmem_int16_g (const int16_t* addr, int pe);
int32_t shmem_int32_g (const int32_t* addr, int pe);
int64_t shmem_int64_g (const int64_t* addr, int pe);
uint8_t shmem_uint8_g (const uint8_t* addr, int pe);
uint16_t shmem_uint16_g (const uint16_t* addr, int pe);
uint32_t shmem_uint32_g (const uint32_t* addr, int pe);
uint64_t shmem_uint64_g (const uint64_t* addr, int pe);
size_t shmem_size_g (const size_t* addr, int pe);
ptrdiff_t shmem_ptrdiff_g (const ptrdiff_t* addr, int pe);

/*
 * Block data get routines
 */
void shmem_ctx_char_get (shmem_ctx_t ctx, char* target, const char* source, size_t len, int pe);
void shmem_ctx_short_get (shmem_ctx_t ctx, short* target, const short* source, size_t len, int pe);
void shmem_ctx_int_get (shmem_ctx_t ctx, int* target, const int* source, size_t len, int pe);
void shmem_ctx_long_get (shmem_ctx_t ctx, long* target, const long* source, size_t len, int pe);
void shmem_ctx_float_get (shmem_ctx_t ctx, float* target, const float* source, size_t len, int pe);
void shmem_ctx_double_get (shmem_ctx_t ctx, double* target, const double* source, size_t len, int pe);
void shmem_ctx_longlong_get (shmem_ctx_t ctx, long long* target, const long long* source, size_t len, int pe);
void shmem_ctx_schar_get (shmem_ctx_t ctx, signed char* target, const signed char* source, size_t len, int pe);
void shmem_ctx_uchar_get (shmem_ctx_t ctx, unsigned char* target, const unsigned char* source, size_t len, int pe);
void shmem_ctx_ushort_get (shmem_ctx_t ctx, unsigned short* target, const unsigned short* source, size_t len, int pe);
void shmem_ctx_uint_get (shmem_ctx_t ctx, unsigned int* target, const unsigned int* source, size_t len, int pe);
void shmem_ctx_ulong_get (shmem_ctx_t ctx, unsigned long* target, const unsigned long* source, size_t len, int pe);
void shmem_ctx_ulonglong_get (shmem_ctx_t ctx, unsigned long long* target, const unsigned long long* source, size_t len, int pe);
void shmem_ctx_longdouble_get (shmem_ctx_t ctx, long double* target, const long double* source, size_t len, int pe);
void shmem_ctx_int8_get (shmem_ctx_t ctx, int8_t* target, const int8_t* source, size_t len, int pe);
void shmem_ctx_int16_get (shmem_ctx_t ctx, int16_t* target, const int16_t* source, size_t len, int pe);
void shmem_ctx_int32_get (shmem_ctx_t ctx, int32_t* target, const int32_t* source, size_t len, int pe);
void shmem_ctx_int64_get (shmem_ctx_t ctx, int64_t* target, const int64_t* source, size_t len, int pe);
void shmem_ctx_uint8_get (shmem_ctx_t ctx, uint8_t* target, const uint8_t* source, size_t len, int pe);
void shmem_ctx_uint16_get (shmem_ctx_t ctx, uint16_t* target, const uint16_t* source, size_t len, int pe);
void shmem_ctx_uint32_get (shmem_ctx_t ctx, uint32_t* target, const uint32_t* source, size_t len, int pe);
void shmem_ctx_uint64_get (shmem_ctx_t ctx, uint64_t* target, const uint64_t* source, size_t len, int pe);
void shmem_ctx_size_get (shmem_ctx_t ctx, size_t* target, const size_t* source, size_t len, int pe);
void shmem_ctx_ptrdiff_get (shmem_ctx_t ctx, ptrdiff_t* target, const ptrdiff_t* source, size_t len, int pe);

void shmem_char_get (char* target, const char* source, size_t len, int pe);
void shmem_short_get (short* target, const short* source, size_t len, int pe);
void shmem_int_get (int* target, const int* source, size_t len, int pe);
void shmem_long_get (long* target, const long* source, size_t len, int pe);
void shmem_float_get (float* target, const float* source, size_t len, int pe);
void shmem_double_get (double* target, const double* source, size_t len, int pe);
void shmem_longlong_get (long long* target, const long long* source, size_t len, int pe);
void shmem_schar_get (signed char* target, const signed char* source, size_t len, int pe);
void shmem_uchar_get (unsigned char* target, const unsigned char* source, size_t len, int pe);
void shmem_ushort_get (unsigned short* target, const unsigned short* source, size_t len, int pe);
void shmem_uint_get (unsigned int* target, const unsigned int* source, size_t len, int pe);
void shmem_ulong_get (unsigned long* target, const unsigned long* source, size_t len, int pe);
void shmem_ulonglong_get (unsigned long long* target, const unsigned long long* source, size_t len, int pe);
void shmem_longdouble_get (long double* target, const long double* source, size_t len, int pe);
void shmem_int8_get (int8_t* target, const int8_t* source, size_t len, int pe);
void shmem_int16_get (int16_t* target, const int16_t* source, size_t len, int pe);
void shmem_int32_get (int32_t* target, const int32_t* source, size_t len, int pe);
void shmem_int64_get (int64_t* target, const int64_t* source, size_t len, int pe);
void shmem_uint8_get (uint8_t* target, const uint8_t* source, size_t len, int pe);
void shmem_uint16_get (uint16_t* target, const uint16_t* source, size_t len, int pe);
void shmem_uint32_get (uint32_t* target, const uint32_t* source, size_t len, int pe);
void shmem_uint64_get (uint64_t* target, const uint64_t* source, size_t len, int pe);
void shmem_size_get (size_t* target, const size_t* source, size_t len, int pe);
void shmem_ptrdiff_get (ptrdiff_t* target, const ptrdiff_t* source, size_t len, int pe);

void shmem_ctx_get8 (shmem_ctx_t ctx, void* target, const void* source, size_t len, int pe);
void shmem_ctx_get16 (shmem_ctx_t ctx, void* target, const void* source, size_t len, int pe);
void shmem_ctx_get32 (shmem_ctx_t ctx, void* target, const void* source, size_t len, int pe);
void shmem_ctx_get64 (shmem_ctx_t ctx, void* target, const void* source, size_t len, int pe);
void shmem_ctx_get128 (shmem_ctx_t ctx, void* target, const void* source, size_t len, int pe);
void shmem_ctx_getmem (shmem_ctx_t ctx, void* target, const void* source, size_t len, int pe);

void shmem_get8 (void* target, const void* source, size_t len, int pe);
void shmem_get16 (void* target, const void* source, size_t len, int pe);
void shmem_get32 (void* target, const void* source, size_t len, int pe);
void shmem_get64 (void* target, const void* source, size_t len, int pe);
void shmem_get128 (void* target, const void* source, size_t len, int pe);
void shmem_getmem (void* target, const void* source, size_t len, int pe);

/*
 * Strided get routines
 */
void shmem_ctx_char_iget (shmem_ctx_t ctx, char* target, const char* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_ctx_short_iget (shmem_ctx_t ctx, short* target, const short* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_ctx_int_iget (shmem_ctx_t ctx, int* target, const int* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_ctx_long_iget (shmem_ctx_t ctx, long* target, const long* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_ctx_longlong_iget (shmem_ctx_t ctx, long long* target, const long long* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_ctx_schar_iget (shmem_ctx_t ctx, signed char* target, const signed char* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_ctx_uchar_iget (shmem_ctx_t ctx, unsigned char* target, const unsigned char* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_ctx_ushort_iget (shmem_ctx_t ctx, unsigned short* target, const unsigned short* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_ctx_uint_iget (shmem_ctx_t ctx, unsigned int* target, const unsigned int* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_ctx_ulong_iget (shmem_ctx_t ctx, unsigned long* target, const unsigned long* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_ctx_ulonglong_iget (shmem_ctx_t ctx, unsigned long long* target, const unsigned long long* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_ctx_float_iget (shmem_ctx_t ctx, float* target, const float* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_ctx_double_iget (shmem_ctx_t ctx, double* target, const double* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_ctx_longdouble_iget (shmem_ctx_t ctx, long double* target, const long double* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_ctx_int8_iget (shmem_ctx_t ctx, int8_t* target, const int8_t* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_ctx_int16_iget (shmem_ctx_t ctx, int16_t* target, const int16_t* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_ctx_int32_iget (shmem_ctx_t ctx, int32_t* target, const int32_t* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_ctx_int64_iget (shmem_ctx_t ctx, int64_t* target, const int64_t* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_ctx_uint8_iget (shmem_ctx_t ctx, uint8_t* target, const uint8_t* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_ctx_uint16_iget (shmem_ctx_t ctx, uint16_t* target, const uint16_t* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_ctx_uint32_iget (shmem_ctx_t ctx, uint32_t* target, const uint32_t* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_ctx_uint64_iget (shmem_ctx_t ctx, uint64_t* target, const uint64_t* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_ctx_size_iget (shmem_ctx_t ctx, size_t* target, const size_t* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_ctx_ptrdiff_iget (shmem_ctx_t ctx, ptrdiff_t* target, const ptrdiff_t* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);

void shmem_char_iget (char* target, const char* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_short_iget (short* target, const short* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_int_iget (int* target, const int* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_float_iget (float* target, const float* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_double_iget (double* target, const double* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_longlong_iget (long long* target, const long long* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_longdouble_iget (long double* target, const long double* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_long_iget (long* target, const long* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_schar_iget (signed char* target, const signed char* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_uchar_iget (unsigned char* target, const unsigned char* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_ushort_iget (unsigned short* target, const unsigned short* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_uint_iget (unsigned int* target, const unsigned int* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_ulong_iget (unsigned long* target, const unsigned long* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_ulonglong_iget (unsigned long long* target, const unsigned long long* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_int8_iget (int8_t* target, const int8_t* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_int16_iget (int16_t* target, const int16_t* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_int32_iget (int32_t* target, const int32_t* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_int64_iget (int64_t* target, const int64_t* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_uint8_iget (uint8_t* target, const uint8_t* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_uint16_iget (uint16_t* target, const uint16_t* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_uint32_iget (uint32_t* target, const uint32_t* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_uint64_iget (uint64_t* target, const uint64_t* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_size_iget (size_t* target, const size_t* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);
void shmem_ptrdiff_iget (ptrdiff_t* target, const ptrdiff_t* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe);

void shmem_ctx_iget8 (shmem_ctx_t ctx, void* target, const void* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_ctx_iget16 (shmem_ctx_t ctx, void* target, const void* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_ctx_iget32 (shmem_ctx_t ctx, void* target, const void* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_ctx_iget64 (shmem_ctx_t ctx, void* target, const void* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_ctx_iget128 (shmem_ctx_t ctx, void* target, const void* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);

void shmem_iget8 (void* target, const void* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_iget16 (void* target, const void* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_iget32 (void* target, const void* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_iget64 (void* target, const void* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);
void shmem_iget128 (void* target, const void* source, ptrdiff_t tst, ptrdiff_t sst,size_t len, int pe);

/*
 * Nonblocking data get routines
 */
void shmem_ctx_char_get_nbi (shmem_ctx_t ctx, char* target, const char* source, size_t len, int pe);
void shmem_ctx_short_get_nbi (shmem_ctx_t ctx, short* target, const short* source, size_t len, int pe);
void shmem_ctx_int_get_nbi (shmem_ctx_t ctx, int* target, const int* source, size_t len, int pe);
void shmem_ctx_long_get_nbi (shmem_ctx_t ctx, long* target, const long* source, size_t len, int pe);
void shmem_ctx_longlong_get_nbi (shmem_ctx_t ctx, long long* target, const long long* source, size_t len, int pe);
void shmem_ctx_schar_get_nbi (shmem_ctx_t ctx, signed char* target, const signed char* source, size_t len, int pe);
void shmem_ctx_uchar_get_nbi (shmem_ctx_t ctx, unsigned char* target, const unsigned char* source, size_t len, int pe);
void shmem_ctx_ushort_get_nbi (shmem_ctx_t ctx, unsigned short* target, const unsigned short* source, size_t len, int pe);
void shmem_ctx_uint_get_nbi (shmem_ctx_t ctx, unsigned int* target, const unsigned int* source, size_t len, int pe);
void shmem_ctx_ulong_get_nbi (shmem_ctx_t ctx, unsigned long* target, const unsigned long* source, size_t len, int pe);
void shmem_ctx_ulonglong_get_nbi (shmem_ctx_t ctx, unsigned long long* target, const unsigned long long* source, size_t len, int pe);
void shmem_ctx_float_get_nbi (shmem_ctx_t ctx, float* target, const float* source, size_t len, int pe);
void shmem_ctx_double_get_nbi (shmem_ctx_t ctx, double* target, const double* source, size_t len, int pe);
void shmem_ctx_longdouble_get_nbi (shmem_ctx_t ctx, long double* target, const long double* source, size_t len, int pe);
void shmem_ctx_int8_get_nbi (shmem_ctx_t ctx, int8_t* target, const int8_t* source, size_t len, int pe);
void shmem_ctx_int16_get_nbi (shmem_ctx_t ctx, int16_t* target, const int16_t* source, size_t len, int pe);
void shmem_ctx_int32_get_nbi (shmem_ctx_t ctx, int32_t* target, const int32_t* source, size_t len, int pe);
void shmem_ctx_int64_get_nbi (shmem_ctx_t ctx, int64_t* target, const int64_t* source, size_t len, int pe);
void shmem_ctx_uint8_get_nbi (shmem_ctx_t ctx, uint8_t* target, const uint8_t* source, size_t len, int pe);
void shmem_ctx_uint16_get_nbi (shmem_ctx_t ctx, uint16_t* target, const uint16_t* source, size_t len, int pe);
void shmem_ctx_uint32_get_nbi (shmem_ctx_t ctx, uint32_t* target, const uint32_t* source, size_t len, int pe);
void shmem_ctx_uint64_get_nbi (shmem_ctx_t ctx, uint64_t* target, const uint64_t* source, size_t len, int pe);
void shmem_ctx_size_get_nbi (shmem_ctx_t ctx, size_t* target, const size_t* source, size_t len, int pe);
void shmem_ctx_ptrdiff_get_nbi (shmem_ctx_t ctx, ptrdiff_t* target, const ptrdiff_t* source, size_t len, int pe);

void shmem_char_get_nbi (char* target, const char* source, size_t len, int pe);
void shmem_short_get_nbi (short* target, const short* source, size_t len, int pe);
void shmem_int_get_nbi (int* target, const int* source, size_t len, int pe);
void shmem_long_get_nbi (long* target, const long* source, size_t len, int pe);
void shmem_longlong_get_nbi (long long* target, const long long* source, size_t len, int pe);
void shmem_schar_get_nbi (signed char* target, const signed char* source, size_t len, int pe);
void shmem_uchar_get_nbi (unsigned char* target, const unsigned char* source, size_t len, int pe);
void shmem_ushort_get_nbi (unsigned short* target, const unsigned short* source, size_t len, int pe);
void shmem_uint_get_nbi (unsigned int* target, const unsigned int* source, size_t len, int pe);
void shmem_ulong_get_nbi (unsigned long* target, const unsigned long* source, size_t len, int pe);
void shmem_ulonglong_get_nbi (unsigned long long* target, const unsigned long long* source, size_t len, int pe);
void shmem_float_get_nbi (float* target, const float* source, size_t len, int pe);
void shmem_double_get_nbi (double* target, const double* source, size_t len, int pe);
void shmem_longdouble_get_nbi (long double* target, const long double* source, size_t len, int pe);
void shmem_int8_get_nbi (int8_t* target, const int8_t* source, size_t len, int pe);
void shmem_int16_get_nbi (int16_t* target, const int16_t* source, size_t len, int pe);
void shmem_int32_get_nbi (int32_t* target, const int32_t* source, size_t len, int pe);
void shmem_int64_get_nbi (int64_t* target, const int64_t* source, size_t len, int pe);
void shmem_uint8_get_nbi (uint8_t* target, const uint8_t* source, size_t len, int pe);
void shmem_uint16_get_nbi (uint16_t* target, const uint16_t* source, size_t len, int pe);
void shmem_uint32_get_nbi (uint32_t* target, const uint32_t* source, size_t len, int pe);
void shmem_uint64_get_nbi (uint64_t* target, const uint64_t* source, size_t len, int pe);
void shmem_size_get_nbi (size_t* target, const size_t* source, size_t len, int pe);
void shmem_ptrdiff_get_nbi (ptrdiff_t* target, const ptrdiff_t* source, size_t len, int pe);

void shmem_ctx_get8_nbi (shmem_ctx_t ctx, void* target, const void* source, size_t len, int pe);
void shmem_ctx_get16_nbi (shmem_ctx_t ctx, void* target, const void* source, size_t len, int pe);
void shmem_ctx_get32_nbi (shmem_ctx_t ctx, void* target, const void* source, size_t len, int pe);
void shmem_ctx_get64_nbi (shmem_ctx_t ctx, void* target, const void* source, size_t len, int pe);
void shmem_ctx_get128_nbi (shmem_ctx_t ctx, void* target, const void* source, size_t len, int pe);
void shmem_ctx_getmem_nbi (shmem_ctx_t ctx, void* target, const void* source, size_t len, int pe);

void shmem_get8_nbi (void* target, const void* source, size_t len, int pe);
void shmem_get16_nbi (void* target, const void* source, size_t len, int pe);
void shmem_get32_nbi (void* target, const void* source, size_t len, int pe);
void shmem_get64_nbi (void* target, const void* source, size_t len, int pe);
void shmem_get128_nbi (void* target, const void* source, size_t len, int pe);
void shmem_getmem_nbi (void* target, const void* source, size_t len, int pe);

/*
 * Atomic operations
 */
/* Atomic swap */
int shmem_ctx_int_atomic_swap (shmem_ctx_t ctx, int* target, int value, int pe);
long shmem_ctx_long_atomic_swap (shmem_ctx_t ctx, long* target, long value, int pe);
long long shmem_ctx_longlong_atomic_swap (shmem_ctx_t ctx, long long* target, long long value, int pe);
unsigned int shmem_ctx_uint_atomic_swap (shmem_ctx_t ctx, unsigned int* target, unsigned int value, int pe);
unsigned long shmem_ctx_ulong_atomic_swap (shmem_ctx_t ctx, unsigned long* target, unsigned long value, int pe);
unsigned long long shmem_ctx_ulonglong_atomic_swap (shmem_ctx_t ctx, unsigned long long* target, unsigned long long value, int pe);
float shmem_ctx_float_atomic_swap (shmem_ctx_t ctx, float* target, float value, int pe);
double shmem_ctx_double_atomic_swap (shmem_ctx_t ctx, double* target, double value, int pe);

int shmem_int_atomic_swap (int* target, int value, int pe);
long shmem_long_atomic_swap (long* target, long value, int pe);
long long shmem_longlong_atomic_swap (long long*target, long long value, int pe);
unsigned int shmem_uint_atomic_swap (unsigned int* target, unsigned int value, int pe);
unsigned long shmem_ulong_atomic_swap (unsigned long* target, unsigned long value, int pe);
unsigned long long shmem_ulonglong_atomic_swap (unsigned long long* target, unsigned long long value, int pe);
float shmem_float_atomic_swap (float* target, float value, int pe);
double shmem_double_atomic_swap (double* target, double value, int pe);

int shmem_int_swap (int* target, int value, int pe);
long shmem_long_swap (long* target, long value, int pe);
long long shmem_longlong_swap (long long*target, long long value, int pe);
float shmem_float_swap (float* target, float value, int pe);
double shmem_double_swap (double* target, double value, int pe);

/* Atomic set */
void shmem_ctx_int_atomic_set (shmem_ctx_t ctx, int* target, int value, int pe);
void shmem_ctx_long_atomic_set (shmem_ctx_t ctx, long* target, long value, int pe);
void shmem_ctx_longlong_atomic_set (shmem_ctx_t ctx, long long* target, long long value, int pe);
void shmem_ctx_uint_atomic_set (shmem_ctx_t ctx, unsigned int* target, unsigned int value, int pe);
void shmem_ctx_ulong_atomic_set (shmem_ctx_t ctx, unsigned long* target, unsigned long value, int pe);
void shmem_ctx_ulonglong_atomic_set (shmem_ctx_t ctx, unsigned long long* target, unsigned long long value, int pe);
void shmem_ctx_float_atomic_set (shmem_ctx_t ctx, float* target, float value, int pe);
void shmem_ctx_double_atomic_set (shmem_ctx_t ctx, double* target, double value, int pe);

void shmem_int_atomic_set (int* target, int value, int pe);
void shmem_long_atomic_set (long* target, long value, int pe);
void shmem_longlong_atomic_set (long long* target, long long value, int pe);
void shmem_uint_atomic_set (unsigned int* target, unsigned int value, int pe);
void shmem_ulong_atomic_set (unsigned long* target, unsigned long value, int pe);
void shmem_ulonglong_atomic_set (unsigned long long* target, unsigned long long value, int pe);
void shmem_float_atomic_set (float* target, float value, int pe);
void shmem_double_atomic_set (double* target, double value, int pe);

void shmem_int_set (int* target, int value, int pe);
void shmem_long_set (long* target, long value, int pe);
void shmem_longlong_set (long long* target, long long value, int pe);
void shmem_float_set (float* target, float value, int pe);
void shmem_double_set (double* target, double value, int pe);

/* Atomic conditional swap */
int shmem_ctx_int_atomic_compare_swap (shmem_ctx_t ctx, int* target, int cond, int value, int pe);
long shmem_ctx_long_atomic_compare_swap (shmem_ctx_t ctx, long* target, long cond, long value, int pe);
long long shmem_ctx_longlong_atomic_compare_swap (shmem_ctx_t ctx, long long* target, long long cond, long long value, int pe);
unsigned int shmem_ctx_uint_atomic_compare_swap (shmem_ctx_t ctx, unsigned int* target, unsigned int cond, unsigned int value, int pe);
unsigned long shmem_ctx_ulong_atomic_compare_swap (shmem_ctx_t ctx, unsigned long* target, unsigned long cond, unsigned long value, int pe);
unsigned long long shmem_ctx_ulonglong_atomic_compare_swap (shmem_ctx_t ctx, unsigned long long* target, unsigned long long cond, unsigned long long value, int pe);

int shmem_int_atomic_compare_swap (int* target, int cond, int value, int pe);
long shmem_long_atomic_compare_swap (long* target, long cond, long value, int pe);
long long shmem_longlong_atomic_compare_swap (long long* target, long long cond, long long value, int pe);
unsigned int shmem_uint_atomic_compare_swap (unsigned int* target, unsigned int cond, unsigned int value, int pe);
unsigned long shmem_ulong_atomic_compare_swap (unsigned long* target, unsigned long cond, unsigned long value, int pe);
unsigned long long shmem_ulonglong_atomic_compare_swap (unsigned long long* target, unsigned long long cond, unsigned long long value, int pe);

int shmem_int_cswap (int* target, int cond, int value, int pe);
long shmem_long_cswap (long* target, long cond, long value, int pe);
long long shmem_longlong_cswap (long long* target, long long cond, long long value, int pe);


/* Atomic Fetch&Add */
int shmem_ctx_int_atomic_fetch_add (shmem_ctx_t ctx, int* target, int value, int pe);
long shmem_ctx_long_atomic_fetch_add (shmem_ctx_t ctx, long* target, long value, int pe);
long long shmem_ctx_longlong_atomic_fetch_add (shmem_ctx_t ctx, long long* target, long long value, int pe);
unsigned int shmem_ctx_uint_atomic_fetch_add (shmem_ctx_t ctx, unsigned int* target, unsigned int value, int pe);
unsigned long shmem_ctx_ulong_atomic_fetch_add (shmem_ctx_t ctx, unsigned long* target, unsigned long value, int pe);
unsigned long long shmem_ctx_ulonglong_atomic_fetch_add (shmem_ctx_t ctx, unsigned long long* target, unsigned long long value, int pe);

int shmem_int_atomic_fetch_add (int* target, int value, int pe);
long shmem_long_atomic_fetch_add (long* target, long value, int pe);
long long shmem_longlong_atomic_fetch_add (long long* target, long long value, int pe);
unsigned int shmem_uint_atomic_fetch_add (unsigned int* target, unsigned int value, int pe);
unsigned long shmem_ulong_atomic_fetch_add (unsigned long* target, unsigned long value, int pe);
unsigned long long shmem_ulonglong_atomic_fetch_add (unsigned long long* target, unsigned long long value, int pe);

int shmem_int_fadd (int* target, int value, int pe);
long shmem_long_fadd (long* target, long value, int pe);
long long shmem_longlong_fadd (long long* target, long long value, int pe);

/* Atomic Fetch&And */
int shmem_ctx_int_atomic_fetch_and (shmem_ctx_t ctx, int* target, int value, int pe);
long shmem_ctx_long_atomic_fetch_and (shmem_ctx_t ctx, long* target, long value, int pe);
long long shmem_ctx_longlong_atomic_fetch_and (shmem_ctx_t ctx, long long* target, long long value, int pe);
unsigned int shmem_ctx_uint_atomic_fetch_and (shmem_ctx_t ctx, unsigned int* target, unsigned int value, int pe);
unsigned long shmem_ctx_ulong_atomic_fetch_and (shmem_ctx_t ctx, unsigned long* target, unsigned long value, int pe);
unsigned long long shmem_ctx_ulonglong_atomic_fetch_and (shmem_ctx_t ctx, unsigned long long* target, unsigned long long value, int pe);
int32_t shmem_ctx_int32_atomic_fetch_and (shmem_ctx_t ctx, int32_t* target, int32_t value, int pe);
int64_t shmem_ctx_int64_atomic_fetch_and (shmem_ctx_t ctx, int64_t* target, int64_t value, int pe);
uint32_t shmem_ctx_uint32_atomic_fetch_and (shmem_ctx_t ctx, uint32_t* target, uint32_t value, int pe);
uint64_t shmem_ctx_uint64_atomic_fetch_and (shmem_ctx_t ctx, uint64_t* target, uint64_t value, int pe);

int shmem_int_atomic_fetch_and (int* target, int value, int pe);
long shmem_long_atomic_fetch_and (long* target, long value, int pe);
long long shmem_longlong_atomic_fetch_and (long long* target, long long value, int pe);
unsigned int shmem_uint_atomic_fetch_and (unsigned int* target, unsigned int value, int pe);
unsigned long shmem_ulong_atomic_fetch_and (unsigned long* target, unsigned long value, int pe);
unsigned long long shmem_ulonglong_atomic_fetch_and (unsigned long long* target, unsigned long long value, int pe);
int32_t shmem_int32_atomic_fetch_and (int32_t* target, int32_t value, int pe);
int64_t shmem_int64_atomic_fetch_and (int64_t* target, int64_t value, int pe);
uint32_t shmem_uint32_atomic_fetch_and (uint32_t* target, uint32_t value, int pe);
uint64_t shmem_uint64_atomic_fetch_and (uint64_t* target, uint64_t value, int pe);

/* Atomic Fetch&Or */
int shmem_ctx_int_atomic_fetch_or (shmem_ctx_t ctx, int* target, int value, int pe);
long shmem_ctx_long_atomic_fetch_or (shmem_ctx_t ctx, long* target, long value, int pe);
long long shmem_ctx_longlong_atomic_fetch_or (shmem_ctx_t ctx, long long* target, long long value, int pe);
unsigned int shmem_ctx_uint_atomic_fetch_or (shmem_ctx_t ctx, unsigned int* target, unsigned int value, int pe);
unsigned long shmem_ctx_ulong_atomic_fetch_or (shmem_ctx_t ctx, unsigned long* target, unsigned long value, int pe);
unsigned long long shmem_ctx_ulonglong_atomic_fetch_or (shmem_ctx_t ctx, unsigned long long* target, unsigned long long value, int pe);
int32_t shmem_ctx_int32_atomic_fetch_or (shmem_ctx_t ctx, int32_t* target, int32_t value, int pe);
int64_t shmem_ctx_int64_atomic_fetch_or (shmem_ctx_t ctx, int64_t* target, int64_t value, int pe);
uint32_t shmem_ctx_uint32_atomic_fetch_or (shmem_ctx_t ctx, uint32_t* target, uint32_t value, int pe);
uint64_t shmem_ctx_uint64_atomic_fetch_or (shmem_ctx_t ctx, uint64_t* target, uint64_t value, int pe);

int shmem_int_atomic_fetch_or (int* target, int value, int pe);
long shmem_long_atomic_fetch_or (long* target, long value, int pe);
long long shmem_longlong_atomic_fetch_or (long long* target, long long value, int pe);
unsigned int shmem_uint_atomic_fetch_or (unsigned int* target, unsigned int value, int pe);
unsigned long shmem_ulong_atomic_fetch_or (unsigned long* target, unsigned long value, int pe);
unsigned long long shmem_ulonglong_atomic_fetch_or (unsigned long long* target, unsigned long long value, int pe);
int32_t shmem_int32_atomic_fetch_or (int32_t* target, int32_t value, int pe);
int64_t shmem_int64_atomic_fetch_or (int64_t* target, int64_t value, int pe);
uint32_t shmem_uint32_atomic_fetch_or (uint32_t* target, uint32_t value, int pe);
uint64_t shmem_uint64_atomic_fetch_or (uint64_t* target, uint64_t value, int pe);

/* Atomic Fetch&Xor */
int shmem_ctx_int_atomic_fetch_xor (shmem_ctx_t ctx, int* target, int value, int pe);
long shmem_ctx_long_atomic_fetch_xor (shmem_ctx_t ctx, long* target, long value, int pe);
long long shmem_ctx_longlong_atomic_fetch_xor (shmem_ctx_t ctx, long long* target, long long value, int pe);
unsigned int shmem_ctx_uint_atomic_fetch_xor (shmem_ctx_t ctx, unsigned int* target, unsigned int value, int pe);
unsigned long shmem_ctx_ulong_atomic_fetch_xor (shmem_ctx_t ctx, unsigned long* target, unsigned long value, int pe);
unsigned long long shmem_ctx_ulonglong_atomic_fetch_xor (shmem_ctx_t ctx, unsigned long long* target, unsigned long long value, int pe);
int32_t shmem_ctx_int32_atomic_fetch_xor (shmem_ctx_t ctx, int32_t* target, int32_t value, int pe);
int64_t shmem_ctx_int64_atomic_fetch_xor (shmem_ctx_t ctx, int64_t* target, int64_t value, int pe);
uint32_t shmem_ctx_uint32_atomic_fetch_xor (shmem_ctx_t ctx, uint32_t* target, uint32_t value, int pe);
uint64_t shmem_ctx_uint64_atomic_fetch_xor (shmem_ctx_t ctx, uint64_t* target, uint64_t value, int pe);

int shmem_int_atomic_fetch_xor (int* target, int value, int pe);
long shmem_long_atomic_fetch_xor (long* target, long value, int pe);
long long shmem_longlong_atomic_fetch_xor (long long* target, long long value, int pe);
unsigned int shmem_uint_atomic_fetch_xor (unsigned int* target, unsigned int value, int pe);
unsigned long shmem_ulong_atomic_fetch_xor (unsigned long* target, unsigned long value, int pe);
unsigned long long shmem_ulonglong_atomic_fetch_xor (unsigned long long* target, unsigned long long value, int pe);
int32_t shmem_int32_atomic_fetch_xor (int32_t* target, int32_t value, int pe);
int64_t shmem_int64_atomic_fetch_xor (int64_t* target, int64_t value, int pe);
uint32_t shmem_uint32_atomic_fetch_xor (uint32_t* target, uint32_t value, int pe);
uint64_t shmem_uint64_atomic_fetch_xor (uint64_t* target, uint64_t value, int pe);

/* Atomic Fetch */
int shmem_ctx_int_atomic_fetch (shmem_ctx_t ctx, const int* target, int pe);
long shmem_ctx_long_atomic_fetch (shmem_ctx_t ctx, const long* target, int pe);
long long shmem_ctx_longlong_atomic_fetch (shmem_ctx_t ctx, const long long* target, int pe);
unsigned int shmem_ctx_uint_atomic_fetch (shmem_ctx_t ctx, const unsigned int* target, int pe);
unsigned long shmem_ctx_ulong_atomic_fetch (shmem_ctx_t ctx, const unsigned long* target, int pe);
unsigned long long shmem_ctx_ulonglong_atomic_fetch (shmem_ctx_t ctx, const unsigned long long* target, int pe);
float shmem_ctx_float_atomic_fetch (shmem_ctx_t ctx, const float* target, int pe);
double shmem_ctx_double_atomic_fetch (shmem_ctx_t ctx, const double* target, int pe);

int shmem_int_atomic_fetch (const int* target, int pe);
long shmem_long_atomic_fetch (const long* target, int pe);
long long shmem_longlong_atomic_fetch (const long long* target, int pe);
unsigned int shmem_uint_atomic_fetch (const unsigned int* target, int pe);
unsigned long shmem_ulong_atomic_fetch (const unsigned long* target, int pe);
unsigned long long shmem_ulonglong_atomic_fetch (const unsigned long long* target, int pe);
float shmem_float_atomic_fetch (const float* target, int pe);
double shmem_double_atomic_fetch (const double* target, int pe);

int shmem_int_fetch (const int* target, int pe);
long shmem_long_fetch (const long* target, int pe);
long long shmem_longlong_fetch (const long long* target, int pe);
float shmem_float_fetch (const float* target, int pe);
double shmem_double_fetch (const double* target, int pe);

/* Atomic Fetch&Inc */
int shmem_ctx_int_atomic_fetch_inc (shmem_ctx_t ctx, int* target, int pe);
long shmem_ctx_long_atomic_fetch_inc (shmem_ctx_t ctx, long* target, int pe);
long long shmem_ctx_longlong_atomic_fetch_inc (shmem_ctx_t ctx, long long* target, int pe);
unsigned int shmem_ctx_uint_atomic_fetch_inc (shmem_ctx_t ctx, unsigned int* target, int pe);
unsigned long shmem_ctx_ulong_atomic_fetch_inc (shmem_ctx_t ctx, unsigned long* target, int pe);
unsigned long long shmem_ctx_ulonglong_atomic_fetch_inc (shmem_ctx_t ctx, unsigned long long* target, int pe);

int shmem_int_atomic_fetch_inc (int* target, int pe);
long shmem_long_atomic_fetch_inc (long* target, int pe);
long long shmem_longlong_atomic_fetch_inc (long long* target, int pe);
unsigned int shmem_uint_atomic_fetch_inc (unsigned int* target, int pe);
unsigned long shmem_ulong_atomic_fetch_inc (unsigned long* target, int pe);
unsigned long long shmem_ulonglong_atomic_fetch_inc (unsigned long long* target, int pe);

int shmem_int_finc (int* target, int pe);
long shmem_long_finc (long* target, int pe);
long long shmem_longlong_finc (long long* target, int pe);

/* Atomic Add */
void shmem_ctx_int_atomic_add (shmem_ctx_t ctx, int* target, int value, int pe);
void shmem_ctx_long_atomic_add (shmem_ctx_t ctx, long* target, long value, int pe);
void shmem_ctx_longlong_atomic_add (shmem_ctx_t ctx, long long* target, long long value, int pe);
void shmem_ctx_uint_atomic_add (shmem_ctx_t ctx, unsigned int* target, unsigned int value, int pe);
void shmem_ctx_ulong_atomic_add (shmem_ctx_t ctx, unsigned long* target, unsigned long value, int pe);
void shmem_ctx_ulonglong_atomic_add (shmem_ctx_t ctx, unsigned long long* target, unsigned long long value, int pe);

void shmem_int_atomic_add (int* target, int value, int pe);
void shmem_long_atomic_add (long* target, long value, int pe);
void shmem_longlong_atomic_add (long long* target, long long value, int pe);
void shmem_uint_atomic_add (unsigned int* target, unsigned int value, int pe);
void shmem_ulong_atomic_add (unsigned long* target, unsigned long value, int pe);
void shmem_ulonglong_atomic_add (unsigned long long* target, unsigned long long value, int pe);


void shmem_int_add (int* target, int value, int pe);
void shmem_long_add (long* target, long value, int pe);
void shmem_longlong_add (long long* target, long long value, int pe);
/* Atomic And */
void shmem_ctx_int_atomic_and (shmem_ctx_t ctx, int* target, int value, int pe);
void shmem_ctx_long_atomic_and (shmem_ctx_t ctx, long* target, long value, int pe);
void shmem_ctx_longlong_atomic_and (shmem_ctx_t ctx, long long* target, long long value, int pe);
void shmem_ctx_uint_atomic_and (shmem_ctx_t ctx, unsigned int* target, unsigned int value, int pe);
void shmem_ctx_ulong_atomic_and (shmem_ctx_t ctx, unsigned long* target, unsigned long value, int pe);
void shmem_ctx_ulonglong_atomic_and (shmem_ctx_t ctx, unsigned long long* target, unsigned long long value, int pe);
void shmem_ctx_int32_atomic_and (shmem_ctx_t ctx, int32_t* target, int32_t value, int pe);
void shmem_ctx_int64_atomic_and (shmem_ctx_t ctx, int64_t* target, int64_t value, int pe);
void shmem_ctx_uint32_atomic_and (shmem_ctx_t ctx, uint32_t* target, uint32_t value, int pe);
void shmem_ctx_uint64_atomic_and (shmem_ctx_t ctx, uint64_t* target, uint64_t value, int pe);

void shmem_int_atomic_and (int* target, int value, int pe);
void shmem_long_atomic_and (long* target, long value, int pe);
void shmem_longlong_atomic_and (long long* target, long long value, int pe);
void shmem_uint_atomic_and (unsigned int* target, unsigned int value, int pe);
void shmem_ulong_atomic_and (unsigned long* target, unsigned long value, int pe);
void shmem_ulonglong_atomic_and (unsigned long long* target, unsigned long long value, int pe);
void shmem_int32_atomic_and (int32_t* target, int32_t value, int pe);
void shmem_int64_atomic_and (int64_t* target, int64_t value, int pe);
void shmem_uint32_atomic_and (uint32_t* target, uint32_t value, int pe);
void shmem_uint64_atomic_and (uint64_t* target, uint64_t value, int pe);

/* Atomic Or */
void shmem_ctx_int_atomic_or (shmem_ctx_t ctx, int* target, int value, int pe);
void shmem_ctx_long_atomic_or (shmem_ctx_t ctx, long* target, long value, int pe);
void shmem_ctx_longlong_atomic_or (shmem_ctx_t ctx, long long* target, long long value, int pe);
void shmem_ctx_uint_atomic_or (shmem_ctx_t ctx, unsigned int* target, unsigned int value, int pe);
void shmem_ctx_ulong_atomic_or (shmem_ctx_t ctx, unsigned long* target, unsigned long value, int pe);
void shmem_ctx_ulonglong_atomic_or (shmem_ctx_t ctx, unsigned long long* target, unsigned long long value, int pe);
void shmem_ctx_int32_atomic_or (shmem_ctx_t ctx, int32_t* target, int32_t value, int pe);
void shmem_ctx_int64_atomic_or (shmem_ctx_t ctx, int64_t* target, int64_t value, int pe);
void shmem_ctx_uint32_atomic_or (shmem_ctx_t ctx, uint32_t* target, uint32_t value, int pe);
void shmem_ctx_uint64_atomic_or (shmem_ctx_t ctx, uint64_t* target, uint64_t value, int pe);

void shmem_int_atomic_or (int* target, int value, int pe);
void shmem_long_atomic_or (long* target, long value, int pe);
void shmem_longlong_atomic_or (long long* target, long long value, int pe);
void shmem_uint_atomic_or (unsigned int* target, unsigned int value, int pe);
void shmem_ulong_atomic_or (unsigned long* target, unsigned long value, int pe);
void shmem_ulonglong_atomic_or (unsigned long long* target, unsigned long long value, int pe);
void shmem_int32_atomic_or (int32_t* target, int32_t value, int pe);
void shmem_int64_atomic_or (int64_t* target, int64_t value, int pe);
void shmem_uint32_atomic_or (uint32_t* target, uint32_t value, int pe);
void shmem_uint64_atomic_or (uint64_t* target, uint64_t value, int pe);

/* Atomic Xor */
void shmem_ctx_int_atomic_xor (shmem_ctx_t ctx, int* target, int value, int pe);
void shmem_ctx_long_atomic_xor (shmem_ctx_t ctx, long* target, long value, int pe);
void shmem_ctx_longlong_atomic_xor (shmem_ctx_t ctx, long long* target, long long value, int pe);
void shmem_ctx_uint_atomic_xor (shmem_ctx_t ctx, unsigned int* target, unsigned int value, int pe);
void shmem_ctx_ulong_atomic_xor (shmem_ctx_t ctx, unsigned long* target, unsigned long value, int pe);
void shmem_ctx_ulonglong_atomic_xor (shmem_ctx_t ctx, unsigned long long* target, unsigned long long value, int pe);
void shmem_ctx_int32_atomic_xor (shmem_ctx_t ctx, int32_t* target, int32_t value, int pe);
void shmem_ctx_int64_atomic_xor (shmem_ctx_t ctx, int64_t* target, int64_t value, int pe);
void shmem_ctx_uint32_atomic_xor (shmem_ctx_t ctx, uint32_t* target, uint32_t value, int pe);
void shmem_ctx_uint64_atomic_xor (shmem_ctx_t ctx, uint64_t* target, uint64_t value, int pe);

void shmem_int_atomic_xor (int* target, int value, int pe);
void shmem_long_atomic_xor (long* target, long value, int pe);
void shmem_longlong_atomic_xor (long long* target, long long value, int pe);
void shmem_uint_atomic_xor (unsigned int* target, unsigned int value, int pe);
void shmem_ulong_atomic_xor (unsigned long* target, unsigned long value, int pe);
void shmem_ulonglong_atomic_xor (unsigned long long* target, unsigned long long value, int pe);
void shmem_int32_atomic_xor (int32_t* target, int32_t value, int pe);
void shmem_int64_atomic_xor (int64_t* target, int64_t value, int pe);
void shmem_uint32_atomic_xor (uint32_t* target, uint32_t value, int pe);
void shmem_uint64_atomic_xor (uint64_t* target, uint64_t value, int pe);

/* Atomic Inc */
void shmem_ctx_int_atomic_inc (shmem_ctx_t ctx, int* target, int pe);
void shmem_ctx_long_atomic_inc (shmem_ctx_t ctx, long* target, int pe);
void shmem_ctx_longlong_atomic_inc (shmem_ctx_t ctx, long long* target, int pe);
void shmem_ctx_uint_atomic_inc (shmem_ctx_t ctx, unsigned int* target, int pe);
void shmem_ctx_ulong_atomic_inc (shmem_ctx_t ctx, unsigned long* target, int pe);
void shmem_ctx_ulonglong_atomic_inc (shmem_ctx_t ctx, unsigned long long* target, int pe);

void shmem_int_atomic_inc (int* target, int pe);
void shmem_long_atomic_inc (long* target, int pe);
void shmem_longlong_atomic_inc (long long* target, int pe);
void shmem_uint_atomic_inc (unsigned int* target, int pe);
void shmem_ulong_atomic_inc (unsigned long* target, int pe);
void shmem_ulonglong_atomic_inc (unsigned long long* target, int pe);

void shmem_int_inc (int* target, int pe);
void shmem_long_inc (long* target, int pe);
void shmem_longlong_inc (long long* target, int pe);
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
