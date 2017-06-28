# ifndef clas_unroll_txx
# define clas_unroll_txx

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
#endif

