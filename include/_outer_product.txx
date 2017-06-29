#ifndef _outer_product_txx
#define _outer_product_txx
//------------------------------------------------------------------------------
template <class T, class U>
static inline void outer_product_1 (T* _Out, 
																		T* _In0, 
																		T* _In1, 
																		volatile const U m, 
																		volatile const U n,
																		volatile const U Outs = 0,
																		volatile const U In0s = 0,
																		volatile const U In1s = 0) { 
	register T *Out, *In0, *In1;
	register T *out,  in0, *in1;
	register U i, j;

	Out = _Out;
	In0 = _In0;
	In1 = _In1;

	for (i = m; i; i--) {
		in0 = *In0;
		in1 = In1;
		out = Out;
		In0 += In0s;
		In1 += In1s;
		Out += Outs;
		for (j = n; j; j--) {
			*(out +   0) = in0 * *(in1 +   0); 
			in1 ++  ;
			out ++  ;
		}
	}
}
//------------------------------------------------------------------------------
template <class T, class U>
static inline void outer_product_2 (T* _Out, 
																		T* _In0, 
																		T* _In1, 
																		volatile const U m, 
																		volatile const U n,
																		volatile const U Outs = 0,
																		volatile const U In0s = 0,
																		volatile const U In1s = 0) { 
	register T *Out, *In0, *In1;
	register T *out,  in0, *in1;
	register U i, j;
	volatile U div, mod;

	Out = _Out;
	In0 = _In0;
	In1 = _In1;
	div = n >> 1;
	mod = n & 1;

	for (i = m; i != 0; i--) {
		in0 = *In0;
		in1 = In1;
		out = Out;
		In0 += In0s;
		In1 += In1s;
		Out += Outs;
		for (j = div; j != 0; j--) {
			*(out +   0) = in0 * *(in1 +   0); 
			*(out +   1) = in0 * *(in1 +   1); 
			in1 += 2;
			out += 2;
		}
	}
	if (mod) {
		div = n - mod;
		outer_product_1(_Out + div, _In0, _In1 + div, m, mod, Outs, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void outer_product_4 (T* _Out, 
																		T* _In0, 
																		T* _In1, 
																		volatile const U m, 
																		volatile const U n,
																		volatile const U Outs = 0,
																		volatile const U In0s = 0,
																		volatile const U In1s = 0) { 
	register T *Out, *In0, *In1;
	register T *out,  in0, *in1;
	register U i, j;
	volatile U div, mod;

	Out = _Out;
	In0 = _In0;
	In1 = _In1;
	div = n >> 2;
	mod = n & 3;

	for (i = m; i; i--) {
		in0 = *In0;
		in1 = In1;
		out = Out;
		In0 += In0s;
		In1 += In1s;
		Out += Outs;
		for (j = div; j; j--) {
			*(out +   0) = in0 * *(in1 +   0); 
			*(out +   1) = in0 * *(in1 +   1); 
			*(out +   2) = in0 * *(in1 +   2); 
			*(out +   3) = in0 * *(in1 +   3); 
			in1 += 4;
			out += 4;
		}
	}	
	if (mod) {
		div = n - mod;
		outer_product_2(_Out + div, _In0, _In1 + div, m, mod, Outs, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void outer_product_8 (T* _Out, 
																		T* _In0, 
																		T* _In1, 
																		volatile const U m, 
																		volatile const U n,
																		volatile const U Outs = 0,
																		volatile const U In0s = 0,
																		volatile const U In1s = 0) { 
	register T *Out, *In0, *In1;
	register T *out,  in0, *in1;
	register U i, j;
	volatile U div, mod;

	Out = _Out;
	In0 = _In0;
	In1 = _In1;
	div = n >> 3;
	mod = n & 7;

	for (i = m; i; i--) {
		in0 = *In0;
		in1 = In1;
		out = Out;
		In0 += In0s;
		In1 += In1s;
		Out += Outs;
		for (j = div; j; j--) {
			*(out +   0) = in0 * *(in1 +   0); 
			*(out +   1) = in0 * *(in1 +   1); 
			*(out +   2) = in0 * *(in1 +   2); 
			*(out +   3) = in0 * *(in1 +   3); 
			*(out +   4) = in0 * *(in1 +   4); 
			*(out +   5) = in0 * *(in1 +   5); 
			*(out +   6) = in0 * *(in1 +   6); 
			*(out +   7) = in0 * *(in1 +   7); 
			in1 += 8;
			out += 8;
		}
	}
	if (mod) {
		div = n - mod;
		outer_product_4(_Out + div, _In0, _In1 + div, m, mod, Outs, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void outer_product_16(T* _Out, 
																		T* _In0, 
																		T* _In1, 
																		volatile const U m, 
																		volatile const U n,
																		volatile const U Outs = 0,
																		volatile const U In0s = 0,
																		volatile const U In1s = 0) { 
	register T *Out, *In0, *In1;
	register T *out,  in0, *in1;
	register U i, j;
	volatile U div, mod;

	Out = _Out;
	In0 = _In0;
	In1 = _In1;
	div = n >> 4;
	mod = n & 15;

	for (i = m; i; i--) {
		in0 = *In0;
		in1 = In1;
		out = Out;
		In0 += In0s;
		In1 += In1s;
		Out += Outs;
		for (j = div; j; j--) {
			*(out +   0) = in0 * *(in1 +   0); 
			*(out +   1) = in0 * *(in1 +   1); 
			*(out +   2) = in0 * *(in1 +   2); 
			*(out +   3) = in0 * *(in1 +   3); 
			*(out +   4) = in0 * *(in1 +   4); 
			*(out +   5) = in0 * *(in1 +   5); 
			*(out +   6) = in0 * *(in1 +   6); 
			*(out +   7) = in0 * *(in1 +   7); 
			*(out +   8) = in0 * *(in1 +   8); 
			*(out +   9) = in0 * *(in1 +   9); 
			*(out +  10) = in0 * *(in1 +  10); 
			*(out +  11) = in0 * *(in1 +  11); 
			*(out +  12) = in0 * *(in1 +  12); 
			*(out +  13) = in0 * *(in1 +  13); 
			*(out +  14) = in0 * *(in1 +  14); 
			*(out +  15) = in0 * *(in1 +  15); 
			in1 += 16;
			out += 16;
		}
	}
	if (mod) {
		div = n - mod;
		outer_product_8(_Out + div, _In0, _In1 + div, m, mod, Outs, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void outer_product_32(T* _Out, 
																		T* _In0, 
																		T* _In1, 
																		volatile const U m, 
																		volatile const U n,
																		volatile const U Outs = 0,
																		volatile const U In0s = 0,
																		volatile const U In1s = 0) { 
	register T *Out, *In0, *In1;
	register T *out,  in0, *in1;
	register U i, j;
	volatile U div, mod;

	Out = _Out;
	In0 = _In0;
	In1 = _In1;
	div = n >> 5;
  mod = n & 31;

	for (i = m; i; i--) {
		in0 = *In0;
		in1 = In1;
		out = Out;
		In0 += In0s;
		In1 += In1s;
		Out += Outs;
		for (j = div; j; j--) {
			*(out +   0) = in0 * *(in1 +   0); 
			*(out +   1) = in0 * *(in1 +   1); 
			*(out +   2) = in0 * *(in1 +   2); 
			*(out +   3) = in0 * *(in1 +   3); 
			*(out +   4) = in0 * *(in1 +   4); 
			*(out +   5) = in0 * *(in1 +   5); 
			*(out +   6) = in0 * *(in1 +   6); 
			*(out +   7) = in0 * *(in1 +   7); 
			*(out +   8) = in0 * *(in1 +   8); 
			*(out +   9) = in0 * *(in1 +   9); 
			*(out +  10) = in0 * *(in1 +  10); 
			*(out +  11) = in0 * *(in1 +  11); 
			*(out +  12) = in0 * *(in1 +  12); 
			*(out +  13) = in0 * *(in1 +  13); 
			*(out +  14) = in0 * *(in1 +  14); 
			*(out +  15) = in0 * *(in1 +  15); 
			*(out +  16) = in0 * *(in1 +  16); 
			*(out +  17) = in0 * *(in1 +  17); 
			*(out +  18) = in0 * *(in1 +  18); 
			*(out +  19) = in0 * *(in1 +  19); 
			*(out +  20) = in0 * *(in1 +  20); 
			*(out +  21) = in0 * *(in1 +  21); 
			*(out +  22) = in0 * *(in1 +  22); 
			*(out +  23) = in0 * *(in1 +  23); 
			*(out +  24) = in0 * *(in1 +  24); 
			*(out +  25) = in0 * *(in1 +  25); 
			*(out +  26) = in0 * *(in1 +  26); 
			*(out +  27) = in0 * *(in1 +  27); 
			*(out +  28) = in0 * *(in1 +  28); 
			*(out +  29) = in0 * *(in1 +  29); 
			*(out +  30) = in0 * *(in1 +  30); 
			*(out +  31) = in0 * *(in1 +  31); 
			in1 += 32;
			out += 32;
		}
	}
	if (mod) {
		div = n - mod;
		outer_product_16(_Out + div, _In0, _In1 + div, m, mod, Outs, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void outer_product_64(T* _Out, 
																		T* _In0, 
																		T* _In1, 
																		volatile const U m, 
																		volatile const U n,
																		volatile const U Outs = 0,
																		volatile const U In0s = 0,
																		volatile const U In1s = 0) { 
	register T *Out, *In0, *In1;
	register T *out,  in0, *in1;
	register U i, j;
	volatile U div, mod;

	Out = _Out;
	In0 = _In0;
	In1 = _In1;
	div = n >> 6;
	mod = n & 63;

	for (i = m; i; i--) {
		in0 = *In0;
		in1 = In1;
		out = Out;
		In0 += In0s;
		In1 += In1s;
		Out += Outs;
		for (j = div; j; j--) {
			*(out +   0) = in0 * *(in1 +   0); 
			*(out +   1) = in0 * *(in1 +   1); 
			*(out +   2) = in0 * *(in1 +   2); 
			*(out +   3) = in0 * *(in1 +   3); 
			*(out +   4) = in0 * *(in1 +   4); 
			*(out +   5) = in0 * *(in1 +   5); 
			*(out +   6) = in0 * *(in1 +   6); 
			*(out +   7) = in0 * *(in1 +   7); 
			*(out +   8) = in0 * *(in1 +   8); 
			*(out +   9) = in0 * *(in1 +   9); 
			*(out +  10) = in0 * *(in1 +  10); 
			*(out +  11) = in0 * *(in1 +  11); 
			*(out +  12) = in0 * *(in1 +  12); 
			*(out +  13) = in0 * *(in1 +  13); 
			*(out +  14) = in0 * *(in1 +  14); 
			*(out +  15) = in0 * *(in1 +  15); 
			*(out +  16) = in0 * *(in1 +  16); 
			*(out +  17) = in0 * *(in1 +  17); 
			*(out +  18) = in0 * *(in1 +  18); 
			*(out +  19) = in0 * *(in1 +  19); 
			*(out +  20) = in0 * *(in1 +  20); 
			*(out +  21) = in0 * *(in1 +  21); 
			*(out +  22) = in0 * *(in1 +  22); 
			*(out +  23) = in0 * *(in1 +  23); 
			*(out +  24) = in0 * *(in1 +  24); 
			*(out +  25) = in0 * *(in1 +  25); 
			*(out +  26) = in0 * *(in1 +  26); 
			*(out +  27) = in0 * *(in1 +  27); 
			*(out +  28) = in0 * *(in1 +  28); 
			*(out +  29) = in0 * *(in1 +  29); 
			*(out +  30) = in0 * *(in1 +  30); 
			*(out +  31) = in0 * *(in1 +  31); 
			*(out +  32) = in0 * *(in1 +  32); 
			*(out +  33) = in0 * *(in1 +  33); 
			*(out +  34) = in0 * *(in1 +  34); 
			*(out +  35) = in0 * *(in1 +  35); 
			*(out +  36) = in0 * *(in1 +  36); 
			*(out +  37) = in0 * *(in1 +  37); 
			*(out +  38) = in0 * *(in1 +  38); 
			*(out +  39) = in0 * *(in1 +  39); 
			*(out +  40) = in0 * *(in1 +  40); 
			*(out +  41) = in0 * *(in1 +  41); 
			*(out +  42) = in0 * *(in1 +  42); 
			*(out +  43) = in0 * *(in1 +  43); 
			*(out +  44) = in0 * *(in1 +  44); 
			*(out +  45) = in0 * *(in1 +  45); 
			*(out +  46) = in0 * *(in1 +  46); 
			*(out +  47) = in0 * *(in1 +  47); 
			*(out +  48) = in0 * *(in1 +  48); 
			*(out +  49) = in0 * *(in1 +  49); 
			*(out +  50) = in0 * *(in1 +  50); 
			*(out +  51) = in0 * *(in1 +  51); 
			*(out +  52) = in0 * *(in1 +  52); 
			*(out +  53) = in0 * *(in1 +  53); 
			*(out +  54) = in0 * *(in1 +  54); 
			*(out +  55) = in0 * *(in1 +  55); 
			*(out +  56) = in0 * *(in1 +  56); 
			*(out +  57) = in0 * *(in1 +  57); 
			*(out +  58) = in0 * *(in1 +  58); 
			*(out +  59) = in0 * *(in1 +  59); 
			*(out +  50) = in0 * *(in1 +  50); 
			*(out +  61) = in0 * *(in1 +  61); 
			*(out +  62) = in0 * *(in1 +  62); 
			*(out +  63) = in0 * *(in1 +  63); 
			in1 += 64;
			out += 64;
		}
	}
	if (mod) {
		div = n - mod;
		outer_product_32(_Out + div, _In0, _In1 + div, m, mod, Outs, In0s, In1s);
	}
}
//------------------------------------------------------------------------------
#endif
