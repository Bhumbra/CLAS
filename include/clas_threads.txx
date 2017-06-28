# ifndef clas_threads_txx
# define clas_threads_txx
# include <thread>
//------------------------------------------------------------------------------
template <class U>
static inline U set_num_threads(volatile U NT = 0) { 
	U nt = std::thread::hardware_concurrency();
	if (!nt) {
		nt = NT ? NT : (U)1;
	}
	else {
		if ((NT) && (NT < nt)) {
			nt = NT;
		}
	}
	return(nt);
}

//------------------------------------------------------------------------------
#endif

