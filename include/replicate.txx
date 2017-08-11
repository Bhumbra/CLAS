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
					for (j = n; j; j--) {
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
					for (j = n; j; j--) {
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
					for (j = n; j; j--) {
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
					for (j = n; j; j--) {
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
					for (j = n; j; j--) {
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
					for (j = n; j; j--) {
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
			return replicate_1x8x1(O, m, n, R, I, S, s);
		}
		default: {
			return replicate_1x1xr(O, m, n, R, I, S, s, r);
		}
	}

}
//------------------------------------------------------------------------------
# endif

