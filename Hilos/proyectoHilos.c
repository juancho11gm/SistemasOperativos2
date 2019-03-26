#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>
#include "proyectoHilos.h"

#define MAX 10000
//variables globales
int matriz1 [MAX][MAX];
int matriz2 [MAX][MAX];
int matrizR [MAX][MAX];
int n;
//unica funcion en el archivo principal para poder crear los hilos satisfactoriamente
void *multiplicarMatrices(void* arg){
	struct x * p;//asigno memoria para crear un structx
	p = ( struct x *) arg ;
	int valor=0,i,j,k;
	printf("\nInicio: %d ----- Fin: %d\n",p->inicioFila,p->finFila);
	for(i=p->inicioFila;i<(p->finFila);i++){// cada hilo se encarga de un rango de filas. es igual al tamaño de la matriz dividio en el numero de hilos.
		for(j=0;j<n;j++){
			valor=0;
			for(k=0;k<n;k++){
				valor+=(matriz1[i][k]*matriz2[k][j]);
			}
			matrizR[i][j]=valor;
		}
	}
}
//funcion principal
int main(int argc, char *argv[])
{
	if(argc<6){
		printf("Hacen falta parametros \n");//verifica que no hayan menos de 5 argumentos
	}
	if(argc>6){
		printf("Envie los parametros adecuados \n");//verifica que no hayan mas de 5 argumentos
	}
	if(argc==6){//verifica que no hayan mas de 5 argumentos
	
		n=atoi(argv[1]);//tamano de la matriz
		int nHilos=atoi(argv[2]);//numero de hilos
		char* nomAr1=argv[3];//archivo matriz1
		char* nomAr2=argv[4];//archivo matriz2
		char *texSalida=argv[5];//archivo matriz resultado
		int i,inicioFila=0,finFila=(n/nHilos),filasMas=0;
		
		
		//matrices aleatorias para n=5000
		matrizAleatoria(n,matriz1);
		matrizAleatoria(n,matriz2);
		
		//insertarMatriz(n,matriz1,nomAr1);
		//insertarMatriz(n,matriz2,nomAr2);
		
		//imprime las matrices
	 	imprimirMatriz(n,matriz1);
		printf("\n");
		imprimirMatriz(n,matriz2);
		printf("\n");
		
		//funcion clock() para calcular el tiempo
		clock_t start_t,end_t,total_t;
		start_t = clock();
		
		//declaracion array de hilos
		pthread_t hilo[nHilos];
		filasMas=n - ((int)n/nHilos)*nHilos;//filas de mas que haran los hilos, en caso de que la divison no sea exacta 
		for(i=0; i<nHilos; i++){//Creacion de los hilos de acuerdo al numero ingresado
			struct x* valor=malloc(sizeof(struct x));
			valor->inicioFila=inicioFila;
			valor->finFila=finFila;	
	  		pthread_create(&hilo[i],NULL,multiplicarMatrices,(void*) valor);//creacion de los hilos, para continuar con la operacion de multiplicacion de matrices
			if(i==nHilos-2){
				finFila+=filasMas;	//aumenta el rango
			}		
			inicioFila+=(n/nHilos);//cambian los intervalos de inicio y fin de las filas
			finFila+=(n/nHilos);
	 	}
		printf("\n");
		for(i=0;i<nHilos;i++){
			pthread_join(hilo[i], NULL);//espera a que terminen los demas hilos
		}
		end_t = clock();
		double tiempoTotal=(double)(end_t - start_t)/ CLOCKS_PER_SEC;
		//imprime los resultados
		imprimirMatriz(n,matrizR);
		//escribe la matriz resultado en el archivo pedido
	 	escribirMatriz(texSalida,n,matrizR);
		printf("\nTotal time taken by CPU: %lf\n",tiempoTotal );
		printf("\n");
	}	
	return 0;
}
