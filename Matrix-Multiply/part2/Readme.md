# Part 2 - Profiling Cache-Oblivious Matrix

<img align="right" width="300px" src="./media/header.jpg">

> "Measure Measure Measure"

In this final part, you are going to implement a cache-oblivious matrix multiply algorithm and use the Google Benchmark framework to measure it.

# Resources to help

Provided below are a list of curated resources to help you complete the task(s) below. Consult them (read them, or do <kbd>ctrl+f</kbd> for keywords) if you get stuck.

1. Cache-Oblivious Matrix Multiply Example
	- https://www.youtube.com/watch?v=vxkZkcbwU40
2. AVX Tutorial
	- https://www.codeproject.com/Articles/874396/Crunching-Numbers-with-AVX-and-AVX

## The goal

The goal of this assignment is to learn yet another benchmarking tool to create reproducable tests, as well as to implement at least one cache-oblivious algorithm.

## The report

Fill out the accompanying report in [ReportTemplate.odt](./ReportTemplate.odt) as you complete each task.

# Task 1 - Cache-Oblivious

Cache-Oblivious algorithms are algorithms that will eventually fit into each layer of the memory hierarchy (in each layer of the cache), to take advantage of faster memory. Provided in [main.cpp](./main.cpp) is a sample cache-oblivious matrix multiplication and a regular matrix multiplication.

```cpp
// Assume that n is an exact power of 2.
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

```

## Your task

Your task is to modify the [main.cpp](./main.cpp) and do the following:

1. First implement a second cache-oblivious implementation of matrix multiply. This time modify 'n' (lowercase n) to a value such as 4 or 8, and take advantage of the SIMD instructions to perform multiple multiplications at once.
2. Modify the example to instead use google benchmark, such that you can compare (a) regular matrix multiply (b) cache-oblivious matrix multiply(n==1) (c) your cache-oblivious matrix mutiply(n>1).
	- Fill out the corresponding report with your submission.

### SIMD Speed up

If we look carefully at the example below, `n` is the value that we will want to tune. This is essentially the size of the tile that we can multiply. Think about if a value of n==2, n==4, n==8, etc. will do better when combined with SIMD instructions to perform multiple multiplication or multiple add instructions (or perhaps investigate if the SIMD instrinics have helpful dot product computations...hmmm). Also consider what happens if you make n something that will not be able to fit all of the data in the L1 cache. Hmm, consider some of these things as you experiment--this is a research investigation!

```cpp
  if (n == 1)
        C[0] += A[0] * B[0];	
```

# Submission/Deliverables


### Submission

- Commit all of your files to github, including any additional files you create.
- Do not commit any binary files unless told to do so.
- Do not commit any 'data' files generated when executing a binary, but otherwise commit 'data' files you used for colleting results..

### Deliverables

- A modified [main.cpp](./main.cpp) with your implmentation of a cache-oblivious matrix multiply.
- Fill out the [ReportTemplate.odt](./ReportTemplate.odt) with your results
- Commit any code that you have written. 
	- You may also simply submit a url to your quick-bench tool

# Going Further

An optional task(if any) that will reinforce your learning throughout the semester--this is not graded.

1. Feel free to add other tools to your report that may measure interesting things.

# F.A.Q. (Instructor Anticipated Questions)

1. Q: Can I write my report in LaTex?
	- A: Yes, please feel free to do so. Just make sure to upload the .pdf to this directory.
2. Q: Should I include any scripts or spreadsheets of the data I collected?
	- A: Yes please do.
	- A: It may make sense to also include these in your report as well.
3. Q: Can I use a value such as n==16 or compare more values?
	- A: Sure!
