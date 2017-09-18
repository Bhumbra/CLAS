# include <iostream>
# include <cblas.h>
# include <clas.h>
# include "tictoc.txx"

//---------------------------------------------------------------------------
#pragma hdrstop
#pragma argsused

//---------------------------------------------------------------------------
void cblas_inner(double* Out, double* In0, double* In1, 
		uint64_t m, uint64_t k, uint64_t p, uint64_t q, 
		bool I0T = false, bool I1B = false);
//---------------------------------------------------------------------------

int main(int argc, char* argv[])
{
	std::cout << "-----------------------------------------------------" << std::endl;
	std::cout << "CBLAS vs CLAS test program benchmarking inner product" << std::endl << std::endl;

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
	double* c = new double[m * p * q]; 

	struct timeb t0;
	double dt;
	uint64_t i;

	for (i = 0; i < m*k; i++) {
		a[i] = (double)((int)(i+1));
	}
	for (i = 0; i < m*k*p*q; i++) {
		b[i] = (double)((int)(-i-1));
	}
	for (i = 0; i < m*p*q; i++) {
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
		cblas_inner(c, a, b, m, k, p, q);	
	}
	dt = 1000.*toc(t0);
	std::cout << "cblas_dgemv:" << std::endl;
	std::cout << "\t Total time = " << dt << " ms" << std::endl;
	std::cout << "\t Mean time per rep. = " << dt/(double)(N) << " ms" << std::endl << std::endl;

	tic(t0);
	for (i = 0; i<N; i++) {
		clas::inner_product_double(c, a, b, m, k, p, q, false, false, (double*)0, 0, 0.);
	}
	dt = 1000.*toc(t0);
	std::cout << "clas::inner_product_double (single-thread):" << std::endl;
	std::cout << "\t Total time = " << dt << " ms" << std::endl;
	std::cout << "\t Mean time per rep. = " << dt/(double)(N) << " ms" << std::endl << std::endl;

	tic(t0);
	for (i = 0; i<N; i++) {
		clas::inner_product_double(c, a, b, m, k, p, q);
	}
	dt = 1000.*toc(t0);
	std::cout << "clas::inner_product_double (multithreaded):" << std::endl;
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
void cblas_inner(double* Out, double* In0, double* In1, 
		uint64_t m, uint64_t k, uint64_t p, uint64_t q, 
		bool I0T, bool I1B) {
	uint64_t i, j, OutS, In1S, Outs, In0s, In1s, incx;
	double *out, *in0, *in1, in0s;
	OutS = m * q;
	Outs = q;
	if (!I1B) {
		In1S = m * q * k;
		In1s = q * k;
	}
	else {
		In1S = q * k;
		In1s = (uint64_t)0;
	}
	if (!I0T) {
		In0s = k;
		for (i = 0; i < p; i++) {
			out = Out + i * OutS;
			in0 = In0;
			in1 = In1 + i * In1S;
			for (j = 0; j < m; j++) {
				cblas_dgemv(CblasRowMajor, CblasNoTrans, q, k, 1.,
										in1, k, in0, 1, 0., out + j * Outs, 1);
				in0 += In0s;
				in1 += In1s;
			}
		}
	}
	else {
		In0s = (uint64_t)1;
		for (i = 0; i < p; i++) {
			out = Out + i * OutS;
			in0 = In0;
			in1 = In1 + i * In1S;
			for (j = 0; j < m; j++) {
				cblas_dgemv(CblasRowMajor, CblasNoTrans, q, k, 1.,
										in1, k, in0, m, 0., out + j * Outs, 1);
				in0 += In0s;
				in1 += In1s;
			}
		}
	}
}

//---------------------------------------------------------------------------
