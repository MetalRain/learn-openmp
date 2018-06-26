CC=gcc
CFLAGS=-march=native -fopenmp -O3
DEPS=

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

openmp: main.o
	$(CC) -o openmp main.o  $(CFLAGS)