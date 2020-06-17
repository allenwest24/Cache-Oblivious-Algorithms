user@user-VirtualBox:~/Desktop/matrix_transpose$ vim inPlaceCacheOblivious.cpp 
user@user-VirtualBox:~/Desktop/matrix_transpose$ g++ inPlaceCacheOblivious.cpp -O3 -o superior
user@user-VirtualBox:~/Desktop/matrix_transpose$ valgrind --tool=cachegrind ./superior
==13897== Cachegrind, a cache and branch-prediction profiler
==13897== Copyright (C) 2002-2017, and GNU GPL'd, by Nicholas Nethercote et al.
==13897== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==13897== Command: ./superior
==13897== 
--13897-- warning: L3 cache found, using its data for the LL simulation.
==13897== 
==13897== I   refs:      7,982,126
==13897== I1  misses:          911
==13897== LLi misses:          900
==13897== I1  miss rate:      0.01%
==13897== LLi miss rate:      0.01%
==13897== 
==13897== D   refs:      2,925,058  (1,865,464 rd   + 1,059,594 wr)
==13897== D1  misses:       21,911  (   13,100 rd   +     8,811 wr)
==13897== LLd misses:        9,798  (    1,264 rd   +     8,534 wr)
==13897== D1  miss rate:       0.7% (      0.7%     +       0.8%  )
==13897== LLd miss rate:       0.3% (      0.1%     +       0.8%  )
==13897== 
==13897== LL refs:          22,822  (   14,011 rd   +     8,811 wr)
==13897== LL misses:        10,698  (    2,164 rd   +     8,534 wr)
==13897== LL miss rate:        0.1% (      0.0%     +       0.8%  )
