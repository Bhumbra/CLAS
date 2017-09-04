# ifndef _products_ut_txx
# define _products_ut_txx
//------------------------------------------------------------------------------
# include <math.h>
# include <functional>
# include <algorithm>

//------------------------------------------------------------------------------
# include "clas_unroll.txx"
# define DEF_MCDOT_OUTER_UNROLL_MAX DEF_OUTER_UNROLL_MAX
# define DEF_MCDOT_INNER_UNROLL_MAX DEF_INNER_UNROLL_MAX
# define DEF_MCDOT_OUTER_UNROLL DEF_OUTER_UNROLL
# define DEF_MCDOT_INNER_UNROLL DEF_INNER_UNROLL

//------------------------------------------------------------------------------
# include "_replicate.txx"
# include "_ewise_product.txx"
# include "_outer_product.txx"
# include "_inner_product.txx"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/* ewise:
   C = A .* B
*/
template <class T, class U>
static void ewise_product_ut (T* Out, 
															T* In0, 
															T* In1, 
															volatile const U m, 
															volatile const U k, 
															volatile const U Outs = 0,
															volatile const U In0s = 0,
															volatile const U In1s = 0,
															volatile U U1 = 0) { 

	register U u1 = set_unroll((U)sqrt(k), U1);

	switch (u1) {
		case 1: {
			return ewise_product_1(Out, In0, In1, m, k, Outs, In0s, In1s); 
		}
		case 2: {
			return ewise_product_2(Out, In0, In1, m, k, Outs, In0s, In1s); 
		}
		case 4: {
			return ewise_product_4(Out, In0, In1, m, k, Outs, In0s, In1s); 
		}
		case 8: {
			return ewise_product_8(Out, In0, In1, m, k, Outs, In0s, In1s); 
		}
		default: {
			return ewise_product_16(Out, In0, In1, m, k, Outs, In0s, In1s); 
		}
	}
}

//------------------------------------------------------------------------------
/* outer:
   C   = a * b.T
	 C.T = a * b.T
*/
template <class T, class U>
static inline void outer_product_ut(T* Out, 
																		T* In0, 
																		T* In1, 
																		volatile const U m, 
																		volatile const U n,
																		volatile const U Outs = 0,
																		volatile const U In0s = 0,
																		volatile const U In1s = 0,
																		volatile U U1 = 0) { 

	register U u1 = set_unroll((U)sqrt(n), U1);

	// Note for single-threads, U1=2 seems to outperform all others
	
	switch (u1) {
		case 1: {
			return outer_product_1(Out, In0, In1, m, n, Outs, In0s, In1s); 
		}
		case 2: {
			return outer_product_2(Out, In0, In1, m, n, Outs, In0s, In1s); 
		}                                             
		case 4: {                                     
			return outer_product_4(Out, In0, In1, m, n, Outs, In0s, In1s); 
		}                                             
		case 8: {                                     
			return outer_product_8(Out, In0, In1, m, n, Outs, In0s, In1s); 
		}
		case 16: {
			return outer_product_16(Out, In0, In1, m, n, Outs, In0s, In1s); 
		}
		case 32: {
			return outer_product_32(Out, In0, In1, m, n, Outs, In0s, In1s); 
		}
		default: {
			return outer_product_64(Out, In0, In1, m, n, Outs, In0s, In1s); 
		}
	}
}

//------------------------------------------------------------------------------
/* inner:
  c   = a.T * b
	c.T = a.T * b
*/
template <class T, class U>
static inline void inner_product_ut(T* Out, 
																		T* In0, 
																		T* In1, 
																		volatile const U m, 
																		volatile const U k, 
																		volatile const U Outs = 1, 
																		volatile U In0s = 1, 
																		volatile U In1s = 1, 
																		T* In2 = 0,
																		volatile U U1 = 0) {
	register U u1 = set_unroll((U)sqrt(k), U1);
	register U h;

  if (k > 1) {
		if (In0s == 1) {In0s = k;}
		if (In1s == 1) {In1s = k;}
	}

	switch (u1) {
		case 1: {
			replicate_1x1 (Out, m, In2, Outs, (U)1);
			inner_product_1 (Out, In0, In1, m, k, Outs, In0s, In1s); 
			return;
		}
		case 2: {
			replicate_1x2 (Out, m, In2, Outs, (U)1);
			inner_product_2 (Out, In0, In1, m, k, Outs, In0s, In1s); 
			return;
		}
		case 4: {
			replicate_1x4 (Out, m, In2, Outs, (U)1);
			inner_product_4 (Out, In0, In1, m, k, Outs, In0s, In1s); 
			return;
		}
		case 8: {
			replicate_1x8 (Out, m, In2, Outs, (U)1);
			inner_product_8 (Out, In0, In1, m, k, Outs, In0s, In1s); 
			return;
		}
		case 16: {
			replicate_1x16(Out, m, In2, Outs, (U)1);
			inner_product_16(Out, In0, In1, m, k, Outs, In0s, In1s); 
			return;
		}
		default: {
			replicate_1x32(Out, m, In2, Outs, (U)1);
			inner_product_32(Out, In0, In1, m, k, Outs, In0s, In1s); 
			return;
		}
	}
}

//------------------------------------------------------------------------------
#endif

