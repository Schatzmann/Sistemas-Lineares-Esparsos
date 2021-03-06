/**
 * @author  Annelyse Schatzmann           GRR20151731
 * @author  Eduardo Zimermam Pereira      GRR20152952  
*/

/**
 * @file cgSolver.c
 * @brief Programa principal.
*/


#include "functions.h"

int main(int argc, char **argv){
	srand(20182);

 	int dim, diag, maxIt, error, contIter;
 	double tipo, eps, *iterX, *X_new, tempoResiduo, tempoIteracao, tempoPC, residuo, *Mtransp, *matrizNew;
 	char arqSaida[256];


 	error = getLinhaComando(&dim, &diag, &tipo, &maxIt, &eps, arqSaida, argc, argv);


	if(error != -1){ 	

		double *matriz = geraMatrizA(diag, dim);
 		double *vetor = geraB(diag, dim);

 		double *matrizNew = alocaMatriz(dim, dim);
 		double *vetorNew = alocaVetor(dim);

 		Mtransp = matrizTransposta(matriz, dim);

 		matriz_por_matriz(Mtransp, matriz, dim, matrizNew);
		multiplica_matriz_vetor(matrizNew, vetor, dim, vetorNew);
		
		iterX = alocaVetor(dim);
		X_new = alocaVetor(dim);

 		if (tipo == 0.0){
 			tempoPC = timestamp();
 			X_new = gradienteConjugado(matrizNew, vetorNew, maxIt, eps, dim, &contIter, iterX, &tempoIteracao);
 			tempoPC = fabs(timestamp() - tempoPC);
 		} else{
 			if((tipo > 0.0)&&(tipo < 1.0)){
 				tempoPC = timestamp();
				double* M = preCond_Jacobi(matrizNew, dim, dim);
				X_new = gradConj_comPreCondicionador(matrizNew, vetorNew, M, maxIt, eps, dim, &contIter, iterX, &tempoIteracao);
 				tempoPC = fabs(timestamp() - tempoPC);
			}
 		}

 		if(X_new == NULL){
 			printf("\nERRO: O método não convergiu.\n");
 		}else{
 			calcResiduo(matriz, vetor, dim, X_new, &tempoResiduo, &residuo);
 			escreveSaida(arqSaida, contIter, iterX, residuo, tempoPC, tempoIteracao, tempoResiduo, dim, X_new);
	 	}

		return(0);	
	
	} else {
	
		printf("\n\nA EXECUÇÃO DO PROGRAMA FOI ABORTADA POR ERRO!!!\n\n");
	
		return(-1);
	
	}
}