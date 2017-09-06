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
						U _M = (U)0, U _K = (U)0, U _N = (U)1, T* _I2 = (T*)0,
						U _D = (U)0, U _R = (U)0, U _A = (U)0);
		~tinner<T, U>();
		virtual void init(T* _OP = (T*)0, T* _I0 = (T*)0, T* _I1 = (T*)0,
											U _M = (U)0, U _K = (U)0, U _N = (U)1, T* _I2 = (T*)0,
											bool _OPT = false, bool _I0T = false, bool _I1T = false, 
											bool _ColM = false, T* _I2 = (T*)0, 
											U _D = (U)0, U _R = (U)0, U _A = (U)0);
		void setPtr(T* _OP = (T*)0 , T* _I0 = (T*)0, T* _I1 = (T*)0, T* _I2 = (T*)0);
		void setDim(U _M = (U)0, U _K = (U)0, U _N = (U)1);
		void setDRA(U _D = (U)0, U _R = (U)0, U _A = (U)0);
		void exec();
		std::thread Thread;
	protected:
		T* OP;
		T* I0;
		T* I1;
		T* I2;
		U M;
		U K;
		U N;
		T* op;
		T* i0;
		T* i1;
		T* i2;
		U m;
		U k;
		U n;
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
tinner<T, U>::tinner( T* _OP, T* _I0, T* _I1, U _M, U _K, U _N, T* _I2, 
											U _D, U _R, U _A) {
	this -> init(	_OP, _I0, _I1, _M, _K, _N, _I2, _D, _R, _A);
}

//---------------------------------------------------------------------------
template <class T, class U>
tinner<T, U>::~tinner() {
	this -> init();
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
template <class T, class U>
void tinner<T, U>::init(T* _OP, T* _I0, T* _I1, U _M, U _K, U _N,
												T* _I2, U _D, U _R, U _A) {
	this -> setPtr(_OP, _I0, _I1, _I2);
	if (!this -> OP) {return;}
	this -> setDim(_M, _K, _N);
	this -> setDRA(_D, _R, _A);
}

//---------------------------------------------------------------------------
template <class T, class U>
void tinner<T, U>::setPtr(T* _OP, T* _I0, T* _I1, T* _I2) {
	this -> OP = _OP;
	this -> I0 = _I0;
	this -> I1 = _I1;
	this -> I2 = _I2;
}

//---------------------------------------------------------------------------
template <class T, class U>
void tinner<T, U>::setDim(U _M, U _K, U _N) {
	this -> M = _M;
	this -> K = _K;
	this -> N = _N;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
template <class T, class U>
void tinner<T, U>::setDRA(U _D, U _R, U _A) {
	this -> D = _D; // (future diagnostic) Direction matrix unrolling
	this -> R = _R; // (future diagnostic) Radix
	this -> A = _A; // Architecture
}

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
																	U _n,
																	T* _I2 = (T*)0) {
	tinner<T, U> Tinner;
	Tinner.init(_OP, _I0, _I1, _m, _k, _n, _I2);
  Tinner.exec();
}

//---------------------------------------------------------------------------


# endif

