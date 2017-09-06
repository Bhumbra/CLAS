# ifndef clas_threads_txx
# define clas_threads_txx
# include <thread>
//------------------------------------------------------------------------------
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
	dm = preferred divisor load per through (default md)
	outputs to td with thread per load and returns number of threads with loads.
*/
template <class U>
static inline U set_thread_load(U* td, volatile U n, U mt = 1, U md = 1, U dm = 0) { 

	if (!dm) {dm = md;}
	U i, f, R, D;
	double d, r, q;

	if (n < md * mt) {
		f = (U)0;
		R = (U)0;
		while (R < n) {
			*(td+f) = R + md > n ? n - R : md;
			R += *(td+f++);
		}
	}
	else if (md < 2) {
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
	else {
		D = n / mt;
		if (n % D) {D ++;}
		R = D % dm;
		if (D <= md) {
			D = md;
			while (D*mt < n) {
				D += dm;
			}
		}
		else if (R) {
			D += (dm - R);
		}
		f = (U)0;
		R = (U)0;
		while (R < n) {
			*(td+f) = R + D > n ? n - R : D;
			R += *(td+f++);
		}
	}
	for (i = f; i<mt; i++) {
		*(td+i) = 0;
	}
	return (f);
}
//------------------------------------------------------------------------------
template <class T, class U>
static inline U set_max_threads(U MT = (U)0, T FT = (T)1.) { 
	U NT;
	U TT = std::thread::hardware_concurrency();

	MT = (!MT || MT > TT) ? TT : MT;
	if (FT <= 0.) {
		NT = 0.;
		return(NT);
	}
	else if (FT >= 1.) {
		NT = MT;
		return(NT);
	}

	NT = (U) (FT * (T)MT);
	if (NT <= 0) {
		NT = (U)1;
		return (NT);
	}
	else if (NT > MT) {
		NT = MT;
		return (NT);
	}
	return (NT);
}	


//------------------------------------------------------------------------------
#endif

