# Install Instructions

This project works largely the same as the matrix multiply cache-oblivious assignment
To run the experiment for yourself please do the following:

### Timing:

- Download main.cpp
- in the same directory as main.cpp, execute the following compilation command:
    - g++ main.cpp -lbenchmark -lpthread -O3 -o transpose_time
- From here, simply run with ./transpose_time

The results should be printed out as is the standard for Google Benchmarks.

### Demo:

As proof of concept on a small scale, I provided a separate file not using goole benchmarks that prints out the matrix transposition for the first three implementations on a very small scale (4x4)

To view the output, go to the demo directory and open demo.bash

or

- Download demo.cpp
- in the same directory as demo.cpp, execute the following compilation command:
    - g++ demo.cpp -O3 -o transpose_demo
- From here, simply run with ./transpose_demo

### Cache hits

In the results folder, I provided the naive implementation and the in-place cache-oblivious implementation along with their cache hit/miss rates as given by cache grind.

To replicate this for yourself, download them, compile the same way as for demo.cpp, then run the following:
   - valgrind --tool=cachegrind ./program_name
