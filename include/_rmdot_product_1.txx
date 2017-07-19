#ifndef _rmdot_product_1_txx
#define _rmdot_product_1_txx

//------------------------------------------------------------------------------
template <class T, class U>
static inline void rmdot_product_1x1 (T* Out, 
																			T* _In0, 
																			T* _In1, 
																			volatile const U k, 
																			volatile const U n = 1,
																			volatile const U In1s = 0) { 

	register T in0;
	register T *out, *in1;
	register T *In0, *In1;

	register U i, j;

	In0 = _In0;
	In1 = _In1;

	for (i = k; i; i--) {
		out = Out;
		in0 = *In0;
		In0 ++;
		in1 = In1;
		In1 += In1s;
		for (j = n; j; j--) {
			*(out +   0) += in0 * *(in1 +   0); 
			out ++;
			in1 ++;
		}
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void rmdot_product_1x2 (T* Out, 
																			T* _In0, 
																			T* _In1, 
																			volatile const U k, 
																			volatile const U n = 1,
																			volatile const U In1s = 0) { 

	register T in0;
	register T *out, *in1;
	register T *In0, *In1;

  register U i, j;
  volatile U div, mod;

	In0 = _In0;
	In1 = _In1;
	div = n >> 1;
  mod = n & 1;

	for (i = k; i; i--) {
		out = Out;
		in0 = *In0;
		In0 ++;
		in1 = In1;
		In1 += In1s;
		for (j = div; j; j--) {
			*(out +   0) += in0 * *(in1 +   0); 
			*(out +   1) += in0 * *(in1 +   1); 
			out += 2;
			in1 += 2;
		}
	}

	if (mod) {
		div = n - mod;
		rmdot_product_1x1 (Out + div, _In0, _In1 + div, k, mod, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void rmdot_product_1x4 (T* Out, 
																			T* _In0, 
																			T* _In1, 
																			volatile const U k, 
																			volatile const U n = 1,
																			volatile const U In1s = 0) { 

	register T in0;
	register T *out, *in1;
	register T *In0, *In1;

  register U i, j;
  volatile U div, mod;

	In0 = _In0;
	In1 = _In1;
	div = n >> 2;
	mod = n & 3;

	for (i = k; i; i--) {
		out = Out;
		in0 = *In0;
		in1 = In1;
		In0 ++;
		In1 += In1s;
		for (j = div; j; j--) {
			*(out +   0) += in0 * *(in1 +   0); 
			*(out +   1) += in0 * *(in1 +   1); 
			*(out +   2) += in0 * *(in1 +   2); 
			*(out +   3) += in0 * *(in1 +   3); 
			out += 4;
			in1 += 4;
		}
	}

	if (mod) {
		div = n - mod;
		rmdot_product_1x2(Out + div, _In0, _In1 + div, k, mod, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void rmdot_product_1x8 (T* Out, 
																			T* _In0, 
																			T* _In1, 
																			volatile const U k, 
																			volatile const U n = 1,
																			volatile const U In1s = 0) { 

	register T in0;
	register T *out, *in1;
	register T *In0, *In1;

  register U i, j;
  volatile U div, mod;

	In0 = _In0;
	In1 = _In1;
	div = n >> 3;
	mod = n & 7;

	for (i = k; i; i--) {
		out = Out;
		in0 = *In0;
		In0 ++;
		in1 = In1;
		In1 += In1s;
		for (j = div; j; j--) {
			*(out +   0) += in0 * *(in1 +   0); 
			*(out +   1) += in0 * *(in1 +   1); 
			*(out +   2) += in0 * *(in1 +   2); 
			*(out +   3) += in0 * *(in1 +   3); 
			*(out +   4) += in0 * *(in1 +   4); 
			*(out +   5) += in0 * *(in1 +   5); 
			*(out +   6) += in0 * *(in1 +   6); 
			*(out +   7) += in0 * *(in1 +   7); 
			out += 8;
			in1 += 8;
		}
	}

	if (mod) {
		div = n - mod;
		rmdot_product_1x4(Out + div, _In0, _In1 + div, k, mod, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void rmdot_product_1x16(T* Out, 
																			T* _In0, 
																			T* _In1, 
																			volatile const U k, 
																			volatile const U n = 1,
																			volatile const U In1s = 0) { 

	register T in0;
	register T *out, *in1;
	register T *In0, *In1;

  register U i, j;
  volatile U div, mod;

	In0 = _In0;
	In1 = _In1;
	div = n >> 4;
	mod = n & 15;

	for (i = k; i; i--) {
		out = Out;
		in0 = *In0;
		In0 ++; 
		in1 = In1;
		In1 += In1s;
		for (j = div; j; j--) {
			*(out +   0) += in0 * *(in1 +   0); 
			*(out +   1) += in0 * *(in1 +   1); 
			*(out +   2) += in0 * *(in1 +   2); 
			*(out +   3) += in0 * *(in1 +   3); 
			*(out +   4) += in0 * *(in1 +   4); 
			*(out +   5) += in0 * *(in1 +   5); 
			*(out +   6) += in0 * *(in1 +   6); 
			*(out +   7) += in0 * *(in1 +   7); 
			*(out +   8) += in0 * *(in1 +   8); 
			*(out +   9) += in0 * *(in1 +   9); 
			*(out +  10) += in0 * *(in1 +  10); 
			*(out +  11) += in0 * *(in1 +  11); 
			*(out +  12) += in0 * *(in1 +  12); 
			*(out +  13) += in0 * *(in1 +  13); 
			*(out +  14) += in0 * *(in1 +  14); 
			*(out +  15) += in0 * *(in1 +  15); 
			out += 16;
			in1 += 16;
		}
	}

	if (mod) {
		div = n - mod;
		rmdot_product_1x8(Out + div, _In0, _In1 + div, k, mod, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void rmdot_product_1x32(T* Out, 
																			T* _In0, 
																			T* _In1, 
																			volatile const U k, 
																			volatile const U n = 1,
																			volatile const U In1s = 0) { 

	register T in0;
	register T *out, *in1;
	register T *In0, *In1;

  register U i, j;
  volatile U div, mod;

	In0 = _In0;
	In1 = _In1;
	div = n >> 5;
	mod = n & 31;

	for (i = k; i; i--) {
		out = Out;
		in0 = *In0;
		In0 ++;
		in1 = In1;
		In1 += In1s;
		for (j = div; j; j--) {
			*(out +   0) += in0 * *(in1 +   0); 
			*(out +   1) += in0 * *(in1 +   1); 
			*(out +   2) += in0 * *(in1 +   2); 
			*(out +   3) += in0 * *(in1 +   3); 
			*(out +   4) += in0 * *(in1 +   4); 
			*(out +   5) += in0 * *(in1 +   5); 
			*(out +   6) += in0 * *(in1 +   6); 
			*(out +   7) += in0 * *(in1 +   7); 
			*(out +   8) += in0 * *(in1 +   8); 
			*(out +   9) += in0 * *(in1 +   9); 
			*(out +  10) += in0 * *(in1 +  10); 
			*(out +  11) += in0 * *(in1 +  11); 
			*(out +  12) += in0 * *(in1 +  12); 
			*(out +  13) += in0 * *(in1 +  13); 
			*(out +  14) += in0 * *(in1 +  14); 
			*(out +  15) += in0 * *(in1 +  15); 
			*(out +  16) += in0 * *(in1 +  16); 
			*(out +  17) += in0 * *(in1 +  17); 
			*(out +  18) += in0 * *(in1 +  18); 
			*(out +  19) += in0 * *(in1 +  19); 
			*(out +  20) += in0 * *(in1 +  20); 
			*(out +  21) += in0 * *(in1 +  21); 
			*(out +  22) += in0 * *(in1 +  22); 
			*(out +  23) += in0 * *(in1 +  23); 
			*(out +  24) += in0 * *(in1 +  24); 
			*(out +  25) += in0 * *(in1 +  25); 
			*(out +  26) += in0 * *(in1 +  26); 
			*(out +  27) += in0 * *(in1 +  27); 
			*(out +  28) += in0 * *(in1 +  28); 
			*(out +  29) += in0 * *(in1 +  29); 
			*(out +  30) += in0 * *(in1 +  30); 
			*(out +  31) += in0 * *(in1 +  31); 
			out += 32;
			in1 += 32;
		}
	}

	if (mod) {
		div = n - mod;
		rmdot_product_1x16(Out + div, _In0, _In1 + div, k, mod, In1s);
	}
}

//------------------------------------------------------------------------------
#endif
