//------------------------------------------------------------------------------
# ifndef _dot_product_mnk_txx
# define _dot_product_mnk_txx

# include "clas_defs.h"
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// C += A X B
template <class T, class U>
static inline void dot_product_mnk_1x8x8 (register T* Out, 
																					register T* In0, 
																					register T* In1, 
																					register U m,
																					volatile const U k, 
																					volatile const U n,
																					volatile const U Outs) {
	register T i0, i1, i2, i3, i4, i5, i6, i7;
	register T o0, o1, o2, o3, o4, o5, o6, o7;
	register U i, j; 
	U k3, n3;
	register U N3;
	register T *_out, *_in0, *_in1;	
	register T *out,  *in0,  *in1;

	k3 = k >> 3;
	n3 = n >> 3;
	N3 = n >> 3;

	for (; m; m--) {
		_out = Out;
		Out += Outs;
		_in0 = In0; 
		In0 += k;
		_in1 = In1;
		for (i = n3; i; i--) {
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
			for (j = k3; j; j--) {
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
				PREFETCH_READ_3(in1+N3);
				in1 += n;
				o0 += i1 * *(in1 + 0);
				o1 += i1 * *(in1 + 1);
				o2 += i1 * *(in1 + 2);
				o3 += i1 * *(in1 + 3);
				o4 += i1 * *(in1 + 4);
				o5 += i1 * *(in1 + 5);
				o6 += i1 * *(in1 + 6);
				o7 += i1 * *(in1 + 7);
				PREFETCH_READ_3(in1+N3);
				in1 += n;
				o0 += i2 * *(in1 + 0);
				o1 += i2 * *(in1 + 1);
				o2 += i2 * *(in1 + 2);
				o3 += i2 * *(in1 + 3);
				o4 += i2 * *(in1 + 4);
				o5 += i2 * *(in1 + 5);
				o6 += i2 * *(in1 + 6);
				o7 += i2 * *(in1 + 7);
				PREFETCH_READ_3(in1+N3);
				in1 += n;
				o0 += i3 * *(in1 + 0);
				o1 += i3 * *(in1 + 1);
				o2 += i3 * *(in1 + 2);
				o3 += i3 * *(in1 + 3);
				o4 += i3 * *(in1 + 4);
				o5 += i3 * *(in1 + 5);
				o6 += i3 * *(in1 + 6);
				o7 += i3 * *(in1 + 7);
				PREFETCH_READ_3(in1+N3);
				in1 += n;
				o0 += i4 * *(in1 + 0);
				o1 += i4 * *(in1 + 1);
				o2 += i4 * *(in1 + 2);
				o3 += i4 * *(in1 + 3);
				o4 += i4 * *(in1 + 4);
				o5 += i4 * *(in1 + 5);
				o6 += i4 * *(in1 + 6);
				o7 += i4 * *(in1 + 7);
				PREFETCH_READ_3(in1+N3);
				in1 += n;
				o0 += i5 * *(in1 + 0);
				o1 += i5 * *(in1 + 1);
				o2 += i5 * *(in1 + 2);
				o3 += i5 * *(in1 + 3);
				o4 += i5 * *(in1 + 4);
				o5 += i5 * *(in1 + 5);
				o6 += i5 * *(in1 + 6);
				o7 += i5 * *(in1 + 7);
				PREFETCH_READ_3(in1+N3);
				in1 += n;
				o0 += i6 * *(in1 + 0);
				o1 += i6 * *(in1 + 1);
				o2 += i6 * *(in1 + 2);
				o3 += i6 * *(in1 + 3);
				o4 += i6 * *(in1 + 4);
				o5 += i6 * *(in1 + 5);
				o6 += i6 * *(in1 + 6);
				o7 += i6 * *(in1 + 7);
				PREFETCH_READ_3(in1+N3);
				in1 += n;
				o0 += i7 * *(in1 + 0);
				o1 += i7 * *(in1 + 1);
				o2 += i7 * *(in1 + 2);
				o3 += i7 * *(in1 + 3);
				o4 += i7 * *(in1 + 4);
				o5 += i7 * *(in1 + 5);
				o6 += i7 * *(in1 + 6);
				o7 += i7 * *(in1 + 7);
				PREFETCH_READ_3(in1+N3);
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

//------------------------------------------------------------------------------
template <class T, class U>
static inline void dot_product_mnk_ex8x8 (register T* Out, 
																					register T* In0, 
																					register T* In1, 
																					register U m,
																					volatile const U k, 
																					volatile const U n,
																					volatile const U Outs) {
	register T i0, i1, i2, i3, i4, i5, i6, i7;
	register T o0, o1, o2, o3, o4, o5, o6, o7;
	register U i, j; 
	U k3, n3;
	register U N3;
	register T *_out, *_in0, *_in1;	
	register T *out,  *in0,  *in1;

	k3 = k >> 3;
	n3 = n >> 3;
	N3 = n >> 3;

	for (; m; m--) {
		_out = Out;
		Out += Outs;
		_in0 = In0; 
		In0 += k;
		_in1 = In1;
		for (i = n3; i; i--) {
			out = _out;
			_out += (U)8;
			in0 = _in0;
			in1 = _in1;
			_in1 += (U)8;
			o0 = *(out + 0);
			//o1 = *(out + 1);
			o2 = *(out + 2);
			//o3 = *(out + 3);
			o4 = *(out + 4);
			//o5 = *(out + 5);
			o6 = *(out + 6);
			//o7 = *(out + 7);
			for (j = k3; j; j--) {
				i0 = *(in0 + 0);
				//i1 = *(in0 + 1);
				i2 = *(in0 + 2);
				//i3 = *(in0 + 3);
				i4 = *(in0 + 4);
				//i5 = *(in0 + 5);
				i6 = *(in0 + 6);
				//i7 = *(in0 + 7);
				in0 += (U)8;
				PREFETCH_READ_3(in0);
				o0 += i0 * *(in1 + 0);
				//o1 += i0 * *(in1 + 1);
				o2 += i0 * *(in1 + 2);
				//o3 += i0 * *(in1 + 3);
				o4 += i0 * *(in1 + 4);
				//o5 += i0 * *(in1 + 5);
				o6 += i0 * *(in1 + 6);
				//o7 += i0 * *(in1 + 7);
				PREFETCH_READ_3(in1+N3);
				in1 += n;
				o0 += i1 * *(in1 + 0);
				//o1 += i1 * *(in1 + 1);
				o2 += i1 * *(in1 + 2);
				//o3 += i1 * *(in1 + 3);
				o4 += i1 * *(in1 + 4);
				//o5 += i1 * *(in1 + 5);
				o6 += i1 * *(in1 + 6);
				//o7 += i1 * *(in1 + 7);
				PREFETCH_READ_3(in1+N3);
				in1 += n;
				o0 += i2 * *(in1 + 0);
				//o1 += i2 * *(in1 + 1);
				o2 += i2 * *(in1 + 2);
				//o3 += i2 * *(in1 + 3);
				o4 += i2 * *(in1 + 4);
				//o5 += i2 * *(in1 + 5);
				o6 += i2 * *(in1 + 6);
				//o7 += i2 * *(in1 + 7);
				PREFETCH_READ_3(in1+N3);
				in1 += n;
				o0 += i3 * *(in1 + 0);
				//o1 += i3 * *(in1 + 1);
				o2 += i3 * *(in1 + 2);
				//o3 += i3 * *(in1 + 3);
				o4 += i3 * *(in1 + 4);
				//o5 += i3 * *(in1 + 5);
				o6 += i3 * *(in1 + 6);
				//o7 += i3 * *(in1 + 7);
				PREFETCH_READ_3(in1+N3);
				in1 += n;
				o0 += i4 * *(in1 + 0);
				//o1 += i4 * *(in1 + 1);
				o2 += i4 * *(in1 + 2);
				//o3 += i4 * *(in1 + 3);
				o4 += i4 * *(in1 + 4);
				//o5 += i4 * *(in1 + 5);
				o6 += i4 * *(in1 + 6);
				//o7 += i4 * *(in1 + 7);
				PREFETCH_READ_3(in1+N3);
				in1 += n;
				o0 += i5 * *(in1 + 0);
				//o1 += i5 * *(in1 + 1);
				o2 += i5 * *(in1 + 2);
				//o3 += i5 * *(in1 + 3);
				o4 += i5 * *(in1 + 4);
				//o5 += i5 * *(in1 + 5);
				o6 += i5 * *(in1 + 6);
				//o7 += i5 * *(in1 + 7);
				PREFETCH_READ_3(in1+N3);
				in1 += n;
				o0 += i6 * *(in1 + 0);
				//o1 += i6 * *(in1 + 1);
				o2 += i6 * *(in1 + 2);
				//o3 += i6 * *(in1 + 3);
				o4 += i6 * *(in1 + 4);
				//o5 += i6 * *(in1 + 5);
				o6 += i6 * *(in1 + 6);
				//o7 += i6 * *(in1 + 7);
				PREFETCH_READ_3(in1+N3);
				in1 += n;
				o0 += i7 * *(in1 + 0);
				//o1 += i7 * *(in1 + 1);
				o2 += i7 * *(in1 + 2);
				//o3 += i7 * *(in1 + 3);
				o4 += i7 * *(in1 + 4);
				//o5 += i7 * *(in1 + 5);
				o6 += i7 * *(in1 + 6);
				//o7 += i7 * *(in1 + 7);
				PREFETCH_READ_3(in1+N3);
				in1 += n;
			}
			*(out + 0) = o0;
			//*(out + 1) = o1;
			*(out + 2) = o2;
			//*(out + 3) = o3;
			*(out + 4) = o4;
			//*(out + 5) = o5;
			*(out + 6) = o6;
			//*(out + 7) = o7;
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
	U OutS, m3, n3;
	register U N3;
	register T *Out, *_out, *_in0, *_in1;
	register T *out,  *in0,  *in1;

	OutS = Outs << 3;
	m3 = m >> 3;
	n3 = n >> 3;

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
			for (j = n3; j; j--) {
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
				out += Outs;

				*(out + 0) += in0_1 * in1_0;
				*(out + 1) += in0_1 * in1_1;
				*(out + 2) += in0_1 * in1_2;
				*(out + 3) += in0_1 * in1_3;
				*(out + 4) += in0_1 * in1_4;
				*(out + 5) += in0_1 * in1_5;
				*(out + 6) += in0_1 * in1_6;
				*(out + 7) += in0_1 * in1_7;
				out += Outs;

				*(out + 0) += in0_2 * in1_0;
				*(out + 1) += in0_2 * in1_1;
				*(out + 2) += in0_2 * in1_2;
				*(out + 3) += in0_2 * in1_3;
				*(out + 4) += in0_2 * in1_4;
				*(out + 5) += in0_2 * in1_5;
				*(out + 6) += in0_2 * in1_6;
				*(out + 7) += in0_2 * in1_7;
				out += Outs;

				*(out + 0) += in0_3 * in1_0;
				*(out + 1) += in0_3 * in1_1;
				*(out + 2) += in0_3 * in1_2;
				*(out + 3) += in0_3 * in1_3;
				*(out + 4) += in0_3 * in1_4;
				*(out + 5) += in0_3 * in1_5;
				*(out + 6) += in0_3 * in1_6;
				*(out + 7) += in0_3 * in1_7;
				out += Outs;

				*(out + 0) += in0_4 * in1_0;
				*(out + 1) += in0_4 * in1_1;
				*(out + 2) += in0_4 * in1_2;
				*(out + 3) += in0_4 * in1_3;
				*(out + 4) += in0_4 * in1_4;
				*(out + 5) += in0_4 * in1_5;
				*(out + 6) += in0_4 * in1_6;
				*(out + 7) += in0_4 * in1_7;
				out += Outs;

				*(out + 0) += in0_5 * in1_0;
				*(out + 1) += in0_5 * in1_1;
				*(out + 2) += in0_5 * in1_2;
				*(out + 3) += in0_5 * in1_3;
				*(out + 4) += in0_5 * in1_4;
				*(out + 5) += in0_5 * in1_5;
				*(out + 6) += in0_5 * in1_6;
				*(out + 7) += in0_5 * in1_7;
				out += Outs;

				*(out + 0) += in0_6 * in1_0;
				*(out + 1) += in0_6 * in1_1;
				*(out + 2) += in0_6 * in1_2;
				*(out + 3) += in0_6 * in1_3;
				*(out + 4) += in0_6 * in1_4;
				*(out + 5) += in0_6 * in1_5;
				*(out + 6) += in0_6 * in1_6;
				*(out + 7) += in0_6 * in1_7;
				out += Outs;

				*(out + 0) += in0_7 * in1_0;
				*(out + 1) += in0_7 * in1_1;
				*(out + 2) += in0_7 * in1_2;
				*(out + 3) += in0_7 * in1_3;
				*(out + 4) += in0_7 * in1_4;
				*(out + 5) += in0_7 * in1_5;
				*(out + 6) += in0_7 * in1_6;
				*(out + 7) += in0_7 * in1_7;
				out += Outs;
			}
		}
	}
}

//------------------------------------------------------------------------------
// C += A.T X B
template <class T, class U>
static inline void dot_product_kmn_ex8x8 (register T* _Out, 
																					register T* In0, 
																					register T* In1, 
																					volatile const U m,
																					volatile const U k, 
																					volatile const U n,
																					volatile const U Outs) {
	register T in0_0, in0_1, in0_2, in0_3, in0_4, in0_5, in0_6, in0_7;
	register T in1_0, in1_1, in1_2, in1_3, in1_4, in1_5, in1_6, in1_7;
	register U h, i, j; 
	U OutS, m3, n3;
	register U N3;
	register T *Out, *_out, *_in0, *_in1;
	register T *out,  *in0,  *in1;

	OutS = Outs << 3;
	m3 = m >> 3;
	n3 = n >> 3;

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
			for (j = n3; j; j--) {
				out = _out;
				_out += (U)8;
				in1_0 = *(in1 + 0);
				//in1_1 = *(in1 + 1);
				in1_2 = *(in1 + 2);
				//in1_3 = *(in1 + 3);
				in1_4 = *(in1 + 4);
				//in1_5 = *(in1 + 5);
				in1_6 = *(in1 + 6);
				//in1_7 = *(in1 + 7);
				in1 += (U)8;

				*(out + 0) += in0_0 * in1_0;
				//*(out + 1) += in0_0 * in1_1;
				*(out + 2) += in0_0 * in1_2;
				//*(out + 3) += in0_0 * in1_3;
				*(out + 4) += in0_0 * in1_4;
				//*(out + 5) += in0_0 * in1_5;
				*(out + 6) += in0_0 * in1_6;
				//*(out + 7) += in0_0 * in1_7;
				out += Outs;

				*(out + 0) += in0_1 * in1_0;
				//*(out + 1) += in0_1 * in1_1;
				*(out + 2) += in0_1 * in1_2;
				//*(out + 3) += in0_1 * in1_3;
				*(out + 4) += in0_1 * in1_4;
				//*(out + 5) += in0_1 * in1_5;
				*(out + 6) += in0_1 * in1_6;
				//*(out + 7) += in0_1 * in1_7;
				out += Outs;

				*(out + 0) += in0_2 * in1_0;
				//*(out + 1) += in0_2 * in1_1;
				*(out + 2) += in0_2 * in1_2;
				//*(out + 3) += in0_2 * in1_3;
				*(out + 4) += in0_2 * in1_4;
				//*(out + 5) += in0_2 * in1_5;
				*(out + 6) += in0_2 * in1_6;
				//*(out + 7) += in0_2 * in1_7;
				out += Outs;

				*(out + 0) += in0_3 * in1_0;
				//*(out + 1) += in0_3 * in1_1;
				*(out + 2) += in0_3 * in1_2;
				//*(out + 3) += in0_3 * in1_3;
				*(out + 4) += in0_3 * in1_4;
				//*(out + 5) += in0_3 * in1_5;
				*(out + 6) += in0_3 * in1_6;
				//*(out + 7) += in0_3 * in1_7;
				out += Outs;

				*(out + 0) += in0_4 * in1_0;
				//*(out + 1) += in0_4 * in1_1;
				*(out + 2) += in0_4 * in1_2;
				//*(out + 3) += in0_4 * in1_3;
				*(out + 4) += in0_4 * in1_4;
				//*(out + 5) += in0_4 * in1_5;
				*(out + 6) += in0_4 * in1_6;
				//*(out + 7) += in0_4 * in1_7;
				out += Outs;

				*(out + 0) += in0_5 * in1_0;
				//*(out + 1) += in0_5 * in1_1;
				*(out + 2) += in0_5 * in1_2;
				//*(out + 3) += in0_5 * in1_3;
				*(out + 4) += in0_5 * in1_4;
				//*(out + 5) += in0_5 * in1_5;
				*(out + 6) += in0_5 * in1_6;
				//*(out + 7) += in0_5 * in1_7;
				out += Outs;

				*(out + 0) += in0_6 * in1_0;
				//*(out + 1) += in0_6 * in1_1;
				*(out + 2) += in0_6 * in1_2;
				//*(out + 3) += in0_6 * in1_3;
				*(out + 4) += in0_6 * in1_4;
				//*(out + 5) += in0_6 * in1_5;
				*(out + 6) += in0_6 * in1_6;
				//*(out + 7) += in0_6 * in1_7;
				out += Outs;

				*(out + 0) += in0_7 * in1_0;
				//*(out + 1) += in0_7 * in1_1;
				*(out + 2) += in0_7 * in1_2;
				//*(out + 3) += in0_7 * in1_3;
				*(out + 4) += in0_7 * in1_4;
				//*(out + 5) += in0_7 * in1_5;
				*(out + 6) += in0_7 * in1_6;
				//*(out + 7) += in0_7 * in1_7;
				out += Outs;
			}
		}
	}
}

//------------------------------------------------------------------------------
#endif

