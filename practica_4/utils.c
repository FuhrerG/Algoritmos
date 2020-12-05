#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>

#include "utils.h"

/*****UTILIDADES PARA LA INICIALIZACION DE VECTORES*****/

// Inicializa la semilla para los numeros aleatorios
void inicializar_semilla(){
  srand(time(NULL));
}

// Genera un vector de numeros aleatorios entre n y -n
void aleatorio( int v[], int n ){
  int i, m = 2 * n + 1;
  for ( i = 0; i < n; i++ )
    v[i] = (rand() % m) - n;
}

// Genera un vector de n numeros ordenados de forma ascendente
void ascendente( int v[], int n ){
  int i;
  for ( i = 0; i < n; i++ )
    v[i] = i;
}

// Genera un vector de n numeros ordenados de forma descendente
void descendente( int v[], int n ){
  int i;
  for ( i = 0 ; i < n ; i++ )
    v[i] = n - i;
}

/******UTILIDADES DE TESTEO*******/

// Función que muestra todo el contenido de un vector
void listar_vector( int v[], int n ) {
   int i;

   printf("[ ");
   for (i = 0; i < n; ++i) {
      printf("%2d ", v[i]);
   }
   printf("]\n");
}

// Función que comprueba si un vector está ordenado
bool esta_ordenado(int v[],int n){
   int i;

   for (i=0;i<(n-1);i++){ //Se recorre el vector
      if(v[i]>v[(i+1)]){ //Si el siguiente elemento es menor que el actual
         return false; //El vector no está ordenado
      }
   }
   return true;//Si no, el vector está ordenado
}
