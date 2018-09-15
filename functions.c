/*Autores:
Annelyse Schatzmann           GRR20151731
Eduardo Zimermam Pereira      GRR20152952  */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "functions.h"

/***********************
 * Função que gera os coeficientes de um sistema linear k-diagonal
 * i,j: coordenadas do elemento a ser calculado (0<=i,j<n)
 * k: numero de diagonais da matriz A
 ***********************/
inline double generateRandomA( unsigned int i, unsigned int j, unsigned int k){
  static double invRandMax = 1.0 / (double)RAND_MAX;
  return ( (i==j)?(double)(k<<1) : 1.0 )  * (double)rand() * invRandMax;
}

/***********************
 * Função que gera os termos independentes de um sistema linear k-diagonal
 * k: numero de diagonais da matriz A
 ***********************/
inline double generateRandomB( unsigned int k )
{
  static double invRandMax = 1.0 / (double)RAND_MAX;
  return (double)(k<<2) * (double)rand() * invRandMax;
}


double** alocaMatriz(int linhas, int colunas){
	double **matriz;

	matriz = (double**) malloc(linhas * sizeof(double*));

	for(int i = 0; i < linhas; i++){
			matriz[i] = (double*) malloc(colunas * sizeof(double));
	}

	for(int i = 0; i < linhas; i++){
		for(int j = 0; j < colunas; j++){
			matriz[i][j] = 0;
		}
	}

	return matriz;
}

void printMatriz(double** matriz, int linhas, int colunas){
	for (int i = 0; i < linhas; i++){
		for(int j = 0; j < colunas; j++){
			printf("%.15g ", matriz[i][j]);
		}
		printf("\n");
	}
}

double* alocaVetor(int tamVetor){

	double *vetorSaida = malloc(tamVetor * sizeof(double));

 return(vetorSaida);
}

double* copiaVetor(double* vetorA, int tamVetor){
	double* aux;

	aux = vetorA;

	return(aux);
}

double produtoInterno_vetor(double *vetorA, double *vetorB, int tamVetor){
 double escalar;

  for(int i=0; i<tamVetor; i++){
 		escalar += (vetorA[i] * vetorB[i]);
 	}

 return(escalar);
}

double* multiplica_escalarVetor(double *vetorA, double escalar, int tamVetor, double *vetorSaida){

  for(int i=0; i<tamVetor; i++){
 		vetorSaida[i]= (vetorA[i] * escalar);
 	}
}

double* soma_vetor(double *vetorA, double *vetorB, int tamVetor, double *vetorSaida){

  for(int i=0; i<tamVetor; i++){
 		vetorSaida[i]= (vetorA[i] + vetorB[i]);
 	}
}

double* subtrai_vetor(double *vetorA, double *vetorB, int tamVetor, double *vetorSaida){

  for(int i=0; i<tamVetor; i++){
 		vetorSaida[i]= (vetorA[i] - vetorB[i]);
 	}
}


double* multiplica_matriz_vetor(double **matriz, double *vetorA, int tamVetor, double *vetorSaida){

  for(int i=0; i<tamVetor; i++){
  	for(int j=0; j<tamVetor; j++){
  		vetorSaida[i]+= (matriz[i][j] * vetorA[j]);
  	}
  }
}

double* gradienteConjugado(double **matriz, double *vetor, double MaxIt, double eps, int tamVetor){
	double *X, *z, *r, *v, *vet_aux, escalar, aux1;

	X = alocaVetor(tamVetor);
	z = alocaVetor(tamVetor);
	vet_aux = alocaVetor(tamVetor);

	r = copiaVetor(vetor, tamVetor);
	v = copiaVetor(vetor, tamVetor);

	double aux = produtoInterno_vetor(r, r, tamVetor);

	for(int itr = 0; itr < MaxIt; itr++){
		multiplica_matriz_vetor(matriz, v, tamVetor, z);
		escalar = produtoInterno_vetor(v, z, tamVetor);
		double s = aux / escalar;
		multiplica_escalarVetor(v, s, tamVetor, vet_aux);
		soma_vetor(X, vet_aux, tamVetor, X);

		multiplica_matriz_vetor(matriz, X, tamVetor, vet_aux);
		subtrai_vetor(vetor, vet_aux, tamVetor, r);

		for(int i = 0; i < tamVetor; i++){
			aux1 += r[i];
		}

		aux1 = sqrt(aux1);

		if(aux1 < eps){
			return(X);
		}

		double m = aux1/aux;
		aux = aux1;
		printf("%lf\n", aux);

		multiplica_escalarVetor(v, m, tamVetor, vet_aux);
		soma_vetor(r, vet_aux, tamVetor, v);
	}
}

double** preCond_Jacobi(double** matriz, int linhas, int colunas){
	double **matrizPreCond = (double**) malloc(linhas * sizeof(double**));

	for (int i = 0; i < linhas; i++) {
		matrizPreCond[i] = (double*) malloc(colunas * sizeof(double*));
	}


	for (int i = 0; i < linhas; i++) {
		for (int j = 0; j < colunas; j++) {
			matrizPreCond[i][j] = 0;
		}
	}

	for (int i = 0; i < linhas; i++) {
		matrizPreCond[i][i] = matriz[i][i];
	}

	return (matrizPreCond);
}

double* gradConj_comPreCondicionador(double **matriz, double *vetor, double **M, double MaxIt, double eps, int tamVetor){
	double *X, *y, *z, *r, *v, *vet_aux, escalar, aux1;

  X = alocaVetor(tamVetor);
  v = alocaVetor(tamVetor);
  y = alocaVetor(tamVetor);
	z = alocaVetor(tamVetor);
	vet_aux = alocaVetor(tamVetor);

	r = copiaVetor(vetor, tamVetor);
	multiplica_matriz_vetor(M, vetor, tamVetor, v);  /* v = (M*b) */
	multiplica_matriz_vetor(M, r, tamVetor, y);			/* y = (M*r) */

	double aux = produtoInterno_vetor(y, r, tamVetor);

	for(int itr = 0; itr < MaxIt; itr++){
		multiplica_matriz_vetor(matriz, v, tamVetor, z);
		escalar = produtoInterno_vetor(v, z, tamVetor);
		double s = aux / escalar;

		multiplica_escalarVetor(v, s, tamVetor, vet_aux);
		soma_vetor(X, vet_aux, tamVetor, X);

		multiplica_matriz_vetor(matriz, X, tamVetor, vet_aux);
		subtrai_vetor(vetor, vet_aux, tamVetor, r);

		multiplica_matriz_vetor(M, r, tamVetor, y);			/* y = (M*r) */

		for(int i = 0; i < tamVetor; i++){
			aux1 += r[i];
		}

		aux1 = sqrt(aux1);

		if(aux1 < eps){
			return(X);
		}

		aux1 = produtoInterno_vetor(y, r, tamVetor);

		double m = aux1 / aux;
		aux = aux1;

		multiplica_escalarVetor(v, m, tamVetor, vet_aux);
		soma_vetor(y, vet_aux, tamVetor, v);
	}
}

double** geraMatrizA(int k_diag, int dim){
		double** matriz = alocaMatriz(dim, dim);
		int divK = k_diag / 2;

		for (int i = 0; i < dim; i++) {
				for (int j = 0; j < dim; j++) {
					if(fabs(i-j) <= divK){
							matriz[i][j] = generateRandomA(i, j, k_diag);
					}
				}
		}

		return matriz;
}

double* geraB(int k_diag, int dim){
	double* vetorB;

	vetorB = (double*) malloc(dim * sizeof(double));

	for (int i = 0; i < dim; i++) {
		vetorB[i] = generateRandomB(k_diag);
	}

	return vetorB;
}
