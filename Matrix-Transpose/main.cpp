#include <stdio.h> 
#include <stdlib.h>

#define N 4
  
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
  
int main() { 
    double A[N][N];
    double B[N][N];
    double C[N][N];
    double D[N][N];
    double E[N][N];
    for(int ii = 0; ii < N; ++ii){
        for(int jj = 0; jj < N; ++jj){
            A[ii][jj] = (double)rand() / (double)RAND_MAX;
            B[ii][jj] = (double)rand() / (double)RAND_MAX;
	    C[ii][jj] = (double)rand() / (double)RAND_MAX;
            D[ii][jj] = (double)rand() / (double)RAND_MAX;
            E[ii][jj] = (double)rand() / (double)RAND_MAX;
        }
    }
    transpose((double *)A, (double *)B);
    cacheObliviousTranspose(0, N, 0, N,(double*) C, (double*) D);
    inPlaceCacheObliviousTranspose(0, N, 0, N,(double*) E);
  
    return 0; 
} 
