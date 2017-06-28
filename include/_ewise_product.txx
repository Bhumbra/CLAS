#ifndef _ewise_product_txx
#define _ewise_product_txx
//------------------------------------------------------------------------------
template <class T, class U>
static inline void ewise_product_1 (T* _Out, 
																		T* _In0, 
																		T* _In1, 
																		volatile const U m, 
																		volatile const U k,
																		volatile const U Outs,
																		volatile const U In0s,
																		volatile const U In1s = 0) { 
	register T *Out, *In0, *In1;
	register T *out, *in0, *in1;
	register U i, j;

	In0 = _In0;
	In1 = _In1;
	Out = _Out;

	for (i = m; i; i--) {
		in0 = In0;
		in1 = In1;
		out = Out;
		In0 += In0s;
		In1 += In1s;
		Out += Outs;
		for (j = k; j; j--) {
			*(out +   0) = *(in0 +   0) * *(in1 +   0); 
			in0 ++;
			in1 ++;
			out ++;
		}
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void ewise_product_2 (T* _Out, 
																		T* _In0, 
																		T* _In1, 
																		volatile const U m, 
																		volatile const U k,
																		volatile const U Outs,
																		volatile const U In0s,
																		volatile const U In1s = 0) { 
	register T *Out, *In0, *In1;
	register T *out, *in0, *in1;
	register U i, j;
	volatile U div, mod;

	Out = _Out;
	In0 = _In0;
	In1 = _In1;
	div = k >> 1;
	mod = k & 1;

	for (i = m; i; i--) {
		in0 = In0;
		in1 = In1;
		out = Out;
		In0 += In0s;
		In1 += In1s;
		Out += Outs;
		for (j = div; j; j--) {
			*(out +   0) = *(in0 +   0) * *(in1 +   0); 
			*(out +   1) = *(in0 +   1) * *(in1 +   1); 
			in0 += 2;
			in1 += 2;
			out += 2;
		}
	}
	if (mod) {
		div = k - mod;
		ewise_product_1(_Out + div, _In0 + div, _In1 + div, m, mod, Outs, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void ewise_product_4 (T* _Out, 
																		T* _In0, 
																		T* _In1, 
																		volatile const U m, 
																		volatile const U k,
																		volatile const U Outs,
																		volatile const U In0s,
																		volatile const U In1s = 0) { 
	register T *Out, *In0, *In1;
	register T *out, *in0, *in1;
	register U i, j;
	volatile U div, mod;

	Out = _Out;
	In0 = _In0;
	In1 = _In1;
	div = k >> 2;
	mod = k & 3;

	for (i = m; i; i--) {
		in0 = In0;
		in1 = In1;
		out = Out;
		In0 += In0s;
		In1 += In1s;
		Out += Outs;
		for (j = div; j; j--) {
			*(out +   0) = *(in0 +   0) * *(in1 +   0); 
			*(out +   1) = *(in0 +   1) * *(in1 +   1); 
			*(out +   2) = *(in0 +   2) * *(in1 +   2); 
			*(out +   3) = *(in0 +   3) * *(in1 +   3); 
			in0 += 4;
			in1 += 4;
			out += 4;
		}
	}
	if (mod) {
		div = k - mod;
		ewise_product_2(_Out + div, _In0 + div, _In1 + div, m, mod, Outs, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void ewise_product_8 (T* _Out, 
																		T* _In0, 
																		T* _In1, 
																		volatile const U m, 
																		volatile const U k,
																		volatile const U Outs,
																		volatile const U In0s,
																		volatile const U In1s = 0) { 
	register T *Out, *In0, *In1;
	register T *out, *in0, *in1;
	register U i, j;
	volatile U div, mod;

	Out = _Out;
	In0 = _In0;
	In1 = _In1;
	div = k >> 3;
	mod = k & 7;

	for (i = m; i; i--) {
		in0 = In0;
		in1 = In1;
		out = Out;
		In0 += In0s;
		In1 += In1s;
		Out += Outs;
		for (j = div; j; j--) {
			*(out +   0) = *(in0 +   0) * *(in1 +   0); 
			*(out +   1) = *(in0 +   1) * *(in1 +   1); 
			*(out +   2) = *(in0 +   2) * *(in1 +   2); 
			*(out +   3) = *(in0 +   3) * *(in1 +   3); 
			*(out +   4) = *(in0 +   4) * *(in1 +   4); 
			*(out +   5) = *(in0 +   5) * *(in1 +   5); 
			*(out +   6) = *(in0 +   6) * *(in1 +   6); 
			*(out +   7) = *(in0 +   7) * *(in1 +   7); 
			in0 += 8;
			in1 += 8;
			out += 8;
		}
  }
	if (mod) {
		div = k - mod;
		ewise_product_4(_Out + div, _In0 + div, _In1 + div, m, mod, Outs, In0s, In1s);
	}
}
//------------------------------------------------------------------------------
template <class T, class U>
static inline void ewise_product_16(T* _Out, 
																		T* _In0, 
																		T* _In1, 
																		volatile const U m, 
																		volatile const U k,
																		volatile const U Outs,
																		volatile const U In0s,
																		volatile const U In1s = 0) { 
	register T *Out, *In0, *In1;
	register T *out, *in0, *in1;
	register U i, j;
	volatile U div, mod;

	Out = _Out;
	In0 = _In0;
	In1 = _In1;
	div = k >> 4;
	mod = k & 15;

	for (i = m; i; i--) {
		in0 = In0;
		in1 = In1;
		out = Out;
		In0 += In0s;
		In1 += In1s;
		Out += Outs;
		for (j = div; j; j--) {
			*(out +   0) = *(in0 +   0) * *(in1 +   0); 
			*(out +   1) = *(in0 +   1) * *(in1 +   1); 
			*(out +   2) = *(in0 +   2) * *(in1 +   2); 
			*(out +   3) = *(in0 +   3) * *(in1 +   3); 
			*(out +   4) = *(in0 +   4) * *(in1 +   4); 
			*(out +   5) = *(in0 +   5) * *(in1 +   5); 
			*(out +   6) = *(in0 +   6) * *(in1 +   6); 
			*(out +   7) = *(in0 +   7) * *(in1 +   7); 
			*(out +   8) = *(in0 +   8) * *(in1 +   8); 
			*(out +   9) = *(in0 +   9) * *(in1 +   9); 
			*(out +  10) = *(in0 +  10) * *(in1 +  10); 
			*(out +  11) = *(in0 +  11) * *(in1 +  11); 
			*(out +  12) = *(in0 +  12) * *(in1 +  12); 
			*(out +  13) = *(in0 +  13) * *(in1 +  13); 
			*(out +  14) = *(in0 +  14) * *(in1 +  14); 
			*(out +  15) = *(in0 +  15) * *(in1 +  15); 
			in0 += 16;
			in1 += 16;
			out += 16;
		}
	}
	if (mod) {
		div = k - mod;
		ewise_product_8(_Out + div, _In0 + div, _In1 + div, m, mod, Outs, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
#endif

