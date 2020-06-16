#include <stdio.h> 
#include <stdlib.h>
#include <sys/time.h>
#include <benchmark/benchmark.h>

// Set to a value of 2
#define N 512
  
void transpose(double* A, double* B) { 
    int ii, jj; 
    for (ii = 0; ii < N; ii++) { 
        for (jj = 0; jj < N; jj++) { 
            B[(ii * N) + jj] = A[(jj * N) + ii];
	} 
    }
}

void cacheObliviousTranspose(int x, int hix, int y, int hiy, double* matrix, double* out) {
    if ((hix == 1) && (hiy == 1)) {
	if(x < y) {
            out[(N * x) + y] = matrix[(N * y) + x];
            out[(N * y) + x] = matrix[(N * x) + y];
        }
        return;
    }

    if (hix >= hiy) {
        int xmid = hix / 2;
        cacheObliviousTranspose(x, xmid, y, hiy, matrix, out);
        cacheObliviousTranspose(x + xmid, hix - xmid, y, hiy, matrix, out);
        return;
    }

    int ymid = hiy / 2;
    cacheObliviousTranspose(x, hix, y, ymid, matrix, out);
    cacheObliviousTranspose(x, hix, y + ymid, hiy - ymid, matrix, out);
}

void inPlaceCacheObliviousTranspose(int x, int hix, int y, int hiy, double* matrix) {
    if ((hix == 1) && (hiy == 1)) {
	if(x < y) {
            double tmp = matrix[(N * y) + x];
            matrix[(N * y) + x] = matrix[(N * x) + y];
            matrix[(N * x) + y] = tmp;
        }
        return;
    }

    if (hix >= hiy) {
        int xmid = hix / 2;
        inPlaceCacheObliviousTranspose(x, xmid, y, hiy, matrix);
        inPlaceCacheObliviousTranspose(x + xmid, hix - xmid, y, hiy, matrix);
        return;
    }

    int ymid = hiy / 2;
    inPlaceCacheObliviousTranspose(x, hix, y, ymid, matrix);
    inPlaceCacheObliviousTranspose(x, hix, y + ymid, hiy - ymid, matrix);
}

static void BM_transpose(benchmark::State& state) {
    double A[N][N];
    double B[N][N];
    // Initialize array
    for(int ii = 0; ii < N; ++ii){
        for(int jj = 0; jj < N; ++jj){
            A[ii][jj] = (double)rand() / (double)RAND_MAX;
            B[ii][jj] = (double)rand() / (double)RAND_MAX;
	}
    }
    for (auto _ : state)
	transpose((double *)A, (double *)B);
}

static void BM_cacheObliviousTranspose(benchmark::State& state) {
    double C[N][N];
    double D[N][N];
	
    // Initialize array
    for(int ii = 0; ii < N; ++ii){
        for(int jj = 0; jj < N; ++jj){
	    C[ii][jj] = (double)rand() / (double)RAND_MAX;
            D[ii][jj] = (double)rand() / (double)RAND_MAX;
        }
    }
    for (auto _ : state)
	cacheObliviousTranspose(0, N, 0, N,(double*) C, (double*) D);
}

static void BM_inPlaceCacheObliviousTranspose(benchmark::State& state) {
    double E[N][N];
	
    // Initialize array
    for(int ii = 0; ii < N; ++ii){
        for(int jj = 0; jj < N; ++jj){
            E[ii][jj] = (double)rand() / (double)RAND_MAX;
        }
    }
	for (auto _ : state) 
    	    inPlaceCacheObliviousTranspose(0, N, 0, N,(double*) E);
}

BENCHMARK(BM_transpose);
BENCHMARK(BM_cacheObliviousTranspose);
BENCHMARK(BM_inPlaceCacheObliviousTranspose);
BENCHMARK_MAIN();
