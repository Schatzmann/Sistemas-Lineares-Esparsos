/**
 * @author  Annelyse Schatzmann           GRR20151731
 * @author  Eduardo Zimermam Pereira      GRR20152952  
 */

/**
 * @file functions.c
 * @brief Todas as funções utilizadas nos métodos.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "functions.h"
#include <string.h>

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

/**
 * @brief Lê a linha de comando de forma dinâmica.
 * @param dim     Dimensão do Sistema Linear.
 * @param diag    Número de Diagonais da Matriz.
 * @param tipo    Pré Condicionador a ser utilizado. 
 * @param maxIt   Máximo de iterações a serem executadas.
 * @param eps     Erro Aproximado Absoluto Máximo. 
 * @param arqDEst Caminho da solução.
 * @param argc    Número de argumentos da linha de comando.
 * @param argv    Vetor de argumentos da linha de comando.
 * @return Retorna os valores passados por entrada padrão.
 *
 * Considera todas as condições de entrada das variáveis.
 */
int getLinhaComando(int* dim, int* diag, double* tipo, int* maxIt, double* eps, char* arqDest, int argc, char **argv){

  char  *aux;

  //Definição de valores default para as váriaveis.
  *dim = -1;  
  *diag = -1; 
  *tipo = -1; 
  *maxIt = -1; 
  *eps = -1;


	for(int i = 1; i < argc; i += 2){
		if (strcmp(argv[i], "-n") == 0) {				
			*dim = atoi(argv[i+1]);		
		}
		else if (strcmp(argv[i], "-k") == 0 ){
				*diag =atoi(argv [i+1]);
			}
			else if (strcmp(argv[i], "-p") == 0) {				
					*tipo = strtod(argv[i+1], &aux);
				}
				else if (strcmp(argv[i], "-i") == 0 ){
						*maxIt = strtod(argv[i+1], &aux);
					}
					else if (strcmp(argv[i], "-e") == 0 ){		
							*eps = atof(argv[i+1]);
						}
						else if (strcmp(argv[i], "-o") == 0 ){
								strcpy(arqDest, argv [i+1]);
							}
	}	

	if (*dim != -1){
		if (*dim < 10)
 			printf("ERRO: o valor da dimensão do Sistema Linear tem que ser maior que 10.\n");
 	} else {
		printf("ERRO: falta o parâmetro obrigatório -n (dimensão do Sistema Linear)\n");
	 	return (-1);
	}

	if (*diag != -1){
		if ((*diag % 2 == 0) || (*diag <= 1))
 			printf("ERRO: o número de diagonais da matriz A tem que ser maior que 1 e ímpar.\n");
 	} else {
		printf("ERRO: falta o parâmetro obrigatório -k (número de diagonais da matriz A)\n");
	 	return (-1);	
	}

	if (*tipo == -1){
		printf("ERRO: falta o parâmetro obrigatório -p (pré-condicionador a ser utilizado)\n");
	 	return (-1);	
	}

	if (*maxIt == -1){
		printf("ERRO: falta o parâmetro obrigatório -i (número máximo de iterações a serem executadas)\n");
	 	return (-1);	
	}

	if (! arqDest){
		printf("ERRO: falta o parâmetro obrigatório -o (arquivo de saída)\n");
	 	return (-1);	
	}

	if(*eps == -1){
		*eps = 1.0e-8;
	}	
 
 return 0;
}

/**
 * @brief Alocação dinâmica de matriz.
 * @param linhas   Quantidade de linhas da matriz.
 * @param colunas  Quantidade de colunas da matriz.
 * @return Retorna uma matriz alocada.
 */
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

/**
 * @brief Printa uma matriz.
 * @param matriz   Matriz a ser impressa.
 * @param linhas   Quantidade de linhas da matriz.
 * @param colunas  Quantidade de colunas da matriz.
 * @return Imprime na tela a matriz passada.
 */
void printMatriz(double** matriz, int linhas, int colunas){
	for (int i = 0; i < linhas; i++){
		for(int j = 0; j < colunas; j++){
			printf("%.15g ", matriz[i][j]);
		}
		printf("\n");
	}
}


/**
 * @brief Alocação dinâmica de um Vetor.
 * @param tamVetor  Tamanho do vetor a ser alocado.
 * @return Retorna um vetor alocado.
 */
double* alocaVetor(int tamVetor){

	double *vetorSaida = malloc(tamVetor * sizeof(double));
	for (int i = 0; i < tamVetor; ++i){
		vetorSaida[i] = 0;
	}

 return(vetorSaida);
}


/**
 * @brief Copia um vetor existente para um novo.
 * @param vetorA    Vetor a ser copiado.
 * @param tamVetor  Tamanho do vetor a ser copiado.
 * @return Retorna um vetor copia do vetor que foi passado no parâmetro.
 */
double* copiaVetor(double* vetorA, int tamVetor){
	double* aux = alocaVetor(tamVetor);

	for (int i = 0; i < tamVetor; ++i){
		aux[i] = vetorA[i];
	}

	return(aux);
}


/**
 * @brief Produto interno entre dois vetores.
 * @param vetorA    Vetor a ser multiplicado.
 * @param vetorB    Vetor a ser multiplicado.
 * @param tamVetor  Tamanho do vetor.
 * @return Retorna um escalar resultante do Produto Interno.
 */
double produtoInterno_vetor(double *vetorA, double *vetorB, int tamVetor){
 double escalar;

  for(int i=0; i<tamVetor; i++){
 		escalar += (vetorA[i] * vetorB[i]);
 	}

 return(escalar);
}

/**
 * @brief Multiplica um vetor por um Escalar.
 * @param vetorA     Vetor a ser multiplicado.
 * @param escalar    Número a ser multiplicado pelo vetor.
 * @param tamVetor   Tamanho do vetor.
 * @param vetorSaida Vetor contendo a saída da função.
 * @return Retorna um vetor resultante da multiplicação entre um vetor e um escalar.
 */
double* multiplica_escalarVetor(double *vetorA, double escalar, int tamVetor, double *vetorSaida){

  for(int i=0; i<tamVetor; i++){
 		vetorSaida[i]= (vetorA[i] * escalar);
 	}
}


/**
 * @brief Soma de dois vetores.
 * @param vetorA     Vetor a ser somado.
 * @param vetorB     Vetor a ser somado.
 * @param tamVetor   Tamanho do vetor.
 * @param vetorSaida Vetor contendo a saída da função.
 * @return Retorna um vetor resultante da soma entre dois vetores.
 */
double* soma_vetor(double *vetorA, double *vetorB, int tamVetor, double *vetorSaida){

  	for(int i=0; i<tamVetor; i++){
 		vetorSaida[i]= (vetorA[i] + vetorB[i]);
 	}
}

/**
 * @brief Subtração de dois vetores.
 * @param vetorA     Vetor a ser subtraido.
 * @param vetorB     Vetor a ser subtraido.
 * @param tamVetor   Tamanho do vetor.
 * @param vetorSaida Vetor contendo a saída da função.
 * @return Retorna um vetor resultante da subtração entre dois vetores.
 */
double* subtrai_vetor(double *vetorA, double *vetorB, int tamVetor, double *vetorSaida){

  for(int i=0; i<tamVetor; i++){
 		vetorSaida[i]= (vetorA[i] - vetorB[i]);
 	}
}

/**
 * @brief Multiplicação de uma matriz com um vetor.
 * @param matriz     matriz a ser multiplicada.
 * @param vetorB     Vetor a ser multiplicado.
 * @param tamVetor   Tamanho do vetor.
 * @param vetorSaida Vetor contendo a saída da função.
 * @return Retorna um vetor resultante da multiplicação entre uma matriz e um vetor.
 */
double* multiplica_matriz_vetor(double **matriz, double *vetorA, int tamVetor, double *vetorSaida){

  for(int i=0; i<tamVetor; i++){
  	for(int j=0; j<tamVetor; j++){
  		vetorSaida[i]+= (matriz[i][j] * vetorA[j]);
  	}
  }
}

double* gradienteConjugado(double **matriz, double *vetor, int MaxIt, double eps, int tamVetor, int *contIter, double *iterX, double *tempoResiduo, double *tempoIteracao, double *residuo){
	double *X_new, *X_old, *z, *r, *v, *vet_aux, escalar, aux1;

	int contIterAux = 0;

	X_new = alocaVetor(tamVetor);
	X_old = alocaVetor(tamVetor);
	z = alocaVetor(tamVetor);
	vet_aux = alocaVetor(tamVetor);

	r = copiaVetor(vetor, tamVetor);
	v = copiaVetor(vetor, tamVetor);

	double aux = produtoInterno_vetor(r, r, tamVetor);

	*tempoIteracao = timestamp();
	
	for(int itr = 0; itr < MaxIt; itr++){
        
		multiplica_matriz_vetor(matriz, v, tamVetor, z);
		escalar = produtoInterno_vetor(v, z, tamVetor);
		double s = aux / escalar;
		multiplica_escalarVetor(v, s, tamVetor, vet_aux);
		soma_vetor(X_old, vet_aux, tamVetor, X_new);

		*tempoResiduo = timestamp();

		multiplica_matriz_vetor(matriz, X_new, tamVetor, vet_aux);
		subtrai_vetor(vetor, vet_aux, tamVetor, r);

		for(int i = 0; i < tamVetor; i++){
			aux1 += r[i];
		}

		aux1 = sqrt(fabs(aux1));

		*tempoResiduo = fabs(timestamp() -  *tempoResiduo);

		contIterAux++;
		subtrai_vetor(X_new, X_old, tamVetor, vet_aux);
		iterX[itr] = maxVetor(vet_aux, tamVetor);

		if(aux1 < eps){
			*tempoIteracao = fabs(timestamp() -  *tempoIteracao);
			*contIter = contIterAux;
			*residuo = aux1;
			return(X_new);
		}

		double m = aux1/aux;
		aux = aux1;

		multiplica_escalarVetor(v, m, tamVetor, vet_aux);
		soma_vetor(r, vet_aux, tamVetor, v);
	}

	*tempoIteracao = fabs(timestamp() -  *tempoIteracao);
	*contIter = contIterAux;
	*residuo = aux1;
	return(-1);
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

double* gradConj_comPreCondicionador(double **matriz, double *vetor, double **M, int MaxIt, double eps, int tamVetor, int *contIter, double *iterX, double* tempoResiduo, double* tempoIteracao, double* residuo){
	double *X_new, *X_old, *y, *z, *r, *v, *vet_aux, escalar, aux1;
	
	int contIterAux = 0;

	X_new = alocaVetor(tamVetor);
	X_old = alocaVetor(tamVetor);

  	v = alocaVetor(tamVetor);
 	y = alocaVetor(tamVetor);
	z = alocaVetor(tamVetor);
	vet_aux = alocaVetor(tamVetor);

	r = copiaVetor(vetor, tamVetor);
	multiplica_matriz_vetor(M, vetor, tamVetor, v);  /* v = (M*b) */
	multiplica_matriz_vetor(M, r, tamVetor, y);			/* y = (M*r) */

	double aux = produtoInterno_vetor(y, r, tamVetor);
	
	*tempoIteracao = timestamp();

	for(int itr = 0; itr < MaxIt; itr++){
		multiplica_matriz_vetor(matriz, v, tamVetor, z);
		escalar = produtoInterno_vetor(v, z, tamVetor);
		double s = aux / escalar;

		multiplica_escalarVetor(v, s, tamVetor, vet_aux);
		soma_vetor(X_old, vet_aux, tamVetor, X_new);

		*tempoResiduo = timestamp();

		multiplica_matriz_vetor(matriz, X_new, tamVetor, vet_aux);
		subtrai_vetor(vetor, vet_aux, tamVetor, r);

		multiplica_matriz_vetor(M, r, tamVetor, y);			/* y = (M*r) */

		for(int i = 0; i < tamVetor; i++){
			aux1 += r[i];
		}

		aux1 = sqrt(fabs(aux1));

		*tempoResiduo = fabs(timestamp() -  *tempoResiduo);

		contIterAux++;
		subtrai_vetor(X_new, X_old, tamVetor, vet_aux);
		iterX[itr] = maxVetor(vet_aux, tamVetor);

		if(aux1 < eps){
			*tempoIteracao = fabs(timestamp() -  *tempoIteracao);
			*contIter = contIterAux;
			*residuo = aux1;
			return(X_new);
		}

		aux1 = produtoInterno_vetor(y, r, tamVetor);

		double m = aux1 / aux;
		aux = aux1;

		multiplica_escalarVetor(v, m, tamVetor, vet_aux);
		soma_vetor(y, vet_aux, tamVetor, v);
	}

	*tempoIteracao = fabs(timestamp() -  *tempoIteracao);
	*contIter = contIterAux;
	*residuo = aux1;
	return (-1);
}

double maxVetor(double* vetorA, int tamVetor){
	double max = vetorA[0];

	for (int i = 1; i < tamVetor; ++i){
		if(vetorA[i] > max){
			max = vetorA[i];
		}
	}

	return fabs(max);
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

void escreveSaida(char* arqSaida, int contIter, double* iterX, double residuo, double tempo_pc, double tempo_itr, double tempo_res){

	FILE *arq;

	arq = fopen(arqSaida, "w");

	if(!arq){
		
		printf("ERRO: erro ao abrir arquivo.\n");

	} else {
	
		fprintf(arq, "# ans15  Annelyse Schatzmann\n");
		fprintf(arq, "# ezp15  Eduardo Zimermam Pereira\n");
		
		fprintf(arq, "# \n");


		for(int i = 0; i <  contIter; i++){
			fprintf(arq, "# iter [%d]: %.15g\n", i, iterX[i]);
		}

		fprintf(arq, "# \n");

		fprintf(arq, "# residuo: %.15g\n", fabs(residuo));
		fprintf(arq, "# Tempo PC: %.15g\n", tempo_pc);
		fprintf(arq, "# Tempo iter: %.15g\n", tempo_itr);
		fprintf(arq, "# Tempo residuo: %.15g\n", tempo_res);

		fclose(arq);
	}
}
