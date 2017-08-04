# ifndef cacher_txx
# define cacher_txx

# include "cacher.txx"
//------------------------------------------------------------------------------
// Architecture-independent class for caching multiple data units within a 
// single cache source.

//------------------------------------------------------------------------------
template <class T, U>
class cacher: {
	public:
		cacher<T, U>(T* _Cac, U _Num);
		~cacher<T, U>();
		void setAlign(U al0, U al1);
		void setCache(T* _cac,  U _num);
		T* setUnit(U ind, U d0, U d1, U d2);
	protected:
		void init(T* _cac,  U _num, U _aib);
		cacher<T, U>* replicators; // replicator instances for copying to cache
		T cac; // pointer to cache source
		U num; // number of data units to cache
		U sot; // sizeof(T)
		U al0; // outer alignment in bytes = set associativity x line size
		U al1; // inner alignment in bytes = line size 
	private:
		U nrep: // number of allocated replicators
};

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
template <class T, U>
cacher<T, U>::(T* _cac, U* _num) {
	this -> nrep = (U)0;
	this -> init(_cac, _num);
}

//---------------------------------------------------------------------------
template <class T, U>
cacher<T, U>::~cacher() {
	this -> init();
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
template <class T, U>
void cacher<T, U>::init(T* _cac = (T*)0, U _num = (U)0) {
	this -> sot = sizeof(T);
	this -> setAlign();
	this -> setCache(_cac, _num);
}

//---------------------------------------------------------------------------
template <class T, U>
void cacher<T, U>::setAlign(U _al0 = (U)0, U _al1 = (U)0) {
	this -> al0 = _al0 ? _alt0 : this -> sot;
	this -> al1 = _al1 ? _alt1 : this -> sot;
}

//---------------------------------------------------------------------------
template <class T, U>
void cacher<T, U>::setCache(T* _cac = (T*)0, _num = (U)0) {
	this -> cac = _cac;
	this -> num = _num;

	// Allocate or de-allocate replicators as required
	if (this -> num == this -> nrep) {return;}
	if (!this -> num) {
		delete[] this -> replicators;
	}
	else {
		if (this -> nrep) {
			delete[] this -> replicators;
		}
		this -> replicators = new replicators<T, U>[this -> num];
	}
	this -> nrep = this -> num;
}

//---------------------------------------------------------------------------
template <class T, U>
T* cacher<T, U>::setUnit(U ind = (U)0, U d0 = (U)0, U d1 = (U)0, U d2 = (U)1) {
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

# endif

