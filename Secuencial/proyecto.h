#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 10000

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
//funcion que recorre dos matrices, las recorre y las multiplica, guarda el resultado en matrizR
void multiplicarMatrices(int n,int matriz1[][MAX],int matriz2[][MAX],int matrizR[][MAX]){
	int columna=0,valor=0,i,j,k;
	for(i=0;i<n;i++){//recorre filas
		for(j=0;j<n;j++){
			valor=0;
			for(k=0;k<n;k++){//recorre columnas
				valor+=(matriz1[i][k]*matriz2[k][j]);//acumulador
			}
			matrizR[i][j]=valor;//almacena el acumulador en la posicion i,j
		}
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
