# ifndef clas_unroll_txx
# define clas_unroll_txx

# define DEF_OUTER_UNROLL 8
# define DEF_INNER_UNROLL 8
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
#endif

