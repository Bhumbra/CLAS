# ifndef clas_cache_txx
# define clas_cache_txx

# define DEF_CACHE_LINE_SIZE 64

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
#endif

