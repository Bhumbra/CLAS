# ifndef replicate_txx
# define replicate_txx

//------------------------------------------------------------------------------
template <class T, class U>//mxnxr
static inline void replicate_1x1x1 (T* O, 
																		U m,
																		U n,
																		U R = (U)(-1),
																		T* I = (T*)0,
																		U S = (U)0,
																		U s = (U)0) {
	if (R == (U)(-1)) {R = n;}

	register T t0;
	register T *o0;
	register T *i0;
	register U i;
	register U j;

	T* O0 = O;
	T* I0 = I;
  
	if (I == 0) { 
		for (i = m; i; i--) {
			o0 = O0;
			O0 += R;
			for (j = n; j; j--) {
				*(o0 +   0) = (T)0;
				o0 ++;
			}
		}
	}
	else {
		switch (s) {
			case 0: {
				for (i = m; i; i--) {
					o0 = O0;
					O0 += R;
					t0 = *I0;
					I0 += S;
					for (j = n; j; j--) {
						*(o0 +   0) = t0;
						o0 ++;
					}
				}
				break;
			}
			case 1: {
				for (i = m; i; i--) {
					o0 = O0;
					O0 += R;
					i0 = I0;
					I0 += S;
					for (j = n; j; j--) {
						*(o0 +   0) = *(i0 +   0);
						i0 ++;
						o0 ++;
					}
				}
				break;
			}
			default: {
				for (i = m; i; i--) {
					o0 = O0;
					O0 += R;
					i0 = I0;
					I0 += S;
					for (j = n; j; j--) {
						*(o0 +   0) = * i0; i0 += s;
						o0 ++;
					}
				}
				break;
			}
		}
	}
}

//------------------------------------------------------------------------------
template <class T, class U>//mxnxr
static inline void replicate_1x2x1 (T* O, 
																		U m,
																		U n,
																		U R = (U)(-1),
																		T* I = (T*)0,
																		U S = (U)0,
																		U s = (U)0) {
	if (R == (U)(-1)) {R = n;}

	register T t0;
	register T *o0;
	register T *i0;
	register U i;
	register U j;

	T* O0 = O;
	T* I0 = I;

	U d = n >> 1;
  
	if (I == 0) { 
		for (i = m; i; i--) {
			o0 = O0;
			O0 += R;
			for (j = d; j; j--) {
				*(o0 +   0) = (T)0;
				*(o0 +   1) = (T)0;
				o0 += 2;
			}
		}
	}
	else {
		switch (s) {
			case 0: {
				for (i = m; i; i--) {
					o0 = O0;
					O0 += R;
					t0 = *I0;
					I0 += S;
					for (j = d; j; j--) {
						*(o0 +   0) = t0;
						*(o0 +   1) = t0;
						o0 += 2;
					}
				}
				break;
			}
			case 1: {
				for (i = m; i; i--) {
					o0 = O0;
					O0 += R;
					i0 = I0;
					I0 += S;
					for (j = d; j; j--) {
						*(o0 +   0) = *(i0 +   0);
						*(o0 +   1) = *(i0 +   1);
						i0 += 2;
						o0 += 2;
					}
				}
				break;
			}
			default: {
				for (i = m; i; i--) {
					o0 = O0;
					O0 += R;
					i0 = I0;
					I0 += S;
					for (j = d; j; j--) {
						*(o0 +   0) = * i0; i0 += s;
						*(o0 +   1) = * i0; i0 += s;
						o0 += 2;
					}
				}
				break;
			}
		}
	}

	j = n & 1;
	if (j) {
		d = n - j;
		replicate_1x1x1(O + d, m, j, R, I + d*s, S, s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>//mxnxr
static inline void replicate_1x4x1 (T* O, 
																		U m,
																		U n,
																		U R = (U)(-1),
																		T* I = (T*)0,
																		U S = (U)0,
																		U s = (U)0) {
	if (R == (U)(-1)) {R = n;}

	register T t0;
	register T *o0;
	register T *i0;
	register U i;
	register U j;

	T* O0 = O;
	T* I0 = I;

	U d = n >> 2;
  
	if (I == 0) { 
		for (i = m; i; i--) {
			o0 = O0;
			O0 += R;
			for (j = d; j; j--) {
				*(o0 +   0) = (T)0;
				*(o0 +   1) = (T)0;
				*(o0 +   2) = (T)0;
				*(o0 +   3) = (T)0;
				o0 += 4;
			}
		}
	}
	else {
		switch (s) {
			case 0: {
				for (i = m; i; i--) {
					o0 = O0;
					O0 += R;
					t0 = *I0;
					I0 += S;
					for (j = d; j; j--) {
						*(o0 +   0) = t0;
						*(o0 +   1) = t0;
						*(o0 +   2) = t0;
						*(o0 +   3) = t0;
						o0 += 4;
					}
				}
				break;
			}
			case 1: {
				for (i = m; i; i--) {
					o0 = O0;
					O0 += R;
					i0 = I0;
					I0 += S;
					for (j = d; j; j--) {
						*(o0 +   0) = *(i0 +   0);
						*(o0 +   1) = *(i0 +   1);
						*(o0 +   2) = *(i0 +   2);
						*(o0 +   3) = *(i0 +   3);
						i0 += 4;
						o0 += 4;
					}
				}
				break;
			}
			default: {
				for (i = m; i; i--) {
					o0 = O0;
					O0 += R;
					i0 = I0;
					I0 += S;
					for (j = d; j; j--) {
						*(o0 +   0) = * i0; i0 += s;
						*(o0 +   1) = * i0; i0 += s;
						*(o0 +   2) = * i0; i0 += s;
						*(o0 +   3) = * i0; i0 += s;
						o0 += 4;
					}
				}
				break;
			}
		}
	}

	j = n & 3;
	if (j) {
		d = n - j;
		replicate_1x2x1(O + d, m, j, R, I + d*s, S, s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>//mxnxr
static inline void replicate_1x8x1 (T* O, 
																		U m,
																		U n,
																		U R = (U)(-1),
																		T* I = (T*)0,
																		U S = (U)0,
																		U s = (U)0) {
	if (R == (U)(-1)) {R = n;}
	register T t0;
	register T *o0;
	register T *i0;
	register U i;
	register U j;

	T* O0 = O;
	T* I0 = I; 
	U d = n >> 3;
  
	if (I == 0) { 
		for (i = m; i; i--) {
			o0 = O0;
			O0 += R;
			for (j = d; j; j--) {
				*(o0 +   0) = (T)0;
				*(o0 +   1) = (T)0;
				*(o0 +   2) = (T)0;
				*(o0 +   3) = (T)0;
				*(o0 +   4) = (T)0;
				*(o0 +   5) = (T)0;
				*(o0 +   6) = (T)0;
				*(o0 +   7) = (T)0;
				o0 += 8;
			}
		}
	}
	else {
		switch (s) {
			case 0: {
				for (i = m; i; i--) {
					o0 = O0;
					O0 += R;
					t0 = *I0;
					I0 += S;
					for (j = d; j; j--) {
						*(o0 +   0) = t0;
						*(o0 +   1) = t0;
						*(o0 +   2) = t0;
						*(o0 +   3) = t0;
						*(o0 +   4) = t0;
						*(o0 +   5) = t0;
						*(o0 +   6) = t0;
						*(o0 +   7) = t0;
						o0 += 8;
					}
				}
				break;
			}
			case 1: {
				for (i = m; i; i--) {
					o0 = O0;
					O0 += R;
					i0 = I0;
					I0 += S;
					for (j = d; j; j--) {
						*(o0 +   0) = *(i0 +   0);
						*(o0 +   1) = *(i0 +   1);
						*(o0 +   2) = *(i0 +   2);
						*(o0 +   3) = *(i0 +   3);
						*(o0 +   4) = *(i0 +   4);
						*(o0 +   5) = *(i0 +   5);
						*(o0 +   6) = *(i0 +   6);
						*(o0 +   7) = *(i0 +   7);
						i0 += 8;
						o0 += 8;
					}
				}
				break;
			}
			default: {
				for (i = m; i; i--) {
					o0 = O0;
					O0 += R;
					i0 = I0;
					I0 += S;
					for (j = d; j; j--) {
						*(o0 +   0) = * i0; i0 += s;
						*(o0 +   1) = * i0; i0 += s;
						*(o0 +   2) = * i0; i0 += s;
						*(o0 +   3) = * i0; i0 += s;
						*(o0 +   4) = * i0; i0 += s;
						*(o0 +   5) = * i0; i0 += s;
						*(o0 +   6) = * i0; i0 += s;
						*(o0 +   7) = * i0; i0 += s;
						o0 += 8;
					}
				}
				break;
			}
		}
	}

	j = n & 7;
	if (j) {
		d = n - j;
		replicate_1x4x1(O + d, m, j, R, I + d*s, S, s);
	}
}
//------------------------------------------------------------------------------
template <class T, class U>//mxnxr
static inline void replicate_2x1x1 (T* O, 
																		U m,
																		U n,
																		U R = (U)(-1),
																		T* I = (T*)0,
																		U S = (U)0,
																		U s = (U)0) {
	if (R == (U)(-1)) {R = n;}

	register T t0, t1;
	register T *o0, *o1;
	register T *i0, *i1;
	register U i;
	register U j;

	U D = m >> 1;
	U P = R << 1;
	U Q = S << 1;

	T* O0 = O + R * 0;
	T* O1 = O + R * 1;
	T* I0 = I + S * 0;
	T* I1 = I + S * 1;
  
	if (I == 0) { 
		for (i = D; i; i--) {
			o0 = O0;
			o1 = O1;
			O0 += P;
			O1 += P;
			for (j = n; j; j--) {
				*(o0 +   0) = (T)0;
				*(o1 +   0) = (T)0;
				o0 ++;
				o1 ++;
			}
		}
	}
	else {
		switch (s) {
			case 0: {
				for (i = D; i; i--) {
					o0 = O0;
					o1 = O1;
					O0 += P;
					O1 += P;
					t0 = *I0;
					t1 = *I1;
					I0 += Q;
					I1 += Q;
					for (j = n; j; j--) {
						*(o0 +   0) = t0;
						*(o1 +   0) = t1;
						o0 ++;
						o1 ++;
					}
				}
				break;
			}
			case 1: {
				for (i = D; i; i--) {
					o0 = O0;
					o1 = O1;
					O0 += P;
					O1 += P;
					i0 = I0;
					i1 = I1;
					I0 += Q;
					I1 += Q;
					for (j = n; j; j--) {
						*(o0 +   0) = *(i0 +   0);
						*(o1 +   0) = *(i1 +   0);
						i0 ++;
						o0 ++;
						i1 ++;
						o1 ++;
					}
				}
				break;
			}
			default: {
				for (i = D; i; i--) {
					o0 = O0;
					o1 = O1;
					O0 += P;
					O1 += P;
					i0 = I0;
					i1 = I1;
					I0 += Q;
					I1 += Q;
					for (j = n; j; j--) {
						*(o0 +   0) = * i0; i0 += s;
						*(o1 +   0) = * i1; i1 += s;
						o0 ++;
						o1 ++;
					}
				}
				break;
			}
		}
	}
	i = m & 1;
	if (i) {
		D = m - i;
		replicate_1x1x1(O + D*R, i, n, R, I + D*S, S, s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>//mxnxr
static inline void replicate_2x2x1 (T* O, 
																		U m,
																		U n,
																		U R = (U)(-1),
																		T* I = (T*)0,
																		U S = (U)0,
																		U s = (U)0) {
	if (R == (U)(-1)) {R = n;}

	register T t0, t1;
	register T *o0, *o1;
	register T *i0, *i1;
	register U i;
	register U j;

	U d = n >> 1;
	U D = m >> 1;
	U P = R << 1;
	U Q = S << 1;

	T* O0 = O + R * 0;
	T* O1 = O + R * 1;
	T* I0 = I + S * 0;
	T* I1 = I + S * 1;
  
	if (I == 0) { 
		for (i = D; i; i--) {
			o0 = O0;
			o1 = O1;
			O0 += P;
			O1 += P;
			for (j = d; j; j--) {
				*(o0 +   0) = (T)0;
				*(o1 +   0) = (T)0;
				*(o0 +   1) = (T)0;
				*(o1 +   1) = (T)0;
				o0 += 2;
				o1 += 2;
			}
		}
	}
	else {
		switch (s) {
			case 0: {
				for (i = D; i; i--) {
					o0 = O0;
					o1 = O1;
					O0 += P;
					O1 += P;
					t0 = *I0;
					t1 = *I1;
					I0 += Q;
					I1 += Q;
					for (j = d; j; j--) {
						*(o0 +   0) = t0;
						*(o1 +   0) = t1;
						*(o0 +   1) = t0;
						*(o1 +   1) = t1;
						o0 += 2;
						o1 += 2;
					}
				}
				break;
			}
			case 1: {
				for (i = D; i; i--) {
					o0 = O0;
					o1 = O1;
					O0 += P;
					O1 += P;
					i0 = I0;
					i1 = I1;
					I0 += Q;
					I1 += Q;
					for (j = d; j; j--) {
						*(o0 +   0) = *(i0 +   0);
						*(o1 +   0) = *(i1 +   0);
						*(o0 +   1) = *(i0 +   1);
						*(o1 +   1) = *(i1 +   1);
						i0 += 2;
						o0 += 2;
						i1 += 2;
						o1 += 2;
					}
				}
				break;
			}
			default: {
				for (i = D; i; i--) {
					o0 = O0;
					o1 = O1;
					O0 += P;
					O1 += P;
					i0 = I0;
					i1 = I1;
					I0 += Q;
					I1 += Q;
					for (j = d; j; j--) {
						*(o0 +   0) = * i0; i0 += s;
						*(o1 +   0) = * i1; i1 += s;
						*(o0 +   1) = * i0; i0 += s;
						*(o1 +   1) = * i1; i1 += s;
						o0 += 2;
						o1 += 2;
					}
				}
				break;
			}
		}
	}

	j = D ? n & 1 : (U)0;
	if (j) {
		i = D << 1;
		d = n - j;
		replicate_2x1x1(O + d, i, j, R, I + d*s, S, s);
	}
	i = m & 1;
	if (i) {
		D = m - i;
		replicate_1x2x1(O + D*R, i, n, R, I + D*S, S, s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>//mxnxr
static inline void replicate_2x4x1 (T* O, 
																		U m,
																		U n,
																		U R = (U)(-1),
																		T* I = (T*)0,
																		U S = (U)0,
																		U s = (U)0) {
	if (R == (U)(-1)) {R = n;}

	register T t0, t1;
	register T *o0, *o1;
	register T *i0, *i1;
	register U i;
	register U j;

	U d = n >> 2;
	U D = m >> 1;
	U P = R << 1;
	U Q = S << 1;

	T* O0 = O + R * 0;
	T* O1 = O + R * 1;
	T* I0 = I + S * 0;
	T* I1 = I + S * 1;
  
	if (I == 0) { 
		for (i = D; i; i--) {
			o0 = O0;
			o1 = O1;
			O0 += P;
			O1 += P;
			for (j = d; j; j--) {
				*(o0 +   0) = (T)0;
				*(o1 +   0) = (T)0;
				*(o0 +   1) = (T)0;
				*(o1 +   1) = (T)0;
				*(o0 +   2) = (T)0;
				*(o1 +   2) = (T)0;
				*(o0 +   3) = (T)0;
				*(o1 +   3) = (T)0;
				o0 += 4;
				o1 += 4;
			}
		}
	}
	else {
		switch (s) {
			case 0: {
				for (i = D; i; i--) {
					o0 = O0;
					o1 = O1;
					O0 += P;
					O1 += P;
					t0 = *I0;
					t1 = *I1;
					I0 += Q;
					I1 += Q;
					for (j = d; j; j--) {
						*(o0 +   0) = t0;
						*(o1 +   0) = t1;
						*(o0 +   1) = t0;
						*(o1 +   1) = t1;
						*(o0 +   2) = t0;
						*(o1 +   2) = t1;
						*(o0 +   3) = t0;
						*(o1 +   3) = t1;
						o0 += 4;
						o1 += 4;
					}
				}
				break;
			}
			case 1: {
				for (i = D; i; i--) {
					o0 = O0;
					o1 = O1;
					O0 += P;
					O1 += P;
					i0 = I0;
					i1 = I1;
					I0 += Q;
					I1 += Q;
					for (j = d; j; j--) {
						*(o0 +   0) = *(i0 +   0);
						*(o1 +   0) = *(i1 +   0);
						*(o0 +   1) = *(i0 +   1);
						*(o1 +   1) = *(i1 +   1);
						*(o0 +   2) = *(i0 +   2);
						*(o1 +   2) = *(i1 +   2);
						*(o0 +   3) = *(i0 +   3);
						*(o1 +   3) = *(i1 +   3);
						i0 += 4;
						o0 += 4;
						i1 += 4;
						o1 += 4;
					}
				}
				break;
			}
			default: {
				for (i = D; i; i--) {
					o0 = O0;
					o1 = O1;
					O0 += P;
					O1 += P;
					i0 = I0;
					i1 = I1;
					I0 += Q;
					I1 += Q;
					for (j = d; j; j--) {
						*(o0 +   0) = * i0; i0 += s;
						*(o1 +   0) = * i1; i1 += s;
						*(o0 +   1) = * i0; i0 += s;
						*(o1 +   1) = * i1; i1 += s;
						*(o0 +   2) = * i0; i0 += s;
						*(o1 +   2) = * i1; i1 += s;
						*(o0 +   3) = * i0; i0 += s;
						*(o1 +   3) = * i1; i1 += s;
						o0 += 4;
						o1 += 4;
					}
				}
				break;
			}
		}
	}

	j = D ? n & 3 : (U)0;
	if (j) {
		i = D << 1;
		d = n - j;
		replicate_2x2x1(O + d, i, j, R, I + d*s, S, s);
	}
	i = m & 1;
	if (i) {
		D = m - i;
		replicate_1x4x1(O + D*R, i, n, R, I + D*S, S, s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>//mxnxr
static inline void replicate_2x8x1 (T* O, 
																		U m,
																		U n,
																		U R = (U)(-1),
																		T* I = (T*)0,
																		U S = (U)0,
																		U s = (U)0) {
	if (R == (U)(-1)) {R = n;}

	register T t0, t1;
	register T *o0, *o1;
	register T *i0, *i1;
	register U i;
	register U j;

	U d = n >> 3;
	U D = m >> 1;
	U P = R << 1;
	U Q = S << 1;

	T* O0 = O + R * 0;
	T* O1 = O + R * 1;
	T* I0 = I + S * 0;
	T* I1 = I + S * 1;
  
	if (I == 0) { 
		for (i = D; i; i--) {
			o0 = O0;
			o1 = O1;
			O0 += P;
			O1 += P;
			for (j = d; j; j--) {
				*(o0 +   0) = (T)0;
				*(o1 +   0) = (T)0;
				*(o0 +   1) = (T)0;
				*(o1 +   1) = (T)0;
				*(o0 +   2) = (T)0;
				*(o1 +   2) = (T)0;
				*(o0 +   3) = (T)0;
				*(o1 +   3) = (T)0;
				*(o0 +   4) = (T)0;
				*(o1 +   4) = (T)0;
				*(o0 +   5) = (T)0;
				*(o1 +   5) = (T)0;
				*(o0 +   6) = (T)0;
				*(o1 +   6) = (T)0;
				*(o0 +   7) = (T)0;
				*(o1 +   7) = (T)0;
				o0 += 8;
				o1 += 8;
			}
		}
	}
	else {
		switch (s) {
			case 0: {
				for (i = D; i; i--) {
					o0 = O0;
					o1 = O1;
					O0 += P;
					O1 += P;
					t0 = *I0;
					t1 = *I1;
					I0 += Q;
					I1 += Q;
					for (j = d; j; j--) {
						*(o0 +   0) = t0;
						*(o1 +   0) = t1;
						*(o0 +   1) = t0;
						*(o1 +   1) = t1;
						*(o0 +   2) = t0;
						*(o1 +   2) = t1;
						*(o0 +   3) = t0;
						*(o1 +   3) = t1;
						*(o0 +   4) = t0;
						*(o1 +   4) = t1;
						*(o0 +   5) = t0;
						*(o1 +   5) = t1;
						*(o0 +   6) = t0;
						*(o1 +   6) = t1;
						*(o0 +   7) = t0;
						*(o1 +   7) = t1;
						o0 += 8;
						o1 += 8;
					}
				}
				break;
			}
			case 1: {
				for (i = D; i; i--) {
					o0 = O0;
					o1 = O1;
					O0 += P;
					O1 += P;
					i0 = I0;
					i1 = I1;
					I0 += Q;
					I1 += Q;
					for (j = d; j; j--) {
						*(o0 +   0) = *(i0 +   0);
						*(o1 +   0) = *(i1 +   0);
						*(o0 +   1) = *(i0 +   1);
						*(o1 +   1) = *(i1 +   1);
						*(o0 +   2) = *(i0 +   2);
						*(o1 +   2) = *(i1 +   2);
						*(o0 +   3) = *(i0 +   3);
						*(o1 +   3) = *(i1 +   3);
						*(o0 +   4) = *(i0 +   4);
						*(o1 +   4) = *(i1 +   4);
						*(o0 +   5) = *(i0 +   5);
						*(o1 +   5) = *(i1 +   5);
						*(o0 +   6) = *(i0 +   6);
						*(o1 +   6) = *(i1 +   6);
						*(o0 +   7) = *(i0 +   7);
						*(o1 +   7) = *(i1 +   7);
						i0 += 8;
						o0 += 8;
						i1 += 8;
						o1 += 8;
					}
				}
				break;
			}
			default: {
				for (i = D; i; i--) {
					o0 = O0;
					o1 = O1;
					O0 += P;
					O1 += P;
					i0 = I0;
					i1 = I1;
					I0 += Q;
					I1 += Q;
					for (j = d; j; j--) {
						*(o0 +   0) = * i0; i0 += s;
						*(o1 +   0) = * i1; i1 += s;
						*(o0 +   1) = * i0; i0 += s;
						*(o1 +   1) = * i1; i1 += s;
						*(o0 +   2) = * i0; i0 += s;
						*(o1 +   2) = * i1; i1 += s;
						*(o0 +   3) = * i0; i0 += s;
						*(o1 +   3) = * i1; i1 += s;
						*(o0 +   4) = * i0; i0 += s;
						*(o1 +   4) = * i1; i1 += s;
						*(o0 +   5) = * i0; i0 += s;
						*(o1 +   5) = * i1; i1 += s;
						*(o0 +   6) = * i0; i0 += s;
						*(o1 +   6) = * i1; i1 += s;
						*(o0 +   7) = * i0; i0 += s;
						*(o1 +   7) = * i1; i1 += s;
						o0 += 8;
						o1 += 8;
					}
				}
				break;
			}
		}
	}

	j = D ? n & 7 : (U)0;
	if (j) {
		i = D << 1;
		d = n - j;
		replicate_2x4x1(O + d, i, j, R, I + d*s, S, s);
	}
	i = m & 1;
	if (i) {
		D = m - i;
		replicate_1x8x1(O + D*R, i, n, R, I + D*S, S, s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>//mxnxr
static inline void replicate_4x1x1 (T* O, 
																		U m,
																		U n,
																		U R = (U)(-1),
																		T* I = (T*)0,
																		U S = (U)0,
																		U s = (U)0) {
	if (R == (U)(-1)) {R = n;}

	register T t0, t1, t2, t3;
	register T *o0, *o1, *o2, *o3;
	register T *i0, *i1, *i2, *i3;
	register U i;
	register U j;

	U D = m >> 2;
	U P = R << 2;
	U Q = S << 2;

	T* O0 = O + R * 0;
	T* O1 = O + R * 1;
	T* O2 = O + R * 2;
	T* O3 = O + R * 3;
	T* I0 = I + S * 0;
	T* I1 = I + S * 1;
	T* I2 = I + S * 2;
	T* I3 = I + S * 3;
  
	if (I == 0) { 
		for (i = D; i; i--) {
			o0 = O0;
			o1 = O1;
			o2 = O2;
			o3 = O3;
			O0 += P;
			O1 += P;
			O2 += P;
			O3 += P;
			for (j = n; j; j--) {
				*(o0 +   0) = (T)0;
				*(o1 +   0) = (T)0;
				*(o2 +   0) = (T)0;
				*(o3 +   0) = (T)0;
				o0 ++;
				o1 ++;
				o2 ++;
				o3 ++;
			}
		}
	}
	else {
		switch (s) {
			case 0: {
				for (i = D; i; i--) {
					o0 = O0;
					o1 = O1;
					o2 = O2;
					o3 = O3;
					O0 += P;
					O1 += P;
					O2 += P;
					O3 += P;
					t0 = *I0;
					t1 = *I1;
					t2 = *I2;
					t3 = *I3;
					I0 += Q;
					I1 += Q;
					I2 += Q;
					I3 += Q;
					for (j = n; j; j--) {
						*(o0 +   0) = t0;
						*(o1 +   0) = t1;
						*(o2 +   0) = t2;
						*(o3 +   0) = t3;
						o0 ++;
						o1 ++;
						o2 ++;
						o3 ++;
					}
				}
				break;
			}
			case 1: {
				for (i = D; i; i--) {
					o0 = O0;
					o1 = O1;
					o2 = O2;
					o3 = O3;
					O0 += P;
					O1 += P;
					O2 += P;
					O3 += P;
					i0 = I0;
					i1 = I1;
					i2 = I2;
					i3 = I3;
					I0 += Q;
					I1 += Q;
					I2 += Q;
					I3 += Q;
					for (j = n; j; j--) {
						*(o0 +   0) = *(i0 +   0);
						*(o1 +   0) = *(i1 +   0);
						*(o2 +   0) = *(i2 +   0);
						*(o3 +   0) = *(i3 +   0);
						i0 ++;
						o0 ++;
						i1 ++;
						o1 ++;
						i2 ++;
						o2 ++;
						i3 ++;
						o3 ++;
					}
				}
				break;
			}
			default: {
				for (i = D; i; i--) {
					o0 = O0;
					o1 = O1;
					o2 = O2;
					o3 = O3;
					O0 += P;
					O1 += P;
					O2 += P;
					O3 += P;
					i0 = I0;
					i1 = I1;
					i2 = I2;
					i3 = I3;
					I0 += Q;
					I1 += Q;
					I2 += Q;
					I3 += Q;
					for (j = n; j; j--) {
						*(o0 +   0) = * i0; i0 += s;
						*(o1 +   0) = * i1; i1 += s;
						*(o2 +   0) = * i2; i2 += s;
						*(o3 +   0) = * i3; i3 += s;
						o0 ++;
						o1 ++;
						o2 ++;
						o3 ++;
					}
				}
				break;
			}
		}
	}
	i = m & 3;
	if (i) {
		D = m - i;
		replicate_2x1x1(O + D*R, i, n, R, I + D*S, S, s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>//mxnxr
static inline void replicate_4x2x1 (T* O, 
																		U m,
																		U n,
																		U R = (U)(-1),
																		T* I = (T*)0,
																		U S = (U)0,
																		U s = (U)0) {
	if (R == (U)(-1)) {R = n;}

	register T t0, t1, t2, t3;
	register T *o0, *o1, *o2, *o3;
	register T *i0, *i1, *i2, *i3;
	register U i;
	register U j;

	U d = n >> 1;
	U D = m >> 2;
	U P = R << 2;
	U Q = S << 2;

	T* O0 = O + R * 0;
	T* O1 = O + R * 1;
	T* O2 = O + R * 2;
	T* O3 = O + R * 3;
	T* I0 = I + S * 0;
	T* I1 = I + S * 1;
	T* I2 = I + S * 2;
	T* I3 = I + S * 3;

	if (I == 0) { 
		for (i = D; i; i--) {
			o0 = O0;
			o1 = O1;
			o2 = O2;
			o3 = O3;
			O0 += P;
			O1 += P;
			O2 += P;
			O3 += P;
			for (j = d; j; j--) {
				*(o0 +   0) = (T)0;
				*(o1 +   0) = (T)0;
				*(o2 +   0) = (T)0;
				*(o3 +   0) = (T)0;
				*(o0 +   1) = (T)0;
				*(o1 +   1) = (T)0;
				*(o2 +   1) = (T)0;
				*(o3 +   1) = (T)0;
				o0 += 2;
				o1 += 2;
				o2 += 2;
				o3 += 2;
			}
		}
	}
	else {
		switch (s) {
			case 0: {
				for (i = D; i; i--) {
					o0 = O0;
					o1 = O1;
					o2 = O2;
					o3 = O3;
					O0 += P;
					O1 += P;
					O2 += P;
					O3 += P;
					t0 = *I0;
					t1 = *I1;
					t2 = *I2;
					t3 = *I3;
					I0 += Q;
					I1 += Q;
					I2 += Q;
					I3 += Q;
					for (j = d; j; j--) {
						*(o0 +   0) = t0;
						*(o1 +   0) = t1;
						*(o2 +   0) = t2;
						*(o3 +   0) = t3;
						*(o0 +   1) = t0;
						*(o1 +   1) = t1;
						*(o2 +   1) = t2;
						*(o3 +   1) = t3;
						o0 += 2;
						o1 += 2;
						o2 += 2;
						o3 += 2;
					}
				}
				break;
			}
			case 1: {
				for (i = D; i; i--) {
					o0 = O0;
					o1 = O1;
					o2 = O2;
					o3 = O3;
					O0 += P;
					O1 += P;
					O2 += P;
					O3 += P;
					i0 = I0;
					i1 = I1;
					i2 = I2;
					i3 = I3;
					I0 += Q;
					I1 += Q;
					I2 += Q;
					I3 += Q;
					for (j = d; j; j--) {
						*(o0 +   0) = *(i0 +   0);
						*(o1 +   0) = *(i1 +   0);
						*(o2 +   0) = *(i2 +   0);
						*(o3 +   0) = *(i3 +   0);
						*(o0 +   1) = *(i0 +   1);
						*(o1 +   1) = *(i1 +   1);
						*(o2 +   1) = *(i2 +   1);
						*(o3 +   1) = *(i3 +   1);
						i0 += 2;
						o0 += 2;
						i1 += 2;
						o1 += 2;
						i2 += 2;
						o2 += 2;
						i3 += 2;
						o3 += 2;
					}
				}
				break;
			}
			default: {
				for (i = D; i; i--) {
					o0 = O0;
					o1 = O1;
					o2 = O2;
					o3 = O3;
					O0 += P;
					O1 += P;
					O2 += P;
					O3 += P;
					i0 = I0;
					i1 = I1;
					i2 = I2;
					i3 = I3;
					I0 += Q;
					I1 += Q;
					I2 += Q;
					I3 += Q;
					for (j = d; j; j--) {
						*(o0 +   0) = * i0; i0 += s;
						*(o1 +   0) = * i1; i1 += s;
						*(o2 +   0) = * i2; i2 += s;
						*(o3 +   0) = * i3; i3 += s;
						*(o0 +   1) = * i0; i0 += s;
						*(o1 +   1) = * i1; i1 += s;
						*(o2 +   1) = * i2; i2 += s;
						*(o3 +   1) = * i3; i3 += s;
						o0 += 2;
						o1 += 2;
						o2 += 2;
						o3 += 2;
					}
				}
				break;
			}
		}
	}

	j = D ? n & 1 : (U)0;
	if (j) {
		i = D << 1;
		d = n - j;
		replicate_4x1x1(O + d, i, j, R, I + d*s, S, s);
	}
	i = m & 3;
	if (i) {
		D = m - i;
		replicate_2x2x1(O + D*R, i, n, R, I + D*S, S, s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>//mxnxr
static inline void replicate_4x4x1 (T* O, 
																		U m,
																		U n,
																		U R = (U)(-1),
																		T* I = (T*)0,
																		U S = (U)0,
																		U s = (U)0) {
	if (R == (U)(-1)) {R = n;}

	register T t0, t1, t2, t3;
	register T *o0, *o1, *o2, *o3;
	register T *i0, *i1, *i2, *i3;
	register U i;
	register U j;

	U d = n >> 2;
	U D = m >> 2;
	U P = R << 2;
	U Q = S << 2;

	T* O0 = O + R * 0;
	T* O1 = O + R * 1;
	T* O2 = O + R * 2;
	T* O3 = O + R * 3;
	T* I0 = I + S * 0;
	T* I1 = I + S * 1;
	T* I2 = I + S * 2;
	T* I3 = I + S * 3;

	if (I == 0) { 
		for (i = D; i; i--) {
			o0 = O0;
			o1 = O1;
			o2 = O2;
			o3 = O3;
			O0 += P;
			O1 += P;
			O2 += P;
			O3 += P;
			for (j = d; j; j--) {
				*(o0 +   0) = (T)0;
				*(o1 +   0) = (T)0;
				*(o2 +   0) = (T)0;
				*(o3 +   0) = (T)0;
				*(o0 +   1) = (T)0;
				*(o1 +   1) = (T)0;
				*(o2 +   1) = (T)0;
				*(o3 +   1) = (T)0;
				*(o0 +   2) = (T)0;
				*(o1 +   2) = (T)0;
				*(o2 +   2) = (T)0;
				*(o3 +   2) = (T)0;
				*(o0 +   3) = (T)0;
				*(o1 +   3) = (T)0;
				*(o2 +   3) = (T)0;
				*(o3 +   3) = (T)0;
				o0 += 4;
				o1 += 4;
				o2 += 4;
				o3 += 4;
			}
		}
	}
	else {
		switch (s) {
			case 0: {
				for (i = D; i; i--) {
					o0 = O0;
					o1 = O1;
					o2 = O2;
					o3 = O3;
					O0 += P;
					O1 += P;
					O2 += P;
					O3 += P;
					t0 = *I0;
					t1 = *I1;
					t2 = *I2;
					t3 = *I3;
					I0 += Q;
					I1 += Q;
					I2 += Q;
					I3 += Q;
					for (j = d; j; j--) {
						*(o0 +   0) = t0;
						*(o1 +   0) = t1;
						*(o2 +   0) = t2;
						*(o3 +   0) = t3;
						*(o0 +   1) = t0;
						*(o1 +   1) = t1;
						*(o2 +   1) = t2;
						*(o3 +   1) = t3;
						*(o0 +   2) = t0;
						*(o1 +   2) = t1;
						*(o2 +   2) = t2;
						*(o3 +   2) = t3;
						*(o0 +   3) = t0;
						*(o1 +   3) = t1;
						*(o2 +   3) = t2;
						*(o3 +   3) = t3;
						o0 += 4;
						o1 += 4;
						o2 += 4;
						o3 += 4;
					}
				}
				break;
			}
			case 1: {
				for (i = D; i; i--) {
					o0 = O0;
					o1 = O1;
					o2 = O2;
					o3 = O3;
					O0 += P;
					O1 += P;
					O2 += P;
					O3 += P;
					i0 = I0;
					i1 = I1;
					i2 = I2;
					i3 = I3;
					I0 += Q;
					I1 += Q;
					I2 += Q;
					I3 += Q;
					for (j = d; j; j--) {
						*(o0 +   0) = *(i0 +   0);
						*(o1 +   0) = *(i1 +   0);
						*(o2 +   0) = *(i2 +   0);
						*(o3 +   0) = *(i3 +   0);
						*(o0 +   1) = *(i0 +   1);
						*(o1 +   1) = *(i1 +   1);
						*(o2 +   1) = *(i2 +   1);
						*(o3 +   1) = *(i3 +   1);
						*(o0 +   2) = *(i0 +   2);
						*(o1 +   2) = *(i1 +   2);
						*(o2 +   2) = *(i2 +   2);
						*(o3 +   2) = *(i3 +   2);
						*(o0 +   3) = *(i0 +   3);
						*(o1 +   3) = *(i1 +   3);
						*(o2 +   3) = *(i2 +   3);
						*(o3 +   3) = *(i3 +   3);
						i0 += 4;
						o0 += 4;
						i1 += 4;
						o1 += 4;
						i2 += 4;
						o2 += 4;
						i3 += 4;
						o3 += 4;
					}
				}
				break;
			}
			default: {
				for (i = D; i; i--) {
					o0 = O0;
					o1 = O1;
					o2 = O2;
					o3 = O3;
					O0 += P;
					O1 += P;
					O2 += P;
					O3 += P;
					i0 = I0;
					i1 = I1;
					i2 = I2;
					i3 = I3;
					I0 += Q;
					I1 += Q;
					I2 += Q;
					I3 += Q;
					for (j = d; j; j--) {
						*(o0 +   0) = * i0; i0 += s;
						*(o1 +   0) = * i1; i1 += s;
						*(o2 +   0) = * i2; i2 += s;
						*(o3 +   0) = * i3; i3 += s;
						*(o0 +   1) = * i0; i0 += s;
						*(o1 +   1) = * i1; i1 += s;
						*(o2 +   1) = * i2; i2 += s;
						*(o3 +   1) = * i3; i3 += s;
						*(o0 +   2) = * i0; i0 += s;
						*(o1 +   2) = * i1; i1 += s;
						*(o2 +   2) = * i2; i2 += s;
						*(o3 +   2) = * i3; i3 += s;
						*(o0 +   3) = * i0; i0 += s;
						*(o1 +   3) = * i1; i1 += s;
						*(o2 +   3) = * i2; i2 += s;
						*(o3 +   3) = * i3; i3 += s;
						o0 += 4;
						o1 += 4;
						o2 += 4;
						o3 += 4;
					}
				}
				break;
			}
		}
	}

	j = D ? n & 3 : (U)0;
	if (j) {
		i = D << 1;
		d = n - j;
		replicate_4x2x1(O + d, i, j, R, I + d*s, S, s);
	}
	i = m & 3;
	if (i) {
		D = m - i;
		replicate_2x4x1(O + D*R, i, n, R, I + D*S, S, s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>//mxnxr
static inline void replicate_4x8x1 (T* O, 
																		U m,
																		U n,
																		U R = (U)(-1),
																		T* I = (T*)0,
																		U S = (U)0,
																		U s = (U)0) {
	if (R == (U)(-1)) {R = n;}

	register T t0, t1, t2, t3;
	register T *o0, *o1, *o2, *o3;
	register T *i0, *i1, *i2, *i3;
	register U i;
	register U j;

	U d = n >> 3;
	U D = m >> 2;
	U P = R << 2;
	U Q = S << 2;

	T* O0 = O + R * 0;
	T* O1 = O + R * 1;
	T* O2 = O + R * 2;
	T* O3 = O + R * 3;
	T* I0 = I + S * 0;
	T* I1 = I + S * 1;
	T* I2 = I + S * 2;
	T* I3 = I + S * 3;

	if (I == 0) { 
		for (i = D; i; i--) {
			o0 = O0;
			o1 = O1;
			o2 = O2;
			o3 = O3;
			O0 += P;
			O1 += P;
			O2 += P;
			O3 += P;
			for (j = d; j; j--) {
				*(o0 +   0) = (T)0;
				*(o1 +   0) = (T)0;
				*(o2 +   0) = (T)0;
				*(o3 +   0) = (T)0;
				*(o0 +   1) = (T)0;
				*(o1 +   1) = (T)0;
				*(o2 +   1) = (T)0;
				*(o3 +   1) = (T)0;
				*(o0 +   2) = (T)0;
				*(o1 +   2) = (T)0;
				*(o2 +   2) = (T)0;
				*(o3 +   2) = (T)0;
				*(o0 +   3) = (T)0;
				*(o1 +   3) = (T)0;
				*(o2 +   3) = (T)0;
				*(o3 +   3) = (T)0;
				*(o0 +   4) = (T)0;
				*(o1 +   4) = (T)0;
				*(o2 +   4) = (T)0;
				*(o3 +   4) = (T)0;
				*(o0 +   5) = (T)0;
				*(o1 +   5) = (T)0;
				*(o2 +   5) = (T)0;
				*(o3 +   5) = (T)0;
				*(o0 +   6) = (T)0;
				*(o1 +   6) = (T)0;
				*(o2 +   6) = (T)0;
				*(o3 +   6) = (T)0;
				*(o0 +   7) = (T)0;
				*(o1 +   7) = (T)0;
				*(o2 +   7) = (T)0;
				*(o3 +   7) = (T)0;
				o0 += 8;
				o1 += 8;
				o2 += 8;
				o3 += 8;
			}
		}
	}
	else {
		switch (s) {
			case 0: {
				for (i = D; i; i--) {
					o0 = O0;
					o1 = O1;
					o2 = O2;
					o3 = O3;
					O0 += P;
					O1 += P;
					O2 += P;
					O3 += P;
					t0 = *I0;
					t1 = *I1;
					t2 = *I2;
					t3 = *I3;
					I0 += Q;
					I1 += Q;
					I2 += Q;
					I3 += Q;
					for (j = d; j; j--) {
						*(o0 +   0) = t0;
						*(o1 +   0) = t1;
						*(o2 +   0) = t2;
						*(o3 +   0) = t3;
						*(o0 +   1) = t0;
						*(o1 +   1) = t1;
						*(o2 +   1) = t2;
						*(o3 +   1) = t3;
						*(o0 +   2) = t0;
						*(o1 +   2) = t1;
						*(o2 +   2) = t2;
						*(o3 +   2) = t3;
						*(o0 +   3) = t0;
						*(o1 +   3) = t1;
						*(o2 +   3) = t2;
						*(o3 +   3) = t3;
						*(o0 +   4) = t0;
						*(o1 +   4) = t1;
						*(o2 +   4) = t2;
						*(o3 +   4) = t3;
						*(o0 +   5) = t0;
						*(o1 +   5) = t1;
						*(o2 +   5) = t2;
						*(o3 +   5) = t3;
						*(o0 +   6) = t0;
						*(o1 +   6) = t1;
						*(o2 +   6) = t2;
						*(o3 +   6) = t3;
						*(o0 +   7) = t0;
						*(o1 +   7) = t1;
						*(o2 +   7) = t2;
						*(o3 +   7) = t3;
						o0 += 8;
						o1 += 8;
						o2 += 8;
						o3 += 8;
					}
				}
				break;
			}
			case 1: {
				for (i = D; i; i--) {
					o0 = O0;
					o1 = O1;
					o2 = O2;
					o3 = O3;
					O0 += P;
					O1 += P;
					O2 += P;
					O3 += P;
					i0 = I0;
					i1 = I1;
					i2 = I2;
					i3 = I3;
					I0 += Q;
					I1 += Q;
					I2 += Q;
					I3 += Q;
					for (j = d; j; j--) {
						*(o0 +   0) = *(i0 +   0);
						*(o1 +   0) = *(i1 +   0);
						*(o2 +   0) = *(i2 +   0);
						*(o3 +   0) = *(i3 +   0);
						*(o0 +   1) = *(i0 +   1);
						*(o1 +   1) = *(i1 +   1);
						*(o2 +   1) = *(i2 +   1);
						*(o3 +   1) = *(i3 +   1);
						*(o0 +   2) = *(i0 +   2);
						*(o1 +   2) = *(i1 +   2);
						*(o2 +   2) = *(i2 +   2);
						*(o3 +   2) = *(i3 +   2);
						*(o0 +   3) = *(i0 +   3);
						*(o1 +   3) = *(i1 +   3);
						*(o2 +   3) = *(i2 +   3);
						*(o3 +   3) = *(i3 +   3);
						*(o0 +   4) = *(i0 +   4);
						*(o1 +   4) = *(i1 +   4);
						*(o2 +   4) = *(i2 +   4);
						*(o3 +   4) = *(i3 +   4);
						*(o0 +   5) = *(i0 +   5);
						*(o1 +   5) = *(i1 +   5);
						*(o2 +   5) = *(i2 +   5);
						*(o3 +   5) = *(i3 +   5);
						*(o0 +   6) = *(i0 +   6);
						*(o1 +   6) = *(i1 +   6);
						*(o2 +   6) = *(i2 +   6);
						*(o3 +   6) = *(i3 +   6);
						*(o0 +   7) = *(i0 +   7);
						*(o1 +   7) = *(i1 +   7);
						*(o2 +   7) = *(i2 +   7);
						*(o3 +   7) = *(i3 +   7);
						i0 += 8;
						o0 += 8;
						i1 += 8;
						o1 += 8;
						i2 += 8;
						o2 += 8;
						i3 += 8;
						o3 += 8;
					}
				}
				break;
			}
			default: {
				for (i = D; i; i--) {
					o0 = O0;
					o1 = O1;
					o2 = O2;
					o3 = O3;
					O0 += P;
					O1 += P;
					O2 += P;
					O3 += P;
					i0 = I0;
					i1 = I1;
					i2 = I2;
					i3 = I3;
					I0 += Q;
					I1 += Q;
					I2 += Q;
					I3 += Q;
					for (j = d; j; j--) {
						*(o0 +   0) = * i0; i0 += s;
						*(o1 +   0) = * i1; i1 += s;
						*(o2 +   0) = * i2; i2 += s;
						*(o3 +   0) = * i3; i3 += s;
						*(o0 +   1) = * i0; i0 += s;
						*(o1 +   1) = * i1; i1 += s;
						*(o2 +   1) = * i2; i2 += s;
						*(o3 +   1) = * i3; i3 += s;
						*(o0 +   2) = * i0; i0 += s;
						*(o1 +   2) = * i1; i1 += s;
						*(o2 +   2) = * i2; i2 += s;
						*(o3 +   2) = * i3; i3 += s;
						*(o0 +   3) = * i0; i0 += s;
						*(o1 +   3) = * i1; i1 += s;
						*(o2 +   3) = * i2; i2 += s;
						*(o3 +   3) = * i3; i3 += s;
						*(o0 +   4) = * i0; i0 += s;
						*(o1 +   4) = * i1; i1 += s;
						*(o2 +   4) = * i2; i2 += s;
						*(o3 +   4) = * i3; i3 += s;
						*(o0 +   5) = * i0; i0 += s;
						*(o1 +   5) = * i1; i1 += s;
						*(o2 +   5) = * i2; i2 += s;
						*(o3 +   5) = * i3; i3 += s;
						*(o0 +   6) = * i0; i0 += s;
						*(o1 +   6) = * i1; i1 += s;
						*(o2 +   6) = * i2; i2 += s;
						*(o3 +   6) = * i3; i3 += s;
						*(o0 +   7) = * i0; i0 += s;
						*(o1 +   7) = * i1; i1 += s;
						*(o2 +   7) = * i2; i2 += s;
						*(o3 +   7) = * i3; i3 += s;
						o0 += 8;
						o1 += 8;
						o2 += 8;
						o3 += 8;
					}
				}
				break;
			}
		}
	}

	j = D ? n & 7 : (U)0;
	if (j) {
		i = D << 1;
		d = n - j;
		replicate_4x4x1(O + d, i, j, R, I + d*s, S, s);
	}
	i = m & 3;
	if (i) {
		D = m - i;
		replicate_2x8x1(O + D*R, i, n, R, I + D*S, S, s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>//mxnxr
static inline void replicate_8x1x1 (T* O, 
																		U m,
																		U n,
																		U R = (U)(-1),
																		T* I = (T*)0,
																		U S = (U)0,
																		U s = (U)0) {
	if (R == (U)(-1)) {R = n;}

	register T t0, t1, t2, t3, t4, t5, t6, t7;
	register T *o0, *o1, *o2, *o3, *o4, *o5, *o6, *o7;
	register T *i0, *i1, *i2, *i3, *i4, *i5, *i6, *i7;
	register U i;
	register U j;

	U D = m >> 3;
	U P = R << 3;
	U Q = S << 3;

	T* O0 = O + R * 0;
	T* O1 = O + R * 1;
	T* O2 = O + R * 2;
	T* O3 = O + R * 3;
	T* O4 = O + R * 4;
	T* O5 = O + R * 5;
	T* O6 = O + R * 6;
	T* O7 = O + R * 7;
	T* I0 = I + S * 0;
	T* I1 = I + S * 1;
	T* I2 = I + S * 2;
	T* I3 = I + S * 3;
	T* I4 = I + S * 4;
	T* I5 = I + S * 5;
	T* I6 = I + S * 6;
	T* I7 = I + S * 7;
  
	if (I == 0) { 
		for (i = D; i; i--) {
			o0 = O0;
			o1 = O1;
			o2 = O2;
			o3 = O3;
			o4 = O4;
			o5 = O5;
			o6 = O6;
			o7 = O7;
			O0 += P;
			O1 += P;
			O2 += P;
			O3 += P;
			O4 += P;
			O5 += P;
			O6 += P;
			O7 += P;
			for (j = n; j; j--) {
				*(o0 +   0) = (T)0;
				*(o1 +   0) = (T)0;
				*(o2 +   0) = (T)0;
				*(o3 +   0) = (T)0;
				*(o4 +   0) = (T)0;
				*(o5 +   0) = (T)0;
				*(o6 +   0) = (T)0;
				*(o7 +   0) = (T)0;
				o0 ++;
				o1 ++;
				o2 ++;
				o3 ++;
				o4 ++;
				o5 ++;
				o6 ++;
				o7 ++;
			}
		}
	}
	else {
		switch (s) {
			case 0: {
				for (i = D; i; i--) {
					o0 = O0;
					o1 = O1;
					o2 = O2;
					o3 = O3;
					o4 = O4;
					o5 = O5;
					o6 = O6;
					o7 = O7;
					O0 += P;
					O1 += P;
					O2 += P;
					O3 += P;
					O4 += P;
					O5 += P;
					O6 += P;
					O7 += P;
					t0 = *I0;
					t1 = *I1;
					t2 = *I2;
					t3 = *I3;
					t4 = *I4;
					t5 = *I5;
					t6 = *I6;
					t7 = *I7;
					I0 += Q;
					I1 += Q;
					I2 += Q;
					I3 += Q;
					I4 += Q;
					I5 += Q;
					I6 += Q;
					I7 += Q;
					for (j = n; j; j--) {
						*(o0 +   0) = t0;
						*(o1 +   0) = t1;
						*(o2 +   0) = t2;
						*(o3 +   0) = t3;
						*(o4 +   0) = t4;
						*(o5 +   0) = t5;
						*(o6 +   0) = t6;
						*(o7 +   0) = t7;
						o0 ++;
						o1 ++;
						o2 ++;
						o3 ++;
						o4 ++;
						o5 ++;
						o6 ++;
						o7 ++;
					}
				}
				break;
			}
			case 1: {
				for (i = D; i; i--) {
					o0 = O0;
					o1 = O1;
					o2 = O2;
					o3 = O3;
					o4 = O4;
					o5 = O5;
					o6 = O6;
					o7 = O7;
					O0 += P;
					O1 += P;
					O2 += P;
					O3 += P;
					O4 += P;
					O5 += P;
					O6 += P;
					O7 += P;
					i0 = I0;
					i1 = I1;
					i2 = I2;
					i3 = I3;
					i4 = I4;
					i5 = I5;
					i6 = I6;
					i7 = I7;
					I0 += Q;
					I1 += Q;
					I2 += Q;
					I3 += Q;
					I4 += Q;
					I5 += Q;
					I6 += Q;
					I7 += Q;
					for (j = n; j; j--) {
						*(o0 +   0) = *(i0 +   0);
						*(o1 +   0) = *(i1 +   0);
						*(o2 +   0) = *(i2 +   0);
						*(o3 +   0) = *(i3 +   0);
						*(o4 +   0) = *(i4 +   0);
						*(o5 +   0) = *(i5 +   0);
						*(o6 +   0) = *(i6 +   0);
						*(o7 +   0) = *(i7 +   0);
						i0 ++;
						o0 ++;
						i1 ++;
						o1 ++;
						i2 ++;
						o2 ++;
						i3 ++;
						o3 ++;
						i4 ++;
						o4 ++;
						i5 ++;
						o5 ++;
						i6 ++;
						o6 ++;
						i7 ++;
						o7 ++;
					}
				}
				break;
			}
			default: {
				for (i = D; i; i--) {
					o0 = O0;
					o1 = O1;
					o2 = O2;
					o3 = O3;
					o4 = O4;
					o5 = O5;
					o6 = O6;
					o7 = O7;
					O0 += P;
					O1 += P;
					O2 += P;
					O3 += P;
					O4 += P;
					O5 += P;
					O6 += P;
					O7 += P;
					i0 = I0;
					i1 = I1;
					i2 = I2;
					i3 = I3;
					i4 = I4;
					i5 = I5;
					i6 = I6;
					i7 = I7;
					I0 += Q;
					I1 += Q;
					I2 += Q;
					I3 += Q;
					I4 += Q;
					I5 += Q;
					I6 += Q;
					I7 += Q;
					for (j = n; j; j--) {
						*(o0 +   0) = * i0; i0 += s;
						*(o1 +   0) = * i1; i1 += s;
						*(o2 +   0) = * i2; i2 += s;
						*(o3 +   0) = * i3; i3 += s;
						*(o4 +   0) = * i4; i4 += s;
						*(o5 +   0) = * i5; i5 += s;
						*(o6 +   0) = * i6; i6 += s;
						*(o7 +   0) = * i7; i7 += s;
						o0 ++;
						o1 ++;
						o2 ++;
						o3 ++;
						o4 ++;
						o5 ++;
						o6 ++;
						o7 ++;
					}
				}
				break;
			}
		}
	}
	i = m & 7;
	if (i) {
		D = m - i;
		replicate_4x1x1(O + D*R, i, n, R, I + D*S, S, s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>//mxnxr
static inline void replicate_8x2x1 (T* O, 
																		U m,
																		U n,
																		U R = (U)(-1),
																		T* I = (T*)0,
																		U S = (U)0,
																		U s = (U)0) {
	if (R == (U)(-1)) {R = n;}

	register T t0, t1, t2, t3, t4, t5, t6, t7;
	register T *o0, *o1, *o2, *o3, *o4, *o5, *o6, *o7;
	register T *i0, *i1, *i2, *i3, *i4, *i5, *i6, *i7;
	register U i;
	register U j;

	U d = n >> 1;
	U D = m >> 3;
	U P = R << 3;
	U Q = S << 3;

	T* O0 = O + R * 0;
	T* O1 = O + R * 1;
	T* O2 = O + R * 2;
	T* O3 = O + R * 3;
	T* O4 = O + R * 4;
	T* O5 = O + R * 5;
	T* O6 = O + R * 6;
	T* O7 = O + R * 7;
	T* I0 = I + S * 0;
	T* I1 = I + S * 1;
	T* I2 = I + S * 2;
	T* I3 = I + S * 3;
	T* I4 = I + S * 4;
	T* I5 = I + S * 5;
	T* I6 = I + S * 6;
	T* I7 = I + S * 7;

	if (I == 0) { 
		for (i = D; i; i--) {
			o0 = O0;
			o1 = O1;
			o2 = O2;
			o3 = O3;
			o4 = O4;
			o5 = O5;
			o6 = O6;
			o7 = O7;
			O0 += P;
			O1 += P;
			O2 += P;
			O3 += P;
			O4 += P;
			O5 += P;
			O6 += P;
			O7 += P;
			for (j = d; j; j--) {
				*(o0 +   0) = (T)0;
				*(o1 +   0) = (T)0;
				*(o2 +   0) = (T)0;
				*(o3 +   0) = (T)0;
				*(o4 +   0) = (T)0;
				*(o5 +   0) = (T)0;
				*(o6 +   0) = (T)0;
				*(o7 +   0) = (T)0;
				*(o0 +   1) = (T)0;
				*(o1 +   1) = (T)0;
				*(o2 +   1) = (T)0;
				*(o3 +   1) = (T)0;
				*(o4 +   1) = (T)0;
				*(o5 +   1) = (T)0;
				*(o6 +   1) = (T)0;
				*(o7 +   1) = (T)0;
				o0 += 2;
				o1 += 2;
				o2 += 2;
				o3 += 2;
				o4 += 2;
				o5 += 2;
				o6 += 2;
				o7 += 2;
			}
		}
	}
	else {
		switch (s) {
			case 0: {
				for (i = D; i; i--) {
					o0 = O0;
					o1 = O1;
					o2 = O2;
					o3 = O3;
					o4 = O4;
					o5 = O5;
					o6 = O6;
					o7 = O7;
					O0 += P;
					O1 += P;
					O2 += P;
					O3 += P;
					O4 += P;
					O5 += P;
					O6 += P;
					O7 += P;
					t0 = *I0;
					t1 = *I1;
					t2 = *I2;
					t3 = *I3;
					t4 = *I4;
					t5 = *I5;
					t6 = *I6;
					t7 = *I7;
					I0 += Q;
					I1 += Q;
					I2 += Q;
					I3 += Q;
					I4 += Q;
					I5 += Q;
					I6 += Q;
					I7 += Q;
					for (j = d; j; j--) {
						*(o0 +   0) = t0;
						*(o1 +   0) = t1;
						*(o2 +   0) = t2;
						*(o3 +   0) = t3;
						*(o4 +   0) = t4;
						*(o5 +   0) = t5;
						*(o6 +   0) = t6;
						*(o7 +   0) = t7;
						*(o0 +   1) = t0;
						*(o1 +   1) = t1;
						*(o2 +   1) = t2;
						*(o3 +   1) = t3;
						*(o4 +   1) = t4;
						*(o5 +   1) = t5;
						*(o6 +   1) = t6;
						*(o7 +   1) = t7;
						o0 += 2;
						o1 += 2;
						o2 += 2;
						o3 += 2;
						o4 += 2;
						o5 += 2;
						o6 += 2;
						o7 += 2;
					}
				}
				break;
			}
			case 1: {
				for (i = D; i; i--) {
					o0 = O0;
					o1 = O1;
					o2 = O2;
					o3 = O3;
					o4 = O4;
					o5 = O5;
					o6 = O6;
					o7 = O7;
					O0 += P;
					O1 += P;
					O2 += P;
					O3 += P;
					O4 += P;
					O5 += P;
					O6 += P;
					O7 += P;
					i0 = I0;
					i1 = I1;
					i2 = I2;
					i3 = I3;
					i4 = I4;
					i5 = I5;
					i6 = I6;
					i7 = I7;
					I0 += Q;
					I1 += Q;
					I2 += Q;
					I3 += Q;
					I4 += Q;
					I5 += Q;
					I6 += Q;
					I7 += Q;
					for (j = d; j; j--) {
						*(o0 +   0) = *(i0 +   0);
						*(o1 +   0) = *(i1 +   0);
						*(o2 +   0) = *(i2 +   0);
						*(o3 +   0) = *(i3 +   0);
						*(o4 +   0) = *(i4 +   0);
						*(o5 +   0) = *(i5 +   0);
						*(o6 +   0) = *(i6 +   0);
						*(o7 +   0) = *(i7 +   0);
						*(o0 +   1) = *(i0 +   1);
						*(o1 +   1) = *(i1 +   1);
						*(o2 +   1) = *(i2 +   1);
						*(o3 +   1) = *(i3 +   1);
						*(o4 +   1) = *(i4 +   1);
						*(o5 +   1) = *(i5 +   1);
						*(o6 +   1) = *(i6 +   1);
						*(o7 +   1) = *(i7 +   1);
						i0 += 2;
						o0 += 2;
						i1 += 2;
						o1 += 2;
						i2 += 2;
						o2 += 2;
						i3 += 2;
						o3 += 2;
						i4 += 2;
						o4 += 2;
						i5 += 2;
						o5 += 2;
						i6 += 2;
						o6 += 2;
						i7 += 2;
						o7 += 2;
					}
				}
				break;
			}
			default: {
				for (i = D; i; i--) {
					o0 = O0;
					o1 = O1;
					o2 = O2;
					o3 = O3;
					o4 = O4;
					o5 = O5;
					o6 = O6;
					o7 = O7;
					O0 += P;
					O1 += P;
					O2 += P;
					O3 += P;
					O4 += P;
					O5 += P;
					O6 += P;
					O7 += P;
					i0 = I0;
					i1 = I1;
					i2 = I2;
					i3 = I3;
					i4 = I4;
					i5 = I5;
					i6 = I6;
					i7 = I7;
					I0 += Q;
					I1 += Q;
					I2 += Q;
					I3 += Q;
					I4 += Q;
					I5 += Q;
					I6 += Q;
					I7 += Q;
					for (j = d; j; j--) {
						*(o0 +   0) = * i0; i0 += s;
						*(o1 +   0) = * i1; i1 += s;
						*(o2 +   0) = * i2; i2 += s;
						*(o3 +   0) = * i3; i3 += s;
						*(o4 +   0) = * i4; i4 += s;
						*(o5 +   0) = * i5; i5 += s;
						*(o6 +   0) = * i6; i6 += s;
						*(o7 +   0) = * i7; i7 += s;
						*(o0 +   1) = * i0; i0 += s;
						*(o1 +   1) = * i1; i1 += s;
						*(o2 +   1) = * i2; i2 += s;
						*(o3 +   1) = * i3; i3 += s;
						*(o4 +   1) = * i4; i4 += s;
						*(o5 +   1) = * i5; i5 += s;
						*(o6 +   1) = * i6; i6 += s;
						*(o7 +   1) = * i7; i7 += s;
						o0 += 2;
						o1 += 2;
						o2 += 2;
						o3 += 2;
						o4 += 2;
						o5 += 2;
						o6 += 2;
						o7 += 2;
					}
				}
				break;
			}
		}
	}

	j = D ? n & 1 : (U)0;
	if (j) {
		i = D << 1;
		d = n - j;
		replicate_8x1x1(O + d, i, j, R, I + d*s, S, s);
	}
	i = m & 7;
	if (i) {
		D = m - i;
		replicate_4x2x1(O + D*R, i, n, R, I + D*S, S, s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>//mxnxr
static inline void replicate_8x4x1 (T* O, 
																		U m,
																		U n,
																		U R = (U)(-1),
																		T* I = (T*)0,
																		U S = (U)0,
																		U s = (U)0) {
	if (R == (U)(-1)) {R = n;}

	register T t0, t1, t2, t3, t4, t5, t6, t7;
	register T *o0, *o1, *o2, *o3, *o4, *o5, *o6, *o7;
	register T *i0, *i1, *i2, *i3, *i4, *i5, *i6, *i7;
	register U i;
	register U j;

	U d = n >> 2;
	U D = m >> 3;
	U P = R << 3;
	U Q = S << 3;

	T* O0 = O + R * 0;
	T* O1 = O + R * 1;
	T* O2 = O + R * 2;
	T* O3 = O + R * 3;
	T* O4 = O + R * 4;
	T* O5 = O + R * 5;
	T* O6 = O + R * 6;
	T* O7 = O + R * 7;
	T* I0 = I + S * 0;
	T* I1 = I + S * 1;
	T* I2 = I + S * 2;
	T* I3 = I + S * 3;
	T* I4 = I + S * 4;
	T* I5 = I + S * 5;
	T* I6 = I + S * 6;
	T* I7 = I + S * 7;

	if (I == 0) { 
		for (i = D; i; i--) {
			o0 = O0;
			o1 = O1;
			o2 = O2;
			o3 = O3;
			o4 = O4;
			o5 = O5;
			o6 = O6;
			o7 = O7;
			O0 += P;
			O1 += P;
			O2 += P;
			O3 += P;
			O4 += P;
			O5 += P;
			O6 += P;
			O7 += P;
			for (j = d; j; j--) {
				*(o0 +   0) = (T)0;
				*(o1 +   0) = (T)0;
				*(o2 +   0) = (T)0;
				*(o3 +   0) = (T)0;
				*(o4 +   0) = (T)0;
				*(o5 +   0) = (T)0;
				*(o6 +   0) = (T)0;
				*(o7 +   0) = (T)0;
				*(o0 +   1) = (T)0;
				*(o1 +   1) = (T)0;
				*(o2 +   1) = (T)0;
				*(o3 +   1) = (T)0;
				*(o4 +   1) = (T)0;
				*(o5 +   1) = (T)0;
				*(o6 +   1) = (T)0;
				*(o7 +   1) = (T)0;
				*(o0 +   2) = (T)0;
				*(o1 +   2) = (T)0;
				*(o2 +   2) = (T)0;
				*(o3 +   2) = (T)0;
				*(o4 +   2) = (T)0;
				*(o5 +   2) = (T)0;
				*(o6 +   2) = (T)0;
				*(o7 +   2) = (T)0;
				*(o0 +   3) = (T)0;
				*(o1 +   3) = (T)0;
				*(o2 +   3) = (T)0;
				*(o3 +   3) = (T)0;
				*(o4 +   3) = (T)0;
				*(o5 +   3) = (T)0;
				*(o6 +   3) = (T)0;
				*(o7 +   3) = (T)0;
				o0 += 4;
				o1 += 4;
				o2 += 4;
				o3 += 4;
				o4 += 4;
				o5 += 4;
				o6 += 4;
				o7 += 4;
			}
		}
	}
	else {
		switch (s) {
			case 0: {
				for (i = D; i; i--) {
					o0 = O0;
					o1 = O1;
					o2 = O2;
					o3 = O3;
					o4 = O4;
					o5 = O5;
					o6 = O6;
					o7 = O7;
					O0 += P;
					O1 += P;
					O2 += P;
					O3 += P;
					O4 += P;
					O5 += P;
					O6 += P;
					O7 += P;
					t0 = *I0;
					t1 = *I1;
					t2 = *I2;
					t3 = *I3;
					t4 = *I4;
					t5 = *I5;
					t6 = *I6;
					t7 = *I7;
					I0 += Q;
					I1 += Q;
					I2 += Q;
					I3 += Q;
					I4 += Q;
					I5 += Q;
					I6 += Q;
					I7 += Q;
					for (j = d; j; j--) {
						*(o0 +   0) = t0;
						*(o1 +   0) = t1;
						*(o2 +   0) = t2;
						*(o3 +   0) = t3;
						*(o4 +   0) = t4;
						*(o5 +   0) = t5;
						*(o6 +   0) = t6;
						*(o7 +   0) = t7;
						*(o0 +   1) = t0;
						*(o1 +   1) = t1;
						*(o2 +   1) = t2;
						*(o3 +   1) = t3;
						*(o4 +   1) = t4;
						*(o5 +   1) = t5;
						*(o6 +   1) = t6;
						*(o7 +   1) = t7;
						*(o0 +   2) = t0;
						*(o1 +   2) = t1;
						*(o2 +   2) = t2;
						*(o3 +   2) = t3;
						*(o4 +   2) = t4;
						*(o5 +   2) = t5;
						*(o6 +   2) = t6;
						*(o7 +   2) = t7;
						*(o0 +   3) = t0;
						*(o1 +   3) = t1;
						*(o2 +   3) = t2;
						*(o3 +   3) = t3;
						*(o4 +   3) = t4;
						*(o5 +   3) = t5;
						*(o6 +   3) = t6;
						*(o7 +   3) = t7;
						o0 += 4;
						o1 += 4;
						o2 += 4;
						o3 += 4;
						o4 += 4;
						o5 += 4;
						o6 += 4;
						o7 += 4;
					}
				}
				break;
			}
			case 1: {
				for (i = D; i; i--) {
					o0 = O0;
					o1 = O1;
					o2 = O2;
					o3 = O3;
					o4 = O4;
					o5 = O5;
					o6 = O6;
					o7 = O7;
					O0 += P;
					O1 += P;
					O2 += P;
					O3 += P;
					O4 += P;
					O5 += P;
					O6 += P;
					O7 += P;
					i0 = I0;
					i1 = I1;
					i2 = I2;
					i3 = I3;
					i4 = I4;
					i5 = I5;
					i6 = I6;
					i7 = I7;
					I0 += Q;
					I1 += Q;
					I2 += Q;
					I3 += Q;
					I4 += Q;
					I5 += Q;
					I6 += Q;
					I7 += Q;
					for (j = d; j; j--) {
						*(o0 +   0) = *(i0 +   0);
						*(o1 +   0) = *(i1 +   0);
						*(o2 +   0) = *(i2 +   0);
						*(o3 +   0) = *(i3 +   0);
						*(o4 +   0) = *(i4 +   0);
						*(o5 +   0) = *(i5 +   0);
						*(o6 +   0) = *(i6 +   0);
						*(o7 +   0) = *(i7 +   0);
						*(o0 +   1) = *(i0 +   1);
						*(o1 +   1) = *(i1 +   1);
						*(o2 +   1) = *(i2 +   1);
						*(o3 +   1) = *(i3 +   1);
						*(o4 +   1) = *(i4 +   1);
						*(o5 +   1) = *(i5 +   1);
						*(o6 +   1) = *(i6 +   1);
						*(o7 +   1) = *(i7 +   1);
						*(o0 +   2) = *(i0 +   2);
						*(o1 +   2) = *(i1 +   2);
						*(o2 +   2) = *(i2 +   2);
						*(o3 +   2) = *(i3 +   2);
						*(o4 +   2) = *(i4 +   2);
						*(o5 +   2) = *(i5 +   2);
						*(o6 +   2) = *(i6 +   2);
						*(o7 +   2) = *(i7 +   2);
						*(o0 +   3) = *(i0 +   3);
						*(o1 +   3) = *(i1 +   3);
						*(o2 +   3) = *(i2 +   3);
						*(o3 +   3) = *(i3 +   3);
						*(o4 +   3) = *(i4 +   3);
						*(o5 +   3) = *(i5 +   3);
						*(o6 +   3) = *(i6 +   3);
						*(o7 +   3) = *(i7 +   3);
						i0 += 4;
						o0 += 4;
						i1 += 4;
						o1 += 4;
						i2 += 4;
						o2 += 4;
						i3 += 4;
						o3 += 4;
						i4 += 4;
						o4 += 4;
						i5 += 4;
						o5 += 4;
						i6 += 4;
						o6 += 4;
						i7 += 4;
						o7 += 4;
					}
				}
				break;
			}
			default: {
				for (i = D; i; i--) {
					o0 = O0;
					o1 = O1;
					o2 = O2;
					o3 = O3;
					o4 = O4;
					o5 = O5;
					o6 = O6;
					o7 = O7;
					O0 += P;
					O1 += P;
					O2 += P;
					O3 += P;
					O4 += P;
					O5 += P;
					O6 += P;
					O7 += P;
					i0 = I0;
					i1 = I1;
					i2 = I2;
					i3 = I3;
					i4 = I4;
					i5 = I5;
					i6 = I6;
					i7 = I7;
					I0 += Q;
					I1 += Q;
					I2 += Q;
					I3 += Q;
					I4 += Q;
					I5 += Q;
					I6 += Q;
					I7 += Q;
					for (j = d; j; j--) {
						*(o0 +   0) = * i0; i0 += s;
						*(o1 +   0) = * i1; i1 += s;
						*(o2 +   0) = * i2; i2 += s;
						*(o3 +   0) = * i3; i3 += s;
						*(o4 +   0) = * i4; i4 += s;
						*(o5 +   0) = * i5; i5 += s;
						*(o6 +   0) = * i6; i6 += s;
						*(o7 +   0) = * i7; i7 += s;
						*(o0 +   1) = * i0; i0 += s;
						*(o1 +   1) = * i1; i1 += s;
						*(o2 +   1) = * i2; i2 += s;
						*(o3 +   1) = * i3; i3 += s;
						*(o4 +   1) = * i4; i4 += s;
						*(o5 +   1) = * i5; i5 += s;
						*(o6 +   1) = * i6; i6 += s;
						*(o7 +   1) = * i7; i7 += s;
						*(o0 +   2) = * i0; i0 += s;
						*(o1 +   2) = * i1; i1 += s;
						*(o2 +   2) = * i2; i2 += s;
						*(o3 +   2) = * i3; i3 += s;
						*(o4 +   2) = * i4; i4 += s;
						*(o5 +   2) = * i5; i5 += s;
						*(o6 +   2) = * i6; i6 += s;
						*(o7 +   2) = * i7; i7 += s;
						*(o0 +   3) = * i0; i0 += s;
						*(o1 +   3) = * i1; i1 += s;
						*(o2 +   3) = * i2; i2 += s;
						*(o3 +   3) = * i3; i3 += s;
						*(o4 +   3) = * i4; i4 += s;
						*(o5 +   3) = * i5; i5 += s;
						*(o6 +   3) = * i6; i6 += s;
						*(o7 +   3) = * i7; i7 += s;
						o0 += 4;
						o1 += 4;
						o2 += 4;
						o3 += 4;
						o4 += 4;
						o5 += 4;
						o6 += 4;
						o7 += 4;
					}
				}
				break;
			}
		}
	}

	j = D ? n & 3 : (U)0;
	if (j) {
		i = D << 1;
		d = n - j;
		replicate_8x2x1(O + d, i, j, R, I + d*s, S, s);
	}
	i = m & 7;
	if (i) {
		D = m - i;
		replicate_4x4x1(O + D*R, i, n, R, I + D*S, S, s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>//mxnxr
static inline void replicate_8x8x1 (T* O, 
																		U m,
																		U n,
																		U R = (U)(-1),
																		T* I = (T*)0,
																		U S = (U)0,
																		U s = (U)0) {
	if (R == (U)(-1)) {R = n;}

	register T t0, t1, t2, t3, t4, t5, t6, t7;
	register T *o0, *o1, *o2, *o3, *o4, *o5, *o6, *o7;
	register T *i0, *i1, *i2, *i3, *i4, *i5, *i6, *i7;
	register U i;
	register U j;

	U d = n >> 3;
	U D = m >> 3;
	U P = R << 3;
	U Q = S << 3;

	T* O0 = O + R * 0;
	T* O1 = O + R * 1;
	T* O2 = O + R * 2;
	T* O3 = O + R * 3;
	T* O4 = O + R * 4;
	T* O5 = O + R * 5;
	T* O6 = O + R * 6;
	T* O7 = O + R * 7;
	T* I0 = I + S * 0;
	T* I1 = I + S * 1;
	T* I2 = I + S * 2;
	T* I3 = I + S * 3;
	T* I4 = I + S * 4;
	T* I5 = I + S * 5;
	T* I6 = I + S * 6;
	T* I7 = I + S * 7;

	if (I == 0) { 
		for (i = D; i; i--) {
			o0 = O0;
			o1 = O1;
			o2 = O2;
			o3 = O3;
			o4 = O4;
			o5 = O5;
			o6 = O6;
			o7 = O7;
			O0 += P;
			O1 += P;
			O2 += P;
			O3 += P;
			O4 += P;
			O5 += P;
			O6 += P;
			O7 += P;
			for (j = d; j; j--) {
				*(o0 +   0) = (T)0;
				*(o1 +   0) = (T)0;
				*(o2 +   0) = (T)0;
				*(o3 +   0) = (T)0;
				*(o4 +   0) = (T)0;
				*(o5 +   0) = (T)0;
				*(o6 +   0) = (T)0;
				*(o7 +   0) = (T)0;
				*(o0 +   1) = (T)0;
				*(o1 +   1) = (T)0;
				*(o2 +   1) = (T)0;
				*(o3 +   1) = (T)0;
				*(o4 +   1) = (T)0;
				*(o5 +   1) = (T)0;
				*(o6 +   1) = (T)0;
				*(o7 +   1) = (T)0;
				*(o0 +   2) = (T)0;
				*(o1 +   2) = (T)0;
				*(o2 +   2) = (T)0;
				*(o3 +   2) = (T)0;
				*(o4 +   2) = (T)0;
				*(o5 +   2) = (T)0;
				*(o6 +   2) = (T)0;
				*(o7 +   2) = (T)0;
				*(o0 +   3) = (T)0;
				*(o1 +   3) = (T)0;
				*(o2 +   3) = (T)0;
				*(o3 +   3) = (T)0;
				*(o4 +   3) = (T)0;
				*(o5 +   3) = (T)0;
				*(o6 +   3) = (T)0;
				*(o7 +   3) = (T)0;
				*(o0 +   4) = (T)0;
				*(o1 +   4) = (T)0;
				*(o2 +   4) = (T)0;
				*(o3 +   4) = (T)0;
				*(o4 +   4) = (T)0;
				*(o5 +   4) = (T)0;
				*(o6 +   4) = (T)0;
				*(o7 +   4) = (T)0;
				*(o0 +   5) = (T)0;
				*(o1 +   5) = (T)0;
				*(o2 +   5) = (T)0;
				*(o3 +   5) = (T)0;
				*(o4 +   5) = (T)0;
				*(o5 +   5) = (T)0;
				*(o6 +   5) = (T)0;
				*(o7 +   5) = (T)0;
				*(o0 +   6) = (T)0;
				*(o1 +   6) = (T)0;
				*(o2 +   6) = (T)0;
				*(o3 +   6) = (T)0;
				*(o4 +   6) = (T)0;
				*(o5 +   6) = (T)0;
				*(o6 +   6) = (T)0;
				*(o7 +   6) = (T)0;
				*(o0 +   7) = (T)0;
				*(o1 +   7) = (T)0;
				*(o2 +   7) = (T)0;
				*(o3 +   7) = (T)0;
				*(o4 +   7) = (T)0;
				*(o5 +   7) = (T)0;
				*(o6 +   7) = (T)0;
				*(o7 +   7) = (T)0;
				o0 += 8;
				o1 += 8;
				o2 += 8;
				o3 += 8;
				o4 += 8;
				o5 += 8;
				o6 += 8;
				o7 += 8;
			}
		}
	}
	else {
		switch (s) {
			case 0: {
				for (i = D; i; i--) {
					o0 = O0;
					o1 = O1;
					o2 = O2;
					o3 = O3;
					o4 = O4;
					o5 = O5;
					o6 = O6;
					o7 = O7;
					O0 += P;
					O1 += P;
					O2 += P;
					O3 += P;
					O4 += P;
					O5 += P;
					O6 += P;
					O7 += P;
					t0 = *I0;
					t1 = *I1;
					t2 = *I2;
					t3 = *I3;
					t4 = *I4;
					t5 = *I5;
					t6 = *I6;
					t7 = *I7;
					I0 += Q;
					I1 += Q;
					I2 += Q;
					I3 += Q;
					I4 += Q;
					I5 += Q;
					I6 += Q;
					I7 += Q;
					for (j = d; j; j--) {
						*(o0 +   0) = t0;
						*(o1 +   0) = t1;
						*(o2 +   0) = t2;
						*(o3 +   0) = t3;
						*(o4 +   0) = t4;
						*(o5 +   0) = t5;
						*(o6 +   0) = t6;
						*(o7 +   0) = t7;
						*(o0 +   1) = t0;
						*(o1 +   1) = t1;
						*(o2 +   1) = t2;
						*(o3 +   1) = t3;
						*(o4 +   1) = t4;
						*(o5 +   1) = t5;
						*(o6 +   1) = t6;
						*(o7 +   1) = t7;
						*(o0 +   2) = t0;
						*(o1 +   2) = t1;
						*(o2 +   2) = t2;
						*(o3 +   2) = t3;
						*(o4 +   2) = t4;
						*(o5 +   2) = t5;
						*(o6 +   2) = t6;
						*(o7 +   2) = t7;
						*(o0 +   3) = t0;
						*(o1 +   3) = t1;
						*(o2 +   3) = t2;
						*(o3 +   3) = t3;
						*(o4 +   3) = t4;
						*(o5 +   3) = t5;
						*(o6 +   3) = t6;
						*(o7 +   3) = t7;
						*(o0 +   4) = t0;
						*(o1 +   4) = t1;
						*(o2 +   4) = t2;
						*(o3 +   4) = t3;
						*(o4 +   4) = t4;
						*(o5 +   4) = t5;
						*(o6 +   4) = t6;
						*(o7 +   4) = t7;
						*(o0 +   5) = t0;
						*(o1 +   5) = t1;
						*(o2 +   5) = t2;
						*(o3 +   5) = t3;
						*(o4 +   5) = t4;
						*(o5 +   5) = t5;
						*(o6 +   5) = t6;
						*(o7 +   5) = t7;
						*(o0 +   6) = t0;
						*(o1 +   6) = t1;
						*(o2 +   6) = t2;
						*(o3 +   6) = t3;
						*(o4 +   6) = t4;
						*(o5 +   6) = t5;
						*(o6 +   6) = t6;
						*(o7 +   6) = t7;
						*(o0 +   7) = t0;
						*(o1 +   7) = t1;
						*(o2 +   7) = t2;
						*(o3 +   7) = t3;
						*(o4 +   7) = t4;
						*(o5 +   7) = t5;
						*(o6 +   7) = t6;
						*(o7 +   7) = t7;
						o0 += 8;
						o1 += 8;
						o2 += 8;
						o3 += 8;
						o4 += 8;
						o5 += 8;
						o6 += 8;
						o7 += 8;
					}
				}
				break;
			}
			case 1: {
				for (i = D; i; i--) {
					o0 = O0;
					o1 = O1;
					o2 = O2;
					o3 = O3;
					o4 = O4;
					o5 = O5;
					o6 = O6;
					o7 = O7;
					O0 += P;
					O1 += P;
					O2 += P;
					O3 += P;
					O4 += P;
					O5 += P;
					O6 += P;
					O7 += P;
					i0 = I0;
					i1 = I1;
					i2 = I2;
					i3 = I3;
					i4 = I4;
					i5 = I5;
					i6 = I6;
					i7 = I7;
					I0 += Q;
					I1 += Q;
					I2 += Q;
					I3 += Q;
					I4 += Q;
					I5 += Q;
					I6 += Q;
					I7 += Q;
					for (j = d; j; j--) {
						*(o0 +   0) = *(i0 +   0);
						*(o1 +   0) = *(i1 +   0);
						*(o2 +   0) = *(i2 +   0);
						*(o3 +   0) = *(i3 +   0);
						*(o4 +   0) = *(i4 +   0);
						*(o5 +   0) = *(i5 +   0);
						*(o6 +   0) = *(i6 +   0);
						*(o7 +   0) = *(i7 +   0);
						/*
						*(o0 +   1) = *(i0 +   1);
						*(o1 +   1) = *(i1 +   1);
						*(o2 +   1) = *(i2 +   1);
						*(o3 +   1) = *(i3 +   1);
						*(o4 +   1) = *(i4 +   1);
						*(o5 +   1) = *(i5 +   1);
						*(o6 +   1) = *(i6 +   1);
						*(o7 +   1) = *(i7 +   1);
						*/
						*(o0 +   2) = *(i0 +   2);
						*(o1 +   2) = *(i1 +   2);
						*(o2 +   2) = *(i2 +   2);
						*(o3 +   2) = *(i3 +   2);
						*(o4 +   2) = *(i4 +   2);
						*(o5 +   2) = *(i5 +   2);
						*(o6 +   2) = *(i6 +   2);
						*(o7 +   2) = *(i7 +   2);
						/*
						*(o0 +   3) = *(i0 +   3);
						*(o1 +   3) = *(i1 +   3);
						*(o2 +   3) = *(i2 +   3);
						*(o3 +   3) = *(i3 +   3);
						*(o4 +   3) = *(i4 +   3);
						*(o5 +   3) = *(i5 +   3);
						*(o6 +   3) = *(i6 +   3);
						*(o7 +   3) = *(i7 +   3);
						*/
						*(o0 +   4) = *(i0 +   4);
						*(o1 +   4) = *(i1 +   4);
						*(o2 +   4) = *(i2 +   4);
						*(o3 +   4) = *(i3 +   4);
						*(o4 +   4) = *(i4 +   4);
						*(o5 +   4) = *(i5 +   4);
						*(o6 +   4) = *(i6 +   4);
						*(o7 +   4) = *(i7 +   4);
						/*
						*(o0 +   5) = *(i0 +   5);
						*(o1 +   5) = *(i1 +   5);
						*(o2 +   5) = *(i2 +   5);
						*(o3 +   5) = *(i3 +   5);
						*(o4 +   5) = *(i4 +   5);
						*(o5 +   5) = *(i5 +   5);
						*(o6 +   5) = *(i6 +   5);
						*(o7 +   5) = *(i7 +   5);
						*/
						*(o0 +   6) = *(i0 +   6);
						*(o1 +   6) = *(i1 +   6);
						*(o2 +   6) = *(i2 +   6);
						*(o3 +   6) = *(i3 +   6);
						*(o4 +   6) = *(i4 +   6);
						*(o5 +   6) = *(i5 +   6);
						*(o6 +   6) = *(i6 +   6);
						*(o7 +   6) = *(i7 +   6);
						/*
						*(o0 +   7) = *(i0 +   7);
						*(o1 +   7) = *(i1 +   7);
						*(o2 +   7) = *(i2 +   7);
						*(o3 +   7) = *(i3 +   7);
						*(o4 +   7) = *(i4 +   7);
						*(o5 +   7) = *(i5 +   7);
						*(o6 +   7) = *(i6 +   7);
						*(o7 +   7) = *(i7 +   7);
						*/
						i0 += 8;
						o0 += 8;
						i1 += 8;
						o1 += 8;
						i2 += 8;
						o2 += 8;
						i3 += 8;
						o3 += 8;
						i4 += 8;
						o4 += 8;
						i5 += 8;
						o5 += 8;
						i6 += 8;
						o6 += 8;
						i7 += 8;
						o7 += 8;
					}
				}
				break;
			}
			default: {
				for (i = D; i; i--) {
					o0 = O0;
					o1 = O1;
					o2 = O2;
					o3 = O3;
					o4 = O4;
					o5 = O5;
					o6 = O6;
					o7 = O7;
					O0 += P;
					O1 += P;
					O2 += P;
					O3 += P;
					O4 += P;
					O5 += P;
					O6 += P;
					O7 += P;
					i0 = I0;
					i1 = I1;
					i2 = I2;
					i3 = I3;
					i4 = I4;
					i5 = I5;
					i6 = I6;
					i7 = I7;
					I0 += Q;
					I1 += Q;
					I2 += Q;
					I3 += Q;
					I4 += Q;
					I5 += Q;
					I6 += Q;
					I7 += Q;
					for (j = d; j; j--) {
						*(o0 +   0) = * i0; i0 += s;
						*(o1 +   0) = * i1; i1 += s;
						*(o2 +   0) = * i2; i2 += s;
						*(o3 +   0) = * i3; i3 += s;
						*(o4 +   0) = * i4; i4 += s;
						*(o5 +   0) = * i5; i5 += s;
						*(o6 +   0) = * i6; i6 += s;
						*(o7 +   0) = * i7; i7 += s;
						*(o0 +   1) = * i0; i0 += s;
						*(o1 +   1) = * i1; i1 += s;
						*(o2 +   1) = * i2; i2 += s;
						*(o3 +   1) = * i3; i3 += s;
						*(o4 +   1) = * i4; i4 += s;
						*(o5 +   1) = * i5; i5 += s;
						*(o6 +   1) = * i6; i6 += s;
						*(o7 +   1) = * i7; i7 += s;
						*(o0 +   2) = * i0; i0 += s;
						*(o1 +   2) = * i1; i1 += s;
						*(o2 +   2) = * i2; i2 += s;
						*(o3 +   2) = * i3; i3 += s;
						*(o4 +   2) = * i4; i4 += s;
						*(o5 +   2) = * i5; i5 += s;
						*(o6 +   2) = * i6; i6 += s;
						*(o7 +   2) = * i7; i7 += s;
						*(o0 +   3) = * i0; i0 += s;
						*(o1 +   3) = * i1; i1 += s;
						*(o2 +   3) = * i2; i2 += s;
						*(o3 +   3) = * i3; i3 += s;
						*(o4 +   3) = * i4; i4 += s;
						*(o5 +   3) = * i5; i5 += s;
						*(o6 +   3) = * i6; i6 += s;
						*(o7 +   3) = * i7; i7 += s;
						*(o0 +   4) = * i0; i0 += s;
						*(o1 +   4) = * i1; i1 += s;
						*(o2 +   4) = * i2; i2 += s;
						*(o3 +   4) = * i3; i3 += s;
						*(o4 +   4) = * i4; i4 += s;
						*(o5 +   4) = * i5; i5 += s;
						*(o6 +   4) = * i6; i6 += s;
						*(o7 +   4) = * i7; i7 += s;
						*(o0 +   5) = * i0; i0 += s;
						*(o1 +   5) = * i1; i1 += s;
						*(o2 +   5) = * i2; i2 += s;
						*(o3 +   5) = * i3; i3 += s;
						*(o4 +   5) = * i4; i4 += s;
						*(o5 +   5) = * i5; i5 += s;
						*(o6 +   5) = * i6; i6 += s;
						*(o7 +   5) = * i7; i7 += s;
						*(o0 +   6) = * i0; i0 += s;
						*(o1 +   6) = * i1; i1 += s;
						*(o2 +   6) = * i2; i2 += s;
						*(o3 +   6) = * i3; i3 += s;
						*(o4 +   6) = * i4; i4 += s;
						*(o5 +   6) = * i5; i5 += s;
						*(o6 +   6) = * i6; i6 += s;
						*(o7 +   6) = * i7; i7 += s;
						*(o0 +   7) = * i0; i0 += s;
						*(o1 +   7) = * i1; i1 += s;
						*(o2 +   7) = * i2; i2 += s;
						*(o3 +   7) = * i3; i3 += s;
						*(o4 +   7) = * i4; i4 += s;
						*(o5 +   7) = * i5; i5 += s;
						*(o6 +   7) = * i6; i6 += s;
						*(o7 +   7) = * i7; i7 += s;
						o0 += 8;
						o1 += 8;
						o2 += 8;
						o3 += 8;
						o4 += 8;
						o5 += 8;
						o6 += 8;
						o7 += 8;
					}
				}
				break;
			}
		}
	}

	j = D ? n & 7 : (U)0;
	if (j) {
		i = D << 1;
		d = n - j;
		replicate_8x4x1(O + d, i, j, R, I + d*s, S, s);
	}
	i = m & 7;
	if (i) {
		D = m - i;
		replicate_4x8x1(O + D*R, i, n, R, I + D*S, S, s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>//mxnxr
static inline void replicate_1x1xr (T* O, 
																		U m,
																		U n,
																		U R = (U)(-1),
																		T* I = (T*)0,
																		U S = (U)0,
																		U s = (U)0,
																		U r = (U)1) {
	if (R == (U)(-1)) {R = n;}

	register T t0;
	register T *o0;
	register T *i0;
	register U i;
	register U j;
	register U k;

	T* O0 = O;
	T* I0 = I;
  
	if (I == 0) { 
		for (i = m; i; i--) {
			o0 = O0;
			O0 += R;
			for (j = n*r; j; j--) {
				*(o0 +   0) = 0;
				o0 ++;
			}
		}
	}
	else {
		switch (s) {
			case 0: {
				for (i = m; i; i--) {
					o0 = O0;
					O0 += R;
					t0 = *I0;
					I0 += S;
					for (j = n*r; j; j--) {
						*(o0 +   0) = t0;
						o0 ++;
					}
				}
				break;
			}
			case 1: {
				for (i = m; i; i--) {
					o0 = O0;
					O0 += R;
					i0 = I0;
					I0 += S;
					for (j = n; j; j--) {
						for (k = r; k; k--) {
							*(o0 +   0) = *(i0 +   0);
							o0 ++;
						}
						i0 ++;
					}
				}
				break;
			}
			default: {
				for (i = m; i; i--) {
					o0 = O0;
					O0 += R;
					i0 = I0;
					I0 += S;
					for (j = n; j; j--) {
						for (k = r; k; k--) {
							*(o0 +   0) = * i0;
							o0 ++;
						}
						i0 += s;
					}
				}
				break;
			}
		}
	}
}

//------------------------------------------------------------------------------
template <class T, class U>//mxnxr
static inline void replicate (T* O, 
															U m,
															U n,
															U R = (U)(-1),
															T* I = (T*)0,
															U S = (U)0,
															U s = (U)0,
															U r = (U)1) {
	switch (r) {
		case 1: {
			return replicate_8x8x1(O, m, n, R, I, S, s);
		}
		default: {
			return replicate_1x1xr(O, m, n, R, I, S, s, r);
		}
	}

}
//------------------------------------------------------------------------------
# endif

