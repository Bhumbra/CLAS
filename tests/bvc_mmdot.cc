# include <iostream>
# include <cblas.h>
# include <clas.h>
# include "tictoc.txx"

//---------------------------------------------------------------------------
#pragma hdrstop
#pragma argsused

//---------------------------------------------------------------------------

int main(int argc, char* argv[])
{
	std::cout << "-----------------------------------------------------" << std::endl;
	std::cout << "CBLAS vs CLAS test program benchmarking mmdot product" << std::endl;

	if (argc < 5) {
		std::cout << "Four input arguments required: " << std::endl;
		std::cout << "./bvc_mmdot m k n N" << std::endl;
		std::cout << endl;
		std::cout << "where:" << endl;
		std::cout << "m = number of rows of multiplicand" << endl;
		std::cout << "k = number of columns of multiplicand" << endl;
		std::cout << "n = number of columns of multiple" << endl;
		std::cout << "N = number of product repetitions" << endl;
		return 1;
	}

	uint64_t m = (uint64_t)atoi(argv[1]); // multiplicand rows                     
	uint64_t k = (uint64_t)atoi(argv[2]); // multiplicand cols (and multiple rows) 
	uint64_t n = (uint64_t)atoi(argv[3]);
	uint64_t N = (uint64_t)atoi(argv[4]);

	double* a = new double[m * k];
	double* b = new double[n * k];
	double* c = new double[m * n]; 

	struct timeb t0;
	double dt;
	uint64_t i;

	for (i = 0; i < m*k; i++) {
		a[i] = (double)((int)(i+1));
	}
	for (i = 0; i < n*k; i++) {
		b[i] = (double)((int)(-i-1));
	}
	for (i = 0; i < m*n; i++) {
		c[i] = 0.;
	}
	int lda = k;
	int ldb = n;

	std::cout << "m = " << m << std::endl;
	std::cout << "k = " << k << std::endl;
	std::cout << "n = " << n << std::endl;
	std::cout << "repetitions = " << N << std::endl;

	std::cout << std::endl;
	tic(t0);
	for (i = 0; i<N; i++) {
		cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
								m, n, k, 1.,
								a, lda, b, ldb, 1., 
								c, n);
	}
	dt = 1000.*toc(t0);
	std::cout << "cblas_dgemm:" << std::endl;
	std::cout << "\t Total time = " << dt << " ms" << std::endl;
	std::cout << "\t Mean time per rep. = " << dt/(double)(N) << " ms" << std::endl << std::endl;

	tic(t0);
	for (i = 0; i<N; i++) {
		clas::mmdot_product_double(c, a, b, m, k, n, false, false, false, false, (double*)0, 0, 0.);
	}
	dt = 1000.*toc(t0);
	std::cout << "clas::mmdot_product_double (single-thread):" << std::endl;
	std::cout << "\t Total time = " << dt << " ms" << std::endl;
	std::cout << "\t Mean time per rep. = " << dt/(double)(N) << " ms" << std::endl << std::endl;

	tic(t0);
	for (i = 0; i<N; i++) {
		clas::mmdot_product_double(c, a, b, m, k, n);
	}
	dt = 1000.*toc(t0);
	std::cout << "clas::mmdot_product_double (multithreaded):" << std::endl;
	std::cout << "\t Total time = " << dt << " ms" << std::endl;
	std::cout << "\t Mean time per rep. = " << dt/(double)(N) << " ms" << std::endl << std::endl;

	delete[] a;
	delete[] b;
	delete[] c;

	std::cout << "Test program complete" << std::endl;
	std::cout << "-----------------------------------------------------" << std::endl << std::endl;

	return(0);
}

//---------------------------------------------------------------------------
