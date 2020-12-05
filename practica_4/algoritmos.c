#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "algoritmos.h"
#include "utils.h"
#include "measuretime.h"

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

/******FUNCIONES DE TESTEO*******/

// Testea que los algoritmos realicen la ordenacion correctamente
bool test(void (*ordenar)(int v[],int n),void (*inicializar)
      (int v[],int n),int n) {
  int v[n];

  printf("·Se inicializa el vector\n");
  inicializar(v,n);

  listar_vector(v,n);

  printf("·Se procede a ordenar el vector: \n");
  ordenar(v,n);

  listar_vector(v,n);

  return esta_ordenado(v,n);
}

// Se testean los algoritmos en 3 casos de entrada: que el vector ya esté
// ordenado, que esté ordenado inversamente y que esté desordenado
bool testear(){
  int n = 10;
  bool check = true;

  printf("Ejecutando test\n\n");

  printf("\n+++Test de Ordenación por insercion con vector "
    "ordenado ascendentemente\n\n");
  check = test(&ord_rapida,&ascendente,n) && check;

  printf("\n+++Test de Ordenación por insercion con vector ordenado "
    "descendentemente\n\n");
  check = test(&ord_rapida,&descendente,n) && check;

  printf("\n+++Test de Ordenación por insercion con el vector "
    "desordenado\n\n");
  check = test(&ord_rapida,&aleatorio,n) && check;

  printf("\n+++Test de Ordenación por insercion con vector "
    "ordenado ascendentemente\n\n");
  check = test(&ord_ins,&ascendente,n) && check;

  printf("\n+++Test de Ordenación por insercion con vector ordenado "
    "descendentemente\n\n");
  check = test(&ord_ins,&descendente,n) && check;

  printf("\n+++Test de Ordenación por insercion con el vector "
    "desordenado\n\n");
  check = test(&ord_ins,&aleatorio,n) && check;

  return check;

}
