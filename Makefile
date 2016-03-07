MPICC = mpicxx
CFLAGS = -Wall -O2

PROGS = a02p02

all: $(PROGS)

a02p02: a02p02.cpp
	$(MPICC) -o a02p02 a02p02.cpp

clean:
	rm -f $(PROGS) *~*.o*
