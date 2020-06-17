#include <stdio.h>
#include <stdlib.h>

#define N 256

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
    for(int ii = 0; ii < N; ++ii){
        for(int jj = 0; jj < N; ++jj){
            A[ii][jj] = (double)rand() / (double)RAND_MAX;
        }
    }
    inPlaceCacheObliviousTranspose(0, N, 0, N,(double*) A);

    return 0;
}
