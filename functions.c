/*Autores:
Annelyse Schatzmann           GRR20151731
Eduardo Zimermam Pereira      GRR20152952  */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "functions.h"

double** alocaMatriz(int linhas, int colunas){
	double **matriz;

	matriz = (double**) malloc((linhas*colunas) * sizeof(double));

	for(int i = 0; i < linhas; i++){
		matriz[i] = matriz[i * linhas];
	}

	return matriz;
}


double multiplica_matriz(){
 int i, j, k, linA, colA, linB, colB;

	for(i= 0; i < linA; i++){
		for(j= 0; j < colB; j++){
			matrizC[i][j]=0;
			for(k= 0; k < colA; k++){          //colA = linB
				aux += (matrizA[i][k] * matrizB[k][j]);
	    }
	    matrizC[i][j]= aux;
	    aux= 0;
		}
	}

	return(matrizC)
}



double sem_préCondicionador(double  *A:matriz, double *b:vetor, double *MaxIt, double eps){
 
	double r = b; v = b;
	double aux = produtoInterno_vetor(r,r);
	X = 0;

	for(int itr= 0; itr < MaxIt; itr++){
		z = multiplica_matriz_vetor(A, v);
		escalar =  produtoInterno_vetor(v, z);
		double s = aux / escalar;

		vetor = multiplica_escalarVetor (s, v);
		X = soma_vetor(X, vetor);

		vetor = multiplica_escalarVetor(s, z);
		r = subtrai_Vetor(r, vetor);
		aux1 = produtoInterno_vetor(r,r);

		if(aux1 < eps){
			return(x)
		}

		m = aux1/aux;
		aux = aux1;

		vetor = multiplica_escalarVetor(m, v);
		v = soma_Vetor(r, vetor);
	}
}


double com_préCondicionador(double  *A, double *b, double *M, double *MaxIt, double eps){
 
	double r = b; v = b;
	X = 0;
	MI = inversa(M);
	v = multiplica_matriz_vetor(MI, b);	
	y = multiplica_matriz_vetor(MI, r);
	aux = multiplica_vetor(y,r);

	for(int itr= 0; itr < MaxIt; itr++){
		z = multiplica_matriz_vetor(A, v);
		
		double multi_aux =  multiplica_vetor(v, z);
		s = aux / multi_aux;
		
		multi_aux = multiplica_matriz(s, v);
		X = (X + multi_aux);


		r = r - multiplica_matriz(s, z);
		y = multiplica_matriz(MI, r);
		rT = transposta(r);
		multi_aux = multiplica_matriz(rT, r);

		if(multi_aux < eps){
			return(x)
		}

		yT = transposta(y);
		aux1 = multiplica_matriz(yT, r);
		m = aux1/aux ;
		aux = aux1;
		v = y + (multiplica_matriz(m, v));
	}



double gradienteConjugado(double **matriz, double *b, int maxIt, double eps){


}


