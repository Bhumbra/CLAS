#ifndef _products_mt_txx
#define _products_mt_txx
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
# include "_products_ut.txx"
# include "clas_threads.txx"


//------------------------------------------------------------------------------
# define DEF_RMDOT_THREAD_LOAD_MIN_LO 1 // default minimum if m <= TC*num_threads
# define DEF_RMDOT_THREAD_LOAD_MIN_HI 8 // default minimum otherwise
# define DEF_RMDOT_THREAD_LOAD_MIN_TC 1 // TC (i.e. thresholding coefficient)

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/* ewise:
   C = A .* B
*/
//------------------------------------------------------------------------------
/* ewise:
   C = A .* B
*/
template <class T, class U>
static void ewise_product_mt (T* Out, 
															T* In0, 
															T* In1, 
															volatile const U m, 
															volatile const U k, 
															volatile const U Outs = 0,
															volatile const U In0s = 0,
															volatile const U In1s = 0,
															volatile U U1 = 0) { 
	ewise_product_mt(Out, In0, In1, m, k, Outs, In0s, In1s, U1);
}

//------------------------------------------------------------------------------
/* outer:
   C   = a * b.T
	 C.T = a * b.T
*/
template <class T, class U>
static inline void outer_product_mt(T* Out, 
																		T* In0, 
																		T* In1, 
																		volatile const U m, 
																		volatile const U n,
																		volatile const U Outs = 0,
																		volatile const U In0s = 0,
																		volatile const U In1s = 0,
																		volatile U U1 = 0) { 
	outer_product_mt(Out, In0, In1, m, n, Outs, In0s, In1s, U1);
}
//------------------------------------------------------------------------------
/* inner:
  c   = a.T * b
	c.T = a.T * b
*/
template <class T, class U>
static inline void inner_product_mt(T* Out, 
																		T* In0, 
																		T* In1, 
																		volatile const U m, 
																		volatile const U k, 
																		volatile const U Outs = 1, 
																		volatile U In0s = 1, 
																		volatile U In1s = 1, 
																		T* In2 = 0,
																		volatile U U1 = 0) {
	inner_product_mt(Out, In0, In1, m, k, Outs, In0s, In1s, In2, U1);
}


//------------------------------------------------------------------------------
template <class T, class U>
static inline void rmdot_product_mt(T* Out, 
																		T* In0, 
																		T* In1, 
																		volatile const U m, 
																		volatile const U k,
																		volatile const U n, 
																		T* In2  = 0,
																		volatile const bool In2Tr = false,
																		volatile U U0 = 0,
																		volatile U U1 = 0,
																		volatile U NT = 0,
																		volatile U Arch = 0) { 
	if (NT == (U)-1) {
		return rmdot_product_ut(Out, In0, In1, m, k, n, In2, In2Tr, U0, U1, Arch);
	} 

	U f, g, h;
	volatile U In2S = (U)0;
	volatile U In2s = (U)0;
	volatile U OutS, In0S, In0s, In1s;

	if (In2) {
		if (!In2Tr) {
			In2S = (U)1;
		}
		else {
			In2s = (U)1;
		}
	}

	OutS = n;
	In0S = k;
	In0s = (U)1;
	In1s = n;

	U nt = set_num_threads(NT);
	U tc = U0 ? U0 : (U)DEF_RMDOT_THREAD_LOAD_MIN_TC;
	U md = m <= tc * nt ? (U)DEF_RMDOT_THREAD_LOAD_MIN_LO : (U)DEF_RMDOT_THREAD_LOAD_MIN_HI;
	U* td = new U[nt];
	U Nt = set_thread_load(td, m, nt, md);
	std::thread th[Nt];
	
	for (f = 0, h = 0; f<Nt; f++, h += g) {
		g = td[f];
		th[f] = std::thread(vmdot_product<T,U>, Out+h*n, In0+h*In0S, In1, g, k, n, OutS, In0S, In0s, In1s, In2+h*In2S, In2S, In2s, U0, U1, Arch);
	}
	for (f = 0; f<Nt; f++) {
		th[f].join();
	}

	delete (td);
}
//------------------------------------------------------------------------------
template <class T, class U>
static inline void cmdot_product_mt(T* Out, 
																		T* In0, 
																		T* In1, 
																		volatile const U m, 
																		volatile const U k,
																		volatile const U n, 
																		T* In2 = 0,
																		volatile const bool In2Tr = false,
																		volatile U U0 = 0,
																		volatile U U1 = 0,
																		volatile U NT = 0,
																		volatile U Arch = 0) { 
	if (NT == (U)-1) {
		return cmdot_product_ut(Out, In0, In1, m, k, n, In2, In2Tr, U0, U1, Arch);
	} 

	U f, g, h;
	volatile U In2S = (U)0;
	volatile U In2s = (U)0;
	volatile U OutS, In0S, In0s, In1s;

	if (In2) {
		if (!In2Tr) {
			In2S = (U)1;
		}
		else {
			In2s = (U)1;
		}
	}

	OutS = n;
	In0S = (U)1;
	In0s = m;
	In1s = n;

	U nt = set_num_threads(NT);
	U* td = new U[nt];
	U Nt = set_thread_load(td, m, nt);
	std::thread th[Nt];
	
	for (f = 0, h = 0; f<Nt; f++, h += g) {
		g = td[f];
		th[f] = std::thread(vmdot_product<T,U>, Out+h*n, In0+h*In0S, In1, g, k, n, OutS, In0S, In0s, In1s, In2+h*In2S, In2S, In2s, U0, U1, Arch);
	}
	for (f = 0; f<Nt; f++) {
		th[f].join();
	}

	delete (td);
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mrdot_product_mt(T* Out, 
																		T* _In0, 
																		T* _In1, 
																		volatile const U _m, 
																		volatile const U k,
																		volatile const U _n, 
																		volatile const bool OutCm = false,
																		volatile const bool InpSw = false,
																		T* In2 = 0,
																		volatile U U0 = 0,
																		volatile U U1 = 0,
																		volatile U NT = 0) { 
	if (NT == (U)-1) {
		return mrdot_product_ut(Out, _In0, _In1, _m, k, _n, OutCm, InpSw, In2, U0, U1);
	} 

	T *In0, *In1;
	U m, n;
	volatile U OutS, Outs, In0s, In1s;
	volatile U In2S, In2s;

	In0s = k;
	In1s = k;
	In2S = (U)0;
	In2s = (U)0;

	if (!InpSw) {
		In0 = _In0;
		In1 = _In1;
		m = _m;
		n = _n;
		if (In2) {In2s = (U)1;}
	}
	else {
		In0 = _In1;
		In1 = _In0;
		m = _n;
		n = _m;
		if (In2) {In2S = (U)1;}
	}
	if (!OutCm) {
		OutS = (U)1;
		Outs = _n;
	}
	else {
		OutS = m;
		Outs = (U)1;
	}

	U f, g, h;
	U nt = set_num_threads(NT);
	U* td = new U[nt];
	U Nt = set_thread_load(td, n, nt);
	std::thread th[Nt];
	for (f = 0, h = 0; f<Nt; f++, h += g) {
		g = td[f];
		th[f] = std::thread(mrdot_product<T,U>, Out+h*OutS, In0, In1+h*k, m, k, g, OutS, Outs, In0s, In1s, In2+h*In2S, In2S, In2s, U0, U1);
	}
	for (f = 0; f<Nt; f++) {
		th[f].join();
	}
	delete (td);
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mcdot_product_mt(T* Out, 
																		T* _In0, 
																		T* _In1, 
																		volatile const U _m, 
																		volatile const U k,
																		volatile const U _n, 
																		volatile const bool OutCm = false,
																		volatile const bool InpSw = false,
																		T* In2 = 0,
																		volatile U U0 = 0,
																		volatile U U1 = 0,
																		volatile U NT = 0) { 
	if (NT == (U)-1) {
		return mcdot_product_ut(Out, _In0, _In1, _m, k, _n, OutCm, InpSw, In2, U0, U1);
	} 
	T *In0, *In1;
	U m, n;
	volatile U OutS, Outs, In0s, In1s;
	volatile U In2S, In2s;

	In0s = k;
	In2S = (U)0;
	In2s = (U)0;

	if (!InpSw) {
		In0 = _In0;
		In1 = _In1;
		m = _m;
		n = _n;
		In1s = _n;
		if (In2) {In2s = (U)1;}
	}
	else {
		In0 = _In1;
		In1 = _In0;
		m = _n;
		n = _m;
		In1s = _m;
		if (In2) {In2S = (U)1;}
	}
	if (!OutCm) {
		OutS = (U)1;
		Outs = _n;
	}
	else {
		OutS = m;
		Outs = (U)1;
	}
	U f, g, h;
	U nt = set_num_threads(NT);
	U* td = new U[nt];
	U Nt = set_thread_load(td, n, nt);
	std::thread th[Nt];
	
	for (f = 0, h = 0; f<Nt; f++, h += g) {
		g = td[f];
		th[f] = std::thread(mcdot_product<T,U>, Out+h*OutS, In0, In1+h, m, k, g, OutS, Outs, In0s, In1s, In2+h*In2S, In2S, In2s, U0, U1);
	}
	for (f = 0; f<Nt; f++) {
		th[f].join();
	}
	delete (td);
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mmdot_product_mt(T* Out, 
																		T* In0, 
																		T* In1, 
																		volatile const U m, 
																		volatile const U k,
																		volatile const U n,
																		volatile bool OutCm = false,
																		volatile bool In0Cm = false,
																		volatile bool In1Cm = false,
																		volatile bool r2c = false,
																		T* In2 = 0,
																		volatile U U0 = 0,
																		volatile U U1 = 0,
																		volatile U const UD = 0,
																	 	volatile U NT = 0,
																		volatile U const Arch = 0) { 
	if (NT == (U)-1) {
		return mmdot_product_ut(Out, In0, In1, m, k, n, OutCm, In0Cm, In1Cm, r2c, In2, U0, U1, UD, Arch);
	}

	if (r2c) {
		OutCm = !OutCm;
		In0Cm = !In0Cm;
		In1Cm = !In1Cm;
	}
	// Scalar/vector outputs fast-track

	if (UD < 2) {
		if (m == 1) {        // out can only be a scalar or vector
			if (n == 1) {      // out is a scalar
				return inner_product_mt(Out, In0, In1, m, k, (U)1, (U)0, (U)0, In2, U1);
			}                  // otherwise out is a vector
			else if (!In1Cm) { // untranposed multiple: vector = vector * matrix
				return rmdot_product_mt(Out, In0, In1, m, k, n, In2, false, U0, U1, Arch);
			}
			else {             // transposed multiple:  inner product
				return inner_product_mt(Out, In0, In1, n, k, (U)1, (U)0, k, In2, U1);
			}      
		}
		
		if (n == 1) {        // out can only be a vector
			if (!In0Cm) {      // untranposed multiplicand: 
				return inner_product_mt(Out, In0, In1, m, k, n, k, (U)0, In2, U1);
			}
			else {             // tranposed multiplicand - inner product of swapped inputs
				return cmdot_product_mt(Out, In0, In1, m, k, n, In2, false, U0, U1, Arch);
			}
		}

		// Outer products 
		if (k == 1) {     
			if (!In2) {        // No maxuend
				if (!OutCm) {    // untransposed product
					return outer_product_mt(Out, In0, In1, m, n, n, (U)1, (U)0, U1);
				}
				else {           // transposed product - outer product of swapped inputs
					return outer_product_mt(Out, In1, In0, n, m, m, (U)1, (U)0, U1);
				}
			}
			else {             // Have maxuend
				return mrdot_product_mt(Out, In0, In1, m, (U)1, n, OutCm, false, In2, U0, U1);
			}
		}
	}

	//  matrix = matrix * matrix with 8 transposition permutations

	if (!OutCm) {        // Untransposed product
		if (!In0Cm) {      // Untransposed multiplicand
			if (!In1Cm) {    // Untransposed multiple
				if (UD == 3) {
					return mcdot_product_mt(Out, In0, In1, m, k, n, OutCm, false, In2, U0, U1, NT);
				}
				else {
					return rmdot_product_mt(Out, In0, In1, m, k, n, In2, false, U0, U1, NT, Arch);
				}
			}
			else {           // Transposed multiple
				return mrdot_product_mt(Out, In0, In1, m, k, n, OutCm, false, In2, U0, U1, NT);
			}
		}
		else {             // Transposed multiplicand
			if (!In1Cm) {    // Untransposed multiple
				return cmdot_product_mt(Out, In0, In1, m, k, n, In2, false, U0, U1, NT, Arch);
			}
			else {           // Tranposed multiple
				// C = A.T * B.T => C.T = B * A
				return mcdot_product_mt(Out, In0, In1, m, k, n, true, true, In2, U0, U1, NT);
			}
		}
	}
	else {               // Transposed product
		if (!In0Cm) {      // Untransposed multiplicand
			if (!In1Cm) {    // Untransposed multiple
				return mcdot_product_mt(Out, In0, In1, m, k, n, OutCm, false, In2, U0, U1, NT);
			}
			else {           // Transposed multiple
				return mrdot_product_mt(Out, In0, In1, m, k, n, OutCm, false, In2, U0, U1, NT);
			}
		}
		else {             // Transposed multiplicand
			if (!In1Cm) {    // Untransposed multiple
				// C.T = A.T * B => C = B.T * A
				return cmdot_product_mt(Out, In1, In0, n, k, m, In2, true, U0, U1, NT, Arch);
			}
			else {           // Transposed multiple
				// C.T = A.T * B.T => C = B * A
				if (UD == 3) {
					return mcdot_product_mt(Out, In0, In1, m, k, n, false, true, In2, U0, U1, NT);
				}
				else {
					return rmdot_product_mt(Out, In1, In0, n, k, m, In2, true, U0, U1, NT, Arch);
				}
			}
		}
	}
}
//------------------------------------------------------------------------------
#endif
