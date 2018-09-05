CC = gcc -g

objs = cgSolver.o

all: cgSolver

cgSolver: $(objs)

cgSolver.o: cgSolver.c functions.h utils.h

clean: 
	-rm -f $(objs) *~

purge: clean
		-rm -f cgSolver