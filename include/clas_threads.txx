# ifndef clas_threads_txx
# define clas_threads_txx
# include <thread>
# include <iostream>
using namespace std;
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
/*
	td = thread load array (minimum size = mt)
	n  = total load count
	mt = maximum number of threads to use (default 1)
	md = preferred minimum load per thread (default 1)
	outputs to td with thread per load and returns number of threads with loads.
*/
template <class U>
static inline U set_thread_load(U* td, volatile U n, U mt = 1, U md = 1) { 

	U i, f, R, D, Ur;
	double d, r, q;

	if (n < md * mt) {
		f = (U)0;
		R = (U)0;
		while (R < n) {
			*(td+f) = R + md > n ? n - R : md;
			R += *(td+f++);
		}
	}
	else {
		q = (double)(n)/(double)(mt);
		f = (U)0;
		R = (U)0;
		r = 0.;
		while (R < n) {
			r += q;
			d = r - (double)(R);
			D = (U)(d);
			if (R + D >= n) {
				*(td+f) = n - R;
			}
			else {
				*(td+f) = d >= ((double)(D) + 0.5) ? D + 1 : D;
			}
			R += *(td+f++);
		}
	}
	for (i = f; i<mt; i++) {
		*(td+i) = 0;
	}
	return (f);
}

//------------------------------------------------------------------------------
#endif

