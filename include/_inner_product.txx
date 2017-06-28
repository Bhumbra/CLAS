#ifndef _inner_product_txx
#define _inner_product_txx

//------------------------------------------------------------------------------
template <class T>
static inline void inner_product_1 (T* _Out, 
																		T* _In0, 
																		T* _In1, 
																		volatile const uint64_t m, 
																		volatile const uint64_t k,
																		volatile const uint64_t Outs = 1,
																		volatile const uint64_t In0s = 0,
																		volatile const uint64_t In1s = 0) { 
	register T out0;
	register T *Out, *In0, *In1;
	register T *in0, *in1;
	register uint64_t i, j;

	In0 = _In0;
	In1 = _In1;
	Out = _Out;

	for (i = m; i; i--) {
		in0 = In0;
		in1 = In1;
		out0 = 0.;
		In0 += In0s;
		In1 += In1s;
		for (j = k; j; j--) {
			out0 += *(in0 +   0) * *(in1 +   0); 
			in0 ++;
			in1 ++;
		}
		*Out += out0;
		Out += Outs;
	}
}

//------------------------------------------------------------------------------
template <class T>
static inline void inner_product_2 (T* _Out, 
																		T* _In0, 
																		T* _In1, 
																		volatile const uint64_t m, 
																		volatile const uint64_t k,
																		volatile const uint64_t Outs = 1,
																		volatile const uint64_t In0s = 0,
																		volatile const uint64_t In1s = 0) { 
	register T out0, out1;
	register T *Out, *In0, *In1;
	register T *in0, *in1;
	register uint64_t i, j;
	volatile uint64_t div, mod;

	div = k >> 1;
	mod = k & 1;

	In0 = _In0;
	In1 = _In1;
	Out = _Out;

	for (i = m; i; i--) {
		in0 = In0;
		in1 = In1;
		out0 = 0.;
		out1 = 0.;
		In0 += In0s;
		In1 += In1s;
		for (j = div; j; j--) {
			out0 += *(in0 +   0) * *(in1 +   0); 
			out1 += *(in0 +   1) * *(in1 +   1); 
			in0 += 2;
			in1 += 2;
		}
		*Out += out0 + out1;
		Out += Outs;
	}

	if (mod) {
		div = k - mod;
		inner_product_1(_Out, _In0 + div, _In1 + div, m, mod, Outs, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T>
static inline void inner_product_4 (T* _Out, 
																		T* _In0, 
																		T* _In1, 
																		volatile const uint64_t m, 
																		volatile const uint64_t k,
																		volatile const uint64_t Outs = 1,
																		volatile const uint64_t In0s = 0,
																		volatile const uint64_t In1s = 0) { 
	register T out0, out1;
	register T *Out, *In0, *In1;
	register T *in0, *in1;
	register uint64_t i, j;
	volatile uint64_t div, mod;

	div = k >> 2;
	mod = k & 3;

	In0 = _In0;
	In1 = _In1;
	Out = _Out;

	for (i = m; i; i--) {
		in0 = In0;
		in1 = In1;
		out0 = 0.;
		out1 = 0.;
		In0 += In0s;
		In1 += In1s;
		for (j = div; j; j--) {
			out0 += *(in0 +   0) * *(in1 +   0); 
			out1 += *(in0 +   1) * *(in1 +   1); 
			out0 += *(in0 +   2) * *(in1 +   2); 
			out1 += *(in0 +   3) * *(in1 +   3); 
			in0 += 4;
			in1 += 4;
		}
		*Out += out0 + out1;
		Out += Outs;
	}

	if (mod) {
		div = k - mod;
		inner_product_2(_Out, _In0 + div, _In1 + div, m, mod, Outs, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T>
static inline void inner_product_8 (T* _Out, 
																		T* _In0, 
																		T* _In1, 
																		volatile const uint64_t m, 
																		volatile const uint64_t k,
																		volatile const uint64_t Outs = 1,
																		volatile const uint64_t In0s = 0,
																		volatile const uint64_t In1s = 0) { 
	register T out0, out1;
	register T *Out, *In0, *In1;
	register T *in0, *in1;
	register uint64_t i, j;
	volatile uint64_t div, mod;

	div = k >> 3;
	mod = k & 7;

	In0 = _In0;
	In1 = _In1;
	Out = _Out;

	for (i = m; i; i--) {
		in0 = In0;
		in1 = In1;
		out0 = 0.;
		out1 = 0.;
		In0 += In0s;
		In1 += In1s;
		for (j = div; j; j--) {
			out0 += *(in0 +   0) * *(in1 +   0); 
			out1 += *(in0 +   1) * *(in1 +   1); 
			out0 += *(in0 +   2) * *(in1 +   2); 
			out1 += *(in0 +   3) * *(in1 +   3); 
			out0 += *(in0 +   4) * *(in1 +   4); 
			out1 += *(in0 +   5) * *(in1 +   5); 
			out0 += *(in0 +   6) * *(in1 +   6); 
			out1 += *(in0 +   7) * *(in1 +   7); 
			in0 += 8;
			in1 += 8;
		}
		*Out += out0 + out1;
		Out += Outs;
	}

	if (mod) {
		div = k - mod;
		inner_product_4(_Out, _In0 + div, _In1 + div, m, mod, Outs, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T>
static inline void inner_product_16(T* _Out, 
																		T* _In0, 
																		T* _In1, 
																		volatile const uint64_t m, 
																		volatile const uint64_t k,
																		volatile const uint64_t Outs = 1,
																		volatile const uint64_t In0s = 0,
																		volatile const uint64_t In1s = 0) { 
	register T out0, out1;
	register T *Out, *In0, *In1;
	register T *in0, *in1;
	register uint64_t i, j;
	volatile uint64_t div, mod;

	div = k >> 4;
	mod = k & 15;

	In0 = _In0;
	In1 = _In1;
	Out = _Out;

	for (i = m; i; i--) {
		in0 = In0;
		in1 = In1;
		out0 = 0.;
		out1 = 0.;
		In0 += In0s;
		In1 += In1s;
		for (j = div; j; j--) {
			out0 += *(in0 +   0) * *(in1 +   0); 
			out1 += *(in0 +   1) * *(in1 +   1); 
			out0 += *(in0 +   2) * *(in1 +   2); 
			out1 += *(in0 +   3) * *(in1 +   3); 
			out0 += *(in0 +   4) * *(in1 +   4); 
			out1 += *(in0 +   5) * *(in1 +   5); 
			out0 += *(in0 +   6) * *(in1 +   6); 
			out1 += *(in0 +   7) * *(in1 +   7); 
			out0 += *(in0 +   8) * *(in1 +   8); 
			out1 += *(in0 +   9) * *(in1 +   9); 
			out0 += *(in0 +  10) * *(in1 +  10); 
			out1 += *(in0 +  11) * *(in1 +  11); 
			out0 += *(in0 +  12) * *(in1 +  12); 
			out1 += *(in0 +  13) * *(in1 +  13); 
			out0 += *(in0 +  14) * *(in1 +  14); 
			out1 += *(in0 +  15) * *(in1 +  15); 
			in0 += 16;
			in1 += 16;
		}
		*Out += out0 + out1;
		Out += Outs;
	}

	if (mod) {
		div = k - mod;
		inner_product_8(_Out, _In0 + div, _In1 + div, m, mod, Outs, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T>
static inline void inner_product_32(T* _Out, 
																		T* _In0, 
																		T* _In1, 
																		volatile const uint64_t m, 
																		volatile const uint64_t k,
																		volatile const uint64_t Outs = 1,
																		volatile const uint64_t In0s = 0,
																		volatile const uint64_t In1s = 0) { 
	register T out0, out1;
	register T *Out, *In0, *In1;
	register T *in0, *in1;
	register uint64_t i, j;
	volatile uint64_t div, mod;

	div = k >> 5;
	mod = k & 31;

	In0 = _In0;
	In1 = _In1;
	Out = _Out;

	for (i = m; i; i--) {
		in0 = In0;
		in1 = In1;
		out0 = 0.;
		out1 = 0.;
		In0 += In0s;
		In1 += In1s;
		for (j = div; j; j--) {
			out0 += *(in0 +   0) * *(in1 +   0); 
			out1 += *(in0 +   1) * *(in1 +   1); 
			out0 += *(in0 +   2) * *(in1 +   2); 
			out1 += *(in0 +   3) * *(in1 +   3); 
			out0 += *(in0 +   4) * *(in1 +   4); 
			out1 += *(in0 +   5) * *(in1 +   5); 
			out0 += *(in0 +   6) * *(in1 +   6); 
			out1 += *(in0 +   7) * *(in1 +   7); 
			out0 += *(in0 +   8) * *(in1 +   8); 
			out1 += *(in0 +   9) * *(in1 +   9); 
			out0 += *(in0 +  10) * *(in1 +  10); 
			out1 += *(in0 +  11) * *(in1 +  11); 
			out0 += *(in0 +  12) * *(in1 +  12); 
			out1 += *(in0 +  13) * *(in1 +  13); 
			out0 += *(in0 +  14) * *(in1 +  14); 
			out1 += *(in0 +  15) * *(in1 +  15); 
			out0 += *(in0 +  16) * *(in1 +  16); 
			out1 += *(in0 +  17) * *(in1 +  17); 
			out0 += *(in0 +  18) * *(in1 +  18); 
			out1 += *(in0 +  19) * *(in1 +  19); 
			out0 += *(in0 +  20) * *(in1 +  20); 
			out1 += *(in0 +  21) * *(in1 +  21); 
			out0 += *(in0 +  22) * *(in1 +  22); 
			out1 += *(in0 +  23) * *(in1 +  23); 
			out0 += *(in0 +  24) * *(in1 +  24); 
			out1 += *(in0 +  25) * *(in1 +  25); 
			out0 += *(in0 +  26) * *(in1 +  26); 
			out1 += *(in0 +  27) * *(in1 +  27); 
			out0 += *(in0 +  28) * *(in1 +  28); 
			out1 += *(in0 +  29) * *(in1 +  29); 
			out0 += *(in0 +  30) * *(in1 +  30); 
			out1 += *(in0 +  31) * *(in1 +  31); 
			in0 += 32;
			in1 += 32;
		}
		*Out += out0 + out1;
		Out += Outs;
	}

	if (mod) {
		div = k - mod;
		inner_product_16(_Out, _In0 + div, _In1 + div, m, mod, Outs, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
#endif
