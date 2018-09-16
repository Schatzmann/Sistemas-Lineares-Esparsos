/*Autores:
Annelyse Schatzmann           GRR20151731
Eduardo Zimermam Pereira      GRR20152952  */

#include "functions.h"

int main(int argc, char **argv){
	srand(20182);

 	int dim, diag, maxIt, error, contIter;
 	double tipo, eps, *iterX, tempoResiduo, tempoIteracao, tempoPC, residuo;
 	char arqSaida[256];


 	error = getLinhaComando(&dim, &diag, &tipo, &maxIt, &eps, arqSaida, argc, argv);


	if(error != -1){ 	

		double **matriz = geraMatrizA(diag, dim);
 		double *vetor = geraB(diag, dim);

 		tempoPC = timestamp();

		iterX = alocaVetor(dim);

 		if (tipo == 0.0){
 			gradienteConjugado(matriz, vetor, maxIt, eps, dim, &contIter, iterX, &tempoResiduo, &tempoIteracao, &residuo);
 		} else{
 			if((tipo > 0.0)&&(tipo < 1.0)){
				double** M = preCond_Jacobi(matriz, dim, dim);
				gradConj_comPreCondicionador(matriz, vetor, M, maxIt, eps, dim, &contIter, iterX, &tempoResiduo, &tempoIteracao, &residuo);
			}
 		}

 		tempoPC = fabs(timestamp() - tempoPC);


	 	escreveSaida(arqSaida, contIter, iterX, residuo, tempoPC, tempoIteracao, tempoResiduo);

		return(0);	
	
	} else {
	
		printf("\n\nA EXECUÇÃO DO PROGRAMA FOI ABORTADA POR ERRO!!!\n\n");
	
		return(-1);
	
	}
}