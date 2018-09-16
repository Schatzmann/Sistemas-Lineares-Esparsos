/*Autores:
Annelyse Schatzmann           GRR20151731
Eduardo Zimermam Pereira      GRR20152952  */

#include "functions.h"

int main(int argc, char **argv){
	srand(20182);

 	int dim, diag, maxIt, error;
 	double tipo, eps;
 	char arqSaida[256];

 	error = getLinhaComando(&dim, &diag, &tipo, &maxIt, &eps, arqSaida, argc, argv);

	if(error != -1){ 	
 		// double **matriz = geraMatrizA(diag, dim);
 		// double *vetor = geraB(diag, dim);

 		// if (tipo == 0.0){
 		// 	gradienteConjugado(matriz, vetor, maxIt, eps, dim);
 		// } else{
 		// 	if((tipo > 0.0)&&(tipo < 1.0)){
			// 	/*M = preCond_Jacobi(**matriz, dim, dim);
			// 	gradConj_comPreCondicionador(**matriz, *vetor, **M, maxIt, eps, dim);*/
			// }
 		// }

	 	return(0);	
	
	} else {
	
		printf("\n\nA EXECUÇÃO DO PROGRAMA FOI ABORTADA POR ERRO!!!\n\n");
	
		return(-1);
	
	}
}