//------------------------------------------------------------------------------
// KISS multiplications coded as thought experiments
//------------------------------------------------------------------------------
# ifndef _dot_product_txx
# define _dot_product_txx

//------------------------------------------------------------------------------
# include <iostream>
using namespace std;

//------------------------------------------------------------------------------
# include "cacher.txx"

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mmdot_product_mkn (T* _OUT, 
																			T* _IN0, 
																			T* _IN1, 
																			volatile const U m,
																			volatile const U k, 
																			volatile const U n) { 

	T *OUT, *IN0, *IN1, *_Out, *_In0, *_In1;
  U h, i, j;

	for (h = m; h; h--) {
		OUT = _OUT;
		IN0 = _IN0;
		_OUT += n;
		_IN0 += k;
		IN1 = _IN1;
		for (i = k; i; i--) {
			_Out = OUT;
			_In0 = IN0;
			IN0 ++;
			_In1 = IN1;
			IN1 += n;
			for (j = n; j; j--) {
				*_Out += *_In0 * *_In1;
				_Out ++;
				_In1 ++;
			}
		}
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mmdot_product_MKN (T* _OUT, 
																			T* _IN0, 
																			T* _IN1, 
																			volatile const U m,
																			volatile const U k, 
																			volatile const U n,
																			volatile const U ms = (U)1,
																			volatile const U ks = (U)1,
																			volatile const U ns = (U)1) { 

	
	T *OUT, *IN0, *IN1, *_Out, *_In0, *_In1, *Out, *In0, *In1;
	T  *_out, *_in0, *_in1, *out, *in0, *in1;
  U M, K, N, e, f, g, h, i, j;

	M = m / ms;
	K = k / ks;
	N = n / ns;

	for (e = M; e; e--) {
		OUT = _OUT;
		IN0 = _IN0;
		_OUT += n * ms;
		_IN0 += k * ms;
		IN1 = _IN1;
		for (f = K; f; f--) {
			_Out = OUT;
			_In0 = IN0;
			IN0 += ks;
			_In1 = IN1;
			IN1 += n * ks;
			for (g = N; g; g--) {
				Out = _Out;
				In0 = _In0;
				In1 = _In1;
				_Out += ns;
				_In1 += ns;
				for (h = ms; h; h--) {
					_out = Out;
					Out += n;
					_in0 = In0;
					In0 += k;
					_in1 = In1;
					for (i = ks; i; i--) {
						out = _out;
						in0 = _in0;
						_in0 ++;
						in1 = _in1;
						_in1 += n;
						for (j = ns; j; j--) {
							*out += *in0 *  *in1;
							out ++;
							in1 ++;
						}
					}
				}
			}
		}
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mmdot_product_MKN_2x2x2 (T* _OUT, 
																						T* _IN0, 
																						T* _IN1, 
																						volatile const U m,
																						volatile const U k, 
																						volatile const U n) {
	double _cache[12320];
	T* cache = (T*)_cache;
	cache += nextAlignedInd(cache, (U)256);
	///*
	// REPLICATOR EXAMPLE
	replicator<T, U> rep = replicator<T, U>(_OUT, (U)2);
	rep.setO(4, 8);
	rep.setI(_IN0, 8, 1);
	//Transpose:
	//rep.setO(8, 4);
	//rep.setI(_IN0, 1, 8);
	rep.copy();
	//*/
	return;
	volatile const U ms = (U)2;
	volatile const U ks = (U)2;
	volatile const U ns = (U)2;

	T *OUT, *IN0, *IN1, *_Out, *_In0, *_In1, *Out, *In0, *In1;
	T  *_out, *_in0, *_in1, *out, *in0, *in1;
  U M, K, N, e, f, g, h, i, j;

	M = m / ms;
	K = k / ks;
	N = n / ns;

	for (e = M; e; e--) {
		OUT = _OUT;
		IN0 = _IN0;
		_OUT += n * ms;
		_IN0 += k * ms;
		IN1 = _IN1;
		for (f = K; f; f--) {
			_Out = OUT;
			_In0 = IN0;
			IN0 += ks;
			_In1 = IN1;
			IN1 += n * ks;
			for (g = N; g; g--) {
				Out = _Out;
				In0 = _In0;
				In1 = _In1;
				_Out += ns;
				_In1 += ns;
				for (h = ms; h; h--) {
					_out = Out;
					Out += n;
					_in0 = In0;
					In0 += k;
					_in1 = In1;
					for (i = ks; i; i--) {
						out = _out;
						in0 = _in0;
						_in0 ++;
						in1 = _in1;
						_in1 += n;
						for (j = ns; j; j--) {
							*out += *in0 *  *in1;
							out ++;
							in1 ++;
						}
					}
				}
			}
		}
	}
}

//------------------------------------------------------------------------------
#endif

