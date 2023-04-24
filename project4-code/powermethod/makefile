CC=mpicc
CFLAGS=-O3

all: powermethod

powermethod: powermethod_euler.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f powermethod
