/*Annelyse Schatzmann           GRR20151731
Eduardo Zimermam Pereira      GRR20152952  */

#ifndef __FUNCTIONS__
#define __FUNCTIONS__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


double** alocaMatriz(int, int);
double multiplica_matriz();
double  jacobi (int dim);
double gradienteConjugado(double**, double*, int, double);



/* 
double  jacobi (double  *A, double *B,  double *X,  int n, double *tIteracao, double *tTotal);
double sem_préCondicionador(double  *A, double *b, double *MaxIt, double eps);
ouble com_préCondicionador(double  *A, double *b, double *M, double *MaxIt, double eps){

#endif