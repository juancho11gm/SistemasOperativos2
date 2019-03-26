#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>

#define MAX 10000

//estructura que guarda los intervalos de las filas que multiplicara cada hilo
struct x{
	int inicioFila;
	int finFila;
};
//funcion que recibe el nombre del archivo donde esta la matriz del archivo texto y la almacena en una variable(matriz) dentro del programa
void insertarMatriz(int n,int matriz[][MAX],char* nomAr){
	FILE *fp = fopen(nomAr, "r");//abre el archivo
	char linea[10000];
	char *token;
	int i;
	if(fp){
		int j=0;
		for(i=0;i<n;i++){
			j=0;
			fgets(linea, sizeof(linea), fp);//linea por linea
			linea[sizeof(linea)-1]='\0';
			token = strtok(linea," ");//token por espacio
			while( token != NULL ) {
				if(j<n){
					matriz[i][j]=atoi(token);//matriz en i,j es igual al entero del archivo texto
				}
    				token = strtok(NULL, " ");
				j++;
			}
			
  		}		
	}else{
		printf("No abrio el archivo \n");
	}
}
//funcion que recorre la matriz y la imprime
void imprimirMatriz(int n,int matriz[][MAX]){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("%d",matriz[i][j]);
			printf(" ");
		}
		printf("\n");
	}
}

//funcion que recibe el tamano y genera una matriz aleatoria con numeros de 1 a 50
void matrizAleatoria(int n,int matriz[][MAX]){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			matriz[i][j]=rand() % 50;
		}
	}
}
//funcion que recibe una matriz y la escribe en un archivo
void escribirMatriz(char* nomAr,int n,int matriz[][MAX]){
		FILE *fp = fopen(nomAr, "w");
		char buffer [10000];
		int i,j;
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				sprintf(buffer, "%d", matriz[i][j]);
				fprintf(fp,"%s",buffer);
				fprintf(fp," ");
			}
			fprintf(fp,"\n");
		}
}
