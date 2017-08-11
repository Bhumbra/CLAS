# ifndef clas_cache_txx
# define clas_cache_txx

//------------------------------------------------------------------------------
# include "clas_defs.h"

// A possible vmdot read cache scheme (for thread-safety do not cache OUT):
// Fast: out(8), In0 (8x64x2)     , In1T (64x8)         - 12352
// Slow: out(8*_8), In0 ([_8x8]x64x2), In1T (64x[8x_8]) - 98816
// Shared: In1

//------------------------------------------------------------------------------
#	define PREFETCH_TO_SHARED_CACHE     1 // Effect on cache misses probably homeopathic

	
//------------------------------------------------------------------------------
# define DEF_FAST_CACHE_PER_THREAD    16384  //  DATA ONLY
# define DEF_SLOW_CACHE_PER_THREAD    114688 // (SLOW (131072) - FAST)
# define DEF_SHARED_CACHE_PER_THREAD  901120 // (SHARED (1048576) - (SLOW+FAST))
# define DEF_CACHE_LINE_SIZE          64
# define DEF_LOG2_CACHE_LINE_SIZE     6
# define DEF_LOG2_DOUBLE_SIZE         3

//------------------------------------------------------------------------------
template <class T, class U>
static inline U next_aligned_index(const T* x, const U u, const U M = 0) { 
	// returns index from x to be aligned by u up to a maximum of M (if entered)
	U m = (uint64_t)(x)/sizeof(T) % u;
	if (!m) {return(0);}
	U d = u - m;
	if (M && d >= M) {return(0);}
	return(d);
}

//------------------------------------------------------------------------------

// RW = 0 (read), 1 (write)
// LOCALITY = 0(NTA), 1(L3), 2(L2), 3(L1)

# define PREFETCH_DOUBLE_3(PREFETCH_ADDR, PREFETCH_RW, PREFETCH_LOCALITY)      \
	__builtin_prefetch (ALIGNED_ADDR, PREFETCH_RW, PREFETCH_LOCALITY);           \

# define PREFETCH_DOUBLE_4(PREFETCH_ADDR, PREFETCH_RW, PREFETCH_LOCALITY, PREFETCH_LENGTH) \
	{                                                                            \
		uint64_t DOUBLE_CACHE_LINE_SIZE;                                           \
		uint64_t CACHE_STEPS;                                                      \
		uint64_t ALIGNED_INDEX;                                                    \
		double*  ALIGNED_ADDR;                                                     \
		DOUBLE_CACHE_LINE_SIZE = DEF_CACHE_LINE_SIZE >> DEF_LOG2_DOUBLE_SIZE;      \
		CACHE_STEPS = (uint64_t)PREFETCH_LENGTH >> DEF_LOG2_CACHE_LINE_SIZE;       \
		ALIGNED_INDEX = next_aligned_index(PREFETCH_ADDR, DOUBLE_CACHE_LINE_SIZE); \
		ALIGNED_ADDR = PREFETCH_ADDR + ALIGNED_INDEX;                              \
		if (ALIGNED_INDEX && CACHE_STEPS) {CACHE_STEPS -= 1;}                      \
		for (; CACHE_STEPS; CACHE_STEPS--) {                                       \
			PREFETCH_DOUBLE_3(ALIGNED_ADDR, PREFETCH_RW, PREFETCH_LOCALITY);         \
			ALIGNED_ADDR += DOUBLE_CACHE_LINE_SIZE;                                  \
		}                                                                          \
	}                                                                            

# define PREFETCH_DOUBLE_2(PREFETCH_ADDR, PREFETCH_RW)                         \
	PREFETCH_DOUBLE_3(PREFETCH_ADDR, PREFETCH_RW, 3)

# define PREFETCH_DOUBLE_1(PREFETCH_ADDR)                                      \
	PREFETCH_DOUBLE_2(PREFETCH_ADDR, 0)

# define PREFETCH_DOUBLE_N(NARGS, PREFETCH_ADDR, PREFETCH_RW,                  \
	PREFETECH_LOCALITY, PREFETCH_LENGTH, PREFETCH_DOUBLE_M, ...)                 \
	PREFETCH_DOUBLE_M

# define PREFETCH_DOUBLE(...) \
	PREFETCH_DOUBLE_N(, ##__VA_ARGS__,                                           \
		PREFETCH_DOUBLE_4(__VA_ARGS__),                                            \
		PREFETCH_DOUBLE_3(__VA_ARGS__),                                            \
		PREFETCH_DOUBLE_2(__VA_ARGS__),                                            \
		PREFETCH_DOUBLE_1(__VA_ARGS__)) 

//------------------------------------------------------------------------------
template <class U>
static inline U shared_read_cache_prefetch_double_cols( double* X, 
																												const U nr, 
																												const U nc, 
																												const U maxbytes = DEF_SHARED_CACHE_PER_THREAD) { 
	
	// caches the first N cols of all rows of x,
	// where N depends on maxbytes (default to 1MB whereas 0 denotes no maximum)
	// returns the number of cols cached.

	if (!PREFETCH_TO_SHARED_CACHE) {return ((U)0);}

	U i, cols, maxcols;
	cols = nc;
	if (maxbytes && nr) {
		maxcols = (maxbytes >> DEF_LOG2_DOUBLE_SIZE) / nr;
		if (cols > maxcols) {cols = maxcols;}
	}
	double* x = X;
	for (i = nr; i; i--) {
		PREFETCH_DOUBLE(x, 0, 1, cols)
	}

	return(cols);
}

//------------------------------------------------------------------------------
# endif

