CC = gcc -g

CFLAGS = -lm

objs = cgSolver.o functions.o utils.o

all: cgSolver

cgSolver: $(objs) $(CFLAGS)

utils.o: utils.c

functions.o: functions.c

cgSolver.o: cgSolver.c utils.o functions.o

clean:
	-rm -f $(objs) *~

purge: clean
		-rm -f cgSolver
