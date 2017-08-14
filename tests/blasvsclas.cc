// to debug assembler
// g++ -g -save-temps a.cpp
// gdb a.out
// break class::function
// r
// disp/i $pc
// si

//---------------------------------------------------------------------------

# include <iostream>
# include <cblas.h>
# include <clas.h>
# include "tictoc.txx"

#pragma hdrstop
#pragma argsused

void Cout(double* X, uint64_t r, uint64_t c, bool tr = false);

//---------------------------------------------------------------------------

int main(int argc, char* argv[])
{
	std::cout << std::endl << "Start" << std::endl;
	uint64_t h, i, j;

	uint64_t m = 30;   // maxuend rows -                  (1 for inner/rmdot)
	uint64_t k = 784; // maxuend cols (and multiple rows)  (1 for outer/mrdot)
	uint64_t n = 1024; // multiple cols  - for ewise, m = n (1 for inner/cmdot)
	uint64_t N = 200; // repeats
	bool transpose[] = {false, false, false};
	bool ColMajor = false;
	
	bool showInputs = false;
	bool showResult[] = {0, 0, 0};
	bool benchMark[] =  {1, 1, 1}; 
	uint64_t repDispMax = 10;

	uint64_t nt = 0; // number of threads (-1 - force unithread, 0 - all threads) 
	uint64_t u0 = 0; // maximum outer unroll (0 - optimal)
	uint64_t u1 = 0; // maximum inner unroll (0 - optimal)
	
	double c0 = 1.;  // coefficient to multiply with multiplicand
	double c1 = 1.;  // coefficient to multiply with multiple
	int maxuend = 0;  // 0 means not used - non-zero is casted to double

	uint64_t zr, zc;
	double* d = 0;
	double* a = new double[m * k];
	double* b = new double[n * k];
	double* c = new double[m * n]; 
	double* _d = new double[m];
	double** C = new double*[m];
	double* x = new double[m * k];
	double* y = new double[n * k];

	bool colmajor[3];
	if (ColMajor) {
		colmajor[0] = !transpose[0];
		colmajor[1] = !transpose[1];
		colmajor[2] = !transpose[2];
	}
	else {
		colmajor[0] = transpose[0];
		colmajor[1] = transpose[1];
		colmajor[2] = transpose[2];
	}

	zr = m; 
	zc = n;
	if (colmajor[0]) {
		zr = n; 
		zc = m;
	}

	double* z = new double[zr * zc]; 
	double** Z = new double*[zr];

	struct timeb t, t0;
	double* dt = new double[N+1];

	for (i = 0; i < m*k; i++) {
		a[i] = (double)((int)(i+1)) * c0;
		x[i] = (double)((int)(i+1)) * c0;
	}
	for (i = 0; i < n*k; i++) {
		b[i] = (double)((int)(-i-1)) * c1;
		y[i] = (double)((int)(-i-1)) * c1;
	}
	for (i = 0; i < m*n; i++) {
		c[i] = 0.;
	}
	for (i = 0; i < m; i++) {
		_d[i] = (double)(maxuend * (1+(int)i)); 
	}
	for (i = 0; i < m; i++) {
		C[i] = c + int(i*n);
	}
	for (i = 0; i < zr*zc; i++) {
		z[i] = 0.;
	}
	for (i = 0; i < zr; i++) {
		Z[i] = z + int(i*zc);
	}
	if (maxuend) {d = _d;}
	
	auto cM = colmajor[0] ? CblasRowMajor : CblasColMajor;
	auto aT = colmajor[1] ? CblasTrans : CblasNoTrans;
	auto bT = colmajor[2] ? CblasTrans : CblasNoTrans;
	if (colmajor[0]) {
		aT = colmajor[1] ? CblasTrans : CblasNoTrans;
		bT = colmajor[2] ? CblasTrans : CblasNoTrans;
	}

	int lda = colmajor[1] ? m :  k;
	int ldb = colmajor[2] ? k :  n;

	std::cout << "m = " << m << std::endl;
	std::cout << "k = " << k << std::endl;
	std::cout << "n = " << n << std::endl;
	std::cout << "repetitions = " << N << std::endl;

	if (showInputs) {
		std::cout << std::endl;
		Cout(x, m, k);
		std::cout << std::endl;
		Cout(y, k, n);
		std::cout << std::endl;
		if (maxuend) {
			Cout(d, 1, m);
			std::cout << std::endl;
		}
	}
	
	// RESULTS

	h = 0; 
	cblas_dgemm(CblasRowMajor, aT, bT,
							m, n, k, 1.,
							a, lda, b, ldb, 1., 
							c, n);
	/* in-place - for outer products
	cblas_dger(CblasRowMajor, m, n, k,
			       a, k, b, k, c, n);
	*/
	if (showResult[h++]) {
		std::cout << std::endl;
		Cout(c, m, n, colmajor[0]);
		std::cout << std::endl;
	}
	for (i = 0; i < m*n; i++) {
		c[i] = 0.;
	}
	if (showResult[h++]) {
		clas::mmdot_product_double(z, x, y, m, k, n, transpose[0], transpose[1], transpose[2], ColMajor, d, -1, u0, u1);
		std::cout << std::endl;
		Cout(z, zr, zc);
		std::cout << std::endl;
	}
	for (i = 0; i < zr*zc; i++) {
		z[i] = 0.;
	}

	if (showResult[h++]) {
		clas::mmdot_product_double(z, x, y, m, k, n, transpose[0], transpose[1], transpose[2], ColMajor, d, nt, u0, u1);
		std::cout << std::endl;
		Cout(z, zr, zc);
		std::cout << std::endl;
	}
	for (i = 0; i < zr*zc; i++) {
		z[i] = 0.;
	}

	// BENCHMARKS

	std::cout << std::endl;
	h = 0;
	if (benchMark[h++]) {
		tic(t0);
		for (i = 0; i<N; i++) {
			tic(t);
			cblas_dgemm(CblasRowMajor, aT, bT,
									m, n, k, 1.,
									a, lda, b, ldb, 1., 
									c, n);
			dt[i] = 1000. * toc(t);
		}
		std::cout << "cblas_dgemm:" << std::endl;
		if (N <= repDispMax) {
			for (i = 0; i<N; i++) {
				std::cout << "\t Rep #" << i << ": " << dt[i] << " ms" << std::endl;
			}
		}
		std::cout << "\t Mean time per rep. = " << (1000.*toc(t0))/(double)(N) << " ms" << std::endl;
	}

	if (benchMark[h++]) {
		tic(t0);
		for (i = 0; i<N; i++) {
			tic(t);
			clas::mmdot_product_double(z, x, y, m, k, n, transpose[0], transpose[1], transpose[2], ColMajor, d, -1, u0, u1);
			dt[i] = 1000. * toc(t);
		}
		std::cout << "clas::mmdot_product_double (single thread):" << std::endl;
		if (N <= repDispMax) {
			for (i = 0; i<N; i++) {
				std::cout << "\t Rep #" << i << ": " << dt[i] << " ms" << std::endl;
			}
		}
		std::cout << "\t Mean time per rep. = " << (1000.*toc(t0))/(double)(N) << " ms" << std::endl;
	}

	if (benchMark[h++]) {
		tic(t0);
		for (i = 0; i<N; i++) {
			tic(t);
			clas::mmdot_product_double(z, x, y, m, k, n, transpose[0], transpose[1], transpose[2], ColMajor, d, nt, u0, u1);
			dt[i] = 1000. * toc(t);
		}
		std::cout << "clas::mmdot_product_double (multithreaded):" << std::endl;
		if (N <= repDispMax) {
			for (i = 0; i<N; i++) {
				std::cout << "\t Rep #" << i << ": " << dt[i] << " ms" << std::endl;
			}
		}
		std::cout << "\t Mean time per rep. = " << (1000.*toc(t0))/(double)(N) << " ms" << std::endl;
	}

	delete[] dt;
	delete[] x;
	delete[] y;
	delete[] a;
	delete[] b;
	delete[] _d;
	delete[] Z;
	delete[] C;
	delete[] z;
	delete[] c;
	d = 0;

	std::cout << std::endl << "Finish" << std::endl;
	std::cout << std::endl << "Test program complete" << std::endl;

	return(0);
}

//---------------------------------------------------------------------------
void Cout(double* X, uint64_t r, uint64_t c, bool tr) {
  uint64_t h, i, j;
	h = 0;
	double* x;
	if (!tr) {
		for (i = 0; i<r; i++) {
			for (j = 0; j<c; j++) {
				if (j != 0) {
					std::cout << ", ";
				}
				std::cout << X[h++];
			}
			std::cout << std::endl;
		}
		return;
	}
	for (i = 0; i<c; i++) {
		x = X;
		for (j = 0; j<r; j++) {
			if (j != 0) {
				std::cout << ", ";
			}
			std::cout << *x;
			x += c;
		}
		std::cout << std::endl;
		X++;
	}
}
//---------------------------------------------------------------------------
