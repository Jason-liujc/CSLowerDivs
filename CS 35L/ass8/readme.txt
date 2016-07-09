////////////////////////////////////////////////////// Problem in the lab


Some issues I ran into this lab would be how to solve the program of reproducing the 
results after I implemented the thread function. I have to make many small changes. Also 
the linker wasn't working correctly, and it took me a long time to realize that the 
problem lies in the fact that I put the lpthread tag in CFLAGS instead of LDBLIBS.



////////////////////////////////////////////////////// Improvement of multithreading

Before I used multiththreading, my output from the make clean check is:

gcc -std=gnu99 -g -O2 -Wall -Wextra -Wno-unused-parameter   -c -o raymath.o raymath.c
gcc -std=gnu99 -g -O2 -Wall -Wextra -Wno-unused-parameter   -c -o shaders.o shaders.c
gcc -std=gnu99 -g -O2 -Wall -Wextra -Wno-unused-parameter -o srt main.o raymath.o
 shaders.o -lm
time ./srt 1-test.ppm >1-test.ppm.tmp

real	0m39.462s
user	0m39.050s
sys	0m0.177s
mv 1-test.ppm.tmp 1-test.ppm
time ./srt 2-test.ppm >2-test.ppm.tmp
./srt: Multithreading is not supported yet.

real	0m0.005s
user	0m0.001s
sys	0m0.002s
make: *** [2-test.ppm] Error 1


And after I used multithreading, the make clean check gives me:
gcc -std=gnu99 -g -O2 -Wall -Wextra -Wno-unused-parameter   -c -o 
raymath.o raymath.c
gcc -std=gnu99 -g -O2 -Wall -Wextra -Wno-unused-parameter   -c -o 
shaders.o shaders.c
gcc -std=gnu99 -g -O2 -Wall -Wextra -Wno-unused-parameter -o 
srt main.o raymath.o shaders.o -lm -lpthread
time ./srt 1-test.ppm >1-test.ppm.tmp

real	0m50.284s
user	0m43.289s
sys	0m0.435s
mv 1-test.ppm.tmp 1-test.ppm
time ./srt 2-test.ppm >2-test.ppm.tmp

real	0m29.677s
user	0m45.995s
sys	0m0.398s
mv 2-test.ppm.tmp 2-test.ppm
time ./srt 4-test.ppm >4-test.ppm.tmp

real	0m26.960s
user	1m11.650s
sys	0m0.420s
mv 4-test.ppm.tmp 4-test.ppm
time ./srt 8-test.ppm >8-test.ppm.tmp

real	0m26.400s
user	1m12.298s
sys	0m0.333s
mv 8-test.ppm.tmp 8-test.ppm
for file in 1-test.ppm 2-test.ppm 4-test.ppm 8-test.ppm; do \
 diff -u baseline.ppm $file || exit; \
done


In this way, one can see that multithreading improves the performance of the software
considerably. From 1 threads to 8 threads, the real time keep decreasing while the user 
time increases. The time halfed if we are using 8 threads instead of 1. 