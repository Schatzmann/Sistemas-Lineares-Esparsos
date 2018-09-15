CC = gcc

CFLAGS = -lm

objs = cgSolver.o functions.o

all: cgSolver

cgSolver: $(objs) $(CFLAGS)

cgSolver.o: cgSolver.c functions.o utils.h

functions.o: functions.c

clean:
	-rm -f $(objs) *~

purge: clean
		-rm -f cgSolver
