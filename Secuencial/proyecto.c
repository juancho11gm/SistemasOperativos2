#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "proyecto.h"
#define MAX 10000

//variables globales
int matriz1 [MAX][MAX];
int matriz2 [MAX][MAX];
int matrizR [MAX][MAX];
int n;
//funcion principal
int main(int argc, char *argv[])
{
	if(argc<5){//verifica que no hayan menos de 4 argumentos
		printf("Hacen falta parametros \n");
	}
	if(argc>5){//verifica que no hayan mas de 4 argumentos
		printf("Envie los parametros adecuados \n");
	}
	if(argc==5){//verifica que hayan 4 argumentos
	
		//lee los 4 parametros que se necesitan
		n=atoi(argv[1]);//tamano de la matriz
		char* nomAr1=argv[2];//archivo1
		char* nomAr2=argv[3];//archivo2
		char *texSalida=argv[4];//archivo de salida
		
		
		//matriz aleatoria (para tamaño de 5000)
		/*
		matrizAleatoria(n,matriz1);
		matrizAleatoria(n,matriz2);
		escribirMatriz("5000-1.txt",n,matriz1);
	 	escribirMatriz("5000-2.txt",n,matriz2);
	 	*/
	 	
	 	//almacena las dos matrices en el sistema
	 	insertarMatriz(n,matriz1,nomAr1);
		insertarMatriz(n,matriz2,nomAr2);
		
		//imprime las dos matrices 
		imprimirMatriz(n,matriz1);
		printf("\n");
		imprimirMatriz(n,matriz2);
		printf("\n");
		
		//reloj de la funcion clock()
		clock_t start_t,end_t;
		start_t = clock();
		//funcion que multiplica las matrices
		multiplicarMatrices(n,matriz1,matriz2,matrizR);
		end_t = clock();
		double tiempoTotal=(double)(end_t - start_t)/ CLOCKS_PER_SEC;
		
		//imprime el resultado
		imprimirMatriz(n,matrizR);
		escribirMatriz(texSalida,n,matrizR);
		printf("\nTotal time taken by CPU: %lf\n",tiempoTotal );
		printf("\n");
		
	}
	
	return 0;
}
