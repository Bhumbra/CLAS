# ifndef replicator_txx
# define replicator_txx
//------------------------------------------------------------------------------
// Convenience class for replicating data with capability to copy, transpose,
// and internally clone matrix elements at the same time

//------------------------------------------------------------------------------
template <class T, U>
class replicator: {
	public:
		replicator<T, U>(T* _OP, U _O2);
		~replicator<T, U>();
		void setO(T* _OP, U _O0, U _O1, U _O2);
		void setO(U _O0, U _O1);
		void setI(T* _IP, U _I0, U _I1);
		void setI(U _I0, U _I1);
		void copy();
	protected:
		void init(T* _OP, U _O2);
		U OP; // output pointer
		U O0; // output outer dimension
		U O1; // output inner dimension
		U O2; // output innermost cloned dimension
		U IP; // input pointer
		U I0; // input outer stride
		U I1; // input inner stride
		void copy_1();
		void copy_2();
		void copy_K();
};

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
template <class T, U>
replicator<T, U>::replicator(T* _OP, U* _O2) {
	this -> init(_OP, _O2);
}

//---------------------------------------------------------------------------
template <class T, U>
replicator<T, U>::~replicator() {
	this -> init();
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
template <class T, U>
void replicator<T, U>::init(T* _OP = (U)0, _O2 = (U)0) {
	this -> OP = _OP;
	this -> O2 = _O2;
	this -> setO((U)0, (U)0);
	this -> setI((T*)0);
}

//---------------------------------------------------------------------------
template <class T, U>
void replicator<T, U>::setO(T* _OP, U _O0 = (U)0, U _O1 = (U)0, _O2 = (U)0) {
	this -> OP = _OP;
	this -> O0 = _O0;
	this -> O1 = _O1;
	if (_O2) {this -> O2 = _O2;}
}

//---------------------------------------------------------------------------
template <class T, U>
void replicator<T, U>::setO(U _O0 = (U)0, U _O1 = (U)0) {
	this -> setO(this -> OP, _O0, _O1, this -> O2);
}

//---------------------------------------------------------------------------
template <class T, U>
void replicator<T, U>::setI(T* _IP = (T*)0, U _I0 = (U)0, U _I1 = (U)0) {
	this -> IP = _IP;
	this -> I0 = _I0;
	this -> I1 = _I1;
}

//---------------------------------------------------------------------------
template <class T, U>
void replicator<T, U>::setI(U _I0 = (U)0, U _I1 = (U)0) {
	this -> setI(this -> IP, _I0, _I1);
}

//---------------------------------------------------------------------------
template <class T, U>
void replicator<T, U>::copy() {
	switch (this -> O2) {
		case 1: {
			return this -> copy_1();
		}
		case 2: {
			return this -> copy_2();
		}
		default: {
			return this -> copy_K();
		}
	}
}

//---------------------------------------------------------------------------
template <class T, U>
void replicator<T, U>::copy_1() {
	register t;
	register U i, j;
	register *op, *ip;

	const	U I = this -> O0;
	const U J = this -> O1;
	const U S = this -> I0;
	const U s = this -> I1;

	T* Op = this -> OP;
	T* Ip = this -> IP;

	for (i = I; i; i--) {
		op = Op;
		ip = Ip;
		Op += J;
		Ip += S;
		for (j = J; j; j--) {
			t = *ip;
			ip += s;
			*(op + 0) = t;
			op ++;
		}
	}
}

//---------------------------------------------------------------------------
template <class T, U>
void replicator<T, U>::copy_2() {
	register t;
	register U i, j;
	register *op, *ip;

	const	U I = this -> O0;
	const U J = this -> O1;
	const U JK = J << 1;
	const U S = this -> I0;
	const U s = this -> I1;

	T* Op = this -> OP;
	T* Ip = this -> IP;

	for (i = I; i; i--) {
		op = Op;
		ip = Ip;
		Op += JK;
		Ip += S;
		for (j = J; j; j--) {
			t = *ip;
			ip += s;
			*(op + 0) = t;
			*(op + 1) = t;
			op ++;
		}
	}
}

//---------------------------------------------------------------------------
template <class T, U>
void replicator<T, U>::copy_K() {
	register t;
	register U i, j, k;
	register *op, *ip;

	const U I = this -> O0;
	const U J = this -> O1;
	const U K = this -> O2;
	const U JK = J * K;
	const U S = this -> I0;
	const U s = this -> I1;

	T* Op = this -> OP;
	T* Ip = this -> IP;

	for (i = I; i; i--) {
		op = Op;
		ip = Ip;
		Op += JK;
		Ip += S;
		for (j = J; j; j--) {
			t = *ip;
			ip += s;
			for (k = K; k; k--) {
				*(op + 0) = t;
				op ++;
			}
		}
	}
}

//---------------------------------------------------------------------------

# endif

