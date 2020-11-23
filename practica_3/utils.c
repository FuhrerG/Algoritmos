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

void aleatorio(int v[], int n) {
   int i, m = 2*n+1;
   for (i=0; i < n; i++)
      v[i] = (rand() % m) - n;
}
