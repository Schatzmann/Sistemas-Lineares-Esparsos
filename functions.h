/**
 *  @author Annelyse Schatzmann           GRR20151731
 *  @author Eduardo Zimermam Pereira      GRR20152952
 */

/**
 * @file functions.h
 * @brief Todas as funções utilizadas nos métodos.
 */

#ifndef __FUNCTIONS__
#define __FUNCTIONS__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "utils.h"

double somaElem(double*, int);
double* alocaMatriz(int, int);
void printMatriz(double* , int , int);
double* alocaVetor(int);
double* copiaVetor(double*, int);
double produtoInterno_vetor(double*, double*, int);
double* multiplica_escalarVetor(double*, double, int, double*);
double* soma_vetor(double*, double*, int, double*);
double* subtrai_vetor(double*, double*, int, double*);
double* multiplica_matriz_vetor(double*, double*, int, double*);
double* geraMatrizA(int, int);
double* geraB(int, int);
int getLinhaComando(int*, int*, double*, int*, double*, char*, int, char**);
void escreveSaida(char*, int, double*, double, double, double, double, int, double*);
double maxVetor(double*, int);
void calcResiduo(double*, double*, int, double*, double*, double*);
double* matrizTransposta(double*, int);
void matriz_por_matriz(double*, double*, int, double*);


double* preCond_Jacobi(double*, int, int);
double* gradienteConjugado(double*, double*, int, double, int, int*, double*, double*);
double* gradConj_comPreCondicionador(double*, double*, double*, int, double, int, int*, double*, double*);

#endif
