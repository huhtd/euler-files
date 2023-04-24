CC=mpicc
CFLAGS=-O3 -lm

all: powermethod

powermethod: powermethod_euler.c hpc-power.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f powermethod
