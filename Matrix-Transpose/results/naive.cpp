#include <stdio.h>
#include <stdlib.h>

#define N 256

void transpose(double* A, double* B) { 
    int ii, jj; 
    for (ii = 0; ii < N; ii++) { 
        for (jj = 0; jj < N; jj++) { 
            B[(ii * N) + jj] = A[(jj * N) + ii];
	} 
    }
}


int main() {
    double A[N][N];
    double B[N][N];
    for(int ii = 0; ii < N; ++ii){
        for(int jj = 0; jj < N; ++jj){
            A[ii][jj] = (double)rand() / (double)RAND_MAX;
	    B[ii][jj] = (double)rand() / (double)RAND_MAX;
        }
    }
    transpose((double *)A, (double *)B);

    return 0;
}
