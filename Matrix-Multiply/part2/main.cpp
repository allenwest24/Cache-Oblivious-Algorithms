#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <benchmark/benchmark.h>

// Set to a value of a power of 2
#define N 256

// Note: Initialization and timers are
//       encapsulated in this function.
//       This could be cleaned up in an Object-Oriented Manner
//       if you'd like.
static void regular_matrix(benchmark::State& state){
    double A[N][N];
    double B[N][N];
    double C[N][N];

    // Initialize array
    for(int i =0; i < N; ++i){
        for(int j =0; j < N; ++j){
            A[i][j] = (double)rand() / (double)RAND_MAX;
            B[i][j] = (double)rand() / (double)RAND_MAX;
            C[i][j] = (double)rand() / (double)RAND_MAX;
        }
    }   
    for (auto _ : state)
        // Perform multiplication
        for(int i =0; i < N; ++i){
            for(int j =0; j < N; ++j){
                for(int k =0; k < N; ++k){
                    C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void Rec_Mult(double* C, double* A, double* B, int n, int rowsize) {
    // The smallest 'tile' or our base case where we actually
    // perform a multiplication
    if (n == 1)
        C[0] += A[0] * B[0];
    else {
        // Here we are breaking things into smaller 'tiles'
        // We recursively divide our matrix into smaller pieces
        int64_t d11 = 0;
        int64_t d12 = n/2;
        int64_t d21 = (n/2) * rowsize;
        int64_t d22 = (n/2) * (rowsize+1);
        Rec_Mult(C+d11, A+d11, B+d11, n/2, rowsize);
        Rec_Mult(C+d11, A+d12, B+d21, n/2, rowsize);
        Rec_Mult(C+d12, A+d11, B+d12, n/2, rowsize);
        Rec_Mult(C+d12, A+d12, B+d22, n/2, rowsize);
        Rec_Mult(C+d21, A+d21, B+d11, n/2, rowsize);
        Rec_Mult(C+d21, A+d22, B+d21, n/2, rowsize);
        Rec_Mult(C+d22, A+d21, B+d12, n/2, rowsize);
        Rec_Mult(C+d22, A+d22, B+d22, n/2, rowsize);
    }
}

// Assume that n is an exact power of 2.
static void BM_Rec_Mult(benchmark::State& state) {
    double A[N][N];
    double B[N][N];
    double C[N][N];
    
    // Initialize array
    for(int i =0; i < N; ++i){
        for(int j =0; j < N; ++j){
            A[i][j] = (double)rand() / (double)RAND_MAX;
            B[i][j] = (double)rand() / (double)RAND_MAX;
            C[i][j] = (double)rand() / (double)RAND_MAX;
        }
    }
    for (auto _ : state) 
        Rec_Mult((double *)C, (double *)A, (double *)B, 256, N);
}

// TODO: Implement with n>1
void Rec_Mult2(double* C, double* A, double* B, int n, int rowsize) {
    // The smallest 'tile' or our base case where we actually
    // perform a multiplication
    if (n == 2) {
        C[0] += A[0] * B[0];
        int64_t d11 = 0;
        int64_t d12 = n/2;
        int64_t d21 = (n/2) * rowsize;
        int64_t d22 = (n/2) * (rowsize+1);
        (C+d11)[0] += (A+d11)[0] * (B+d11)[0];
        (C+d11)[0] += (A+d12)[0] * (B+d21)[0];
        (C+d12)[0] += (A+d11)[0] * (B+d12)[0];
        (C+d12)[0] += (A+d12)[0] * (B+d22)[0];
        (C+d21)[0] += (A+d21)[0] * (B+d11)[0];
        (C+d21)[0] += (A+d22)[0] * (B+d21)[0];
        (C+d22)[0] += (A+d21)[0] * (B+d12)[0];
        (C+d22)[0] += (A+d22)[0] * (B+d22)[0];
    }
    else {
        // Here we are breaking things into smaller 'tiles'
        // We recursively divide our matrix into smaller pieces
        int64_t d11 = 0;
        int64_t d12 = n/2;
        int64_t d21 = (n/2) * rowsize;
        int64_t d22 = (n/2) * (rowsize+1);
        Rec_Mult(C+d11, A+d11, B+d11, n/2, rowsize);
        Rec_Mult(C+d11, A+d12, B+d21, n/2, rowsize);
        Rec_Mult(C+d12, A+d11, B+d12, n/2, rowsize);
        Rec_Mult(C+d12, A+d12, B+d22, n/2, rowsize);
        Rec_Mult(C+d21, A+d21, B+d11, n/2, rowsize);
        Rec_Mult(C+d21, A+d22, B+d21, n/2, rowsize);
        Rec_Mult(C+d22, A+d21, B+d12, n/2, rowsize);
        Rec_Mult(C+d22, A+d22, B+d22, n/2, rowsize);
    }
}

// Assume that n is an exact power of 2.
static void BM_Rec_Mult2(benchmark::State& state) {
    double A[N][N];
    double B[N][N];
    double C[N][N];
    
    // Initialize array
    for(int i =0; i < N; ++i){
        for(int j =0; j < N; ++j){
            A[i][j] = (double)rand() / (double)RAND_MAX;
            B[i][j] = (double)rand() / (double)RAND_MAX;
            C[i][j] = (double)rand() / (double)RAND_MAX;
        }
    }
    for (auto _ : state) 
        Rec_Mult2((double *)C, (double *)A, (double *)B, 256, N);
}


BENCHMARK(regular_matrix);
BENCHMARK(BM_Rec_Mult);
BENCHMARK(BM_Rec_Mult2);
BENCHMARK_MAIN();
