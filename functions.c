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


double* alocaVetor(int tamVetor){
	
	double *vetorSaida = malloc(tamVetor * sizeof(double));

 return(vetorSaida);
}

double* copiaVetor(double* vetorA, int tamVetor){
	double* aux = alocaVetor(tamVetor);

	for (int i = 0; i < tamVetor; ++i){
		aux[i] = vetorA[i];
	}

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


double gradienteConjugado(double **matriz, double *vetor, double *MaxIt, double eps, int tamVetor){
	double *X, *z, *r, *v;

  X = alocaVetor(tamVetor);
	z = alocaVetor(tamVetor);

	r = copiaVetor(vetor, tamVetor);
	v = copiaVetor(vetor, tamVetor);
	double aux1;
	double aux = produtoInterno_vetor(r,r);
	

	for(int itr= 0; itr < MaxIt; itr++){
		z[é vetor]= multiplica_matriz_vetor(matriz, v);
		escalar =  produtoInterno_vetor(v, z);
		double s = aux / escalar;

		vetor = multiplica_escalarVetor(s, v);
		X[é vetor]= soma_vetor(X, vetor);

		vetor = multiplica_escalarVetor(s, z);
		r = subtrai_vetor(r, vetor);
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


double gradConj_comPreCondicionador(double **matriz, double *vetor, double *MaxIt, double eps){
 
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


