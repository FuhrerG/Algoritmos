#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "algoritmos.h"
#include "utils.h"

/*****ALGORITMOS DE ORDENACION*****/

// Algoritmo de ordenacion por insercion
void ord_ins (int v[], int n) {
   int i, j, x;

   for (i = 1; i < n; i++) {
      x = v[i];
      j = i - 1;
      while ((j > -1) && (v[j] > x)) {
         v[j + 1] = v[j];
         j--;
      }
      v[j + 1] = x;
   }
}

// Algoritmo QuickSort Auxiliar
void rapida_aux(int v[], int izq, int der){
  int x, i, j, pivote, inter;
  if (izq + UMBRAL <= der){
    x = rand() % (der - izq + 1) + izq;
    pivote = v[x];
    inter = v[x];
    v[x] = v[izq];
    v[izq] = inter;
    i = izq + 1;
    j = der;
    while (i <= j) {
      while ((i <= der) && (v[i] < pivote))
        i++;
      while (v[j] > pivote)
        j--;
      if (i <= j) {
        inter = v[i];
        v[i] = v[j];
        v[j] = inter;
        i++;
        j--;
      }
    }
    inter = v[izq];
    v[izq] = v[j];
    v[j] = inter;
    rapida_aux(v, izq, j-1);
    rapida_aux(v, j+1, der);
  }
}

void ord_rapida(int v[], int n) {
  rapida_aux(v, 0, n-1);
  if (UMBRAL > 1)
    ord_ins(v, n);
}
