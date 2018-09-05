/*Autores:
Annelyse Schatzmann           GRR20151731
Eduardo Zimermam Pereira      GRR20152952  */

#include "functions.h"


double** alocaMatriz(int linhas, int colunas){
	double **matriz;

	matriz = (double**) malloc((linhas*colunas) * sizeof(double));

	for(int i = 0; i < linhas; i++){
		matriz[i] = matriz[i * linhas];
	}

	return matriz;
}

double gradienteConjugado(double **matriz, double *b, int maxIt, double eps){

}