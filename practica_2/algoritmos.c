#include <stdbool.h>
#include <stdio.h>

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

// Algoritmo de ordenacion shell
void ord_shell( int v[], int n ) {
   int incremento = n;
   int i, tmp, j;
   bool seguir;

   do {
      incremento = incremento/2;
      for(i = incremento; i < n ; i++) {
         tmp = v[i];
         j = i;
         seguir = true;
         while (((j-incremento) > -1) && seguir) {
            if(tmp < v[j-incremento]) {
               v[j] = v[j-incremento];
               j = j-incremento;
            } else
              seguir = false;
         }
         v[j] = tmp;
      }
   } while (incremento > 1);
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
  check = test(&ord_ins,&ascendente,n) && check;

  printf("\n+++Test de Ordenación por insercion con vector ordenado "
    "descendentemente\n\n");
  check = test(&ord_ins,&descendente,n) && check;

  printf("\n+++Test de Ordenación por insercion con el vector "
    "desordenado\n\n");
  check = test(&ord_ins,&aleatorio,n) && check;

  printf("\n+++Test de Ordenación de shell con vector "
    "ordenado ascendentemente\n\n");
  check = test(&ord_shell,&ascendente,n) && check;

  printf("\n+++Test de Ordenación de shell con vector ordenado "
    "descendentemente\n\n");
  check = test(&ord_shell,&descendente,n) && check;

  printf("\n+++Test de Ordenación de shell con el vector desordenado\n\n");
  check = test(&ord_shell,&aleatorio,n) && check;

  return check;

}
