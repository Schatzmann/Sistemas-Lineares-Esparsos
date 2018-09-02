/*Autores:
Annelyse Schatzmann           GRR20151731
Eduardo Zimermam Pereira      GRR20152952  */

#include "cgSolver.h"
//#define EPS



int main(int argc, char **argv){
 int dim,k,i;
 float w,eps;
 char *arqSaida;

 char *ret;
 char ch = 'n';


 dim = atoi(argv[2]);
 k = atoi(argv[4]);
 w = atof(argv[6]);

	if (dim < 10){
 		printf("O valor da dimensão do Sistema Linear tem que ser maior que 10.\n");
 	}
 
 	if ((k % 2 == 0) || (k <= 1)){
 		printf("O número de diagonais da matriz A tem que ser maior que 1 e ímpar.\n");
 	}




 printf("%f\n", w);
 	
	

	if(strcmp(argv[9], "-e")){
 		// eps = double(argv[10]);
 		arqSaida = argv[12];
 	}
 	else
 		arqSaida = argv[10];


/*
 cgSolver -n <n> -k <k> -p <ω> -i <i> -e <ε> -o <arquivo_saida> */
	 	



 return(0);	
}
/*

<n>: (n>10) parâmetro obrigatório definindo a dimensão do Sistema Linear.
<k>: (k>1 e k ímpar)  parâmetro obrigatório definindo o número de diagonais da matriz A.
<ω>:  parâmetro obrigatório indicando o pré-condicionador a ser utilizado:
ω=0.0: sem pré-condicionador
0.0 < ω < 1.0: pré-condicionador de Jacobi


<i>: parâmetro obrigatório definindo o número máximo de iterações a serem executadas.
<arquivo_saida>: parâmetro obrigatório no qual arquivo_saida é o caminho completo para o arquivo que vai conter a solução.*/