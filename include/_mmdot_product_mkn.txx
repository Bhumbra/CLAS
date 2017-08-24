//------------------------------------------------------------------------------
// KISS multiplications coded as thought experiments
//------------------------------------------------------------------------------
# ifndef _mmdot_product_mkn_txx
# define _mmdot_product_mkn_txx

//------------------------------------------------------------------------------
# define CACHE_DOUBLE_LENGTH_MKN 12800
// A possible vmdot read cache scheme (for thread-safety do not cache OUT):
// Fast: out(8x8), In0 (8x64)     , In1T (64x8)         			- 12288 ->  12800
// Slow: out([_8x8]x[8x8]), In0 ([_8x8]x64), In1T (64x[8x_8]) - 98304 -> 102400
// Shared: In1

//------------------------------------------------------------------------------
# include <iostream>
using namespace std;

//------------------------------------------------------------------------------
# include "mcache.txx"

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
	double _cache[CACHE_DOUBLE_LENGTH_MKN];
	volatile const U ms = (U)2;
	volatile const U ks = (U)2;
	volatile const U ns = (U)2;

	T *OUT, *IN0, *IN1, *_Out, *_In0, *_In1, *Out, *In0, *In1;
	T  *_out, *_in0, *_in1, *out, *in0, *in1;
  U M, K, N, e, f, g, h, i, j;

	M = m / ms;
	K = k / ks;
	N = n / ns;

	mcache<T, U> Cacher = mcache<T, U>(_cache, (U)3);
	Cacher.setAlign((U)256, (U)64);

	_out = Cacher.setUnit((U)0, ms, ns);
	_in0 = Cacher.setUnit((U)1, ms, ks);
	_in1 = Cacher.setUnit((U)2, ks, ns);

	Cacher.retUnit((U)0).prefetch((U)1, (U)3);
	Cacher.retUnit((U)1).prefetch((U)1, (U)3);
	Cacher.retUnit((U)2).prefetch((U)1, (U)3);

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
			Cacher.retUnit((U)1).copyFr(_In0, k, (U)1);
			for (g = N; g; g--) {
				Cacher.retUnit((U)0).copyFr(_Out, n, (U)1);
				out = _out;
				in0 = _in0;
				in1 = _in1;
				Cacher.retUnit((U)2).copyFr(_In1, n, (U)1);
				_In1 += ns;
				*(out + 0) += *(in0 + 0) * *(in1 + 0);
				*(out + 1) += *(in0 + 0) * *(in1 + 1);
				in1 += ns;
				*(out + 0) += *(in0 + 1) * *(in1 + 0);
				*(out + 1) += *(in0 + 1) * *(in1 + 1);
				out += ns;
				in0 += ms;
				in1 = _in1;
				*(out + 0) += *(in0 + 0) * *(in1 + 0);
				*(out + 1) += *(in0 + 0) * *(in1 + 1);
				in1 += ns;
				*(out + 0) += *(in0 + 1) * *(in1 + 0);
				*(out + 1) += *(in0 + 1) * *(in1 + 1);
				Cacher.retUnit((U)0).copyTo(_Out, n);
				_Out += ns;
			}
		}
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mmdot_product_MKN_4x4x4 (T* _OUT, 
																						T* _IN0, 
																						T* _IN1, 
																						volatile const U m,
																						volatile const U k, 
																						volatile const U n) {
	double _cache[CACHE_DOUBLE_LENGTH_MKN];
	volatile const U ms = (U)4;
	volatile const U ks = (U)4;
	volatile const U ns = (U)4;

	register T t;
	T *OUT, *IN0, *IN1, *_Out, *_In0, *_In1, *Out, *In0, *In1;
	T  *_out, *_in0, *_in1, *out, *in0, *in1;
  U M, K, N, e, f, g, h, i, j;

	M = m / ms;
	K = k / ks;
	N = n / ns;

	mcache<T, U> Cacher = mcache<T, U>(_cache, (U)3);
	Cacher.setAlign((U)256, (U)64);

	_out = Cacher.setUnit((U)0, ms, ns);
	_in0 = Cacher.setUnit((U)1, ms, ks);
	_in1 = Cacher.setUnit((U)2, ks, ns);

	Cacher.retUnit((U)0).prefetch((U)1, (U)3);
	Cacher.retUnit((U)1).prefetch((U)1, (U)3);
	Cacher.retUnit((U)2).prefetch((U)1, (U)3);

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
			Cacher.retUnit((U)1).copyFr(_In0, k, (U)1);
			for (g = N; g; g--) {
				Cacher.retUnit((U)0).copyFr(_Out, n, (U)1);
				out = _out;
				in0 = _in0;
				in1 = _in1;
				Cacher.retUnit((U)2).copyFr(_In1, n, (U)1);
				_In1 += ns;
				*(out + 0) += *(in0 + 0) * *(in1 + 0);
				*(out + 1) += *(in0 + 0) * *(in1 + 1);
				*(out + 2) += *(in0 + 0) * *(in1 + 2);
				*(out + 3) += *(in0 + 0) * *(in1 + 3);
				in1 += ns;
				*(out + 0) += *(in0 + 1) * *(in1 + 0);
				*(out + 1) += *(in0 + 1) * *(in1 + 1);
				*(out + 2) += *(in0 + 1) * *(in1 + 2);
				*(out + 3) += *(in0 + 1) * *(in1 + 3);
				in1 += ns;
				*(out + 0) += *(in0 + 2) * *(in1 + 0);
				*(out + 1) += *(in0 + 2) * *(in1 + 1);
				*(out + 2) += *(in0 + 2) * *(in1 + 2);
				*(out + 3) += *(in0 + 2) * *(in1 + 3);
				in1 += ns;
				*(out + 0) += *(in0 + 3) * *(in1 + 0);
				*(out + 1) += *(in0 + 3) * *(in1 + 1);
				*(out + 2) += *(in0 + 3) * *(in1 + 2);
				*(out + 3) += *(in0 + 3) * *(in1 + 3);
				out += ns;
				in0 += ms;
				in1 = _in1;
				*(out + 0) += *(in0 + 0) * *(in1 + 0);
				*(out + 1) += *(in0 + 0) * *(in1 + 1);
				*(out + 2) += *(in0 + 0) * *(in1 + 2);
				*(out + 3) += *(in0 + 0) * *(in1 + 3);
				in1 += ns;
				*(out + 0) += *(in0 + 1) * *(in1 + 0);
				*(out + 1) += *(in0 + 1) * *(in1 + 1);
				*(out + 2) += *(in0 + 1) * *(in1 + 2);
				*(out + 3) += *(in0 + 1) * *(in1 + 3);
				in1 += ns;
				*(out + 0) += *(in0 + 2) * *(in1 + 0);
				*(out + 1) += *(in0 + 2) * *(in1 + 1);
				*(out + 2) += *(in0 + 2) * *(in1 + 2);
				*(out + 3) += *(in0 + 2) * *(in1 + 3);
				in1 += ns;
				*(out + 0) += *(in0 + 3) * *(in1 + 0);
				*(out + 1) += *(in0 + 3) * *(in1 + 1);
				*(out + 2) += *(in0 + 3) * *(in1 + 2);
				*(out + 3) += *(in0 + 3) * *(in1 + 3);
				out += ns;
				in0 += ms;
				in1 = _in1;
				*(out + 0) += *(in0 + 0) * *(in1 + 0);
				*(out + 1) += *(in0 + 0) * *(in1 + 1);
				*(out + 2) += *(in0 + 0) * *(in1 + 2);
				*(out + 3) += *(in0 + 0) * *(in1 + 3);
				in1 += ns;
				*(out + 0) += *(in0 + 1) * *(in1 + 0);
				*(out + 1) += *(in0 + 1) * *(in1 + 1);
				*(out + 2) += *(in0 + 1) * *(in1 + 2);
				*(out + 3) += *(in0 + 1) * *(in1 + 3);
				in1 += ns;
				*(out + 0) += *(in0 + 2) * *(in1 + 0);
				*(out + 1) += *(in0 + 2) * *(in1 + 1);
				*(out + 2) += *(in0 + 2) * *(in1 + 2);
				*(out + 3) += *(in0 + 2) * *(in1 + 3);
				in1 += ns;
				*(out + 0) += *(in0 + 3) * *(in1 + 0);
				*(out + 1) += *(in0 + 3) * *(in1 + 1);
				*(out + 2) += *(in0 + 3) * *(in1 + 2);
				*(out + 3) += *(in0 + 3) * *(in1 + 3);
				out += ns;
				in0 += ms;
				in1 = _in1;
				*(out + 0) += *(in0 + 0) * *(in1 + 0);
				*(out + 1) += *(in0 + 0) * *(in1 + 1);
				*(out + 2) += *(in0 + 0) * *(in1 + 2);
				*(out + 3) += *(in0 + 0) * *(in1 + 3);
				in1 += ns;
				*(out + 0) += *(in0 + 1) * *(in1 + 0);
				*(out + 1) += *(in0 + 1) * *(in1 + 1);
				*(out + 2) += *(in0 + 1) * *(in1 + 2);
				*(out + 3) += *(in0 + 1) * *(in1 + 3);
				in1 += ns;
				*(out + 0) += *(in0 + 2) * *(in1 + 0);
				*(out + 1) += *(in0 + 2) * *(in1 + 1);
				*(out + 2) += *(in0 + 2) * *(in1 + 2);
				*(out + 3) += *(in0 + 2) * *(in1 + 3);
				in1 += ns;
				*(out + 0) += *(in0 + 3) * *(in1 + 0);
				*(out + 1) += *(in0 + 3) * *(in1 + 1);
				*(out + 2) += *(in0 + 3) * *(in1 + 2);
				*(out + 3) += *(in0 + 3) * *(in1 + 3);
				Cacher.retUnit((U)0).copyTo(_Out, n);
				_Out += ns;
			}
		}
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mmdot_product_MKN_sss_4 (T* _OUT, 
																						T* _IN0, 
																						T* _IN1, 
																						volatile const U m,
																						volatile const U k, 
																						volatile const U n,
																						U ms = 0,
																						U ks = 0) {

	double _cache[CACHE_DOUBLE_LENGTH_MKN];
	U ns = (U)4;
	if (!ms) {ms = ns;}
	if (!ks) {ks = ns;}

	register T i0;
	register T o0, o1, o2, o3;

	T *OUT, *IN0, *IN1, *_Out, *_In0, *_In1, *Out, *In0, *In1;
	T  *_out, *_in0, *_in1, *out, *in0, *in1;
  U M, K, N, e, f, g, h, i, j;

	M = m / ms;
	K = k / ks;
	N = n / ns;

	mcache<T, U> Cacher = mcache<T, U>(_cache, (U)3);
	Cacher.setAlign((U)256, (U)64);

	_out = Cacher.setUnit((U)0, ms, ns);
	_in0 = Cacher.setUnit((U)1, ms, ks);
	_in1 = Cacher.setUnit((U)2, ks, ns);

	Cacher.retUnit((U)0).prefetch((U)1, (U)3);
	Cacher.retUnit((U)1).prefetch((U)1, (U)3);
	Cacher.retUnit((U)2).prefetch((U)1, (U)3);

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
			Cacher.retUnit((U)1).copyFr(_In0, k, (U)1);
			for (g = N; g; g--) {
				Cacher.retUnit((U)0).copyFr(_Out, n, (U)1);
				out = _out;
				Cacher.retUnit((U)2).copyFr(_In1, n, (U)1);
				_In1 += ns;
				in0 = _in0;
				for (h = ms; h; h--) {
					in1 = _in1;
					o0 = *(out + 0);
					o1 = *(out + 1);
					o2 = *(out + 2);
					o3 = *(out + 3);
					for (i = 0; i < ks; i++) {
						i0 = *(in0 + i);
						o0 += i0 * *(in1 + 0);
						o1 += i0 * *(in1 + 1);
						o2 += i0 * *(in1 + 2);
						o3 += i0 * *(in1 + 3);
						in1 += ns;
					}
					*(out + 0) = o0;
					*(out + 1) = o1;
					*(out + 2) = o2;
					*(out + 3) = o3;
					out += ns;
					in0 += ks;
				}
				Cacher.retUnit((U)0).copyTo(_Out, n);
				_Out += ns;
			}
		}
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mmdot_product_MKN_sss_8 (T* _OUT, 
																						T* _IN0, 
																						T* _IN1, 
																						volatile const U m,
																						volatile const U k, 
																						volatile const U n,
																						U ms = 0,
																						U ks = 0) {
	double _cache[CACHE_DOUBLE_LENGTH_MKN];
	U ns = (U)8;
	if (!ms) {ms = ns;}
	if (!ks) {ks = ns;}

	register T i0;
	register T o0, o1, o2, o3, o4, o5, o6, o7;

	T *OUT, *IN0, *IN1, *_Out, *_In0, *_In1, *Out, *In0, *In1;
	T  *_out, *_in0, *_in1, *out, *in0, *in1;
  U M, K, N, e, f, g, h, i, j;

	M = m / ms;
	K = k / ks;
	N = n / ns;

	mcache<T, U> Cacher = mcache<T, U>(_cache, (U)3);
	Cacher.setAlign((U)256, (U)64);

	_out = Cacher.setUnit((U)0, ms, ns);
	_in0 = Cacher.setUnit((U)1, ms, ks);
	_in1 = Cacher.setUnit((U)2, ks, ns);

	Cacher.retUnit((U)0).prefetch((U)1, (U)3);
	Cacher.retUnit((U)1).prefetch((U)1, (U)3);
	Cacher.retUnit((U)2).prefetch((U)1, (U)3);

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
				Cacher.retUnit((U)0).copyFr(_Out, n, (U)1);
				out = _out;
				Cacher.retUnit((U)2).copyFr(_In1, n, (U)1);
				_In1 += ns;
				in0 = _in0;
				for (h = ms; h; h--) {
					in1 = _in1;
					o0 = *(out + 0);
					o1 = *(out + 1);
					o2 = *(out + 2);
					o3 = *(out + 3);
					o4 = *(out + 4);
					o5 = *(out + 5);
					o6 = *(out + 6);
					o7 = *(out + 7);
					for (i = 0; i < ks; i++) {
						i0 = *(in0 + i);
						o0 += i0 * *(in1 + 0);
						o1 += i0 * *(in1 + 1);
						o2 += i0 * *(in1 + 2);
						o3 += i0 * *(in1 + 3);
						o4 += i0 * *(in1 + 4);
						o5 += i0 * *(in1 + 5);
						o6 += i0 * *(in1 + 6);
						o7 += i0 * *(in1 + 7);
						in1 += ns;
					}
					*(out + 0) = o0;
					*(out + 1) = o1;
					*(out + 2) = o2;
					*(out + 3) = o3;
					*(out + 4) = o4;
					*(out + 5) = o5;
					*(out + 6) = o6;
					*(out + 7) = o7;
					out += ns;
					in0 += ks;
				}
				Cacher.retUnit((U)0).copyTo(_Out, n);
				_Out += ns;
			}
		}
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mmdot_product_MKN_sSs_8 (T* _OUT, 
																						T* _IN0, 
																						T* _IN1, 
																						volatile const U m,
																						volatile const U k, 
																						volatile const U n,
																						U ms = 0,
																						U ks = 0) {
	double _cache[CACHE_DOUBLE_LENGTH_MKN];
	U ns = (U)8;
	if (!ms) {ms = ns;}
	if (!ks) {ks = ns;}
	U kS = ks * ks;

	register T i0, i1, i2, i3, i4, i5, i6, i7;
	register T o0, o1, o2, o3, o4, o5, o6, o7;

	T *OUT, *IN0, *IN1, *_Out, *_In0, *_In1, *Out, *In0, *In1;
	T  *_out, *_in0, *_in1, *out, *in0, *in1;
  U M, K, N, e, f, g, h, i, j;

	M = m / ms;
	K = k / kS;
	N = n / ns;

	mcache<T, U> Cacher = mcache<T, U>(_cache, (U)3);
	Cacher.setAlign((U)256, (U)64);

	_out = Cacher.setUnit((U)0, ms, ns);
	_in0 = Cacher.setUnit((U)1, ms, kS);
	_in1 = Cacher.setUnit((U)2, kS, ns);

	Cacher.retUnit((U)0).prefetch((U)1, (U)3);
	Cacher.retUnit((U)1).prefetch((U)1, (U)3);
	Cacher.retUnit((U)2).prefetch((U)1, (U)3);

	for (e = M; e; e--) {
		OUT = _OUT;
		IN0 = _IN0;
		_OUT += n * ms;
		_IN0 += k * ms;
		IN1 = _IN1;
		for (f = K; f; f--) {
			_Out = OUT;
			_In0 = IN0;
			IN0 += kS;
			_In1 = IN1;
			IN1 += n * kS;
			Cacher.retUnit((U)1).copyFr(_In0, k, (U)1);
			for (g = N; g; g--) {
				Cacher.retUnit((U)0).copyFr(_Out, n, (U)1);
				out = _out;
				Cacher.retUnit((U)2).copyFr(_In1, n, (U)1);
				_In1 += ns;
				in0 = _in0;
				for (h = ms; h; h--) {
					in1 = _in1;
					o0 = *(out + 0);
					o1 = *(out + 1);
					o2 = *(out + 2);
					o3 = *(out + 3);
					o4 = *(out + 4);
					o5 = *(out + 5);
					o6 = *(out + 6);
					o7 = *(out + 7);
					for (i = 0; i < ks; i++) {
						i0 = *(in0 + 0);
						i1 = *(in0 + 1);
						i2 = *(in0 + 2);
						i3 = *(in0 + 3);
						i4 = *(in0 + 4);
						i5 = *(in0 + 5);
						i6 = *(in0 + 6);
						i7 = *(in0 + 7);
						in0 += ks;
						o0 += i0 * *(in1 + 0);
						o1 += i0 * *(in1 + 1);
						o2 += i0 * *(in1 + 2);
						o3 += i0 * *(in1 + 3);
						o4 += i0 * *(in1 + 4);
						o5 += i0 * *(in1 + 5);
						o6 += i0 * *(in1 + 6);
						o7 += i0 * *(in1 + 7);
						in1 += ns;
						o0 += i1 * *(in1 + 0);
						o1 += i1 * *(in1 + 1);
						o2 += i1 * *(in1 + 2);
						o3 += i1 * *(in1 + 3);
						o4 += i1 * *(in1 + 4);
						o5 += i1 * *(in1 + 5);
						o6 += i1 * *(in1 + 6);
						o7 += i1 * *(in1 + 7);
						in1 += ns;
						o0 += i2 * *(in1 + 0);
						o1 += i2 * *(in1 + 1);
						o2 += i2 * *(in1 + 2);
						o3 += i2 * *(in1 + 3);
						o4 += i2 * *(in1 + 4);
						o5 += i2 * *(in1 + 5);
						o6 += i2 * *(in1 + 6);
						o7 += i2 * *(in1 + 7);
						in1 += ns;
						o0 += i3 * *(in1 + 0);
						o1 += i3 * *(in1 + 1);
						o2 += i3 * *(in1 + 2);
						o3 += i3 * *(in1 + 3);
						o4 += i3 * *(in1 + 4);
						o5 += i3 * *(in1 + 5);
						o6 += i3 * *(in1 + 6);
						o7 += i3 * *(in1 + 7);
						in1 += ns;
						o0 += i4 * *(in1 + 0);
						o1 += i4 * *(in1 + 1);
						o2 += i4 * *(in1 + 2);
						o3 += i4 * *(in1 + 3);
						o4 += i4 * *(in1 + 4);
						o5 += i4 * *(in1 + 5);
						o6 += i4 * *(in1 + 6);
						o7 += i4 * *(in1 + 7);
						in1 += ns;
						o0 += i5 * *(in1 + 0);
						o1 += i5 * *(in1 + 1);
						o2 += i5 * *(in1 + 2);
						o3 += i5 * *(in1 + 3);
						o4 += i5 * *(in1 + 4);
						o5 += i5 * *(in1 + 5);
						o6 += i5 * *(in1 + 6);
						o7 += i5 * *(in1 + 7);
						in1 += ns;
						o0 += i6 * *(in1 + 0);
						o1 += i6 * *(in1 + 1);
						o2 += i6 * *(in1 + 2);
						o3 += i6 * *(in1 + 3);
						o4 += i6 * *(in1 + 4);
						o5 += i6 * *(in1 + 5);
						o6 += i6 * *(in1 + 6);
						o7 += i6 * *(in1 + 7);
						in1 += ns;
						o0 += i7 * *(in1 + 0);
						o1 += i7 * *(in1 + 1);
						o2 += i7 * *(in1 + 2);
						o3 += i7 * *(in1 + 3);
						o4 += i7 * *(in1 + 4);
						o5 += i7 * *(in1 + 5);
						o6 += i7 * *(in1 + 6);
						o7 += i7 * *(in1 + 7);
						in1 += ns;
					}
					*(out + 0) = o0;
					*(out + 1) = o1;
					*(out + 2) = o2;
					*(out + 3) = o3;
					*(out + 4) = o4;
					*(out + 5) = o5;
					*(out + 6) = o6;
					*(out + 7) = o7;
					out += ns;
				}
				Cacher.retUnit((U)0).copyTo(_Out, n);
				_Out += ns;
			}
		}
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mmdot_product_MKN_SSS_8 (T* _OUT, 
																						T* _IN0, 
																						T* _IN1, 
																						volatile const U m,
																						volatile const U k, 
																						volatile const U n,
																						U ms = 0,
																						U ks = 0) {
	double _cache[CACHE_DOUBLE_LENGTH_MKN];
	U ns = (U)8;
	if (!ms) {ms = ns;}
	if (!ks) {ks = ns;}
	U mS = ms * ms;
	U kS = ks * ks;
	U nS = ns * ns;
	U NS = ns * nS;

	register T i0, i1, i2, i3, i4, i5, i6, i7;
	register T o0, o1, o2, o3, o4, o5, o6, o7;

	T *OUT, *IN0, *IN1, *_Out, *_In0, *_In1, *Out, *In0, *In1;
	T  *_out, *_in0, *_in1, *out, *in0, *in1;
  U M, K, N, e, f, g, h, i, j;

	M = m / mS;
	K = k / kS;
	N = n / nS;

	mcache<T, U> Cacher = mcache<T, U>(_cache, (U)3);
	Cacher.setAlign((U)256, (U)64);

	Out = Cacher.setUnit((U)0, (U)64, (U)64);
	In0 = Cacher.setUnit((U)1, (U)64, (U)64);
	In1 = Cacher.setUnit((U)2, (U)64, (U)64);
	
	Cacher.retUnit((U)0).prefetch((U)1, (U)2);
	Cacher.retUnit((U)1).prefetch((U)1, (U)2);
	Cacher.retUnit((U)2).prefetch((U)1, (U)2);
	

	for (e = M; e; e--) {
		OUT = _OUT;
		IN0 = _IN0;
		_OUT += n * mS;
		_IN0 += k * mS;
		IN1 = _IN1;
		for (f = K; f; f--) {
			_Out = OUT;
			_In0 = IN0;
			IN0 += kS;
			_In1 = IN1;
			IN1 += n * kS;
			Cacher.retUnit((U)1).copyFr(_In0, k, (U)1);
			for (g = N; g; g--) {
				Cacher.retUnit((U)0).copyFr(_Out, n, (U)1);
				Cacher.retUnit((U)2).copyFr(_In1, n, (U)1);
				_In1 += nS;
				for (h = 0; h < mS; h++) {
					_out = Out + h*nS;
					_in0 = In0 + h*kS;
					for (i = 0; i < ns; i++) {
						out = _out + i*ns;
						_in1 = In1 + i*ns;
						o0 = *(out + 0);
						o1 = *(out + 1);
						o2 = *(out + 2);
						o3 = *(out + 3);
						o4 = *(out + 4);
						o5 = *(out + 5);
						o6 = *(out + 6);
						o7 = *(out + 7);
						in1 = _in1;
						for (j = 0; j < ks; j++) {
							in0 = _in0 + j*ks;
							in1 = _in1 + j*NS;
							i0 = *(in0 + 0);
							i1 = *(in0 + 1);
							i2 = *(in0 + 2);
							i3 = *(in0 + 3);
							i4 = *(in0 + 4);
							i5 = *(in0 + 5);
							i6 = *(in0 + 6);
							i7 = *(in0 + 7);
							in0 += ks;
							PREFETCH_READ_3(in0);
							o0 += i0 * *(in1 + 0);
							o1 += i0 * *(in1 + 1);
							o2 += i0 * *(in1 + 2);
							o3 += i0 * *(in1 + 3);
							o4 += i0 * *(in1 + 4);
							o5 += i0 * *(in1 + 5);
							o6 += i0 * *(in1 + 6);
							o7 += i0 * *(in1 + 7);
							in1 += nS;
							PREFETCH_READ_3(in1+NS);
							o0 += i1 * *(in1 + 0);
							o1 += i1 * *(in1 + 1);
							o2 += i1 * *(in1 + 2);
							o3 += i1 * *(in1 + 3);
							o4 += i1 * *(in1 + 4);
							o5 += i1 * *(in1 + 5);
							o6 += i1 * *(in1 + 6);
							o7 += i1 * *(in1 + 7);
							in1 += nS;
							PREFETCH_READ_3(in1+NS);
							o0 += i2 * *(in1 + 0);
							o1 += i2 * *(in1 + 1);
							o2 += i2 * *(in1 + 2);
							o3 += i2 * *(in1 + 3);
							o4 += i2 * *(in1 + 4);
							o5 += i2 * *(in1 + 5);
							o6 += i2 * *(in1 + 6);
							o7 += i2 * *(in1 + 7);
							in1 += nS;
							PREFETCH_READ_3(in1+NS);
							o0 += i3 * *(in1 + 0);
							o1 += i3 * *(in1 + 1);
							o2 += i3 * *(in1 + 2);
							o3 += i3 * *(in1 + 3);
							o4 += i3 * *(in1 + 4);
							o5 += i3 * *(in1 + 5);
							o6 += i3 * *(in1 + 6);
							o7 += i3 * *(in1 + 7);
							in1 += nS;
							PREFETCH_READ_3(in1+NS);
							o0 += i4 * *(in1 + 0);
							o1 += i4 * *(in1 + 1);
							o2 += i4 * *(in1 + 2);
							o3 += i4 * *(in1 + 3);
							o4 += i4 * *(in1 + 4);
							o5 += i4 * *(in1 + 5);
							o6 += i4 * *(in1 + 6);
							o7 += i4 * *(in1 + 7);
							in1 += nS;
							PREFETCH_READ_3(in1+NS);
							o0 += i5 * *(in1 + 0);
							o1 += i5 * *(in1 + 1);
							o2 += i5 * *(in1 + 2);
							o3 += i5 * *(in1 + 3);
							o4 += i5 * *(in1 + 4);
							o5 += i5 * *(in1 + 5);
							o6 += i5 * *(in1 + 6);
							o7 += i5 * *(in1 + 7);
							in1 += nS;
							PREFETCH_READ_3(in1+NS);
							o0 += i6 * *(in1 + 0);
							o1 += i6 * *(in1 + 1);
							o2 += i6 * *(in1 + 2);
							o3 += i6 * *(in1 + 3);
							o4 += i6 * *(in1 + 4);
							o5 += i6 * *(in1 + 5);
							o6 += i6 * *(in1 + 6);
							o7 += i6 * *(in1 + 7);
							in1 += nS;
							PREFETCH_READ_3(in1+NS);
							o0 += i7 * *(in1 + 0);
							o1 += i7 * *(in1 + 1);
							o2 += i7 * *(in1 + 2);
							o3 += i7 * *(in1 + 3);
							o4 += i7 * *(in1 + 4);
							o5 += i7 * *(in1 + 5);
							o6 += i7 * *(in1 + 6);
							o7 += i7 * *(in1 + 7);
							in1 += nS;
							PREFETCH_READ_3(in1+NS);
						}
						*(out + 0) = o0;
						*(out + 1) = o1;
						*(out + 2) = o2;
						*(out + 3) = o3;
						*(out + 4) = o4;
						*(out + 5) = o5;
						*(out + 6) = o6;
						*(out + 7) = o7;
					}
				}
				Cacher.retUnit((U)0).copyTo(_Out, n);
				_Out += nS;
			}
		}
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mmdot_product_MKN_64x64x64(T* _OUT, 
																							T* _IN0, 
																							T* _IN1, 
																							volatile const U m,
																							volatile const U k, 
																							volatile const U n,
																							U ms = 0,
																							U ks = 0) {
	double _cache[CACHE_DOUBLE_LENGTH_MKN];
	U ns = (U)8;
	if (!ms) {ms = ns;}
	if (!ks) {ks = ns;}
	U mS = ms * ms;
	U kS = ks * ks;
	U nS = ns * ns;
	U NS = ns * nS;

	register T i0, i1, i2, i3, i4, i5, i6, i7;
	register T o0, o1, o2, o3, o4, o5, o6, o7;

	T *OUT, *IN0, *IN1, *_Out, *_In0, *_In1, *Out, *In0, *In1;
	T  *_out, *_in0, *_in1, *out, *in0, *in1;
  U M, K, N, e, f, g, h, i, j;

	M = m / mS;
	K = k / kS;
	N = n / nS;

	mcache<T, U> Cacher = mcache<T, U>(_cache, (U)2);
	Cacher.setAlign((U)256, (U)64);

	In0 = Cacher.setUnit((U)0, (U)64, (U)64);
	In1 = Cacher.setUnit((U)1, (U)64, (U)64);
	
	Cacher.retUnit((U)0).prefetch((U)1, (U)2);
	Cacher.retUnit((U)1).prefetch((U)1, (U)2);

	for (e = M; e; e--) {
		OUT = _OUT;
		IN0 = _IN0;
		_OUT += n * mS;
		_IN0 += k * mS;
		IN1 = _IN1;
		for (f = K; f; f--) {
			_In0 = IN0;
			IN0 += kS;
			_In1 = IN1;
			IN1 += n * kS;
			Cacher.retUnit((U)0).copyFr(_In0, k, (U)1);
			for (g = 0; g<N; g++) {
				_Out = OUT + g*nS;
				Cacher.retUnit((U)1).copyFr(_In1, n, (U)1);
				_In1 += nS;
				for (h = 0; h < mS; h++) {
					_out = _Out + h*n;
					_in0 = In0 + h*kS;
					for (i = 0; i < ns; i++) {
						out = _out + i*ns;
						_in1 = In1 + i*ns;
						o0 = *(out + 0);
						o1 = *(out + 1);
						o2 = *(out + 2);
						o3 = *(out + 3);
						o4 = *(out + 4);
						o5 = *(out + 5);
						o6 = *(out + 6);
						o7 = *(out + 7);
						in1 = _in1;
						for (j = 0; j < ks; j++) {
							in0 = _in0 + j*ks;
							in1 = _in1 + j*NS;
							i0 = *(in0 + 0);
							i1 = *(in0 + 1);
							i2 = *(in0 + 2);
							i3 = *(in0 + 3);
							i4 = *(in0 + 4);
							i5 = *(in0 + 5);
							i6 = *(in0 + 6);
							i7 = *(in0 + 7);
							in0 += ks;
							PREFETCH_READ_3(in0);
							o0 += i0 * *(in1 + 0);
							o1 += i0 * *(in1 + 1);
							o2 += i0 * *(in1 + 2);
							o3 += i0 * *(in1 + 3);
							o4 += i0 * *(in1 + 4);
							o5 += i0 * *(in1 + 5);
							o6 += i0 * *(in1 + 6);
							o7 += i0 * *(in1 + 7);
							in1 += nS;
							PREFETCH_READ_3(in1+NS);
							o0 += i1 * *(in1 + 0);
							o1 += i1 * *(in1 + 1);
							o2 += i1 * *(in1 + 2);
							o3 += i1 * *(in1 + 3);
							o4 += i1 * *(in1 + 4);
							o5 += i1 * *(in1 + 5);
							o6 += i1 * *(in1 + 6);
							o7 += i1 * *(in1 + 7);
							in1 += nS;
							PREFETCH_READ_3(in1+NS);
							o0 += i2 * *(in1 + 0);
							o1 += i2 * *(in1 + 1);
							o2 += i2 * *(in1 + 2);
							o3 += i2 * *(in1 + 3);
							o4 += i2 * *(in1 + 4);
							o5 += i2 * *(in1 + 5);
							o6 += i2 * *(in1 + 6);
							o7 += i2 * *(in1 + 7);
							in1 += nS;
							PREFETCH_READ_3(in1+NS);
							o0 += i3 * *(in1 + 0);
							o1 += i3 * *(in1 + 1);
							o2 += i3 * *(in1 + 2);
							o3 += i3 * *(in1 + 3);
							o4 += i3 * *(in1 + 4);
							o5 += i3 * *(in1 + 5);
							o6 += i3 * *(in1 + 6);
							o7 += i3 * *(in1 + 7);
							in1 += nS;
							PREFETCH_READ_3(in1+NS);
							o0 += i4 * *(in1 + 0);
							o1 += i4 * *(in1 + 1);
							o2 += i4 * *(in1 + 2);
							o3 += i4 * *(in1 + 3);
							o4 += i4 * *(in1 + 4);
							o5 += i4 * *(in1 + 5);
							o6 += i4 * *(in1 + 6);
							o7 += i4 * *(in1 + 7);
							in1 += nS;
							PREFETCH_READ_3(in1+NS);
							o0 += i5 * *(in1 + 0);
							o1 += i5 * *(in1 + 1);
							o2 += i5 * *(in1 + 2);
							o3 += i5 * *(in1 + 3);
							o4 += i5 * *(in1 + 4);
							o5 += i5 * *(in1 + 5);
							o6 += i5 * *(in1 + 6);
							o7 += i5 * *(in1 + 7);
							in1 += nS;
							PREFETCH_READ_3(in1+NS);
							o0 += i6 * *(in1 + 0);
							o1 += i6 * *(in1 + 1);
							o2 += i6 * *(in1 + 2);
							o3 += i6 * *(in1 + 3);
							o4 += i6 * *(in1 + 4);
							o5 += i6 * *(in1 + 5);
							o6 += i6 * *(in1 + 6);
							o7 += i6 * *(in1 + 7);
							in1 += nS;
							PREFETCH_READ_3(in1+NS);
							o0 += i7 * *(in1 + 0);
							o1 += i7 * *(in1 + 1);
							o2 += i7 * *(in1 + 2);
							o3 += i7 * *(in1 + 3);
							o4 += i7 * *(in1 + 4);
							o5 += i7 * *(in1 + 5);
							o6 += i7 * *(in1 + 6);
							o7 += i7 * *(in1 + 7);
							in1 += nS;
							PREFETCH_READ_3(in1+NS);
						}
						*(out + 0) = o0;
						*(out + 1) = o1;
						*(out + 2) = o2;
						*(out + 3) = o3;
						*(out + 4) = o4;
						*(out + 5) = o5;
						*(out + 6) = o6;
						*(out + 7) = o7;
					}
				}
			}
		}
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mmdot_product_mkn_64x64x64(T* _OUT, 
																							T* _IN0, 
																							T* _IN1, 
																							volatile const U m,
																							volatile const U k, 
																							volatile const U n,
																							U ms = 0,
																							U ks = 0) {
	double _cache[CACHE_DOUBLE_LENGTH_MKN];
	U ns = (U)8;
	if (!ms) {ms = ns;}
	if (!ks) {ks = ns;}
	U mS = ms * ms;
	U kS = ks * ks;
	U nS = ns * ns;
	U NS = ns * nS;

	register T i0, i1, i2, i3, i4, i5, i6, i7;
	register T o0, o1, o2, o3, o4, o5, o6, o7;

	T *OUT, *IN0, *IN1, *_Out, *_In0, *_In1, *Out, *In0, *In1;
	T  *_out, *_in0, *_in1, *out, *in0, *in1;
  U M, K, N, e, f, g, h, i, j, ksn;

	M = m / mS;
	K = k / kS;
	N = n / nS;

	ksn = (k * ns)/2 + nextAlignedInd(IN1, 64);

	mcache<T, U> Cacher = mcache<T, U>(_cache, (U)1);
	Cacher.setAlign((U)256, (U)64);

	In0 = Cacher.setUnit((U)0, (U)64, (U)64);
	
	Cacher.retUnit((U)0).prefetch((U)1, (U)2);

	for (e = M; e; e--) {
		OUT = _OUT;
		IN0 = _IN0;
		_OUT += n * mS;
		_IN0 += k * mS;
		IN1 = _IN1;
		for (f = K; f; f--) {
			_In0 = IN0;
			IN0 += kS;
			_In1 = IN1;
			IN1 += n * kS;
			Cacher.retUnit((U)0).copyFr(_In0, k, (U)1);
			for (g = 0; g<N; g++) {
				_Out = OUT + g*nS;
				In1 = _In1 + g*nS;
				for (h = 0; h < mS; h++) {
					_out = _Out + h*n;
					_in0 = In0 + h*kS;
					for (i = 0; i < ns; i++) {
						out = _out + i*ns;
						_in1 = In1 + i*ns;
						o0 = *(out + 0);
						o1 = *(out + 1);
						o2 = *(out + 2);
						o3 = *(out + 3);
						o4 = *(out + 4);
						o5 = *(out + 5);
						o6 = *(out + 6);
						o7 = *(out + 7);
						in1 = _in1;
						for (j = 0; j < ks; j++) {
							in1 = _in1 + j*ks*n;
							PREFETCH_READ_2(in1);
							in1 += n;
							PREFETCH_READ_2(in1);
							in1 += n;
							PREFETCH_READ_2(in1);
							in1 += n;
							PREFETCH_READ_2(in1);
							in1 += n;
							PREFETCH_READ_2(in1);
							in1 += n;
							PREFETCH_READ_2(in1);
							in1 += n;
							PREFETCH_READ_2(in1);
							in1 += n;
							PREFETCH_READ_2(in1);
							in1 += n;
						}
						in1 = _in1;
						for (j = 0; j < ks; j++) {
							in0 = _in0 + j*ks;
							in1 = _in1 + j*ks*n;
							i0 = *(in0 + 0);
							i1 = *(in0 + 1);
							i2 = *(in0 + 2);
							i3 = *(in0 + 3);
							i4 = *(in0 + 4);
							i5 = *(in0 + 5);
							i6 = *(in0 + 6);
							i7 = *(in0 + 7);
							in0 += ks;
							PREFETCH_READ_3(in0);
							o0 += i0 * *(in1 + 0);
							o1 += i0 * *(in1 + 1);
							o2 += i0 * *(in1 + 2);
							o3 += i0 * *(in1 + 3);
							o4 += i0 * *(in1 + 4);
							o5 += i0 * *(in1 + 5);
							o6 += i0 * *(in1 + 6);
							o7 += i0 * *(in1 + 7);
							PREFETCH_READ_3(in1+ksn);
							in1 += n;
							o0 += i1 * *(in1 + 0);
							o1 += i1 * *(in1 + 1);
							o2 += i1 * *(in1 + 2);
							o3 += i1 * *(in1 + 3);
							o4 += i1 * *(in1 + 4);
							o5 += i1 * *(in1 + 5);
							o6 += i1 * *(in1 + 6);
							o7 += i1 * *(in1 + 7);
							PREFETCH_READ_3(in1+ksn);
							in1 += n;
							o0 += i2 * *(in1 + 0);
							o1 += i2 * *(in1 + 1);
							o2 += i2 * *(in1 + 2);
							o3 += i2 * *(in1 + 3);
							o4 += i2 * *(in1 + 4);
							o5 += i2 * *(in1 + 5);
							o6 += i2 * *(in1 + 6);
							o7 += i2 * *(in1 + 7);
							PREFETCH_READ_3(in1+ksn);
							in1 += n;
							o0 += i3 * *(in1 + 0);
							o1 += i3 * *(in1 + 1);
							o2 += i3 * *(in1 + 2);
							o3 += i3 * *(in1 + 3);
							o4 += i3 * *(in1 + 4);
							o5 += i3 * *(in1 + 5);
							o6 += i3 * *(in1 + 6);
							o7 += i3 * *(in1 + 7);
							PREFETCH_READ_3(in1+ksn);
							in1 += n;
							o0 += i4 * *(in1 + 0);
							o1 += i4 * *(in1 + 1);
							o2 += i4 * *(in1 + 2);
							o3 += i4 * *(in1 + 3);
							o4 += i4 * *(in1 + 4);
							o5 += i4 * *(in1 + 5);
							o6 += i4 * *(in1 + 6);
							o7 += i4 * *(in1 + 7);
							PREFETCH_READ_3(in1+ksn);
							in1 += n;
							o0 += i5 * *(in1 + 0);
							o1 += i5 * *(in1 + 1);
							o2 += i5 * *(in1 + 2);
							o3 += i5 * *(in1 + 3);
							o4 += i5 * *(in1 + 4);
							o5 += i5 * *(in1 + 5);
							o6 += i5 * *(in1 + 6);
							o7 += i5 * *(in1 + 7);
							PREFETCH_READ_3(in1+ksn);
							in1 += n;
							o0 += i6 * *(in1 + 0);
							o1 += i6 * *(in1 + 1);
							o2 += i6 * *(in1 + 2);
							o3 += i6 * *(in1 + 3);
							o4 += i6 * *(in1 + 4);
							o5 += i6 * *(in1 + 5);
							o6 += i6 * *(in1 + 6);
							o7 += i6 * *(in1 + 7);
							PREFETCH_READ_3(in1+ksn);
							in1 += n;
							o0 += i7 * *(in1 + 0);
							o1 += i7 * *(in1 + 1);
							o2 += i7 * *(in1 + 2);
							o3 += i7 * *(in1 + 3);
							o4 += i7 * *(in1 + 4);
							o5 += i7 * *(in1 + 5);
							o6 += i7 * *(in1 + 6);
							o7 += i7 * *(in1 + 7);
							PREFETCH_READ_3(in1+ksn);
							in1 += n;
						}
						*(out + 0) = o0;
						*(out + 1) = o1;
						*(out + 2) = o2;
						*(out + 3) = o3;
						*(out + 4) = o4;
						*(out + 5) = o5;
						*(out + 6) = o6;
						*(out + 7) = o7;
					}
				}
			}
		}
	}
}

//------------------------------------------------------------------------------
#endif

