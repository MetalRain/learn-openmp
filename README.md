# Learn OpenMP

Learning parallel processing with OpenMP using Intel video series as base.

## Materials

Playlist:
https://www.youtube.com/playlist?list=PLLX-Q6B8xqZ8n8bwjGdzBJ25X2utwnoEG

Exercise files:
https://github.com/lat/esc/tree/master/exercises/openmp

## Building

Choose which parts to compile
```
$ make pi
$ make mandel
$ make prod-cons
$ make random
```

## Running

Control number of threads with environnment variables
```
$ export OMP_NUM_THREADS=4
```

Run compiled code
```
$ ./pi
PI: 3.14159 took 0.032234 seconds

$ ./mandel
Area of Mandlebrot set =   1.51214625 +/-   0.00151215

$ ./prod_cons
 In 0.000372 seconds, The sum is 5030.674031

$ ./random
 In 0.000372 seconds, The sum is 5030.674031
```