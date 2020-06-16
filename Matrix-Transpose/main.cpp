
#include <stdio.h> 
#include <stdlib.h>

#define M 4
#define N 4
  
void transpose(double* A, double* B) 
{ 
    int ii, jj; 
    for (ii = 0; ii < N; ii++) 
        for (jj = 0; jj < M; jj++) 
            B[(ii * N) + jj] = A[(jj * M) + ii]; 
}

void CacheObliviousTransposition(int x, int delx, int y, int dely, double* matrix) {
    if ((delx == 1) && (dely == 1)) {
        if(x<y)
        {
            int tmp = matrix[(N*y) + x];
            matrix[(N*y) + x] = matrix[(N*x) + y];
            matrix[(N*x) + y] = tmp;
        }
        return;
    }

    if (delx >= dely) {
        int xmid = delx / 2;
        CacheObliviousTransposition(x, xmid, y, dely, matrix);
        CacheObliviousTransposition(x + xmid, delx - xmid, y, dely, matrix);
        return;
    }

    int ymid = dely / 2;
    CacheObliviousTransposition(x, delx, y, ymid, matrix);
    CacheObliviousTransposition(x, delx, y + ymid, dely - ymid, matrix);
}
  
int main() 
{ 

    double A[N][M];
    double B[N][M];
    double C[N][M];

    for(int i =0; i < N; ++i){
        for(int j =0; j < M; ++j){
            A[i][j] = (double)rand() / (double)RAND_MAX;
            B[i][j] = (double)rand() / (double)RAND_MAX;
	    C[i][j] = (double)rand() / (double)RAND_MAX;
        }
    }
    int i, j; 

    printf("A matrix was \n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        printf("%f ", A[i][j]);
        printf("\n");
    }
    transpose((double *)A, (double *)B);
    printf("B matrix is \n"); 
    for (i = 0; i < N; i++) 
    { 
        for (j = 0; j < M; j++) 
        printf("%f ", B[i][j]); 
        printf("\n"); 
    } 
    printf("C matrix was \n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        printf("%f ", C[i][j]);
        printf("\n");
    }
    CacheObliviousTransposition(0, N, 0, N,(double*) C);
    printf("C matrix is \n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        printf("%f ", C[i][j]);
        printf("\n");
    }
  
    return 0; 
} 

