//------------------------------------------------------------------------------
// KISS multiplications coded as thought experiments
//------------------------------------------------------------------------------
# ifndef _dot_product_txx
# define _dot_product_txx

//------------------------------------------------------------------------------
# define CACHE_DOUBLE_LENGTH 12448
// A possible vmdot read cache scheme (for thread-safety do not cache OUT):
// Fast: out(8), In0 (8x64x2)     , In1T (64x8)         - 12352
// Slow: out(8*_8), In0 ([_8x8]x64x2), In1T (64x[8x_8]) - 98816
// Shared: In1

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

	/*
	// REPLICATOR EXAMPLE
	replicator<T, U> rep = replicator<T, U>(_OUT, (U)2);
	rep.setO(4, 8);
	rep.setI(_IN0, 8, 1);
	//Transpose:
	//rep.setO(8, 4);
	//rep.setI(_IN0, 1, 8);
	rep.copyFr();
	return;
	*/

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mmdot_product_MKN_2x2x2 (T* _OUT, 
																						T* _IN0, 
																						T* _IN1, 
																						volatile const U m,
																						volatile const U k, 
																						volatile const U n) {
	double _cache[CACHE_DOUBLE_LENGTH];
	T* cache = (T*)_cache;
	cache += nextAlignedInd(cache, (U)256);
	volatile const U ms = (U)2;
	volatile const U ks = (U)2;
	volatile const U ns = (U)2;

	register T t;
	T *OUT, *IN0, *IN1, *_Out, *_In0, *_In1, *Out, *In0, *In1;
	T  *_out, *_in0, *_in1, *out, *in0, *in1;
  U M, K, N, e, f, g, h, i, j;

	M = m / ms;
	K = k / ks;
	N = n / ns;

	cacher<T, U> Cacher = cacher<T, U>(cache, (U)3);
	Cacher.setAlign((U)256, (U)64);

	_out = Cacher.setUnit((U)0, ms, ns);
	_in0 = Cacher.setUnit((U)1, ms, ks);
	_in1 = Cacher.setUnit((U)2, ks, ns);

	Cacher.retUnit((U)1).prefetch((U)1, (U)3);
	Cacher.retUnit((U)2).prefetch((U)1, (U)3);

	for (e = M; e; e--) {
		Cacher.retUnit((U)1).prefetch((U)0, (U)3);
		OUT = _OUT;
		IN0 = _IN0;
		_OUT += n * ms;
		_IN0 += k * ms;
		IN1 = _IN1;
		for (f = K; f; f--) {
			Cacher.retUnit((U)2).prefetch((U)0, (U)3);
			_Out = OUT;
			_In0 = IN0;
			IN0 += ks;
			_In1 = IN1;
			IN1 += n * ks;
			Cacher.retUnit((U)1).copyFr(_In0, k, (U)1);
			for (g = N; g; g--) {
				out = _out;
				in0 = _in0;
				in1 = _in1;
				Cacher.retUnit((U)2).copyFr(_In1, n, (U)1);
				_In1 += ns;
				Cacher.retUnit((U)0).copyFr();
				t = *(in0 + 0);
				*(out + 0) += t * *(in1 + 0);
				*(out + 1) += t * *(in1 + 1);
				in1 += ns;
				t = *(in0 + 1);
				*(out + 0) += t * *(in1 + 0);
				*(out + 1) += t * *(in1 + 1);
				out += ns;
				in0 += ms;
				in1 = _in1;
				t = *(in0 + 0);
				*(out + 0) += t * *(in1 + 0);
				*(out + 1) += t * *(in1 + 1);
				in1 += ns;
				t = *(in0 + 1);
				*(out + 0) += t * *(in1 + 0);
				*(out + 1) += t * *(in1 + 1);
				Out = _Out;
				_Out += ns;
				out = _out;
				*(Out + 0) += *(out + 0);
				*(Out + 1) += *(out + 1);
				out += ns;
				Out += n;
				*(Out + 0) += *(out + 0);
				*(Out + 1) += *(out + 1);
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
	double _cache[CACHE_DOUBLE_LENGTH];
	T* cache = (T*)_cache;
	cache += nextAlignedInd(cache, (U)256);
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

	cacher<T, U> Cacher = cacher<T, U>(cache, (U)3);
	Cacher.setAlign((U)256, (U)64);

	_out = Cacher.setUnit((U)0, ms, ns);
	_in0 = Cacher.setUnit((U)1, ms, ks);
	_in1 = Cacher.setUnit((U)2, ks, ns);

	Cacher.retUnit((U)1).prefetch((U)1, (U)3);
	Cacher.retUnit((U)2).prefetch((U)1, (U)3);

	for (e = M; e; e--) {
		Cacher.retUnit((U)1).prefetch((U)0, (U)3);
		OUT = _OUT;
		IN0 = _IN0;
		_OUT += n * ms;
		_IN0 += k * ms;
		IN1 = _IN1;
		for (f = K; f; f--) {
			Cacher.retUnit((U)2).prefetch((U)0, (U)3);
			_Out = OUT;
			_In0 = IN0;
			IN0 += ks;
			_In1 = IN1;
			IN1 += n * ks;
			Cacher.retUnit((U)1).copyFr(_In0, k, (U)1);
			for (g = N; g; g--) {
				out = _out;
				in0 = _in0;
				in1 = _in1;
				Cacher.retUnit((U)2).copyFr(_In1, n, (U)1);
				_In1 += ns;
				Cacher.retUnit((U)0).copyFr();
				t = *(in0 + 0);
				*(out + 0) += t * *(in1 + 0);
				*(out + 1) += t * *(in1 + 1);
				*(out + 2) += t * *(in1 + 2);
				*(out + 3) += t * *(in1 + 3);
				in1 += ns;
				t = *(in0 + 1);
				*(out + 0) += t * *(in1 + 0);
				*(out + 1) += t * *(in1 + 1);
				*(out + 2) += t * *(in1 + 2);
				*(out + 3) += t * *(in1 + 3);
				in1 += ns;
				t = *(in0 + 2);
				*(out + 0) += t * *(in1 + 0);
				*(out + 1) += t * *(in1 + 1);
				*(out + 2) += t * *(in1 + 2);
				*(out + 3) += t * *(in1 + 3);
				in1 += ns;
				t = *(in0 + 3);
				*(out + 0) += t * *(in1 + 0);
				*(out + 1) += t * *(in1 + 1);
				*(out + 2) += t * *(in1 + 2);
				*(out + 3) += t * *(in1 + 3);
				out += ns;
				in0 += ms;
				in1 = _in1;
				t = *(in0 + 0);
				*(out + 0) += t * *(in1 + 0);
				*(out + 1) += t * *(in1 + 1);
				*(out + 2) += t * *(in1 + 2);
				*(out + 3) += t * *(in1 + 3);
				in1 += ns;
				t = *(in0 + 1);
				*(out + 0) += t * *(in1 + 0);
				*(out + 1) += t * *(in1 + 1);
				*(out + 2) += t * *(in1 + 2);
				*(out + 3) += t * *(in1 + 3);
				in1 += ns;
				t = *(in0 + 2);
				*(out + 0) += t * *(in1 + 0);
				*(out + 1) += t * *(in1 + 1);
				*(out + 2) += t * *(in1 + 2);
				*(out + 3) += t * *(in1 + 3);
				in1 += ns;
				t = *(in0 + 3);
				*(out + 0) += t * *(in1 + 0);
				*(out + 1) += t * *(in1 + 1);
				*(out + 2) += t * *(in1 + 2);
				*(out + 3) += t * *(in1 + 3);
				out += ns;
				in0 += ms;
				in1 = _in1;
				t = *(in0 + 0);
				*(out + 0) += t * *(in1 + 0);
				*(out + 1) += t * *(in1 + 1);
				*(out + 2) += t * *(in1 + 2);
				*(out + 3) += t * *(in1 + 3);
				in1 += ns;
				t = *(in0 + 1);
				*(out + 0) += t * *(in1 + 0);
				*(out + 1) += t * *(in1 + 1);
				*(out + 2) += t * *(in1 + 2);
				*(out + 3) += t * *(in1 + 3);
				in1 += ns;
				t = *(in0 + 2);
				*(out + 0) += t * *(in1 + 0);
				*(out + 1) += t * *(in1 + 1);
				*(out + 2) += t * *(in1 + 2);
				*(out + 3) += t * *(in1 + 3);
				in1 += ns;
				t = *(in0 + 3);
				*(out + 0) += t * *(in1 + 0);
				*(out + 1) += t * *(in1 + 1);
				*(out + 2) += t * *(in1 + 2);
				*(out + 3) += t * *(in1 + 3);
				out += ns;
				in0 += ms;
				in1 = _in1;
				t = *(in0 + 0);
				*(out + 0) += t * *(in1 + 0);
				*(out + 1) += t * *(in1 + 1);
				*(out + 2) += t * *(in1 + 2);
				*(out + 3) += t * *(in1 + 3);
				in1 += ns;
				t = *(in0 + 1);
				*(out + 0) += t * *(in1 + 0);
				*(out + 1) += t * *(in1 + 1);
				*(out + 2) += t * *(in1 + 2);
				*(out + 3) += t * *(in1 + 3);
				in1 += ns;
				t = *(in0 + 2);
				*(out + 0) += t * *(in1 + 0);
				*(out + 1) += t * *(in1 + 1);
				*(out + 2) += t * *(in1 + 2);
				*(out + 3) += t * *(in1 + 3);
				in1 += ns;
				t = *(in0 + 3);
				*(out + 0) += t * *(in1 + 0);
				*(out + 1) += t * *(in1 + 1);
				*(out + 2) += t * *(in1 + 2);
				*(out + 3) += t * *(in1 + 3);
				out += ns;
				in0 += ms;
				in1 = _in1;
				Out = _Out;
				_Out += ns;
				out = _out;
				*(Out + 0) += *(out + 0);
				*(Out + 1) += *(out + 1);
				*(Out + 2) += *(out + 2);
				*(Out + 3) += *(out + 3);
				out += ns;
				Out += n;
				*(Out + 0) += *(out + 0);
				*(Out + 1) += *(out + 1);
				*(Out + 2) += *(out + 2);
				*(Out + 3) += *(out + 3);
				out += ns;
				Out += n;
				*(Out + 0) += *(out + 0);
				*(Out + 1) += *(out + 1);
				*(Out + 2) += *(out + 2);
				*(Out + 3) += *(out + 3);
				out += ns;
				Out += n;
				*(Out + 0) += *(out + 0);
				*(Out + 1) += *(out + 1);
				*(Out + 2) += *(out + 2);
				*(Out + 3) += *(out + 3);
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

	double _cache[CACHE_DOUBLE_LENGTH];
	T* cache = (T*)_cache;
	cache += nextAlignedInd(cache, (U)256);
	U ns = (U)4;
	if (!ms) {ms = ns;}
	if (!ks) {ks = ns;}

	register T t;
	T *OUT, *IN0, *IN1, *_Out, *_In0, *_In1, *Out, *In0, *In1;
	T  *_out, *_in0, *_in1, *out, *in0, *in1;
  U M, K, N, e, f, g, h, i, j;

	M = m / ms;
	K = k / ks;
	N = n / ns;

	cacher<T, U> Cacher = cacher<T, U>(cache, (U)3);
	Cacher.setAlign((U)256, (U)64);

	_out = Cacher.setUnit((U)0, ms, ns);
	_in0 = Cacher.setUnit((U)1, ms, ks);
	_in1 = Cacher.setUnit((U)2, ks, ns);

	Cacher.retUnit((U)1).prefetch((U)1, (U)3);
	Cacher.retUnit((U)2).prefetch((U)1, (U)3);

	for (e = M; e; e--) {
		Cacher.retUnit((U)1).prefetch((U)0, (U)3);
		OUT = _OUT;
		IN0 = _IN0;
		_OUT += n * ms;
		_IN0 += k * ms;
		IN1 = _IN1;
		for (f = K; f; f--) {
			Cacher.retUnit((U)2).prefetch((U)0, (U)3);
			_Out = OUT;
			_In0 = IN0;
			IN0 += ks;
			_In1 = IN1;
			IN1 += n * ks;
			Cacher.retUnit((U)1).copyFr(_In0, k, (U)1);
			for (g = N; g; g--) {
				out = _out;
				Cacher.retUnit((U)2).copyFr(_In1, n, (U)1);
				_In1 += ns;
				Cacher.retUnit((U)0).copyFr();
				in0 = _in0;
				for (h = ms; h; h--) {
					in1 = _in1;
					for (i = 0; i < ks; i++) {
						t = *(in0 + i);
						*(out + 0) += t * *(in1 + 0);
						*(out + 1) += t * *(in1 + 1);
						*(out + 2) += t * *(in1 + 2);
						*(out + 3) += t * *(in1 + 3);
						in1 += ns;
					}
					out += ns;
					in0 += ks;
				}
				out = _out;
				Out = _Out;
				for (h = ms; h; h--) {
					*(Out + 0) += *(out + 0);
					*(Out + 1) += *(out + 1);
					*(Out + 2) += *(out + 2);
					*(Out + 3) += *(out + 3);
					Out += n;
					out += ns;
				}
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
	double _cache[CACHE_DOUBLE_LENGTH];
	T* cache = (T*)_cache;
	cache += nextAlignedInd(cache, (U)256);
	U ns = (U)8;
	if (!ms) {ms = ns;}
	if (!ks) {ks = ns;}

	register T t;
	T *OUT, *IN0, *IN1, *_Out, *_In0, *_In1, *Out, *In0, *In1;
	T  *_out, *_in0, *_in1, *out, *in0, *in1;
  U M, K, N, e, f, g, h, i, j;

	M = m / ms;
	K = k / ks;
	N = n / ns;

	cacher<T, U> Cacher = cacher<T, U>(cache, (U)3);
	Cacher.setAlign((U)256, (U)64);

	_out = Cacher.setUnit((U)0, ms, ns);
	_in0 = Cacher.setUnit((U)1, ms, ks);
	_in1 = Cacher.setUnit((U)2, ks, ns);

	Cacher.retUnit((U)1).prefetch((U)1, (U)3);
	Cacher.retUnit((U)2).prefetch((U)1, (U)3);

	for (e = M; e; e--) {
		OUT = _OUT;
		IN0 = _IN0;
		_OUT += n * ms;
		_IN0 += k * ms;
		IN1 = _IN1;
		for (f = K; f; f--) {
			Cacher.retUnit((U)1).prefetch((U)1, (U)3);
			_Out = OUT;
			_In0 = IN0;
			IN0 += ks;
			_In1 = IN1;
			IN1 += n * ks;
			Cacher.retUnit((U)1).copyFr(_In0, k, (U)1);
			Cacher.retUnit((U)1).prefetch((U)0, (U)3);
			for (g = N; g; g--) {
				Cacher.retUnit((U)2).prefetch((U)1, (U)3);
				Cacher.retUnit((U)0).prefetch((U)1, (U)3);
				out = _out;
				Cacher.retUnit((U)2).copyFr(_In1, n, (U)1);
				_In1 += ns;
				Cacher.retUnit((U)0).copyFr();
				Cacher.retUnit((U)2).prefetch((U)0, (U)3);
				in0 = _in0;
				for (h = ms; h; h--) {
					in1 = _in1;
					for (i = 0; i < ks; i++) {
						t = *(in0 + i);
						*(out + 0) += t * *(in1 + 0);
						*(out + 1) += t * *(in1 + 1);
						*(out + 2) += t * *(in1 + 2);
						*(out + 3) += t * *(in1 + 3);
						*(out + 4) += t * *(in1 + 4);
						*(out + 5) += t * *(in1 + 5);
						*(out + 6) += t * *(in1 + 6);
						*(out + 7) += t * *(in1 + 7);
						in1 += ns;
					}
					out += ns;
					in0 += ks;
				}
				out = _out;
				Out = _Out;
				for (h = ms; h; h--) {
					*(Out + 0) += *(out + 0);
					*(Out + 1) += *(out + 1);
					*(Out + 2) += *(out + 2);
					*(Out + 3) += *(out + 3);
					*(Out + 4) += *(out + 4);
					*(Out + 5) += *(out + 5);
					*(Out + 6) += *(out + 6);
					*(Out + 7) += *(out + 7);
					Out += n;
					out += ns;
				}
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
	double _cache[CACHE_DOUBLE_LENGTH];
	T* cache = (T*)_cache;
	cache += nextAlignedInd(cache, (U)256);
	U ns = (U)8;
	if (!ms) {ms = ns;}
	if (!ks) {ks = ns*ns;}

	register T t;
	T *OUT, *IN0, *IN1, *_Out, *_In0, *_In1, *Out, *In0, *In1;
	T  *_out, *_in0, *_in1, *out, *in0, *in1;
  U M, K, N, e, f, g, h, i, j;

	M = m / ms;
	K = k / ks;
	N = n / ns;

	cacher<T, U> Cacher = cacher<T, U>(cache, (U)3);
	Cacher.setAlign((U)256, (U)64);

	_out = Cacher.setUnit((U)0, ms, ns);
	_in0 = Cacher.setUnit((U)1, ms, ks);
	_in1 = Cacher.setUnit((U)2, ks, ns);

	Cacher.retUnit((U)1).prefetch((U)1, (U)3);
	Cacher.retUnit((U)2).prefetch((U)1, (U)3);

	for (e = M; e; e--) {
		OUT = _OUT;
		IN0 = _IN0;
		_OUT += n * ms;
		_IN0 += k * ms;
		IN1 = _IN1;
		for (f = K; f; f--) {
			Cacher.retUnit((U)1).prefetch((U)1, (U)3);
			_Out = OUT;
			_In0 = IN0;
			IN0 += ks;
			_In1 = IN1;
			IN1 += n * ks;
			Cacher.retUnit((U)1).copyFr(_In0, k, (U)1);
			Cacher.retUnit((U)1).prefetch((U)0, (U)3);
			for (g = N; g; g--) {
				Cacher.retUnit((U)2).prefetch((U)1, (U)3);
				Cacher.retUnit((U)0).prefetch((U)1, (U)3);
				out = _out;
				Cacher.retUnit((U)2).copyFr(_In1, n, (U)1);
				_In1 += ns;
				Cacher.retUnit((U)0).copyFr();
				Cacher.retUnit((U)2).prefetch((U)0, (U)3);
				in0 = _in0;
				for (h = ms; h; h--) {
					PREFETCH_WRITE_3(out + ns);
					PREFETCH_READ_3(in0 + ks);
					in1 = _in1;
					for (i = 0; i < ks; i++) {
						PREFETCH_READ_3(in1 + ns);
						t = *(in0 + i);
						*(out + 0) += t * *(in1 + 0);
						*(out + 1) += t * *(in1 + 1);
						*(out + 2) += t * *(in1 + 2);
						*(out + 3) += t * *(in1 + 3);
						*(out + 4) += t * *(in1 + 4);
						*(out + 5) += t * *(in1 + 5);
						*(out + 6) += t * *(in1 + 6);
						*(out + 7) += t * *(in1 + 7);
						in1 += ns;
					}
					out += ns;
					in0 += ks;
				}
				out = _out;
				Out = _Out;
				for (h = ms; h; h--) {
					*(Out + 0) += *(out + 0);
					*(Out + 1) += *(out + 1);
					*(Out + 2) += *(out + 2);
					*(Out + 3) += *(out + 3);
					*(Out + 4) += *(out + 4);
					*(Out + 5) += *(out + 5);
					*(Out + 6) += *(out + 6);
					*(Out + 7) += *(out + 7);
					Out += n;
					out += ns;
				}
				_Out += ns;
			}
		}
	}
}

//------------------------------------------------------------------------------
#endif

