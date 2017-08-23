// Single cache source for multiple data units.

//------------------------------------------------------------------------------
# ifndef mcache_txx
# define mcache_txx

//------------------------------------------------------------------------------
# include "tcache.txx"

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// mcache class
//------------------------------------------------------------------------------
template <class T, class U>
class mcache {
	public:
		mcache();
		mcache(T* _Cac, U _Num = (U)0);
		~mcache<T, U>();
		void init(T* _cac = (T*)0,  U _num = (U)0);
		void setAlign(U al0 = (U)0, U al1 = (U)0);
		void setCache(T* _cac = (T*)0,  U _num = (U)0);
		U nextAlignedIndOuter(const T* ptr);
		U nextAlignedIndInner(const T* ptr);
		T* setUnit(U uno = (U)0, U d0 = (U)0, U d1 = (U)0, U d2 = (U)1);
		tcache<T, U> retUnit(U uno = (U)0);
	protected:
		tcache<T, U>* tcaches; // tcache instances for copy_toing to cache
		U sot; // sizeof(T);
		T* cac; // pointer to cache source
		U num; // number of data units to cache
		U al0; // outer alignment in bytes = set associativity x line size
		U al1; // inner alignment in bytes = line size 
	private:
		U nrep; // number of allocated tcaches
};

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
template <class T, class U>
mcache<T, U>::mcache() {
	this -> nrep = (U)0;
	this -> init();
}

//---------------------------------------------------------------------------
template <class T, class U>
mcache<T, U>::mcache(T* _cac, U _num) {
	this -> nrep = (U)0;
	this -> init(_cac, _num);
}

//---------------------------------------------------------------------------
template <class T, class U>
mcache<T, U>::~mcache() {
	this -> init();
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
template <class T, class U>
void mcache<T, U>::init(T* _cac, U _num) {
	this -> sot = sizeof(T);
	this -> setAlign();
	this -> setCache(_cac, _num);
}

//---------------------------------------------------------------------------
template <class T, class U>
void mcache<T, U>::setAlign(U _al0, U _al1) {
	this -> al0 = _al0 ? _al0 : this -> sot;
	this -> al1 = _al1 ? _al1 : this -> sot;
}

//---------------------------------------------------------------------------
template <class T, class U>
void mcache<T, U>::setCache(T* _cac, U _num) {
	this -> cac = _cac;
	this -> num = _num;

	// Allocate or de-allocate tcaches as required
	if (this -> num == this -> nrep) {return;}
	if (!this -> num) {
		delete[] this -> tcaches;
	}
	else {
		if (this -> nrep) {
			delete[] this -> tcaches;
		}
		this -> tcaches = new tcache<T, U>[this -> num];
	}
	this -> nrep = this -> num;
}

//---------------------------------------------------------------------------
template <class T, class U>
U mcache<T, U>::nextAlignedIndOuter(const T* ptr) {
	return (nextAlignedInd(ptr, this -> al0));
}

//---------------------------------------------------------------------------
template <class T, class U>
U mcache<T, U>::nextAlignedIndInner(const T* ptr) {
	return (nextAlignedInd(ptr, this -> al1));
}

//---------------------------------------------------------------------------
template <class T, class U>
T* mcache<T, U>::setUnit(U uno, U d0, U d1, U d2) {
	T *last, *next;
	last = uno ? this -> tcaches[uno-1].retCP() : this -> cac;
	if (!last) {return last;} // force an error
	if (uno) {last += this -> tcaches[uno-1].retCL();}
	next = last + this -> nextAlignedIndOuter(last);
	this -> tcaches[uno].setA(this -> al1);
	this -> tcaches[uno].setC(next, d0, d1, d2);
	return (next);
}

//---------------------------------------------------------------------------
template <class T, class U>
tcache<T, U> mcache<T, U>::retUnit(U uno) {
	return this -> tcaches[uno];
}

//---------------------------------------------------------------------------

# endif

