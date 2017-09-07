//------------------------------------------------------------------------------
// Single-threaded inner dot product class
//------------------------------------------------------------------------------
# ifndef tinner_txx
# define tinner_txx

//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
# include "mcache.txx"
# include "clas_threads.txx"

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
template <class T, class U>
class tinner {
	public:
		double cache[CACHE_DOUBLE_LENGTH];
		tinner();
		tinner (T* _OP, T* _I0 = (T*)0, T* _I1 = (T*)0,
						U _M = (U)0, U _K = (U)0, U _P = (U)1, U _Q = (U)1, 
						T* _I2 = (T*)0, U _D = (U)0, U _R = (U)0, U _A = (U)0);
		~tinner<T, U>();
		virtual void init(T* _OP = (T*)0, T* _I0 = (T*)0, T* _I1 = (T*)0,
											U _M = (U)0, U _K = (U)0, U _P = (U)1, U _Q = (U)1,
											T* _I2 = (T*)0, U _D = (U)0, U _R = (U)0, U _A = (U)0);
		void setPtr(T* _OP = (T*)0 , T* _I0 = (T*)0, T* _I1 = (T*)0, T* _I2 = (T*)0);
		void setDim(U _M = (U)0, U _K = (U)0, U _P = (U)1, U _Q = (U)1);
		void setDRA(U _D = (U)0, U _R = (U)0, U _A = (U)0);
		void setStr(U _OPS = (U)0, U _I0S = (U)0, U _I1S = (U)0, U _I2S = (U)0,
								U _OPs = (U)0, U _I0s = (U)0, U _I1s = (U)0, U _I2s = (U)0);
		void chkStr();
		void exec();
		std::thread Thread;
	protected:
		T* op;
		T* i0;
		T* i1;
		T* i2;
		U m;
		U k;
		U p;
		U q;
		U D;
		U R;
		U A;
		U sizeofT;
	private:
};

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
template <class T, class U>
tinner<T, U>::tinner() {
	this -> sizeofT = sizeof(T);
	this -> init();
}

//---------------------------------------------------------------------------
template <class T, class U>
tinner<T, U>::tinner( T* _OP, T* _I0, T* _I1, U _M, U _K, U _P, U _Q,, T* _I2, 
											U _D, U _R, U _A) {
	this -> init(	_OP, _I0, _I1, _M, _K, _P, _Q, _I2, _D, _R, _A);
}

//---------------------------------------------------------------------------
template <class T, class U>
tinner<T, U>::~tinner() {
	this -> init();
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
template <class T, class U>
void tinner<T, U>::init(T* _OP, T* _I0, T* _I1, U _M, U _K, U _P, U _Q, T* _I2, 
												U _D, U _R, U _A) {
	this -> setPtr(_OP, _I0, _I1, _I2);
	if (!this -> OP) {return;}
	this -> setDim(_M, _K, _P, _Q);
	this -> setDRA(_D, _R, _A);
}

//---------------------------------------------------------------------------
template <class T, class U>
void tinner<T, U>::setPtr(T* _OP, T* _I0, T* _I1, T* _I2) {
	this -> op = _OP; // p * m * q
	this -> i0 = _I0; // m * k
	this -> i1 = _I1; // p * m * q * k
	this -> i2 = _I2; // m
	
	// If both p and q is 1, inner performs vector-vector dot products
}

//---------------------------------------------------------------------------
template <class T, class U>
void tinner<T, U>::setDim(U _M, U _K, U _P, U _Q) {
	this -> m = _M; 
	this -> k = _K;
	this -> p = _P;
	this -> q = _Q;
	this -> setStr();
	this -> chkStr();
}


//---------------------------------------------------------------------------
template <class T, class U>
void tinner<T, U>::setDRA(U _D, U _R, U _A) {
	this -> D = _D; // (future diagnostic) Direction matrix unrolling
	this -> R = _R; // (future diagnostic) Radix
	this -> A = _A; // Architecture
}

//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::setStr(U _OPS, U _I0S, U _I1S, U _I2S,
													U _OPs, U _I0s, U _I1s, U _I2s) {
	this -> i0S = _I0S;
	this -> i1S = _I1S;
	this -> i2S = _I2S;
	this -> i0s = _I0s;
	this -> i1s = _I1s;
	this -> i2s = _I2s;
}

//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::chkStr() {
	
	if (! (this -> opS || this -> ops) ) {
		this -> ops = this -> q;
		this -> opS = this -> m * this -> q;
	}
	if (! (this -> i0S || this -> i0s) ) {
		this -> i0s = this -> k;
		this -> i0S = (U)0;
	}

	if (! (this -> i1S || this -> i1s) ) {
		this -> i1s = this -> k;
		this -> i1S = this -> m * this -> q * this -> k;
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
void tinner<T, U>::exec() {
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

template <class T, class U>
static inline void tinner_product(T* _OP, 
																	T* _I0, 
																	T* _I1, 
																	U _m, 
																	U _k,
																	U _p,
																	U _q,
																	T* _I2 = (T*)0) {
	tinner<T, U> Tinner;
	Tinner.init(_OP, _I0, _I1, _m, _k, _n, _I2);
  Tinner.exec();
}

//---------------------------------------------------------------------------


# endif

