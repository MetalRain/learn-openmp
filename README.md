# Learn OpenMP

Learning parallel processing with OpenMP using Intel video series as base.

https://www.youtube.com/playlist?list=PLLX-Q6B8xqZ8n8bwjGdzBJ25X2utwnoEG

https://github.com/lat/esc/tree/master/exercises/openmp

## Building

```
$ make
gcc -c -o main.o main.c -march=native -fopenmp -O3
gcc -o openmp main.o  -march=native -fopenmp -O3
```

## Running
```
$ time ./openmp 1
PI: 3.14159 took 1.02759us using 1 threads

real  0m0.116s
user  0m0.111s
sys 0m0.004s

$ time ./openmp 2
PI: 3.14159 took 1.02958us using 2 threads

real  0m0.060s
user  0m0.111s
sys 0m0.008s

$ time ./openmp 3
PI: 3.14159 took 1.03255us using 3 threads

real  0m0.041s
user  0m0.104s
sys 0m0.016s

$ time ./openmp 4
PI: 3.14159 took 1.03405us using 4 threads

real  0m0.034s
user  0m0.103s
sys 0m0.016s

$ time ./openmp 5
PI: 3.14159 took 1.03544us using 5 threads

real  0m0.037s
user  0m0.109s
sys 0m0.008s
```