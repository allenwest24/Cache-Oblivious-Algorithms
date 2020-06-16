user@user-VirtualBox:~/Desktop$ g++ gb_main.cpp -lbenchmark -lpthread -o matrix_oblivious_gb
user@user-VirtualBox:~/Desktop$ ./matrix_oblivious_gb 
2020-06-10 18:02:15
Running ./matrix_oblivious_gb
Run on (2 X 1800 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x2)
  L1 Instruction 32 KiB (x2)
  L2 Unified 256 KiB (x2)
  L3 Unified 6144 KiB (x2)
Load Average: 0.26, 0.36, 0.29
***WARNING*** Library was built as DEBUG. Timings may be affected.
---------------------------------------------------------
Benchmark               Time             CPU   Iterations
---------------------------------------------------------
regular_matrix  517331627 ns    516437928 ns            2
BM_Rec_Mult     427313045 ns    426812101 ns            2
BM_Rec_Mult2    288979934 ns    288727112 ns            2
