/*Annelyse Schatzmann           GRR20151731
Eduardo Zimermam Pereira      GRR20152952  */

#ifndef __FUNCTIONS__
#define __FUNCTIONS__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


double** alocaMatriz(int, int);
double* alocaVetor(int);
double* copiaVetor(double*, int)
double produtoInterno_vetor(double*, double*, int);
double* multiplica_escalarVetor(double*, double, int, double*);
double* soma_vetor(double*, double*, int, double*);
double* subtrai_vetor(double*, double*, int, double*);
double* multiplica_matriz_vetor(double**, double*, int, double*);

double gradienteConjugado(double**, double*, double*, double);
double gradConj_comPreCondicionador(double**, double*, double*, double);


#endif