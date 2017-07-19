# ifndef clas_unroll_txx
# define clas_unroll_txx

# define DEF_OUTER_UNROLL_MAX 8
# define DEF_INNER_UNROLL_MAX 32
# define DEF_UNROLL_MAX 32


//------------------------------------------------------------------------------
template <class U>
static inline U set_unroll(volatile U UR = 0, volatile U URM = 0) { 
	U ur = (URM > 0 && URM < DEF_UNROLL_MAX) ? URM : DEF_UNROLL_MAX;
	if (!URM) {
		while (ur > UR) {
			ur >>= 1;
		}
	}
	return(ur);
}

//------------------------------------------------------------------------------
template <class U>
static inline U set_outer_unroll(volatile U UR = 0, volatile U URM = 0) { 
	U ur = (URM > 0 && URM < DEF_OUTER_UNROLL_MAX) ? URM : DEF_OUTER_UNROLL_MAX;
	if (!URM) {
		while (ur > UR) {
			ur >>= 1;
		}
	}
	return(ur);
}

//------------------------------------------------------------------------------
template <class U>
static inline U set_inner_unroll(volatile U UR = 0, volatile U URM = 0) { 
	U ur = (URM > 0 && URM < DEF_INNER_UNROLL_MAX) ? URM : DEF_INNER_UNROLL_MAX;
	if (!URM) {
		while (ur > UR) {
			ur >>= 1;
		}
	}
	return(ur);
}

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

