/*Autores:
Annelyse Schatzmann           GRR20151731
Eduardo Zimermam Pereira      GRR20152952  */

#include "functions.h"
//#define EPS


double  jacobi (int dim){

	printf("Entrou Jacobi %d\n",dim);
}




int main(int argc, char **argv){
 int dim, k, intr;
 float w, eps;
 char *arqSaida;
 double *A;

 dim = atoi(argv[2]);     // dimensão do Sistema Linear
 k = atoi(argv[4]);				// número de diagonais da matriz A
 w = atof(argv[6]);				// pré-condicionador a ser utilizado
 intr = atoi(argv[8]);    // número máximo de iterações a serem executadas

	if (dim < 10){
 		printf("O valor da dimensão do Sistema Linear tem que ser maior que 10.\n");
 	}
 
 	if ((k % 2 == 0) || (k <= 1)){
 		printf("O número de diagonais da matriz A tem que ser maior que 1 e ímpar.\n");
 	}


 	if (w == 0.0){
 		//  sem pré-condicionador
 		printf("SEM pré-condicionador\n");
 	}
 	else{
 		if((w > 0.0)&&(w < 1.0)){
			//pré-condicionador de Jacobi
			jacobi(dim);
 		}
 	}

 	if(!strcmp(argv[9], "-e")){
 		eps = atof(argv[10]);
 		arqSaida = argv[12];
 	}
 	else
 		arqSaida = argv[10];

 return(0);	
}

