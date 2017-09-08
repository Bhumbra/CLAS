//------------------------------------------------------------------------------
// Multi-threaded inner dot product class
//------------------------------------------------------------------------------
# ifndef inner_txx
# define inner_txx

//------------------------------------------------------------------------------
# include "tinner.txx"
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
template <class T, class U>
class inner: public tinner<T, U> {
	public:
		inner<T, U>();
		inner(		T* _OP, T* _I0 = (T*)0, T* _I1 = (T*)0,
							U _M = (U)0, U _K = (U)0, U _P = (U)0, U _Q = (U)0,
							T* _I2 = (T*)0, U _MT = (U)0, T _FT = (T)1., 
							U _D = (U)0, U _R = (U)0, U _A = (U)0);
		~inner<T, U>();
		void init(T* _OP = (T*)0 , T* _I0 = (T*)0, T* _I1 = (T*)0,
							U _M = (U)0, U _K = (U)0, U _P = (U)0, U _Q = (U)0,
							T* _I2 = (T*)0, U _MT = (U)0, T _FT = (T)1., 
							U _D = (U)0, U _R = (U)0, U _A = (U)0);
		void exec();
	protected:
		void setThr(U _MT = (U)0, T _FT = (T)1.);
		tinner<T, U>* Tinner;
		U* T_load;
	private:
		U NT;
};

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
template <class T, class U>
inner<T, U>::inner() {
	U Nt = std::thread::hardware_concurrency();
	this -> T_load = new U[Nt];
	this -> Tinner = new tinner<T, U>[Nt];
	this -> init();
}

//---------------------------------------------------------------------------
template <class T, class U>
inner<T, U>::inner( T* _OP, T* _I0, T* _I1, U _M, U _K, U _P, U _Q,
										T* _I2, U _MT, T _FT, U _D, U _R, U _A) {
	this -> init(	_OP, _I0, _I1, _M, _K, _P, _Q,
								_I2, _MT, _FT, _D, _R, _A);
}

//---------------------------------------------------------------------------
template <class T, class U>
inner<T, U>::~inner() {
	this -> init();
	delete[] this -> T_load;
	delete[] this -> Tinner;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
template <class T, class U>
void inner<T, U>::init (T* _OP, T* _I0, T* _I1, U _M, U _K, U _P, U _Q,
												T* _I2, U _MT, T _FT, U _D, U _R, U _A) {
	this -> setPtr(_OP, _I0, _I1, _I2);
	if (!this -> op) {return;}
	this -> setDim(_M, _K, _P, _Q);
	this -> setDRA(_D, _R, _A);
	this -> setThr(_MT, _FT);
}

//---------------------------------------------------------------------------
template <class T, class U>
void inner<T, U>::setThr(U _MT, T _FT) {
	this -> NT = set_max_threads(_MT, _FT);
}

//---------------------------------------------------------------------------
template <class T, class U>
void inner<T, U>::exec() {
	bool unitp, unitm;
	U d, g, G, Nt, M, P, Q;
	U N, outs, in0s, in1s, in2s, _p, _m;

	// If no threads, run execution from thread-blind class thread-blind 
	if (!this -> NT) {
		tinner<T, U>::exec();
		return;
	}
	if (this -> p * this -> m * this -> q * this -> k < 262144) {
		tinner<T, U>::exec();
		return;
	}

	unitp = this -> p == 1;
	unitm = unitp && this -> m == 1;

	P = this -> p;
	M = this -> m;
	Q = this -> q;

	if (!unitp) {
		G = P;
		outs = this -> opS;
		in0s = this -> i0S;
		in1s = this -> i1S;
		in2s = (U)0;
	}
	else if (!unitm) {
		G = M;
		outs = this -> ops;
		in0s = this -> i0s;
		in1s = this -> i1s;
		in2s = this -> i2 ? (U)1 : (U)0;
	}
	else {
		G = Q;
		outs = (U)1;
		in0s = (U)0;
		in1s = this -> k;
		in2s = (U)0;
	}

	g = unitm ? (U)8 : (U)1;
	
	Nt = set_thread_load(this -> T_load, G, this -> NT, g);

	for (d = 0, G = 0; d<Nt; d++, G += g) {
		g = this -> T_load[d];
		if (!unitp) {
			P = g;
		}
		else if (!unitm) {
			M = g;
		}
		else {
			Q = g;
		}
	
		this -> Tinner[d].init   (this -> op + G * outs,
															this -> i0 + G * in0s,
															this -> i1 + G * in1s,
															M, this -> k, P, Q, 
															this -> i2 + G * in2s,
															this -> D, this -> R, this -> A);
	}
	/* // A thread-free version
	for (d = 0, G = 0; d<Nt; d++, G += g) {
		// this -> Tinner[d].nop();
		this -> Tinner[d].exec();
	}
  */
	///* // Threaded version
	for (d = 0; d<Nt; d++) {
		this -> Tinner[d].Thread = std::thread(&tinner<T,U>::exec, &this -> Tinner[d]);
		//this -> Tinner[d].Thread = std::thread(&tinner<T,U>::nop, &this -> Tinner[d]);
	}
	for (d = 0; d<Nt; d++) {
		this -> Tinner[d].Thread.join();
	}
	//*/
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

template <class T, class U>
static inline void inner_product (T* OP, 
																	T* I0, 
																	T* I1, 
																	U m, 
																	U k,
																	U p,
																	U q,
																	T* I2 = (T*)0,
																	U Nt = (U)0,
																	T Ft = 0.,
																	U D = (U)0,
																	U R = (U)0,
																	U A = (U)0) {
	inner<T, U> Inner;
  Inner.init (OP, I0, I1, m, k, p, q, I2, Nt, Ft, D, R, A); 
  Inner.exec();
}

//------------------------------------------------------------------------------
# endif

