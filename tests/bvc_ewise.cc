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
	std::cout << "CBLAS vs CLAS test program benchmarking ewise product" << std::endl << std::endl;
	std::cout << "-----------------------------------------------------" << std::endl << std::endl;

	if (argc < 5) {
		std::cout << "Five input arguments required: " << std::endl;
		std::cout << "./bvc_mmdot m k p q N" << std::endl;
		std::cout << endl;
		std::cout << "where:" << endl;
		std::cout << "m = first dimension of multiplicand and second dimension of multiple" << endl;
		std::cout << "k = second dimension multiplicand and fourth dimension of multiple" << endl;
		std::cout << "p = first dimension of multiple" << endl;
		std::cout << "q = third dimension of multiple" << endl;
		return 1;
	}

	uint64_t m = (uint64_t)atoi(argv[1]); // multiplicand rows                     
	uint64_t k = (uint64_t)atoi(argv[2]); // multiplicand cols (and multiple rows) 
	uint64_t p = (uint64_t)atoi(argv[3]);
	uint64_t q = (uint64_t)atoi(argv[4]);
	uint64_t N = (uint64_t)atoi(argv[5]);

	double* a = new double[m * k];
	double* b = new double[m * k * p * q];
	double* c = new double[m * k * p * q]; 

	struct timeb t0;
	double dt;
	uint64_t i;

	for (i = 0; i < m*k; i++) {
		a[i] = (double)((int)(i+1));
	}
	for (i = 0; i < m*k*p*q; i++) {
		b[i] = (double)((int)(-i-1));
	}
	for (i = 0; i < m*k*p*q; i++) {
		c[i] = 0.;
	}

	std::cout << "m = " << m << std::endl;
	std::cout << "k = " << k << std::endl;
	std::cout << "p = " << p << std::endl;
	std::cout << "q = " << q << std::endl;
	std::cout << "repetitions = " << N << std::endl;

	std::cout << std::endl;
	tic(t0);
	for (i = 0; i<N; i++) {
		//cblas_ewise(c, a, b, m, k, p, q);	
	}
	dt = 1000.*toc(t0);
	std::cout << "cblas_dge_ - no entrywise product:" << std::endl;
	std::cout << "\t Total time =  N/A" << std::endl;
	std::cout << "\t Mean time per rep. = N/A" << std::endl << std::endl;

	tic(t0);
	for (i = 0; i<N; i++) {
		clas::ewise_product_double(c, a, b, m, k, p, q, false, false, (double*)0, 0, 0.);
	}
	dt = 1000.*toc(t0);
	std::cout << "clas::ewise_product_double (single-thread):" << std::endl;
	std::cout << "\t Total time = " << dt << " ms" << std::endl;
	std::cout << "\t Mean time per rep. = " << dt/(double)(N) << " ms" << std::endl << std::endl;

	tic(t0);
	for (i = 0; i<N; i++) {
		clas::ewise_product_double(c, a, b, m, k, p, q);
	}
	dt = 1000.*toc(t0);
	std::cout << "clas::ewise_product_double (multithreaded):" << std::endl;
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

