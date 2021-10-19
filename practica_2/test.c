#include <stdbool.h>
#include <stdio.h>
#include "test.h"
#include "algoritmos.h"
#include "utils.h"



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
