/*Autores:
Annelyse Schatzmann           GRR20151731
Eduardo Zimermam Pereira      GRR20152952  */

#include "functions.h"

int main(int argc, char **argv){
 int dim, k, intr;
 float w, eps;
 char *arqSaida;

 dim = atoi(argv[2]);     // dimensão do Sistema Linear
 k = atoi(argv[4]);				// número de diagonais da matriz A
 w = atof(argv[6]);				// pré-condicionador a ser utilizado
 intr = atoi(argv[8]);    // número máximo de iterações a serem executadas

	double vetor[5] = {3, 8, 7, 9, 18};
  double **matriz = alocaMatriz(dim,dim);

	if (dim < 10){
 		printf("O valor da dimensão do Sistema Linear tem que ser maior que 10.\n");
 	}
 
 	if ((k % 2 == 0) || (k <= 1)){
 		printf("O número de diagonais da matriz A tem que ser maior que 1 e ímpar.\n");
 	}

 	if(!strcmp(argv[9], "-e")){
 		eps = atof(argv[10]);
 		arqSaida = argv[12];
 	}
 	else{
 		eps = 100;
 		arqSaida = argv[10];
 	}

 	if (w == 0.0){
 		gradienteConjugado(matriz, vetor, intr, eps, dim);
 	}
 	else{
 		if((w > 0.0)&&(w < 1.0)){
	/*	M = preCond_Jacobi(**matriz, dim, dim);
			gradConj_comPreCondicionador(**matriz, *vetor, **M, intr, eps, dim);*/
 		}
 	}


 return(0);	
}