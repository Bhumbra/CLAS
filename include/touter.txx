//------------------------------------------------------------------------------
// Single-threaded inner dot product class
//------------------------------------------------------------------------------
# ifndef touter_txx
# define touter_txx
//------------------------------------------------------------------------------
# include "tmmdot.txx"

//------------------------------------------------------------------------------
# ifndef HAVE_ARCHITECTURE 							// calling template C++ code
# define THIS_DOUBLE_PMKQ this -> pmkq
# define DOT_PRODUCT_DOUBLE_MKC_1X8X1 dot_product_mkc_1x8x1
# else                     							// calling wrapper C and assembler
# define THIS_DOUBLE_PMKQ this -> double_pmkq
# define DOT_PRODUCT_DOUBLE_MKC_1X8X1 dot_product_double_mkc_1x8x1
# endif

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
template <class T, class U>
class touter {
	public:
		touter();
		touter (T* _OP, T* _I0 = (T*)0, T* _I1 = (T*)0,
						U _M = (U)0, U _K = (U)0, U _P = (U)1, U _Q = (U)1, 
						bool _I0C = false, bool _I1B = false, T* _I2 = (T*)0, 
						U _D = (U)0, U _R = (U)0, U _A = (U)0);
		~touter<T, U>();
		virtual void init(T* _OP = (T*)0, T* _I0 = (T*)0, T* _I1 = (T*)0,
											U _M = (U)0, U _K = (U)0, U _P = (U)1, U _Q = (U)1,
											bool _I0C = false, bool _I1B = false, T* _I2 = (T*)0, 
											U _D = (U)0, U _R = (U)0, U _A = (U)0);
		void setPtr(T* _OP = (T*)0 , T* _I0 = (T*)0, T* _I1 = (T*)0, T* _I2 = (T*)0);
		void setDim(U _M = (U)0, U _K = (U)0, U _P = (U)1, U _Q = (U)1);
		void setDRA(U _D = (U)0, U _R = (U)0, U _A = (U)0);
		void setTra(bool _I0C = false, bool _I1C = false);
		void setStr(U _OPS = (U)0, U _I0S = (U)0, U _I1S = (U)0, U _I2S = (U)0,
								U _OPs = (U)0, U _I0s = (U)0, U _I1s = (U)0, U _I2s = (U)0);
		void chkStr();
		void exec();
		void double_pmkq();
		void pmkq();
		std::thread Thread;
	protected:
		T* op;
		T* i0;
		T* i1;
		T* i2;
		U opS;
		U i0S;
		U i1S;
		U i2S;
		U ops;
		U i0s;
		U i1s;
		U i2s;
		U m;
		U k;
		U p;
		U q;
		bool i0c;
		bool i1b;
		U D;
		U R;
		U A;
		U kq;
		U sizeofT;
		U sizeofU;
	private:
};

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
template <class T, class U>
touter<T, U>::touter() {
	this -> sizeofT = sizeof(T);
	this -> sizeofU = sizeof(U);
	this -> init();
}

//---------------------------------------------------------------------------
template <class T, class U>
touter<T, U>::touter( T* _OP, T* _I0, T* _I1, U _M, U _K, U _P, U _Q,
											bool _I0C, bool _I1B, T* _I2, U _D, U _R, U _A) {
	this -> init(	_OP, _I0, _I1, _M, _K, _P, _Q, _I0C, _I1B, _I2, _D, _R, _A);
}

//---------------------------------------------------------------------------
template <class T, class U>
touter<T, U>::~touter() {
	this -> init();
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
template <class T, class U>
void touter<T, U>::init(T* _OP, T* _I0, T* _I1, U _M, U _K, U _P, U _Q, 
												bool _I0C, bool _I1B, T* _I2, U _D, U _R, U _A) {
	this -> setPtr(_OP, _I0, _I1, _I2);
	if (!this -> op) {return;}
	this -> setDim(_M, _K, _P, _Q);
	this -> setTra(_I0C, _I1B);
	this -> setDRA(_D, _R, _A);
}

//---------------------------------------------------------------------------
template <class T, class U>
void touter<T, U>::setPtr(T* _OP, T* _I0, T* _I1, T* _I2) {
	this -> op = _OP; // p * m * k * q
	this -> i0 = _I0; // m * k or k * m
	this -> i1 = _I1; // p * m * q or p * 1 * q
	this -> i2 = _I2; // m
	
	// If both m and p is 1, outer performs vector-vector outer products
}

//---------------------------------------------------------------------------
template <class T, class U>
void touter<T, U>::setDim(U _M, U _K, U _P, U _Q) {
	this -> m = _M; 
	this -> k = _K;
	this -> p = _P;
	this -> q = _Q;
	this -> kq = this -> k * this -> q;
}

//---------------------------------------------------------------------------
template <class T, class U>
void touter<T, U>::setTra(bool _I0C, bool _I1B) {
	this -> i0c = _I0C;
	this -> i1b = _I1B;
	this -> setStr();
	this -> chkStr();
}

//---------------------------------------------------------------------------
template <class T, class U>
void touter<T, U>::setDRA(U _D, U _R, U _A) {
	this -> D = _D; // (future diagnostic) Direction matrix unrolling
	this -> R = _R; // (future diagnostic) Radix
	this -> A = _A; // Architecture
}

//---------------------------------------------------------------------------
template <class T, class U>
void touter<T, U>::setStr(U _OPS, U _I0S, U _I1S, U _I2S,
													U _OPs, U _I0s, U _I1s, U _I2s) {
	this -> opS = _OPS;
	this -> i0S = _I0S;
	this -> i1S = _I1S;
	this -> i2S = _I2S;
	this -> ops = _OPs;
	this -> i0s = _I0s;
	this -> i1s = _I1s;
	this -> i2s = _I2s;
}

//---------------------------------------------------------------------------
template <class T, class U>
void touter<T, U>::chkStr() {
	if (! (this -> opS || this -> ops) ) {
		this -> opS = this -> m * this -> k * this -> q;
		this -> ops = this -> k * this -> q;
	}
	if (! (this -> i0S || this -> i0s) ) {
		if (!this -> i0c) {
			this -> i0S = (U)1;
			this -> i0s = this -> k;
		}
		else {
			this -> i0S = this -> m;
			this -> i0s = (U)1;
		}
	}

	if (! (this -> i1S || this -> i1s) ) {
		if (!this -> i1b) {
			this -> i1S = this -> m * this -> q;
			this -> i1s = this -> q;
		}
		else {
			this -> i1S = this -> q;
			this -> i1s = (U)0;
		}
	}

	if (! (this -> i2S || this -> i2s) ) {
		if (this -> i2) {
			this ->  i2S = (U)1;
			this ->  i2s = (U)0;
		}
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
template <class T, class U>
void touter<T, U>::exec() {
	U g;
	if (this -> op != this -> i2) {
		for (g = 0; g < this -> p; g++) {
			replicate(this -> op + g * this -> opS, 
								this -> m, this -> kq, this -> ops,
								this -> i2, this -> i2S, this -> i2s, (U)1);
		}
	}
	if (this -> A == (U)1) {return this -> pmkq();}
	g = this -> sizeofU == (U)8 ? this -> sizeofT : (U)0;
	switch (g) {
		case (U)8: {return THIS_DOUBLE_PMKQ();}
		default: {return this -> pmkq();}
	}
}

//---------------------------------------------------------------------------
template <class T, class U>
void touter<T, U>::pmkq() {
	U g, h;

	T *_Out, *_In0, *_In1;
	T *Out, *In0, *In1;

	for (g = 0; g < this -> p; g++) {
		_Out = this -> op + g * this -> opS;
		_In0 = this -> i0;
		_In1 = this -> i1 + g * this -> i1S;
		for (h = 0; h < this -> m; h++) {
			Out = _Out + h * this -> ops;
			In0 = _In0 + h * this -> i0s;
			In1 = _In1 + h * this -> i1s;
			dot_product_mkn_1x1x8(Out, In0, In1, this -> k, (U)1, this -> q,
														this -> q, this -> i0S, this -> i0s, this -> i1s); 
		}
	}
}

//---------------------------------------------------------------------------
template <class T, class U>
void touter<T, U>::double_pmkq() {
	U g, h;

	T *_Out, *_In0, *_In1;
	T *Out, *In0, *In1;

	for (g = 0; g < this -> p; g++) {
		_Out = this -> op + g * this -> opS;
		_In0 = this -> i0;
		_In1 = this -> i1 + g * this -> i1S;
		for (h = 0; h < this -> m; h++) {
			Out = _Out + h * this -> ops;
			In0 = _In0 + h * this -> i0s;
			In1 = _In1 + h * this -> i1s;
			DOT_PRODUCT_DOUBLE_MKN_1X1X8 (Out, In0, In1, this -> k, (uint64_t)1, this -> q,
																		this -> q, this -> i0S, 
																		this -> i0s, this -> i1s, this -> A);
		}
	}
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

template <class T, class U>
static inline void touter_product(T* _OP, 
																	T* _I0, 
																	T* _I1, 
																	U _m, 
																	U _n,
																	U _p,
																	U _q,
																	bool _i0c,
																	bool _i1b,
																	T* _I2 = (T*)0) {
	touter<T, U> Touter;
	Touter.init(_OP, _I0, _I1, _m, _n, _p, _q, _i0c, _i1b, _I2);
  Touter.exec();
}

//---------------------------------------------------------------------------


# endif

