//------------------------------------------------------------------------------
// Single-threaded mmdot matrix-matrix dot product class
//------------------------------------------------------------------------------
# ifndef tmmdot_txx
# define tmmdot_txx

// A double-precision read cache scheme (for thread-safety do not cache Out):
// Fast: In0 (8x64)    , In1T (64x8)      - 8192  bytes
// Slow: In0 ([_8x8x64), In1T (64x[8x_8]) - 65536 bytes
// Shared: In1

//------------------------------------------------------------------------------
// Minimum double length:	pre-outer-aligned  8192 
//												post-outer-aligned 8256 (for 2 outer-aligned caches)
# define CACHE_DOUBLE_LENGTH 		8256
# define CACHE_OUTER_ALIGNMENT 	256
# define CACHE_INNER_ALIGNMENT 	64

//------------------------------------------------------------------------------
# ifndef HAVE_ARCHITECTURE // calling template C++ code
# define THIS_DOUBLE_MKN this -> mkn
# define THIS_DOUBLE_MKN_4x4x4 this -> mkn_4x4x4
# define DOT_PRODUCT_DOUBLE_MKN_4x4x4 dot_product_mkn_4x4x4
# else                     // calling assembler
# define THIS_DOUBLE_MKN this -> double_mkn
# define THIS_DOUBLE_MKN_4x4x4 this -> this -> double_mkn_4x4x4
# define DOT_PRODUCT_DOUBLE_MKN_4x4x4_DOUBLE dot_product_double_mkn
# endif

//------------------------------------------------------------------------------
# include "mcache.txx"
# include "_dot_product_mnk.txx"
# include "_dot_product_mkn.txx"

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
template <class T, class U>
class tmmdot {
	public:
		double cache[CACHE_DOUBLE_LENGTH];
		tmmdot();
		tmmdot(	T* _OP, T* _I0 = (T*)0, T* _I1 = (T*)0,
						U _m = (U)0, U _k = (U)0, U _n = (U)0,
						bool _OPT = false, bool _I0T = false, bool _I1T = false, 
						bool _ColM = false, T* _I2 = (T*)0, U _Arch = (U)0);
		~tmmdot<T, U>();
		void init(T* _OP = (T*)0 , T* _I0 = (T*)0, T* _I1 = (T*)0,
							U _m = (U)0, U _k = (U)0, U _n = (U)0,
							bool _OPT = false, bool _I0T = false, bool _I1T = false, 
							bool _ColM = false, T* _I2 = (T*)0, U _Arch = (U)0);
		void setAln(U al0 = (U)CACHE_OUTER_ALIGNMENT, U al1 = (U)CACHE_INNER_ALIGNMENT);
		void setPtr(T* _OP = (T*)0 , T* _I0 = (T*)0, T* _I1 = (T*)0, T* _I2 = (T*)0);
		void setDim(U _m = (U)0, U _k = (U)0, U _n = (U)0);
		void setCmj(bool _OPT = false, bool _I0T = false, bool _I1T = false, bool _ColM = false);
		void setStr(U _OPS = (U)0, U _I0S = (U)0, U _I1S = (U)0,
								U _OPs = (U)0, U _I0s = (U)0, U _I1s = (U)0);
		void setArch(U _Arch = (U)0);
		void exec();
		void mkn();
		void mkn_kmn_64x64x64(T* _OP, T* _I0, T* _I1, U M, U K, U N); // an experiment
		void mkn_64x64x64(T* _OP, T* _I0, T* _I1, U M, U K, U N);
		void mkn_64x8x64(T* _OP, T* _I0, T* _I1, U M, U K, U N);
		void mkn_8x64x8(T* _OP, T* _I0, T* _I1, U M, U K, U N);
		void mkn_8x8x8(T* _OP, T* _I0, T* _I1, U M, U K, U N);
		void mkn_4x4x4(T* _OP, T* _I0, T* _I1, U M, U K, U N);
		void mkn_1x1x8(T* _OP, T* _I0, T* _I1, U M, U K, U N);
		void double_mkn();
		void double_mkn_64x64x64(T* _OP, T* _I0, T* _I1, U M, U K, U N);
		void double_mkn_64x8x64(T* _OP, T* _I0, T* _I1, U M, U K, U N);
		void double_mkn_8x64x8(T* _OP, T* _I0, T* _I1, U M, U K, U N);
		void double_mkn_8x8x8(T* _OP, T* _I0, T* _I1, U M, U K, U N);
		void double_mkn_4x4x4(T* _OP, T* _I0, T* _I1, U M, U K, U N);
		void double_mkn_1x1x8(T* _OP, T* _I0, T* _I1, U M, U K, U N);
	protected:
		T* OP;
		T* I0;
		T* I1;
		T* I2;
		U m;
		U k;
		U n;
		bool OPC;
		bool I0C;
		bool I1C;
		U OPS;
		U I0S;
		U I1S;
		U OPs;
		U I0s;
		U I1s;
		U Arch;
		mcache<T, U> cacher;
	private:
};

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
template <class T, class U>
tmmdot<T, U>::tmmdot() {
	this -> cacher.init((T*)this -> cache, (U)2);
	this -> setAln();
	this -> init();
}

//---------------------------------------------------------------------------
template <class T, class U>
tmmdot<T, U>::tmmdot( T* _OP, T* _I0, T* _I1, U _m, U _k, U _n,
											bool _OPT, bool _I0T, bool _I1T, 
											bool _ColM, T* _I2, U _Arch) {
	this -> init(	_OP, _I0, _I1, _m, _k, _n, _OPT, _I0T, _I1T, _ColM, _I2, _Arch);
}

//---------------------------------------------------------------------------
template <class T, class U>
tmmdot<T, U>::~tmmdot() {
	this -> init();
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::init(T* _OP, T* _I0, T* _I1, U _m, U _k, U _n,
												bool _OPT, bool _I0T, bool _I1T, 
												bool _ColM, T* _I2, U _Arch) {
	this -> setPtr(_OP, _I0, _I1, _I2);
	this -> setDim(_m, _k, _n);
	this -> setCmj(_OPT, _I0T, _I1T, _ColM);
	this -> setArch(_Arch);
}

//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::setAln(U _al0, U _al1) {
	this -> cacher.setAlign(_al0, _al1);
}

//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::setPtr(T* _OP, T* _I0, T* _I1, T* _I2) {
	this -> OP = _OP;
	this -> I0 = _I0;
	this -> I1 = _I1;
	this -> I2 = _I2;
}

//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::setDim(U _m, U _k, U _n) {
	this -> m   = _m;
	this -> k   = _k;
	this -> n   = _n;
}

//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::setCmj(bool _OPT, bool _I0T, bool _I1T, bool _ColM) {
	if (!_ColM) {
		this -> OPC = _OPT;
		this -> I0C = _I0T;
		this -> I1C = _I1T;
	}
	else {
		this -> OPC = !_OPT;
		this -> I0C = !_I0T;
		this -> I1C = !_I1T;
	}
	this -> setStr();
}

//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::setStr(U _OPS, U _I0S, U _I1S,
													U _OPs, U _I0s, U _I1s) {
	this -> OPS = _OPS;
	this -> I0S = _I0S;
	this -> I1S = _I1S;
	this -> OPs = _OPs;
	this -> I0s = _I0s;
	this -> I1s = _I1s;

	if (! (this -> OPS || this -> OPs) ) {
		if (!this -> OPC) {
			this -> OPS = this -> n;
			this -> OPs = (U)1;
		}
		else {
			this -> OPS = (U)1;
			this -> OPs = this -> n;
		}
	}
	if (! (this -> I0S || this -> I0s) ) {
		if (!this -> I0C) {
			this -> I0S = this -> k;
			this -> I0s = (U)1;
		}
		else {
			this -> I0S = (U)1;
			this -> I0s = this -> k;
		}
	}
	if (! (this -> I1S || this -> I1s) ) {
		if (!this -> I1C) {
			this -> I1S = this -> n;
			this -> I1s = (U)1;
		}
		else {
			this -> I1S = (U)1;
			this -> I1s = this -> n;
		}
	}
}

//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::setArch(U _Arch) {
	this -> Arch = _Arch;
}

//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::exec() {
	if (this -> OP != this -> I2) {
		if (!this -> OPC) { 
			replicate(this -> OP, this -> m, this -> n, this -> n,
								this -> I2, (U)1, (U)0, (U)1);
		}
		else {
			replicate(this -> OP, this -> n, this -> m, this -> m,
								this -> I2, (U)0, (U)1, (U)1);
		}
	}
	if (this->Arch == (U)1) {return this -> mkn();}
	switch (sizeof(T)) {
		case (U)8: {return THIS_DOUBLE_MKN();}
		default: {return this -> mkn();}
	}
}
//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::mkn() {
	U r = this -> m <= this -> n ? this -> m : this -> n;
	if (this -> m < (U)1) {
		this -> mkn_1x1x8    (this -> OP, this -> I0, this -> I1, 
													this -> m,  this -> k,  this -> n);
	}
	if (this -> k < (U)8 || r < (U)8) {
		this -> mkn_4x4x4    (this -> OP, this -> I0, this -> I1, 
													this -> m,  this -> k,  this -> n);
	}
	else if (this -> k < (U)64 || r < (U)64) {
		this -> mkn_8x8x8    (this -> OP, this -> I0, this -> I1, 
													this -> m,  this -> k,  this -> n);
	}
	else if (r < (U)64) {
		this -> mkn_8x64x8   (this -> OP, this -> I0, this -> I1, 
													this -> m,  this -> k,  this -> n);
	}
	else if (this -> k < (U)64) {
		this -> mkn_64x8x64  (this -> OP, this -> I0, this -> I1, 
													this -> m,  this -> k,  this -> n);
	}
	else {
		this -> mkn_64x64x64 (this -> OP, this -> I0, this -> I1, 
													this -> m,  this -> k,  this -> n);
	}
}

//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::double_mkn() {
		THIS_DOUBLE_MKN_4x4x4 (this -> OP, this -> I0, this -> I1, 
													this -> m,  this -> k,  this -> n);

	/*
	U r = this -> m <= this -> n ? this -> m : this -> n;
	if (this -> m < (U)1) {
		this -> mkn_1x1x8    (this -> OP, this -> I0, this -> I1, 
													this -> m,  this -> k,  this -> n);
	}
	if (this -> k < (U)8 || r < (U)8) {
		this -> mkn_4x4x4    (this -> OP, this -> I0, this -> I1, 
													this -> m,  this -> k,  this -> n);
	}
	else if (this -> k < (U)64 || r < (U)64) {
		this -> mkn_8x8x8    (this -> OP, this -> I0, this -> I1, 
													this -> m,  this -> k,  this -> n);
	}
	else if (r < (U)64) {
		this -> mkn_8x64x8   (this -> OP, this -> I0, this -> I1, 
													this -> m,  this -> k,  this -> n);
	}
	else if (this -> k < (U)64) {
		this -> mkn_64x8x64  (this -> OP, this -> I0, this -> I1, 
													this -> m,  this -> k,  this -> n);
	}
	else {
		this -> mkn_64x64x64 (this -> OP, this -> I0, this -> I1, 
													this -> m,  this -> k,  this -> n);
	}
	*/
}

//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::mkn_64x64x64(T* _OP, T* _I0, T* _I1, U _M, U _K, U _N) {
	U e, f, g, F;
	T *_Out, *_In0, *_In1, *Out, *In0, *In1;
	U Ms, Ks, Ns, M, K, N;

	Ms = (U)64;
	Ks = (U)64;
	Ns = (U)64;

	if (_M < Ms || _N < Ns) {
		return mkn_8x64x8(_OP, _I0, _I1, _M, _K, _N);
	}
	else if (_K < Ks) {
		return mkn_64x8x64(_OP, _I0, _I1, _M, _K, _N);
	}

	M = _M & (U)-Ms;
	K = _K & (U)-Ks;
	N = _N & (U)-Ns;

	In0 = this -> cacher.setUnit((U)0, Ms, Ks);
	In1 = this -> cacher.setUnit((U)1, Ks, Ns);
	
	this -> cacher.retUnit((U)0).prefetch((U)1, (U)2);
	this -> cacher.retUnit((U)1).prefetch((U)1, (U)2);

	for (e = 0; e < M; e += Ms) {
		_Out = _OP + e * this -> OPS;
		_In0 = _I0 + e * this -> I0S;
		for (f = 0; f < K; f += Ks) {
			cacher.retUnit((U)0).copyFr(_In0 + f * this -> I0s, this -> I0S, this -> I0s);
			_In1 = _I1 + f * this -> I1S;
			for (g = 0; g < N; g += Ns) {
				Out = _Out + g * this -> OPs;
				cacher.retUnit((U)1).copyFr(_In1 + g * this -> I1s, this -> I1S, this -> I1s);
				dot_product_mnk_1x8x8(Out, In0, In1, Ms, Ks, Ns, this -> OPS);
			}
		}
	}

	if (K < _K) {
		_Out = _OP; 
		_In0 = _I0 + K * this -> I0s;
		_In1 = _I1 + K * this -> I1S;
		this -> mkn_64x8x64(_Out, _In0, _In1, M, _K - K, N);
	}

	if (N < _N) {
		_Out = _OP + N * this -> OPs;
		_In0 = _I0;
		_In1 = _I1 + N * this -> I1s;
		this -> mkn_8x64x8(_Out, _In0, _In1, M, _K, _N - N);
	}

	if (M < _M) {
		_Out = _OP + M * this -> OPS;
		_In0 = _I0 + M * this -> I0S;
		_In1 = _I1;
		this -> mkn_8x64x8(_Out, _In0, _In1, _M - M, _K, _N);
	}
}

//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::mkn_64x8x64(T* _OP, T* _I0, T* _I1, U _M, U _K, U _N) {
	U e, f, g, F;
	T *_Out, *_In0, *_In1, *Out, *In0, *In1;
	U Ms, Ks, Ns, M, K, N;

	Ms = (U)64;
	Ks = (U)8;
	Ns = (U)64;

	if (_M < Ms || _N < Ns) {
		return mkn_8x8x8(_OP, _I0, _I1, _M, _K, _N);
	}
	else if (_K < Ks) {
		return mkn_4x4x4(_OP, _I0, _I1, _M, _K, _N);
	}

	M = _M & (U)-Ms;
	K = _K & (U)-Ks;
	N = _N & (U)-Ns;

	In0 = this -> cacher.setUnit((U)0, Ms, Ks);
	In1 = this -> cacher.setUnit((U)1, Ks, Ns);
	
	this -> cacher.retUnit((U)0).prefetch((U)1, (U)3);
	this -> cacher.retUnit((U)1).prefetch((U)1, (U)3);

	for (e = 0; e < M; e += Ms) {
		_Out = _OP + e * this -> OPS;
		_In0 = _I0 + e * this -> I0S;
		for (f = 0; f < K; f += Ks) {
			cacher.retUnit((U)0).copyFr(_In0 + f * this -> I0s, this -> I0S, this -> I0s);
			_In1 = _I1 + f * this -> I1S;
			for (g = 0; g < N; g += Ns) {
				Out = _Out + g * this -> OPs;
				cacher.retUnit((U)1).copyFr(_In1 + g * this -> I1s, this -> I1S, this -> I1s);
				dot_product_mnk_1x8x8(Out, In0, In1, Ms, Ks, Ns, this -> OPS);
			}
		}
	}

	if (K < _K) {
		_Out = _OP; 
		_In0 = _I0 + K * this -> I0s;
		_In1 = _I1 + K * this -> I1S;
		this -> mkn_4x4x4(_Out, _In0, _In1, M, _K - K, N);
	}

	if (N < _N) {
		_Out = _OP + N * this -> OPs;
		_In0 = _I0;
		_In1 = _I1 + N * this -> I1s;
		this -> mkn_8x8x8(_Out, _In0, _In1, M, _K, _N - N);
	}

	if (M < _M) {
		_Out = _OP + M * this -> OPS;
		_In0 = _I0 + M * this -> I0S;
		_In1 = _I1;
		this -> mkn_8x8x8(_Out, _In0, _In1, _M - M, _K, _N);
	}
}

//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::mkn_8x64x8(T* _OP, T* _I0, T* _I1, U _M, U _K, U _N) {
	U e, f, g, F;
	T *_Out, *_In0, *_In1, *Out, *In0, *In1;
	U Ms, Ks, Ns, M, K, N;

	Ms = (U)8;
	Ks = (U)64;
	Ns = (U)8;

	if (_M < Ms || _N < Ns) {
		return mkn_4x4x4(_OP, _I0, _I1, _M, _K, _N);
	}
	else if (_K < Ks) {
		return mkn_8x8x8(_OP, _I0, _I1, _M, _K, _N);
	}

	M = _M & (U)-Ms;
	K = _K & (U)-Ks;
	N = _N & (U)-Ns;

	In0 = this -> cacher.setUnit((U)0, Ms, Ks);
	In1 = this -> cacher.setUnit((U)1, Ks, Ns);
	
	this -> cacher.retUnit((U)0).prefetch((U)1, (U)3);
	this -> cacher.retUnit((U)1).prefetch((U)1, (U)3);

	for (e = 0; e < M; e += Ms) {
		_Out = _OP + e * this -> OPS;
		_In0 = _I0 + e * this -> I0S;
		for (f = 0; f < K; f += Ks) {
			cacher.retUnit((U)0).copyFr(_In0 + f * this -> I0s, this -> I0S, this -> I0s);
			_In1 = _I1 + f * this -> I1S;
			for (g = 0; g < N; g += Ns) {
				Out = _Out + g * this -> OPs;
				cacher.retUnit((U)1).copyFr(_In1 + g * this -> I1s, this -> I1S, this -> I1s);
				dot_product_mnk_1x8x8(Out, In0, In1, Ms, Ks, Ns, this -> OPS);
			}
		}
	}

	if (K < _K) {
		_Out = _OP; 
		_In0 = _I0 + K * this -> I0s;
		_In1 = _I1 + K * this -> I1S;
		this -> mkn_8x8x8(_Out, _In0, _In1, M, _K - K, N);
	}

	if (N < _N) {
		_Out = _OP + N * this -> OPs;
		_In0 = _I0;
		_In1 = _I1 + N * this -> I1s;
		this -> mkn_4x4x4(_Out, _In0, _In1, M, _K, _N - N);
	}

	if (M < _M) {
		_Out = _OP + M * this -> OPS;
		_In0 = _I0 + M * this -> I0S;
		_In1 = _I1;
		this -> mkn_4x4x4(_Out, _In0, _In1, _M - M, _K, _N);
	}
}

//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::mkn_8x8x8(T* _OP, T* _I0, T* _I1, U _M, U _K, U _N) {
	U e, f, g, F;
	T *_Out, *_In0, *_In1, *Out, *In0, *In1;
	U Ms, Ks, Ns, M, K, N;

	Ms = (U)8;
	Ks = (U)8;
	Ns = (U)8;

	if (_M < Ms || _N < Ns) {
		return mkn_4x4x4(_OP, _I0, _I1, _M, _K, _N);
	}
	else if (_K < Ks) {
		return mkn_4x4x4(_OP, _I0, _I1, _M, _K, _N);
	}

	M = _M & (U)-Ms;
	K = _K & (U)-Ks;
	N = _N & (U)-Ns;

	In0 = this -> cacher.setUnit((U)0, Ms, Ks);
	In1 = this -> cacher.setUnit((U)1, Ks, Ns);
	
	this -> cacher.retUnit((U)0).prefetch((U)1, (U)3);
	this -> cacher.retUnit((U)1).prefetch((U)1, (U)3);

	for (e = 0; e < M; e += Ms) {
		_Out = _OP + e * this -> OPS;
		_In0 = _I0 + e * this -> I0S;
		for (f = 0; f < K; f += Ks) {
			cacher.retUnit((U)0).copyFr(_In0 + f * this -> I0s, this -> I0S, this -> I0s);
			_In1 = _I1 + f * this -> I1S;
			for (g = 0; g < N; g += Ns) {
				Out = _Out + g * this -> OPs;
				cacher.retUnit((U)1).copyFr(_In1 + g * this -> I1s, this -> I1S, this -> I1s);
				dot_product_mnk_1x8x8(Out, In0, In1, Ms, Ks, Ns, this -> OPS);
			}
		}
	}

	if (K < _K) {
		_Out = _OP; 
		_In0 = _I0 + K * this -> I0s;
		_In1 = _I1 + K * this -> I1S;
		this -> mkn_4x4x4(_Out, _In0, _In1, M, _K - K, N);
	}


	if (N < _N) {
		_Out = _OP + N * this -> OPs;
		_In0 = _I0;
		_In1 = _I1 + N * this -> I1s;
		this -> mkn_4x4x4(_Out, _In0, _In1, M, _K, _N - N);
	}

	if (M < _M) {
		_Out = _OP + M * this -> OPS;
		_In0 = _I0 + M * this -> I0S;
		_In1 = _I1;
		this -> mkn_4x4x4(_Out, _In0, _In1, _M - M, _K, _N);
	}
}

//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::mkn_4x4x4(T* _OP, T* _I0, T* _I1, U _M, U _K, U _N) {
	dot_product_mkn_4x4x4(_OP, _I0, _I1, _M, _K, _N, 
	this -> OPS, this -> I0S, this -> I0s, this -> I1S);
}

//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::double_mkn_4x4x4(T* _OP, T* _I0, T* _I1, U _M, U _K, U _N) {
	DOT_PRODUCT_DOUBLE_MKN_4x4x4(_OP, _I0, _I1, _M, _K, _N, 
	this -> OPS, this -> I0S, this -> I0s, this -> I1S);
}
//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::mkn_1x1x8(T* _OP, T* _I0, T* _I1, U _M, U _K, U _N) {
	dot_product_mkn_1x1x8(_OP, _I0, _I1, _M, _K, _N, 
	this -> OPS, this -> I0S, this -> I0s, this -> I1S);
}
//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::mkn_kmn_64x64x64(T* _OP, T* _I0, T* _I1, U _M, U _K, U _N) {

	U e, f, g, F;
	T *_Out, *_In0, *_In1, *Out, *In0, *In1;

	U M = _M & (U)-64;
	U K = _K;
	U N = _N & (U)-64;

	U Ms = (U)64;
	U Ks = (U)64;
	U Ns = (U)64;

	In0 = this -> cacher.setUnit((U)0, Ms, Ks);
	In1 = this -> cacher.setUnit((U)1, Ks, Ns);
	
	this -> cacher.retUnit((U)0).prefetch((U)1, (U)2);
	this -> cacher.retUnit((U)1).prefetch((U)1, (U)2);

	e = K >= (U)Ks ? 0 : M;

	for (; e < M; e += Ms) {
		_Out = _OP + e*_N;
		_In0 = _I0 + e*_K;
		for (f = 0; f < K; f += Ks) {
			cacher.retUnit((U)0).copyFr(_In0+f, (U)1, _K);
			_In1 = _I1 + f*_N;
			for (g = 0; g < N; g += Ns) {
				Out = _Out + g;
				cacher.retUnit((U)1).copyFr(_In1+g, _N, (U)1);
				dot_product_kmn_1x8x8(Out, In0, In1, Ms, Ks, Ns, _N);
			}
		}
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

template <class T, class U>
static inline void dot_product_mkn (T* _OP, 
																		T* _I0, 
																		T* _I1, 
																		volatile const U _m, 
																		volatile const U _k,
																		volatile const U _n) {
	tmmdot<T, U> mkn;
	mkn.init(_OP, _I0, _I1, _m, _k, _n);
  mkn.exec();
}

//---------------------------------------------------------------------------

# endif

