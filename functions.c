/*Autores:
Annelyse Schatzmann           GRR20151731
Eduardo Zimermam Pereira      GRR20152952  */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


double sem_préCondicionador(double  *A, double *b, double *MaxIt, double eps){
 
	double r = b; v = b;
	double aux =

	for(int itr= 0; itr < MaxIt; itr++){
		z = multiplica_matriz(A, v);
		vT = transposta(v);
		multi_aux =  multiplica_matriz(vT, z);
		s = aux / multi_aux;

		multi_aux = multiplica_matriz (s, v);
			FALTA!

		r = r + multiplica_matriz(s,z);
		rT = transposta(r);
		aux1 = multiplica_matriz(rT,r);
		if(aux1 < eps){
			return(x)
		}

		m = aux1/aux ;
		aux = aux1;
		v = r + (multiplica_matriz(m,v))
	}
}


double com_préCondicionador(double  *A, double *b, double *M, double *MaxIt, double eps){
 
	double r = b; v = b;
	X = 0;
	MI = inversa(M);
	v = multiplica_matriz(MI,b);	
	y = multiplica_matriz(MI, r);
	yT = transposta(y);
	aux = multiplica_matriz (yT,r);

	for(int itr= 0; itr < MaxIt; itr++){
		z = multiplica_matriz(A, v);
		vT = transposta(v);
		multi_aux =  multiplica_matriz(vT, z);
		s = aux / multi_aux;
		
		multi_aux = multiplica_matriz (s, v);
			FALTA!


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
}