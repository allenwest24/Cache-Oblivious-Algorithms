user@user-VirtualBox:~/Desktop/matrix_transpose$ vim naive.cpp
user@user-VirtualBox:~/Desktop/matrix_transpose$ g++ naive.cpp -O3 -o naive
user@user-VirtualBox:~/Desktop/matrix_transpose$ valgrind --tool=cachegrind ./naive
==13664== Cachegrind, a cache and branch-prediction profiler
==13664== Copyright (C) 2002-2017, and GNU GPL'd, by Nicholas Nethercote et al.
==13664== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==13664== Command: ./naive
==13664== 
--13664-- warning: L3 cache found, using its data for the LL simulation.
==13664== 
==13664== I   refs:      11,517,117
==13664== I1  misses:           911
==13664== LLi misses:           900
==13664== I1  miss rate:       0.01%
==13664== LLi miss rate:       0.01%
==13664== 
==13664== D   refs:       4,762,760  (3,636,858 rd   + 1,125,902 wr)
==13664== D1  misses:        92,284  (   67,142 rd   +    25,142 wr)
==13664== LLd misses:        17,974  (    1,392 rd   +    16,582 wr)
==13664== D1  miss rate:        1.9% (      1.8%     +       2.2%  )
==13664== LLd miss rate:        0.4% (      0.0%     +       1.5%  )
==13664== 
==13664== LL refs:           93,195  (   68,053 rd   +    25,142 wr)
==13664== LL misses:         18,874  (    2,292 rd   +    16,582 wr)
==13664== LL miss rate:         0.1% (      0.0%     +       1.5%  )
