#include <stdbool.h>
#include <stdio.h>
#include "test.h"
#include "abb.h"
#include "utils.h"

void testear(){
  arbol a;
  printf("CREAR ARBOL: ");

  a = creararbol();
  printf("Arbol creado correctamente \n");
  printf("ARBOL VACIO: ");
  visualizar(a);
  printf("\n");

  printf("\nTest insertar\n");
  printf("Inserto un 3\n");
  a = insertar(3,a);
  printf("Inserto un 1\n");
  a = insertar(1,a);
  printf("Inserto un 2\n");
  a = insertar(2,a);
  printf("Inserto un 5\n");
  a = insertar(5,a);
  printf("Inserto un 4\n");
  a = insertar(4,a);
  printf("Inserto un 5\n");
  a = insertar(5,a);

  printf("ARBOL: \n");
  visualizar(a);
  printf("\nALTURA DE ARBOL: %i\n", altura(a));
  printf("busco 1 y encuentro 1 repetido: %i veces\n", numerorepeticiones(buscar(1,a)));
  printf("busco 2 y encuentro 2 repetido: %i veces\n", numerorepeticiones(buscar(2,a)));
  printf("busco 3 y encuentro 3 repetido: %i veces\n", numerorepeticiones(buscar(3,a)));
  printf("busco 4 y encuentro 4 repetido: %i veces\n", numerorepeticiones(buscar(4,a)));
  printf("busco 5 y encuentro 5 repetido: %i veces\n", numerorepeticiones(buscar(5,a)));

  printf("borro todos los nodos liberando memoria\n");
  a = eliminararbol(a);
  printf("arbol: ");
  visualizar(a);
  printf("\n");
  printf("\nALTURA DE ARBOL: %i\n", altura(a));
}
