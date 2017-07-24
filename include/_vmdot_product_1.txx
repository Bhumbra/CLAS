#ifndef _vmdot_product_1_txx
#define _vmdot_product_1_txx

//------------------------------------------------------------------------------
template <class T, class U>
static inline void vmdot_product_1x1 (T* Out, 
																			T* In0, 
																			T* _In1, 
																			volatile const U k, 
																			volatile const U n = 1,
																			volatile const U In0s = 0,
																			volatile const U In1s = 0) { 

	register T in0_0;
	register T *out, *in0, *in1;
	register T *In1;

	register U i, j;

	in0 = In0;
	In1 = _In1;

	for (i = k; i; i--) {
		out = Out;
		in0_0 = *in0;
		in0 += In0s;
		in1 = In1;
		In1 += In1s;
		for (j = n; j; j--) {
			*(out +   0) += in0_0 * *(in1 +   0); 
			out ++;
			in1 ++;
		}
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void vmdot_product_1x2 (T* Out, 
																			T* In0, 
																			T* _In1, 
																			volatile const U k, 
																			volatile const U n = 1,
																			volatile const U In0s = 0,
																			volatile const U In1s = 0) { 

	register T in0_0;
	register T *out, *in0, *in1;
	register T *In1;

	register U i, j;
	volatile U div, mod;

	in0 = In0;
	In1 = _In1;
	div = n >> 1;
  mod = n & 1;

	for (i = k; i; i--) {
		out = Out;
		in0_0 = *in0;
		in0 += In0s;
		in1 = In1;
		In1 += In1s;
		for (j = div; j; j--) {
			*(out +   0) += in0_0 * *(in1 +   0); 
			*(out +   1) += in0_0 * *(in1 +   1); 
			out += 2;
			in1 += 2;
		}
	}

	if (mod) {
		div = n - mod;
		vmdot_product_1x1 (Out + div, In0, _In1 + div, k, mod, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void vmdot_product_1x4 (T* Out, 
																			T* In0, 
																			T* _In1, 
																			volatile const U k, 
																			volatile const U n = 1,
																			volatile const U In0s = 0,
																			volatile const U In1s = 0) { 

	register T in0_0;
	register T *out, *in0, *in1;
	register T *In1;

	register U i, j;
	volatile U div, mod;

	in0 = In0;
	In1 = _In1;
	div = n >> 2;
	mod = n & 3;

	for (i = k; i; i--) {
		out = Out;
		in0_0 = *in0;
		in1 = In1;
		in0 += In0s;
		In1 += In1s;
		for (j = div; j; j--) {
			*(out +   0) += in0_0 * *(in1 +   0); 
			*(out +   1) += in0_0 * *(in1 +   1); 
			*(out +   2) += in0_0 * *(in1 +   2); 
			*(out +   3) += in0_0 * *(in1 +   3); 
			out += 4;
			in1 += 4;
		}
	}

	if (mod) {
		div = n - mod;
		vmdot_product_1x2(Out + div, In0, _In1 + div, k, mod, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void vmdot_product_1x8 (T* Out, 
																			T* In0, 
																			T* _In1, 
																			volatile const U k, 
																			volatile const U n = 1,
																			volatile const U In0s = 0,
																			volatile const U In1s = 0) { 

	register T in0_0;
	register T *out, *in0, *in1;
	register T *In1;

	register U i, j;
	volatile U div, mod;

	in0 = In0;
	In1 = _In1;
	div = n >> 3;
	mod = n & 7;

	for (i = k; i; i--) {
		out = Out;
		in0_0 = *in0;
		in0 += In0s;
		in1 = In1;
		In1 += In1s;
		for (j = div; j; j--) {
			*(out +   0) += in0_0 * *(in1 +   0); 
			*(out +   1) += in0_0 * *(in1 +   1); 
			*(out +   2) += in0_0 * *(in1 +   2); 
			*(out +   3) += in0_0 * *(in1 +   3); 
			*(out +   4) += in0_0 * *(in1 +   4); 
			*(out +   5) += in0_0 * *(in1 +   5); 
			*(out +   6) += in0_0 * *(in1 +   6); 
			*(out +   7) += in0_0 * *(in1 +   7); 
			out += 8;
			in1 += 8;
		}
	}

	if (mod) {
		div = n - mod;
		vmdot_product_1x4(Out + div, In0, _In1 + div, k, mod, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void vmdot_product_1x16(T* Out, 
																			T* In0, 
																			T* _In1, 
																			volatile const U k, 
																			volatile const U n = 1,
																			volatile const U In0s = 0,
																			volatile const U In1s = 0) { 

	register T in0_0;
	register T *out, *in0, *in1;
	register T *In1;

	register U i, j;
	volatile U div, mod;

	in0 = In0;
	In1 = _In1;
	div = n >> 4;
	mod = n & 15;

	for (i = k; i; i--) {
		out = Out;
		in0_0 = *in0;
		in0 += In0s; 
		in1 = In1;
		In1 += In1s;
		for (j = div; j; j--) {
			*(out +   0) += in0_0 * *(in1 +   0); 
			*(out +   1) += in0_0 * *(in1 +   1); 
			*(out +   2) += in0_0 * *(in1 +   2); 
			*(out +   3) += in0_0 * *(in1 +   3); 
			*(out +   4) += in0_0 * *(in1 +   4); 
			*(out +   5) += in0_0 * *(in1 +   5); 
			*(out +   6) += in0_0 * *(in1 +   6); 
			*(out +   7) += in0_0 * *(in1 +   7); 
			out += 8;
			in1 += 8;
			*(out +   0) += in0_0 * *(in1 +   0); 
			*(out +   1) += in0_0 * *(in1 +   1); 
			*(out +   2) += in0_0 * *(in1 +   2); 
			*(out +   3) += in0_0 * *(in1 +   3); 
			*(out +   4) += in0_0 * *(in1 +   4); 
			*(out +   5) += in0_0 * *(in1 +   5); 
			*(out +   6) += in0_0 * *(in1 +   6); 
			*(out +   7) += in0_0 * *(in1 +   7); 
			out += 8;
			in1 += 8;
		}
	}

	if (mod) {
		div = n - mod;
		vmdot_product_1x8(Out + div, In0, _In1 + div, k, mod, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void vmdot_product_1x32(T* Out, 
																			T* In0, 
																			T* _In1, 
																			volatile const U k, 
																			volatile const U n = 1,
																			volatile const U In0s = 0,
																			volatile const U In1s = 0) { 

	register T in0_0;
	register T *out, *in0, *in1;
	register T *In1;

	register U i, j;
	volatile U div, mod;

	in0 = In0;
	In1 = _In1;
	div = n >> 5;
	mod = n & 31;

	for (i = k; i; i--) {
		out = Out;
		in0_0 = *in0;
		in0 += In0s;
		in1 = In1;
		In1 += In1s;
		for (j = div; j; j--) {
			*(out +   0) += in0_0 * *(in1 +   0); 
			*(out +   1) += in0_0 * *(in1 +   1); 
			*(out +   2) += in0_0 * *(in1 +   2); 
			*(out +   3) += in0_0 * *(in1 +   3); 
			*(out +   4) += in0_0 * *(in1 +   4); 
			*(out +   5) += in0_0 * *(in1 +   5); 
			*(out +   6) += in0_0 * *(in1 +   6); 
			*(out +   7) += in0_0 * *(in1 +   7); 
			out += 8;
			in1 += 8;
			*(out +   0) += in0_0 * *(in1 +   0); 
			*(out +   1) += in0_0 * *(in1 +   1); 
			*(out +   2) += in0_0 * *(in1 +   2); 
			*(out +   3) += in0_0 * *(in1 +   3); 
			*(out +   4) += in0_0 * *(in1 +   4); 
			*(out +   5) += in0_0 * *(in1 +   5); 
			*(out +   6) += in0_0 * *(in1 +   6); 
			*(out +   7) += in0_0 * *(in1 +   7); 
			out += 8;
			in1 += 8;
			*(out +   0) += in0_0 * *(in1 +   0); 
			*(out +   1) += in0_0 * *(in1 +   1); 
			*(out +   2) += in0_0 * *(in1 +   2); 
			*(out +   3) += in0_0 * *(in1 +   3); 
			*(out +   4) += in0_0 * *(in1 +   4); 
			*(out +   5) += in0_0 * *(in1 +   5); 
			*(out +   6) += in0_0 * *(in1 +   6); 
			*(out +   7) += in0_0 * *(in1 +   7); 
			out += 8;
			in1 += 8;
			*(out +   0) += in0_0 * *(in1 +   0); 
			*(out +   1) += in0_0 * *(in1 +   1); 
			*(out +   2) += in0_0 * *(in1 +   2); 
			*(out +   3) += in0_0 * *(in1 +   3); 
			*(out +   4) += in0_0 * *(in1 +   4); 
			*(out +   5) += in0_0 * *(in1 +   5); 
			*(out +   6) += in0_0 * *(in1 +   6); 
			*(out +   7) += in0_0 * *(in1 +   7); 
			out += 8;
			in1 += 8;
		}
	}

	if (mod) {
		div = n - mod;
		vmdot_product_1x16(Out + div, In0, _In1 + div, k, mod, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
#endif
