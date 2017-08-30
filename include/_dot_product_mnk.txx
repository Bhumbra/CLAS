//------------------------------------------------------------------------------
# ifndef _dot_product_mnk_txx
# define _dot_product_mnk_txx

# include "clas.txx"

# include "tcache.txx"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// C += A X B
template <class T, class U>
static NOINLINE void dot_product_mnk_1x8x8 (T* Out, 
																						T* In0, 
																						T* In1, 
																						volatile const U m,
																						volatile const U k, 
																						volatile const U n,
																						register U OutS = 0,
																						register U In0S = 0,
																						register U In1S = 0) {
	register T i0, i1, i2, i3, i4, i5, i6, i7;
	register T o0, o1, o2, o3, o4, o5, o6, o7;
	register U i, j; 
	U h, M, K, N;
	register T *_out, *_in0, *_in1;	
	register T *out,  *in0,  *in1;

	if (!OutS) {OutS = n;}
	if (!In0S) {In0S = k;}
	if (!In1S) {In1S = n;}
	M = m;
	K = k >> 3;
	N = n >> 3;

	for (h = M; h; h--) {
		_out = Out;
		Out += OutS;
		_in0 = In0; 
		In0 += In0S;
		_in1 = In1;
		for (i = N; i; i--) {
			out = _out;
			_out += (U)8;
			in0 = _in0;
			in1 = _in1;
			_in1 += (U)8;
			o0 = *(out + 0);
			o1 = *(out + 1);
			o2 = *(out + 2);
			o3 = *(out + 3);
			o4 = *(out + 4);
			o5 = *(out + 5);
			o6 = *(out + 6);
			o7 = *(out + 7);
			for (j = K; j; j--) {
				i0 = *(in0 + 0);
				i1 = *(in0 + 1);
				i2 = *(in0 + 2);
				i3 = *(in0 + 3);
				i4 = *(in0 + 4);
				i5 = *(in0 + 5);
				i6 = *(in0 + 6);
				i7 = *(in0 + 7);
				in0 += (U)8;
				o0 += i0 * *(in1 + 0);
				o1 += i0 * *(in1 + 1);
				o2 += i0 * *(in1 + 2);
				o3 += i0 * *(in1 + 3);
				o4 += i0 * *(in1 + 4);
				o5 += i0 * *(in1 + 5);
				o6 += i0 * *(in1 + 6);
				o7 += i0 * *(in1 + 7);
				in1 += In1S;
				o0 += i1 * *(in1 + 0);
				o1 += i1 * *(in1 + 1);
				o2 += i1 * *(in1 + 2);
				o3 += i1 * *(in1 + 3);
				o4 += i1 * *(in1 + 4);
				o5 += i1 * *(in1 + 5);
				o6 += i1 * *(in1 + 6);
				o7 += i1 * *(in1 + 7);
				in1 += In1S;
				o0 += i2 * *(in1 + 0);
				o1 += i2 * *(in1 + 1);
				o2 += i2 * *(in1 + 2);
				o3 += i2 * *(in1 + 3);
				o4 += i2 * *(in1 + 4);
				o5 += i2 * *(in1 + 5);
				o6 += i2 * *(in1 + 6);
				o7 += i2 * *(in1 + 7);
				in1 += In1S;
				o0 += i3 * *(in1 + 0);
				o1 += i3 * *(in1 + 1);
				o2 += i3 * *(in1 + 2);
				o3 += i3 * *(in1 + 3);
				o4 += i3 * *(in1 + 4);
				o5 += i3 * *(in1 + 5);
				o6 += i3 * *(in1 + 6);
				o7 += i3 * *(in1 + 7);
				in1 += In1S;
				o0 += i4 * *(in1 + 0);
				o1 += i4 * *(in1 + 1);
				o2 += i4 * *(in1 + 2);
				o3 += i4 * *(in1 + 3);
				o4 += i4 * *(in1 + 4);
				o5 += i4 * *(in1 + 5);
				o6 += i4 * *(in1 + 6);
				o7 += i4 * *(in1 + 7);
				in1 += In1S;
				o0 += i5 * *(in1 + 0);
				o1 += i5 * *(in1 + 1);
				o2 += i5 * *(in1 + 2);
				o3 += i5 * *(in1 + 3);
				o4 += i5 * *(in1 + 4);
				o5 += i5 * *(in1 + 5);
				o6 += i5 * *(in1 + 6);
				o7 += i5 * *(in1 + 7);
				in1 += In1S;
				o0 += i6 * *(in1 + 0);
				o1 += i6 * *(in1 + 1);
				o2 += i6 * *(in1 + 2);
				o3 += i6 * *(in1 + 3);
				o4 += i6 * *(in1 + 4);
				o5 += i6 * *(in1 + 5);
				o6 += i6 * *(in1 + 6);
				o7 += i6 * *(in1 + 7);
				in1 += In1S;
				o0 += i7 * *(in1 + 0);
				o1 += i7 * *(in1 + 1);
				o2 += i7 * *(in1 + 2);
				o3 += i7 * *(in1 + 3);
				o4 += i7 * *(in1 + 4);
				o5 += i7 * *(in1 + 5);
				o6 += i7 * *(in1 + 6);
				o7 += i7 * *(in1 + 7);
				in1 += In1S;
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

//------------------------------------------------------------------------------
// C += A X B
template <class T, class U>
static NOINLINE void dot_product_MNK_1x8x8 (T* Out, 
																						T* In0, 
																						T* In1, 
																						volatile const U m,
																						volatile const U k, 
																						volatile const U n,
																						register U OutS = 0) {
	register T i0, i1, i2, i3, i4, i5, i6, i7;
	register T o0, o1, o2, o3, o4, o5, o6, o7;
	register U i, j; 
	register U In0S, In1S;
	U h, M, K, N;
	register T *_out, *_in0, *_in1;	
	register T *out,  *in0,  *in1;

	if (!OutS) {OutS = n;}
	In0S = k;
	In1S = n;
	M = m;
	K = k >> 3;
	N = n >> 3;

	for (h = M; h; h--) {
		_out = Out;
		Out += OutS;
		_in0 = In0; 
		In0 += In0S;
		_in1 = In1;
		for (i = N; i; i--) {
			out = _out;
			_out += (U)8;
			in0 = _in0;
			in1 = _in1;
			_in1 += (U)8;
			o0 = *(out + 0);
			o1 = *(out + 1);
			o2 = *(out + 2);
			o3 = *(out + 3);
			o4 = *(out + 4);
			o5 = *(out + 5);
			o6 = *(out + 6);
			o7 = *(out + 7);
			for (j = K; j; j--) {
				i0 = *(in0 + 0);
				i1 = *(in0 + 1);
				i2 = *(in0 + 2);
				i3 = *(in0 + 3);
				i4 = *(in0 + 4);
				i5 = *(in0 + 5);
				i6 = *(in0 + 6);
				i7 = *(in0 + 7);
				in0 += (U)8;
				PREFETCH_READ_3(in0);
				o0 += i0 * *(in1 + 0);
				o1 += i0 * *(in1 + 1);
				o2 += i0 * *(in1 + 2);
				o3 += i0 * *(in1 + 3);
				o4 += i0 * *(in1 + 4);
				o5 += i0 * *(in1 + 5);
				o6 += i0 * *(in1 + 6);
				o7 += i0 * *(in1 + 7);
				in1 += In1S;
				PREFETCH_READ_3(in1+In1S*8);
				o0 += i1 * *(in1 + 0);
				o1 += i1 * *(in1 + 1);
				o2 += i1 * *(in1 + 2);
				o3 += i1 * *(in1 + 3);
				o4 += i1 * *(in1 + 4);
				o5 += i1 * *(in1 + 5);
				o6 += i1 * *(in1 + 6);
				o7 += i1 * *(in1 + 7);
				in1 += In1S;
				PREFETCH_READ_3(in1+In1S*8);
				o0 += i2 * *(in1 + 0);
				o1 += i2 * *(in1 + 1);
				o2 += i2 * *(in1 + 2);
				o3 += i2 * *(in1 + 3);
				o4 += i2 * *(in1 + 4);
				o5 += i2 * *(in1 + 5);
				o6 += i2 * *(in1 + 6);
				o7 += i2 * *(in1 + 7);
				in1 += In1S;
				PREFETCH_READ_3(in1+In1S*8);
				o0 += i3 * *(in1 + 0);
				o1 += i3 * *(in1 + 1);
				o2 += i3 * *(in1 + 2);
				o3 += i3 * *(in1 + 3);
				o4 += i3 * *(in1 + 4);
				o5 += i3 * *(in1 + 5);
				o6 += i3 * *(in1 + 6);
				o7 += i3 * *(in1 + 7);
				in1 += In1S;
				PREFETCH_READ_3(in1+In1S*8);
				o0 += i4 * *(in1 + 0);
				o1 += i4 * *(in1 + 1);
				o2 += i4 * *(in1 + 2);
				o3 += i4 * *(in1 + 3);
				o4 += i4 * *(in1 + 4);
				o5 += i4 * *(in1 + 5);
				o6 += i4 * *(in1 + 6);
				o7 += i4 * *(in1 + 7);
				in1 += In1S;
				PREFETCH_READ_3(in1+In1S*8);
				o0 += i5 * *(in1 + 0);
				o1 += i5 * *(in1 + 1);
				o2 += i5 * *(in1 + 2);
				o3 += i5 * *(in1 + 3);
				o4 += i5 * *(in1 + 4);
				o5 += i5 * *(in1 + 5);
				o6 += i5 * *(in1 + 6);
				o7 += i5 * *(in1 + 7);
				in1 += In1S;
				PREFETCH_READ_3(in1+In1S*8);
				o0 += i6 * *(in1 + 0);
				o1 += i6 * *(in1 + 1);
				o2 += i6 * *(in1 + 2);
				o3 += i6 * *(in1 + 3);
				o4 += i6 * *(in1 + 4);
				o5 += i6 * *(in1 + 5);
				o6 += i6 * *(in1 + 6);
				o7 += i6 * *(in1 + 7);
				in1 += In1S;
				PREFETCH_READ_3(in1+In1S*8);
				o0 += i7 * *(in1 + 0);
				o1 += i7 * *(in1 + 1);
				o2 += i7 * *(in1 + 2);
				o3 += i7 * *(in1 + 3);
				o4 += i7 * *(in1 + 4);
				o5 += i7 * *(in1 + 5);
				o6 += i7 * *(in1 + 6);
				o7 += i7 * *(in1 + 7);
				in1 += In1S;
				PREFETCH_READ_3(in1+In1S*8);
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


//------------------------------------------------------------------------------
// C += A.T X B
template <class T, class U>
static NOINLINE void dot_product_kmn_1x8x8 (register T* _Out, 
																					register T* In0, 
																					register T* In1, 
																					volatile const U m,
																					volatile const U k, 
																					volatile const U n,
																					volatile const U Outs) {
	register T in0_0, in0_1, in0_2, in0_3, in0_4, in0_5, in0_6, in0_7;
	register T in1_0, in1_1, in1_2, in1_3, in1_4, in1_5, in1_6, in1_7;
	register U h, i, j; 
	U OutS, m3, N;
	register U N3;
	register T *Out, *_out, *_in0, *_in1;
	register T *out,  *in0,  *in1;

	OutS = Outs << 3;
	m3 = m >> 3;
	N = n >> 3;

	for (h = k; h; h--) {
		Out = _Out;
		_in0 = In0;
		In0 += (U)64;
		_in1 = In1;
		In1 += (U)64;
		for (i = m3; i; i--) {
			_out = Out;
			Out += OutS;
			in0 = _in0;
			_in0 += (U)8;
			in1 = _in1;
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in0_4 = *(in0 + 4);
			in0_5 = *(in0 + 5);
			in0_6 = *(in0 + 6);
			in0_7 = *(in0 + 7);
			for (j = N; j; j--) {
				out = _out;
				_out += (U)8;
				in1_0 = *(in1 + 0);
				in1_1 = *(in1 + 1);
				in1_2 = *(in1 + 2);
				in1_3 = *(in1 + 3);
				in1_4 = *(in1 + 4);
				in1_5 = *(in1 + 5);
				in1_6 = *(in1 + 6);
				in1_7 = *(in1 + 7);
				in1 += (U)8;

				*(out + 0) += in0_0 * in1_0;
				*(out + 1) += in0_0 * in1_1;
				*(out + 2) += in0_0 * in1_2;
				*(out + 3) += in0_0 * in1_3;
				*(out + 4) += in0_0 * in1_4;
				*(out + 5) += in0_0 * in1_5;
				*(out + 6) += in0_0 * in1_6;
				*(out + 7) += in0_0 * in1_7;
				out += OutS;

				*(out + 0) += in0_1 * in1_0;
				*(out + 1) += in0_1 * in1_1;
				*(out + 2) += in0_1 * in1_2;
				*(out + 3) += in0_1 * in1_3;
				*(out + 4) += in0_1 * in1_4;
				*(out + 5) += in0_1 * in1_5;
				*(out + 6) += in0_1 * in1_6;
				*(out + 7) += in0_1 * in1_7;
				out += OutS;

				*(out + 0) += in0_2 * in1_0;
				*(out + 1) += in0_2 * in1_1;
				*(out + 2) += in0_2 * in1_2;
				*(out + 3) += in0_2 * in1_3;
				*(out + 4) += in0_2 * in1_4;
				*(out + 5) += in0_2 * in1_5;
				*(out + 6) += in0_2 * in1_6;
				*(out + 7) += in0_2 * in1_7;
				out += OutS;

				*(out + 0) += in0_3 * in1_0;
				*(out + 1) += in0_3 * in1_1;
				*(out + 2) += in0_3 * in1_2;
				*(out + 3) += in0_3 * in1_3;
				*(out + 4) += in0_3 * in1_4;
				*(out + 5) += in0_3 * in1_5;
				*(out + 6) += in0_3 * in1_6;
				*(out + 7) += in0_3 * in1_7;
				out += OutS;

				*(out + 0) += in0_4 * in1_0;
				*(out + 1) += in0_4 * in1_1;
				*(out + 2) += in0_4 * in1_2;
				*(out + 3) += in0_4 * in1_3;
				*(out + 4) += in0_4 * in1_4;
				*(out + 5) += in0_4 * in1_5;
				*(out + 6) += in0_4 * in1_6;
				*(out + 7) += in0_4 * in1_7;
				out += OutS;

				*(out + 0) += in0_5 * in1_0;
				*(out + 1) += in0_5 * in1_1;
				*(out + 2) += in0_5 * in1_2;
				*(out + 3) += in0_5 * in1_3;
				*(out + 4) += in0_5 * in1_4;
				*(out + 5) += in0_5 * in1_5;
				*(out + 6) += in0_5 * in1_6;
				*(out + 7) += in0_5 * in1_7;
				out += OutS;

				*(out + 0) += in0_6 * in1_0;
				*(out + 1) += in0_6 * in1_1;
				*(out + 2) += in0_6 * in1_2;
				*(out + 3) += in0_6 * in1_3;
				*(out + 4) += in0_6 * in1_4;
				*(out + 5) += in0_6 * in1_5;
				*(out + 6) += in0_6 * in1_6;
				*(out + 7) += in0_6 * in1_7;
				out += OutS;

				*(out + 0) += in0_7 * in1_0;
				*(out + 1) += in0_7 * in1_1;
				*(out + 2) += in0_7 * in1_2;
				*(out + 3) += in0_7 * in1_3;
				*(out + 4) += in0_7 * in1_4;
				*(out + 5) += in0_7 * in1_5;
				*(out + 6) += in0_7 * in1_6;
				*(out + 7) += in0_7 * in1_7;
				out += OutS;
			}
		}
	}
}


//------------------------------------------------------------------------------
// C += A X B
template <class T, class U>
static NOINLINE void dot_product_MNK_2x8x8 (T* Out, 
																						T* In0, 
																						T* In1, 
																						volatile const U m,
																						volatile const U k, 
																						volatile const U n,
																						register U OutS = 0) {
	T in0_0_0, in0_0_1, in0_0_2, in0_0_3, in0_0_4, in0_0_5, in0_0_6, in0_0_7;
	T in0_1_0, in0_1_1, in0_1_2, in0_1_3, in0_1_4, in0_1_5, in0_1_6, in0_1_7;
	register T in1_0, in1_1, in1_2, in1_3, in1_4, in1_5, in1_6, in1_7;
	register T out0_0, out0_1, out0_2, out0_3, out0_4, out0_5, out0_6, out0_7;
	register T out1_0, out1_1, out1_2, out1_3, out1_4, out1_5, out1_6, out1_7;
	U h, M, K, N;
	register U i, j; 
	register U In0S, In1S;
	register T *_out, *_in0, *_in1;	
	register T *out,  *in0,  *in1;
	register T *out_, *in0_;

	if (!OutS) {OutS = n;}
	In0S = k;
	In1S = n;
	M = m >> 1;
	K = k >> 3;
	N = n >> 3;

	for (h = M; h; h--) {
		_out = Out;
		Out += OutS * 2;
		_in0 = In0; 
		In0 += In0S * 2;
		_in1 = In1;
		for (i = N; i; i--) {
			out = _out;
			out_ = out + OutS;
			_out += (U)8;
			in0 = _in0;
			in0_ = in0 + k;
			in1 = _in1;
			_in1 += (U)8;
			out0_0 = *(out  + 0);
			out0_1 = *(out  + 1);
			out0_2 = *(out  + 2);
			out0_3 = *(out  + 3);
			out0_4 = *(out  + 4);
			out0_5 = *(out  + 5);
			out0_6 = *(out  + 6);
			out0_7 = *(out  + 7);
			out1_0 = *(out_ + 0);
			out1_1 = *(out_ + 1);
			out1_2 = *(out_ + 2);
			out1_3 = *(out_ + 3);
			out1_4 = *(out_ + 4);
			out1_5 = *(out_ + 5);
			out1_6 = *(out_ + 6);
			out1_7 = *(out_ + 7);
			for (j = K; j; j--) {
				in0_0_0 = *(in0  + 0);
				in0_0_1 = *(in0  + 1);
				in0_0_2 = *(in0  + 2);
				in0_0_3 = *(in0  + 3);
				in0_0_4 = *(in0  + 4);
				in0_0_5 = *(in0  + 5);
				in0_0_6 = *(in0  + 6);
				in0_0_7 = *(in0  + 7);
				in0 += (U)8;
				PREFETCH_READ_3(in0);
				in0_1_0 = *(in0_ + 0);
				in0_1_1 = *(in0_ + 1);
				in0_1_2 = *(in0_ + 2);
				in0_1_3 = *(in0_ + 3);
				in0_1_4 = *(in0_ + 4);
				in0_1_5 = *(in0_ + 5);
				in0_1_6 = *(in0_ + 6);
				in0_1_7 = *(in0_ + 7);
				in0_ += (U)8;
				PREFETCH_READ_3(in0_);
				in1_0 = *(in1 + 0);
				in1_1 = *(in1 + 1);
				in1_2 = *(in1 + 2);
				in1_3 = *(in1 + 3);
				in1_4 = *(in1 + 4);
				in1_5 = *(in1 + 5);
				in1_6 = *(in1 + 6);
				in1_7 = *(in1 + 7);
				in1 += In1S;
				PREFETCH_READ_3(in1+In1S*8);
				out0_0 += in0_0_0 * in1_0;
				out0_1 += in0_0_0 * in1_1;
				out0_2 += in0_0_0 * in1_2;
				out0_3 += in0_0_0 * in1_3;
				out0_4 += in0_0_0 * in1_4;
				out0_5 += in0_0_0 * in1_5;
				out0_6 += in0_0_0 * in1_6;
				out0_7 += in0_0_0 * in1_7;
				out1_0 += in0_1_0 * in1_0;
				out1_1 += in0_1_0 * in1_1;
				out1_2 += in0_1_0 * in1_2;
				out1_3 += in0_1_0 * in1_3;
				out1_4 += in0_1_0 * in1_4;
				out1_5 += in0_1_0 * in1_5;
				out1_6 += in0_1_0 * in1_6;
				out1_7 += in0_1_0 * in1_7;

				in1_0 = *(in1 + 0);
				in1_1 = *(in1 + 1);
				in1_2 = *(in1 + 2);
				in1_3 = *(in1 + 3);
				in1_4 = *(in1 + 4);
				in1_5 = *(in1 + 5);
				in1_6 = *(in1 + 6);
				in1_7 = *(in1 + 7);
				in1 += In1S;
				PREFETCH_READ_3(in1+In1S*8);
				out0_0 += in0_0_1 * in1_0;
				out0_1 += in0_0_1 * in1_1;
				out0_2 += in0_0_1 * in1_2;
				out0_3 += in0_0_1 * in1_3;
				out0_4 += in0_0_1 * in1_4;
				out0_5 += in0_0_1 * in1_5;
				out0_6 += in0_0_1 * in1_6;
				out0_7 += in0_0_1 * in1_7;
				out1_0 += in0_1_1 * in1_0;
				out1_1 += in0_1_1 * in1_1;
				out1_2 += in0_1_1 * in1_2;
				out1_3 += in0_1_1 * in1_3;
				out1_4 += in0_1_1 * in1_4;
				out1_5 += in0_1_1 * in1_5;
				out1_6 += in0_1_1 * in1_6;
				out1_7 += in0_1_1 * in1_7;

				in1_0 = *(in1 + 0);
				in1_1 = *(in1 + 1);
				in1_2 = *(in1 + 2);
				in1_3 = *(in1 + 3);
				in1_4 = *(in1 + 4);
				in1_5 = *(in1 + 5);
				in1_6 = *(in1 + 6);
				in1_7 = *(in1 + 7);
				in1 += In1S;
				PREFETCH_READ_3(in1+In1S*8);
				out0_0 += in0_0_2 * in1_0;
				out0_1 += in0_0_2 * in1_1;
				out0_2 += in0_0_2 * in1_2;
				out0_3 += in0_0_2 * in1_3;
				out0_4 += in0_0_2 * in1_4;
				out0_5 += in0_0_2 * in1_5;
				out0_6 += in0_0_2 * in1_6;
				out0_7 += in0_0_2 * in1_7;
				out1_0 += in0_1_2 * in1_0;
				out1_1 += in0_1_2 * in1_1;
				out1_2 += in0_1_2 * in1_2;
				out1_3 += in0_1_2 * in1_3;
				out1_4 += in0_1_2 * in1_4;
				out1_5 += in0_1_2 * in1_5;
				out1_6 += in0_1_2 * in1_6;
				out1_7 += in0_1_2 * in1_7;

				in1_0 = *(in1 + 0);
				in1_1 = *(in1 + 1);
				in1_2 = *(in1 + 2);
				in1_3 = *(in1 + 3);
				in1_4 = *(in1 + 4);
				in1_5 = *(in1 + 5);
				in1_6 = *(in1 + 6);
				in1_7 = *(in1 + 7);
				in1 += In1S;
				PREFETCH_READ_3(in1+In1S*8);
				out0_0 += in0_0_3 * in1_0;
				out0_1 += in0_0_3 * in1_1;
				out0_2 += in0_0_3 * in1_2;
				out0_3 += in0_0_3 * in1_3;
				out0_4 += in0_0_3 * in1_4;
				out0_5 += in0_0_3 * in1_5;
				out0_6 += in0_0_3 * in1_6;
				out0_7 += in0_0_3 * in1_7;
				out1_0 += in0_1_3 * in1_0;
				out1_1 += in0_1_3 * in1_1;
				out1_2 += in0_1_3 * in1_2;
				out1_3 += in0_1_3 * in1_3;
				out1_4 += in0_1_3 * in1_4;
				out1_5 += in0_1_3 * in1_5;
				out1_6 += in0_1_3 * in1_6;
				out1_7 += in0_1_3 * in1_7;

				in1_0 = *(in1 + 0);
				in1_1 = *(in1 + 1);
				in1_2 = *(in1 + 2);
				in1_3 = *(in1 + 3);
				in1_4 = *(in1 + 4);
				in1_5 = *(in1 + 5);
				in1_6 = *(in1 + 6);
				in1_7 = *(in1 + 7);
				in1 += In1S;
				PREFETCH_READ_3(in1+In1S*8);
				out0_0 += in0_0_4 * in1_0;
				out0_1 += in0_0_4 * in1_1;
				out0_2 += in0_0_4 * in1_2;
				out0_3 += in0_0_4 * in1_3;
				out0_4 += in0_0_4 * in1_4;
				out0_5 += in0_0_4 * in1_5;
				out0_6 += in0_0_4 * in1_6;
				out0_7 += in0_0_4 * in1_7;
				out1_0 += in0_1_4 * in1_0;
				out1_1 += in0_1_4 * in1_1;
				out1_2 += in0_1_4 * in1_2;
				out1_3 += in0_1_4 * in1_3;
				out1_4 += in0_1_4 * in1_4;
				out1_5 += in0_1_4 * in1_5;
				out1_6 += in0_1_4 * in1_6;
				out1_7 += in0_1_4 * in1_7;

				in1_0 = *(in1 + 0);
				in1_1 = *(in1 + 1);
				in1_2 = *(in1 + 2);
				in1_3 = *(in1 + 3);
				in1_4 = *(in1 + 4);
				in1_5 = *(in1 + 5);
				in1_6 = *(in1 + 6);
				in1_7 = *(in1 + 7);
				in1 += In1S;
				PREFETCH_READ_3(in1+In1S*8);
				out0_0 += in0_0_5 * in1_0;
				out0_1 += in0_0_5 * in1_1;
				out0_2 += in0_0_5 * in1_2;
				out0_3 += in0_0_5 * in1_3;
				out0_4 += in0_0_5 * in1_4;
				out0_5 += in0_0_5 * in1_5;
				out0_6 += in0_0_5 * in1_6;
				out0_7 += in0_0_5 * in1_7;
				out1_0 += in0_1_5 * in1_0;
				out1_1 += in0_1_5 * in1_1;
				out1_2 += in0_1_5 * in1_2;
				out1_3 += in0_1_5 * in1_3;
				out1_4 += in0_1_5 * in1_4;
				out1_5 += in0_1_5 * in1_5;
				out1_6 += in0_1_5 * in1_6;
				out1_7 += in0_1_5 * in1_7;

				in1_0 = *(in1 + 0);
				in1_1 = *(in1 + 1);
				in1_2 = *(in1 + 2);
				in1_3 = *(in1 + 3);
				in1_4 = *(in1 + 4);
				in1_5 = *(in1 + 5);
				in1_6 = *(in1 + 6);
				in1_7 = *(in1 + 7);
				in1 += In1S;
				PREFETCH_READ_3(in1+In1S*8);
				out0_0 += in0_0_6 * in1_0;
				out0_1 += in0_0_6 * in1_1;
				out0_2 += in0_0_6 * in1_2;
				out0_3 += in0_0_6 * in1_3;
				out0_4 += in0_0_6 * in1_4;
				out0_5 += in0_0_6 * in1_5;
				out0_6 += in0_0_6 * in1_6;
				out0_7 += in0_0_6 * in1_7;
				out1_0 += in0_1_6 * in1_0;
				out1_1 += in0_1_6 * in1_1;
				out1_2 += in0_1_6 * in1_2;
				out1_3 += in0_1_6 * in1_3;
				out1_4 += in0_1_6 * in1_4;
				out1_5 += in0_1_6 * in1_5;
				out1_6 += in0_1_6 * in1_6;
				out1_7 += in0_1_6 * in1_7;

				in1_0 = *(in1 + 0);
				in1_1 = *(in1 + 1);
				in1_2 = *(in1 + 2);
				in1_3 = *(in1 + 3);
				in1_4 = *(in1 + 4);
				in1_5 = *(in1 + 5);
				in1_6 = *(in1 + 6);
				in1_7 = *(in1 + 7);
				in1 += In1S;
				PREFETCH_READ_3(in1+In1S*8);
				out0_0 += in0_0_7 * in1_0;
				out0_1 += in0_0_7 * in1_1;
				out0_2 += in0_0_7 * in1_2;
				out0_3 += in0_0_7 * in1_3;
				out0_4 += in0_0_7 * in1_4;
				out0_5 += in0_0_7 * in1_5;
				out0_6 += in0_0_7 * in1_6;
				out0_7 += in0_0_7 * in1_7;
				out1_0 += in0_1_7 * in1_0;
				out1_1 += in0_1_7 * in1_1;
				out1_2 += in0_1_7 * in1_2;
				out1_3 += in0_1_7 * in1_3;
				out1_4 += in0_1_7 * in1_4;
				out1_5 += in0_1_7 * in1_5;
				out1_6 += in0_1_7 * in1_6;
				out1_7 += in0_1_7 * in1_7;
			}
			*(out  + 0) = out0_0;
			*(out  + 1) = out0_1;
			*(out  + 2) = out0_2;
			*(out  + 3) = out0_3;
			*(out  + 4) = out0_4;
			*(out  + 5) = out0_5;
			*(out  + 6) = out0_6;
			*(out  + 7) = out0_7;
			*(out_ + 0) = out1_0;
			*(out_ + 1) = out1_1;
			*(out_ + 2) = out1_2;
			*(out_ + 3) = out1_3;
			*(out_ + 4) = out1_4;
			*(out_ + 5) = out1_5;
			*(out_ + 6) = out1_6;
			*(out_ + 7) = out1_7;
		}
	}
}

//------------------------------------------------------------------------------
// C += A X B
template <class T, class U>
static NOINLINE void dot_product_mnk_2x1x8 (T* Out, 
																						T* In0, 
																						T* In1, 
																						volatile const U m,
																						volatile const U k, 
																						volatile const U n,
																						register U OutS = 0,
																						register U In0S = 0,
																						register U In1S = 0) {
	register T i0;
	register T in1_0, in1_1, in1_2, in1_3, in1_4, in1_5, in1_6, in1_7;
	register T out0_0, out0_1, out0_2, out0_3, out0_4, out0_5, out0_6, out0_7;
	register T out1_0, out1_1, out1_2, out1_3, out1_4, out1_5, out1_6, out1_7;
	U h, M, K, N;
	register U i, j; 
	register T *_out, *_in0, *_in1;	
	register T *out,  *in0,  *in1;
	register T *out_, *in0_;

	if (!OutS) {OutS = n;}
	if (!In0S) {In0S = k;}
	if (!In1S) {In1S = n;}
	M = m >> 1;
	K = k;
	N = n >> 3;

	for (h = M; h; h--) {
		_out = Out;
		Out += OutS * 2;
		_in0 = In0; 
		In0 += In0S * 2;
		_in1 = In1;
		for (i = N; i; i--) {
			out = _out;
			out_ = out + OutS;
			_out += (U)8;
			in0 = _in0;
			in0_ = in0 + k;
			in1 = _in1;
			_in1 += (U)8;
			out0_0 = *(out  + 0);
			out0_1 = *(out  + 1);
			out0_2 = *(out  + 2);
			out0_3 = *(out  + 3);
			out0_4 = *(out  + 4);
			out0_5 = *(out  + 5);
			out0_6 = *(out  + 6);
			out0_7 = *(out  + 7);
			out1_0 = *(out_ + 0);
			out1_1 = *(out_ + 1);
			out1_2 = *(out_ + 2);
			out1_3 = *(out_ + 3);
			out1_4 = *(out_ + 4);
			out1_5 = *(out_ + 5);
			out1_6 = *(out_ + 6);
			out1_7 = *(out_ + 7);
			for (j = K; j; j--) {
				in1_0 = *(in1 + 0);
				in1_1 = *(in1 + 1);
				in1_2 = *(in1 + 2);
				in1_3 = *(in1 + 3);
				in1_4 = *(in1 + 4);
				in1_5 = *(in1 + 5);
				in1_6 = *(in1 + 6);
				in1_7 = *(in1 + 7);
				in1 += In1S;
				i0 = *(in0 + 0);
				in0  ++;
				out0_0 += i0 * in1_0;
				out0_1 += i0 * in1_1;
				out0_2 += i0 * in1_2;
				out0_3 += i0 * in1_3;
				out0_4 += i0 * in1_4;
				out0_5 += i0 * in1_5;
				out0_6 += i0 * in1_6;
				out0_7 += i0 * in1_7;
				i0 = *(in0_ + 0);
				in0_ ++;
				out1_0 += i0 * in1_0;
				out1_1 += i0 * in1_1;
				out1_2 += i0 * in1_2;
				out1_3 += i0 * in1_3;
				out1_4 += i0 * in1_4;
				out1_5 += i0 * in1_5;
				out1_6 += i0 * in1_6;
				out1_7 += i0 * in1_7;
			}
			*(out  + 0) = out0_0;
			*(out  + 1) = out0_1;
			*(out  + 2) = out0_2;
			*(out  + 3) = out0_3;
			*(out  + 4) = out0_4;
			*(out  + 5) = out0_5;
			*(out  + 6) = out0_6;
			*(out  + 7) = out0_7;
			*(out_ + 0) = out1_0;
			*(out_ + 1) = out1_1;
			*(out_ + 2) = out1_2;
			*(out_ + 3) = out1_3;
			*(out_ + 4) = out1_4;
			*(out_ + 5) = out1_5;
			*(out_ + 6) = out1_6;
			*(out_ + 7) = out1_7;
		}
	}
}

//------------------------------------------------------------------------------
// C += A X B
template <class T, class U>
static NOINLINE void dot_product_MNK_2x1x8 (T* Out, 
																						T* In0, 
																						T* In1, 
																						volatile const U m,
																						volatile const U k, 
																						volatile const U n,
																						register U OutS = 0) {
	register T i0;
	register T in1_0, in1_1, in1_2, in1_3, in1_4, in1_5, in1_6, in1_7;
	register T out0_0, out0_1, out0_2, out0_3, out0_4, out0_5, out0_6, out0_7;
	register T out1_0, out1_1, out1_2, out1_3, out1_4, out1_5, out1_6, out1_7;
	U h, M, K, N;
	register U i, j; 
	register U In0S, In1S;
	register T *_out, *_in0, *_in1;	
	register T *out,  *in0,  *in1;
	register T *out_, *in0_;

	if (!OutS) {OutS = n;}
	In0S = k;
	In1S = n;
	M = m >> 1;
	K = k;
	N = n >> 3;

	for (h = M; h; h--) {
		_out = Out;
		Out += OutS * 2;
		_in0 = In0; 
		In0 += In0S * 2;
		_in1 = In1;
		for (i = N; i; i--) {
			out = _out;
			out_ = out + OutS;
			_out += (U)8;
			in0 = _in0;
			in0_ = in0 + k;
			in1 = _in1;
			_in1 += (U)8;
			out0_0 = *(out  + 0);
			out0_1 = *(out  + 1);
			out0_2 = *(out  + 2);
			out0_3 = *(out  + 3);
			out0_4 = *(out  + 4);
			out0_5 = *(out  + 5);
			out0_6 = *(out  + 6);
			out0_7 = *(out  + 7);
			out1_0 = *(out_ + 0);
			out1_1 = *(out_ + 1);
			out1_2 = *(out_ + 2);
			out1_3 = *(out_ + 3);
			out1_4 = *(out_ + 4);
			out1_5 = *(out_ + 5);
			out1_6 = *(out_ + 6);
			out1_7 = *(out_ + 7);
			for (j = K; j; j--) {
				in1_0 = *(in1 + 0);
				in1_1 = *(in1 + 1);
				in1_2 = *(in1 + 2);
				in1_3 = *(in1 + 3);
				in1_4 = *(in1 + 4);
				in1_5 = *(in1 + 5);
				in1_6 = *(in1 + 6);
				in1_7 = *(in1 + 7);
				in1 += In1S;
				PREFETCH_READ_3(in1+n*8);
				i0 = *(in0 + 0);
				in0  ++;
				PREFETCH_READ_3(in0  + (U)8);
				out0_0 += i0 * in1_0;
				out0_1 += i0 * in1_1;
				out0_2 += i0 * in1_2;
				out0_3 += i0 * in1_3;
				out0_4 += i0 * in1_4;
				out0_5 += i0 * in1_5;
				out0_6 += i0 * in1_6;
				out0_7 += i0 * in1_7;
				i0 = *(in0_ + 0);
				in0_ ++;
				PREFETCH_READ_3(in0_ + (U)8);
				out1_0 += i0 * in1_0;
				out1_1 += i0 * in1_1;
				out1_2 += i0 * in1_2;
				out1_3 += i0 * in1_3;
				out1_4 += i0 * in1_4;
				out1_5 += i0 * in1_5;
				out1_6 += i0 * in1_6;
				out1_7 += i0 * in1_7;
			}
			*(out  + 0) = out0_0;
			*(out  + 1) = out0_1;
			*(out  + 2) = out0_2;
			*(out  + 3) = out0_3;
			*(out  + 4) = out0_4;
			*(out  + 5) = out0_5;
			*(out  + 6) = out0_6;
			*(out  + 7) = out0_7;
			*(out_ + 0) = out1_0;
			*(out_ + 1) = out1_1;
			*(out_ + 2) = out1_2;
			*(out_ + 3) = out1_3;
			*(out_ + 4) = out1_4;
			*(out_ + 5) = out1_5;
			*(out_ + 6) = out1_6;
			*(out_ + 7) = out1_7;
		}
	}
}

//------------------------------------------------------------------------------
// C += A X B
template <class T, class U>
static NOINLINE void dot_product_MNK_8x8x8 (T* Out, 
																						T* In0, 
																						T* In1, 
																						volatile const U m,
																						volatile const U k, 
																						volatile const U n,
																						volatile U OutS = 0,
																						volatile U Arch = 0) {
	switch (Arch) {
		case (U)188: {
			return dot_product_MNK_1x8x8(Out, In0, In1, m, k, n, OutS);
		}
		case (U)288: {
			return dot_product_MNK_2x8x8(Out, In0, In1, m, k, n, OutS);
		}
		case (U)218: {
			return dot_product_MNK_2x1x8(Out, In0, In1, m, k, n, OutS);
		}
		default: {
			return dot_product_MNK_2x1x8(Out, In0, In1, m, k, n, OutS);
		}

	}
}
//------------------------------------------------------------------------------
#endif

