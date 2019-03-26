#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <signal.h>
#include "proyectoProcesos.h"
#define MAX 10000
//declaración variables globales
int matriz1 [MAX][MAX];
int matriz2 [MAX][MAX];
int matrizR [MAX][MAX];
int n;

//funcion que recorre dos matrices, las recorre y las multiplica, guarda el resultado en matrizR
void multiplicarMatrices(int inicioFila,int finFila,int n,int matriz1[][MAX],int matriz2[][MAX],int matrizR[][MAX]){
	FILE *fp = fopen("ben.txt", "a");
	char buffer [10000];
	int columna=0,valor=0,i,j,k;
	for(i=inicioFila;i<finFila;i++){//recorre filas
		for(j=0;j<n;j++){
			valor=0;
			for(k=0;k<n;k++){//recorre columnas
				valor+=(matriz1[i][k]*matriz2[k][j]);//acumulador
				
			}
			matrizR[i][j]=valor;//almacena el acumulador en la posicion i,j
			sprintf(buffer, "%d", matrizR[i][j]);
			fprintf(fp,"%s",buffer);
			fprintf(fp," ");
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
}

int main(int argc, char *argv[])
{
	n=atoi(argv[1]);
	int nProcesos=atoi(argv[2]);
	char* nomAr1=argv[3];
	char* nomAr2=argv[4];
	char *texSalida=argv[5];
	//char* textF = argv[6];

	
	//matrizAleatoria(n,matriz1);
	//matrizAleatoria(n,matriz2);
	
	insertarMatriz(n,matriz1,nomAr1);
	insertarMatriz(n,matriz2,nomAr2);
		
	
 	imprimirMatriz(n,matriz1);
	printf("\n");
	imprimirMatriz(n,matriz2);
	printf("\n");
	
	int inicioFila=0,finFila=(n/nProcesos),status, i,cont=0,pr = nProcesos,filasMas=0;	
 	pid_t childpid; 
	filasMas=n - ((int)n/pr)*pr;
	
	for (i = 0; i < pr; i++) {
     	  if ((childpid = fork()) < 0) {/
        	  perror("fork:");
        	  exit(1);
          }
    // Codigo que ejecutaran los hijos
	     if (childpid == 0) { 
		    printf("uno  %d  %d \n",inicioFila,finFila);
		    multiplicarMatrices(inicioFila,finFila,n,matriz1,matriz2,matrizR);//multiplicacion de las matrices
		    exit(0);
		 }
		if(i==pr-2){
			finFila+=filasMas;	//aumenta el rango de las filas que operará el siguiente proceso
		}	
		inicioFila+=(n/nProcesos);
		finFila+=(n/nProcesos);
	}
	for (i = 0; i < pr; ++i){		
		wait(&status);//espera a que terminen los demas procesos
	}

	arreglarArchivo("ben.txt",texSalida,n); 
    return 0;
}
