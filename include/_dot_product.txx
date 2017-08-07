# ifndef _dot_product_txx
# define _dot_product_txx

// KISS multiplications coded as thought experiments

# include "cacher.txx"
//# include "replicator.txx"

using namespace std;
//------------------------------------------------------------------------------
// Note In1s is also the output stride
//------------------------------------------------------------------------------
template <class T, class U>
static inline void mmdot_product_mkn (T* OUT, 
																			T* IN0, 
																			T* IN1, 
																			volatile const U m,
																			volatile const U k, 
																			volatile const U n) { 

	T *_Out, *_In0, *_In1, *Out, *In0, *In1;
  U h, i, j;


	for (h = m; h; h--) {
		_Out = OUT;
		_In0 = IN0;
		OUT += n;
		IN0 += k;
		_In1 = IN1;
		for (i = k; i; i--) {
			Out = _Out;
			In0 = _In0;
			_In0 ++;
			In1 = _In1;
			_In1 += n;
			for (j = n; j; j--) {
				*Out += *In0 * *In1;
				Out ++;
				In1 ++;
			}
		}
	}
}

//------------------------------------------------------------------------------
#endif

