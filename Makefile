CC=gcc
CFLAGS=-march=native -fopenmp -O3
DEPS=

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

pi: pi.o
	$(CC) -o pi pi.o  $(CFLAGS)

mandel: mandel.o
	$(CC) -o mandel mandel.o  $(CFLAGS)

linked: linked.o
	$(CC) -o linked linked.o  $(CFLAGS)