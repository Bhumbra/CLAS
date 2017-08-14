//------------------------------------------------------------------------------
// KISS multiplications coded as thought experiments
//------------------------------------------------------------------------------
# ifndef _dot_product_mnk_txx
# define _dot_product_mnk_txx

//------------------------------------------------------------------------------
# define CACHE_DOUBLE_LENGTH_MNK 12448
// A possible cache scheme (for thread-safety do not cache OUT):
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
static inline void mmdot_product_MNK_64x64x64(T* _OUT, 
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

	cacher<T, U> Cacher = cacher<T, U>(_cache, (U)2);
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
		for (f = N; f; f--) {
			_Out = OUT;
			OUT += nS;
			IN1 = _IN1;
			_IN1 += nS;
			Cacher.retUnit((U)0).copyFr(_Out, n, (U)1);
			for (g = K; g; g--) {
				_In0 = IN0;
				In0 += kS;
				_In1 = IN1;
				IN1 += n * kS;
				Cacher.retUnit((U)1).copyFr(_In0, k, (U)1);
				Cacher.retUnit((U)2).copyFr(_In1, n, (U)1);
				for (h = 0; h < mS; h++) {
					_in0 = In0 + h*kS;
					for (i = 0; i < ns; i++) {
						_in1 = In1 + i*ns;
						in1 = _in1;
						for (j = 0; j < ks; j++) {
							in0 = _in0 + j*ks;
							in1 = _in1 + j*NS;
							o0 = *(_Out + 0);
							o1 = *(_Out + 1);
							o2 = *(_Out + 2);
							o3 = *(_Out + 3);
							o4 = *(_Out + 4);
							o5 = *(_Out + 5);
							o6 = *(_Out + 6);
							o7 = *(_Out + 7);
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
					}
				}
			}
			*(_Out + 0) = o0;
			*(_Out + 1) = o1;
			*(_Out + 2) = o2;
			*(_Out + 3) = o3;
			*(_Out + 4) = o4;
			*(_Out + 5) = o5;
			*(_Out + 6) = o6;
			*(_Out + 7) = o7;
		}
	}
}

//------------------------------------------------------------------------------
#endif

