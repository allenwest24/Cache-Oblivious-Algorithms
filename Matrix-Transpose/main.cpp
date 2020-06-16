
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

void CacheObliviousTransposition(int x, int hix, int y, int hiy, double* matrix) {
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
        CacheObliviousTransposition(x, xmid, y, hiy, matrix);
        CacheObliviousTransposition(x + xmid, hix - xmid, y, hiy, matrix);
        return;
    }

    int ymid = hiy / 2;
    CacheObliviousTransposition(x, hix, y, ymid, matrix);
    CacheObliviousTransposition(x, hix, y + ymid, hiy - ymid, matrix);
}
  
int main() { 
    double A[N][N];
    double B[N][N];
    double C[N][N];
    for(int ii = 0; ii < N; ++ii){
        for(int jj = 0; jj < N; ++jj){
            A[ii][jj] = (double)rand() / (double)RAND_MAX;
            B[ii][jj] = (double)rand() / (double)RAND_MAX;
	    C[ii][jj] = (double)rand() / (double)RAND_MAX;
        }
    }
    int kk, ll; 

    printf("A matrix was \n");
    for (kk = 0; kk < N; kk++) {
        for (ll = 0; ll < N; ll++) {
            printf("%f ", A[kk][ll]);
	}
	printf("\n");
    }
    transpose((double *)A, (double *)B);
    printf("B matrix is \n"); 
    for (kk = 0; kk < N; kk++) { 
        for (ll = 0; ll < N; ll++) {
            printf("%f ", B[kk][ll]);  
	}
	printf("\n");
    } 
    printf("C matrix was \n");
    for (kk = 0; kk < N; kk++) {
        for (ll = 0; ll < N; ll ++) {
            printf("%f ", C[kk][ll]);
	}
	printf("\n");
    }
    CacheObliviousTransposition(0, N, 0, N,(double*) C);
    printf("C matrix is \n");
    for (kk = 0; kk < N; kk++) {
        for (ll = 0; ll < N; ll++) {
            printf("%f ", C[kk][ll]);
	}
	printf("\n");
    }
  
    return 0; 
} 

