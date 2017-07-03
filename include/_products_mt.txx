#ifndef _products_mt_txx
#define _products_mt_txx
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
# include "_products_ut.txx"
# include "clas_threads.txx"

//------------------------------------------------------------------------------

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
																		volatile U NT = 0) { 
	if (NT == (U)-1) {
		return rmdot_product_ut(Out, In0, In1, m, k, n, In2, U0, U1);
	} 
	U nt = set_num_threads(NT);
	U In2s = In2 ? (U)1 : (U)0;
	U e, f, g, h;
	e = m % nt ? m / nt + 1 : m / nt;
	f = m % e  ? m / e  + 1 : m / e;
	std::thread th[f];
	
	for (g = 0, h = 0; g<f; g++, h += e) {
		if (h + e > m) {e = m - h;}  
		th[g] = std::thread(rmdot_product_ut<T,U>, Out+h*n, In0+h*k, In1, e, k, n, In2+In2s*h, In2Tr, U0, U1);
	}
	for (g = 0; g<f; g++) {
		th[g].join();
	}
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
																		volatile U NT = 0) { 
	if (NT == (U)-1) {
		return cmdot_product_ut(Out, In0, In1, m, k, n, In2, In2Tr, U0, U1);
	} 
	return cmdot_product_ut(Out, In0, In1, m, k, n, In2, In2Tr, U0, U1);
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mrdot_product_mt(T* Out, 
																		T* In0, 
																		T* In1, 
																		volatile const U m, 
																		volatile const U k,
																		volatile const U n, 
																		volatile const bool OutCm = false,
																		T* In2 = 0,
																		volatile U U0 = 0,
																		volatile U U1 = 0,
																		volatile U NT = 0) { 
	if (NT == (U)-1) {
		return mrdot_product_ut(Out, In0, In1, m, k, n, OutCm, In2, U0, U1);
	} 
	return mrdot_product_ut(Out, In0, In1, m, k, n, OutCm, In2, U0, U1);
}
//------------------------------------------------------------------------------
template <class T, class U>
static inline void mcdot_product_mt(T* Out, 
																		T* In0, 
																		T* In1, 
																		volatile const U m, 
																		volatile const U k,
																		volatile const U n, 
																		volatile const bool OutCm = false,
																		T* In2 = 0,
																		volatile U U0 = 0,
																		volatile U U1 = 0,
																		volatile U NT = 0) { 
	if (NT == (U)-1) {
		return mcdot_product_ut(Out, In0, In1, m, k, n, OutCm, In2, U0, U1);
	} 
	return mcdot_product_ut(Out, In0, In1, m, k, n, OutCm, In2, U0, U1);
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
																	 	volatile U NT = 0) { 
	if (NT == (U)-1) {
		return mmdot_product_ut(Out, In0, In1, m, k, n, OutCm, In0Cm, In1Cm, r2c, In2, U0, U1);
	}

	if (r2c) {
		OutCm = !OutCm;
		In0Cm = !In0Cm;
		In1Cm = !In1Cm;
	}

  // Scalar/vector outputs fast-track

	if (m == 1) {       // out can only be a scalar or vector
		if (n == 1) {     // out is a scalar
			return inner_product_mt(Out, In0, In1, m, k, (U)1, (U)0, (U)0, In2, U1);
		}                 // otherwise out is a vector
		else if (!In1Cm) { // untranposed multiple: vector = vector * matrix
			return rmdot_product_mt(Out, In0, In1, m, k, n, In2, U0, U1);
		}
		else {            // transposed multiple:  inner product  		  
			return inner_product_mt(Out, In0, In1, n, k, (U)1, (U)0, k, In2, U1);
		}      
	}
	
	if (n == 1) {       // out can only be a vector
		if (!In0Cm) {      // untranposed multiplicand: 
			return inner_product_mt(Out, In0, In1, m, k, n, k, (U)0, In2, U1);
		}
		else {            // tranposed multiplicand - inner product of swapped inputs
			return mrdot_product_mt(Out, In0, In1, m, k, n, OutCm, In2, U0, U1);
		}
	}

	// Outer products without maxuend fast-track
	if (k == 1) {     
		if (!In2) {       // No maxuend
			if (!OutCm) {    // untransposed product
				return outer_product_mt(Out, In0, In1, m, n, n, (U)1, (U)0, U1);
			}
			else {          // transposed product - outer product of swapped inputs
				return outer_product_mt(Out, In1, In0, n, m, m, (U)1, (U)0, U1);
			}
		}
		else {            // Have maxuend
			if (!OutCm) {    // untransposed product
				return mrdot_product_mt(Out, In0, In1, (U)m, (U)1, (U)1, OutCm, In2, U0, U1);
			}
			else {          // transposed outer product
				return mrdot_product_mt(Out, In0, In1, (U)m, (U)1, (U)1, OutCm, In2, U0, U1);
			}
		}
	}

	if (!OutCm) {        // Untransposed product
		if (!In0Cm) {      // Untransposed multiplicand
			if (!In1Cm) {    // Untransposed multiple
				return rmdot_product_mt(Out, In0, In1, m, k, n, In2, U0, U1, NT);
			}
			else {          // Tranposed multiple
				return mrdot_product_mt(Out, In0, In1, m, k, n, OutCm, In2, U0, U1, NT);
			}
		}
		else {            // Transposed multiplicand
			if (!In1Cm) {    // Untransposed multiple
				return;
			}
			else {          // Transposed multiple
				return;
			}
		}
	}
	else {              // Transposed product
		if (!In0Cm) {      // Untransposed multiplicand
			if (!In1Cm) {    // Untransposed multiple
				return;
			}
			else {          // Transposed multiple
				return mrdot_product_mt(Out, In0, In1, m, k, n, OutCm, In2, U0, U1, NT);
			}
		}
	  else {            // Transposed multiplicand
			if (!In1Cm) {    // Untransposed multiple
				return;
			}
			else {          // Transposed multiple
				return;
			}
		}
	}
}
//------------------------------------------------------------------------------
#endif
