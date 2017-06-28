# ifndef _mcdot_product_1_txx
# define _mcdot_product_1_txx

//------------------------------------------------------------------------------
template <class T>
static inline void mcdot_product_1x1 (T* _Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const uint64_t m, 
																			volatile const uint64_t k,
																			volatile const uint64_t Outs = 1,
																			volatile const uint64_t In0s = 1,
																			volatile const uint64_t In1s = 1) {
	register T out0_0;
	register T in1_0_0;
	register T *Out, *In0;
	register T *in0, *in1;
	register uint64_t i, j;

	In0 = _In0;
	Out = _Out;

	for (i = m; i; i--) {
		in0 = In0;
		in1 = In1;
		out0_0 = 0.;
		In0 += In0s;
		for (j = k; j; j--) {
		  in1_0_0 = *(in1 + 0);
			in1 += In1s;
			out0_0 += *(in0 +   0) * in1_0_0; 
			in0 ++;
		}
		*Out += out0_0;
		Out += Outs;
	}
}

//------------------------------------------------------------------------------
template <class T>
static inline void mcdot_product_1x2 (T* _Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const uint64_t m, 
																			volatile const uint64_t k,
																			volatile const uint64_t Outs = 1,
																			volatile const uint64_t In0s = 1,
																			volatile const uint64_t In1s = 1) { 
	register T out0_0, out0_1;
	register T in1_0_0, in1_0_1;
	register T *Out, *In0;
	register T *in0, *in1;
	register uint64_t i, j;
	volatile uint64_t div, mod;

	div = k >> 1;
	mod = k & 1;

	In0 = _In0;
	Out = _Out;

	for (i = m; i; i--) {
		in0 = In0;
		in1 = In1;
		out0_0 = 0.;
		out0_1 = 0.;
		In0 += In0s;
		for (j = div; j; j--) {
			in1_0_0 = *(in1 +   0);
			in1 += In1s;
			in1_0_1 = *(in1 +   0);
			in1 += In1s;
			out0_0 += *(in0 +   0) * in1_0_0; 
			out0_1 += *(in0 +   1) * in1_0_1; 
			in0 += 2;
		}
		*Out += out0_0 + out0_1;
		Out += Outs;
	}

	if (mod) {
		div = k - mod;
		mcdot_product_1x1 (_Out, _In0 + div, In1 + div*In1s, m, mod, Outs, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T>
static inline void mcdot_product_1x4 (T* _Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const uint64_t m, 
																			volatile const uint64_t k,
																			volatile const uint64_t Outs = 1,
																			volatile const uint64_t In0s = 1,
																			volatile const uint64_t In1s = 1) { 
	register T out0_0, out0_1, out0_2, out0_3;
	register T in1_0_0, in1_0_1, in1_0_2, in1_0_3;
	register T *Out, *In0;
	register T *in0, *in1;
	register uint64_t i, j;
	volatile uint64_t div, mod;

	div = k >> 2;
	mod = k & 3;

	In0 = _In0;
	Out = _Out;

	for (i = m; i; i--) {
		in0 = In0;
		in1 = In1;
		out0_0 = 0.;
		out0_1 = 0.;
		out0_2 = 0.;
		out0_3 = 0.;
		In0 += In0s;
		for (j = div; j; j--) {
			in1_0_0 = *(in1 +   0);
			in1 += In1s;
			in1_0_1 = *(in1 +   0);
			in1 += In1s;
			in1_0_2 = *(in1 +   0);
			in1 += In1s;
			in1_0_3 = *(in1 +   0);
			in1 += In1s;
			out0_0 += *(in0 +   0) * in1_0_0; 
			out0_1 += *(in0 +   1) * in1_0_1; 
			out0_2 += *(in0 +   2) * in1_0_2; 
			out0_3 += *(in0 +   3) * in1_0_3; 
			in0 += 4;
		}
		*Out += (out0_0 + out0_2) + (out0_1 + out0_3);
		Out += Outs;
	}

	if (mod) {
		div = k - mod;
		mcdot_product_1x2 (_Out, _In0 + div, In1 + div*In1s, m, mod, Outs, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T>
static inline void mcdot_product_1x8 (T* _Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const uint64_t m, 
																			volatile const uint64_t k,
																			volatile const uint64_t Outs = 1,
																			volatile const uint64_t In0s = 1,
																			volatile const uint64_t In1s = 1) { 
	register T out0_0, out0_1, out0_2, out0_3;
	register T in1_0_0, in1_0_1, in1_0_2, in1_0_3;
	register T *Out, *In0;
	register T *in0, *in1;
	register uint64_t i, j;
	volatile uint64_t div, mod;

	div = k >> 3;
	mod = k & 7;

	In0 = _In0;
	Out = _Out;

	for (i = m; i; i--) {
		in0 = In0;
		in1 = In1;
		out0_0 = 0.;
		out0_1 = 0.;
		out0_2 = 0.;
		out0_3 = 0.;
		In0 += In0s;
		for (j = div; j; j--) {
			in1_0_0 = *(in1 +   0);
			in1 += In1s;
			in1_0_1 = *(in1 +   0);
			in1 += In1s;
			in1_0_2 = *(in1 +   0);
			in1 += In1s;
			in1_0_3 = *(in1 +   0);
			in1 += In1s;
			out0_0 += *(in0 +   0) * in1_0_0; 
			out0_1 += *(in0 +   1) * in1_0_1; 
			out0_2 += *(in0 +   2) * in1_0_2; 
			out0_3 += *(in0 +   3) * in1_0_3; 
			in0 += 4;
			in1_0_0 = *(in1 +   0);
			in1 += In1s;
			in1_0_1 = *(in1 +   0);
			in1 += In1s;
			in1_0_2 = *(in1 +   0);
			in1 += In1s;
			in1_0_3 = *(in1 +   0);
			in1 += In1s;
			out0_0 += *(in0 +   0) * in1_0_0; 
			out0_1 += *(in0 +   1) * in1_0_1; 
			out0_2 += *(in0 +   2) * in1_0_2; 
			out0_3 += *(in0 +   3) * in1_0_3; 
			in0 += 4;
		}
		*Out += (out0_0 + out0_2) + (out0_1 + out0_3);
		Out += Outs;
	}

	if (mod) {
		div = k - mod;
		mcdot_product_1x4 (_Out, _In0 + div, In1 + div*In1s, m, mod, Outs, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T>
static inline void mcdot_product_1x16(T* _Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const uint64_t m, 
																			volatile const uint64_t k,
																			volatile const uint64_t Outs = 1,
																			volatile const uint64_t In0s = 1,
																			volatile const uint64_t In1s = 1) { 
	register T out0_0, out0_1, out0_2, out0_3;
	register T in1_0_0, in1_0_1, in1_0_2, in1_0_3;
	register T *Out, *In0;
	register T *in0, *in1;
	register uint64_t i, j;
	volatile uint64_t div, mod;

	div = k >> 4;
	mod = k & 15;

	In0 = _In0;
	Out = _Out;

	for (i = m; i; i--) {
		in0 = In0;
		in1 = In1;
		out0_0 = 0.;
		out0_1 = 0.;
		out0_2 = 0.;
		out0_3 = 0.;
		In0 += In0s;
		for (j = div; j; j--) {
			in1_0_0 = *(in1 +   0);
			in1 += In1s;
			in1_0_1 = *(in1 +   0);
			in1 += In1s;
			in1_0_2 = *(in1 +   0);
			in1 += In1s;
			in1_0_3 = *(in1 +   0);
			in1 += In1s;
			out0_0 += *(in0 +   0) * in1_0_0; 
			out0_1 += *(in0 +   1) * in1_0_1; 
			out0_2 += *(in0 +   2) * in1_0_2; 
			out0_3 += *(in0 +   3) * in1_0_3; 
			in0 += 4;
			in1_0_0 = *(in1 +   0);
			in1 += In1s;
			in1_0_1 = *(in1 +   0);
			in1 += In1s;
			in1_0_2 = *(in1 +   0);
			in1 += In1s;
			in1_0_3 = *(in1 +   0);
			in1 += In1s;
			out0_0 += *(in0 +   0) * in1_0_0; 
			out0_1 += *(in0 +   1) * in1_0_1; 
			out0_2 += *(in0 +   2) * in1_0_2; 
			out0_3 += *(in0 +   3) * in1_0_3; 
			in0 += 4;
			in1_0_0 = *(in1 +   0);
			in1 += In1s;
			in1_0_1 = *(in1 +   0);
			in1 += In1s;
			in1_0_2 = *(in1 +   0);
			in1 += In1s;
			in1_0_3 = *(in1 +   0);
			in1 += In1s;
			out0_0 += *(in0 +   0) * in1_0_0; 
			out0_1 += *(in0 +   1) * in1_0_1; 
			out0_2 += *(in0 +   2) * in1_0_2; 
			out0_3 += *(in0 +   3) * in1_0_3; 
			in0 += 4;
			in1_0_0 = *(in1 +   0);
			in1 += In1s;
			in1_0_1 = *(in1 +   0);
			in1 += In1s;
			in1_0_2 = *(in1 +   0);
			in1 += In1s;
			in1_0_3 = *(in1 +   0);
			in1 += In1s;
			out0_0 += *(in0 +   0) * in1_0_0; 
			out0_1 += *(in0 +   1) * in1_0_1; 
			out0_2 += *(in0 +   2) * in1_0_2; 
			out0_3 += *(in0 +   3) * in1_0_3; 
			in0 += 4;
		}
		*Out += (out0_0 + out0_2) + (out0_1 + out0_3);
		Out += Outs;
	}

	if (mod) {
		div = k - mod;
		mcdot_product_1x8 (_Out, _In0 + div, In1 + div*In1s, m, mod, Outs, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T>
static inline void mcdot_product_1x32(T* _Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const uint64_t m, 
																			volatile const uint64_t k,
																			volatile const uint64_t Outs = 1,
																			volatile const uint64_t In0s = 1,
																			volatile const uint64_t In1s = 1) { 
	register T out0_0, out0_1, out0_2, out0_3;
	register T in1_0_0, in1_0_1, in1_0_2, in1_0_3;
	register T *Out, *In0;
	register T *in0, *in1;
	register uint64_t i, j;
	volatile uint64_t div, mod;

	div = k >> 5;
	mod = k & 31;

	In0 = _In0;
	Out = _Out;

	for (i = m; i; i--) {
		in0 = In0;
		in1 = In1;
		out0_0 = 0.;
		out0_1 = 0.;
		out0_2 = 0.;
		out0_3 = 0.;
		In0 += In0s;
		for (j = div; j; j--) {
			in1_0_0 = *(in1 +   0);
			in1 += In1s;
			in1_0_1 = *(in1 +   0);
			in1 += In1s;
			in1_0_2 = *(in1 +   0);
			in1 += In1s;
			in1_0_3 = *(in1 +   0);
			in1 += In1s;
			out0_0 += *(in0 +   0) * in1_0_0; 
			out0_1 += *(in0 +   1) * in1_0_1; 
			out0_2 += *(in0 +   2) * in1_0_2; 
			out0_3 += *(in0 +   3) * in1_0_3; 
			in0 += 4;
			in1_0_0 = *(in1 +   0);
			in1 += In1s;
			in1_0_1 = *(in1 +   0);
			in1 += In1s;
			in1_0_2 = *(in1 +   0);
			in1 += In1s;
			in1_0_3 = *(in1 +   0);
			in1 += In1s;
			out0_0 += *(in0 +   0) * in1_0_0; 
			out0_1 += *(in0 +   1) * in1_0_1; 
			out0_2 += *(in0 +   2) * in1_0_2; 
			out0_3 += *(in0 +   3) * in1_0_3; 
			in0 += 4;
			in1_0_0 = *(in1 +   0);
			in1 += In1s;
			in1_0_1 = *(in1 +   0);
			in1 += In1s;
			in1_0_2 = *(in1 +   0);
			in1 += In1s;
			in1_0_3 = *(in1 +   0);
			in1 += In1s;
			out0_0 += *(in0 +   0) * in1_0_0; 
			out0_1 += *(in0 +   1) * in1_0_1; 
			out0_2 += *(in0 +   2) * in1_0_2; 
			out0_3 += *(in0 +   3) * in1_0_3; 
			in0 += 4;
			in1_0_0 = *(in1 +   0);
			in1 += In1s;
			in1_0_1 = *(in1 +   0);
			in1 += In1s;
			in1_0_2 = *(in1 +   0);
			in1 += In1s;
			in1_0_3 = *(in1 +   0);
			in1 += In1s;
			out0_0 += *(in0 +   0) * in1_0_0; 
			out0_1 += *(in0 +   1) * in1_0_1; 
			out0_2 += *(in0 +   2) * in1_0_2; 
			out0_3 += *(in0 +   3) * in1_0_3; 
			in0 += 4;
			in1_0_0 = *(in1 +   0);
			in1 += In1s;
			in1_0_1 = *(in1 +   0);
			in1 += In1s;
			in1_0_2 = *(in1 +   0);
			in1 += In1s;
			in1_0_3 = *(in1 +   0);
			in1 += In1s;
			out0_0 += *(in0 +   0) * in1_0_0; 
			out0_1 += *(in0 +   1) * in1_0_1; 
			out0_2 += *(in0 +   2) * in1_0_2; 
			out0_3 += *(in0 +   3) * in1_0_3; 
			in0 += 4;
			in1_0_0 = *(in1 +   0);
			in1 += In1s;
			in1_0_1 = *(in1 +   0);
			in1 += In1s;
			in1_0_2 = *(in1 +   0);
			in1 += In1s;
			in1_0_3 = *(in1 +   0);
			in1 += In1s;
			out0_0 += *(in0 +   0) * in1_0_0; 
			out0_1 += *(in0 +   1) * in1_0_1; 
			out0_2 += *(in0 +   2) * in1_0_2; 
			out0_3 += *(in0 +   3) * in1_0_3; 
			in0 += 4;
			in1_0_0 = *(in1 +   0);
			in1 += In1s;
			in1_0_1 = *(in1 +   0);
			in1 += In1s;
			in1_0_2 = *(in1 +   0);
			in1 += In1s;
			in1_0_3 = *(in1 +   0);
			in1 += In1s;
			out0_0 += *(in0 +   0) * in1_0_0; 
			out0_1 += *(in0 +   1) * in1_0_1; 
			out0_2 += *(in0 +   2) * in1_0_2; 
			out0_3 += *(in0 +   3) * in1_0_3; 
			in0 += 4;
			in1_0_0 = *(in1 +   0);
			in1 += In1s;
			in1_0_1 = *(in1 +   0);
			in1 += In1s;
			in1_0_2 = *(in1 +   0);
			in1 += In1s;
			in1_0_3 = *(in1 +   0);
			in1 += In1s;
			out0_0 += *(in0 +   0) * in1_0_0; 
			out0_1 += *(in0 +   1) * in1_0_1; 
			out0_2 += *(in0 +   2) * in1_0_2; 
			out0_3 += *(in0 +   3) * in1_0_3; 
			in0 += 4;
		}
		*Out += (out0_0 + out0_2) + (out0_1 + out0_3);
		Out += Outs;
	}

	if (mod) {
		div = k - mod;
		mcdot_product_1x16(_Out, _In0 + div, In1 + div*In1s, m, mod, Outs, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
#endif
