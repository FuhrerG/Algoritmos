#include <stdio.h>
#include <stdlib.h>
#include "abb.h"

#define MAX(a, b) ((a>b) ? (a) : (b))
#define MIN(a, b) ((a<b) ? (a) : (b))

/*----------FUNCIONES DE ABB----------*/

static struct nodo  *crearnodo(int e) {
   struct nodo *p = malloc(sizeof(struct nodo));
   if (p == NULL) {
      printf("memoria agotada\n"); exit(EXIT_FAILURE);
   }
   p->elem = e;
   p->num_repeticiones = 1;
   p->izq = NULL;
   p->der = NULL;
   return p;
}

arbol insertar(int e, arbol a){
   if (a == NULL)
      return crearnodo(e);
   else if (e < a->elem)
      a->izq = insertar(e, a->izq);
   else if (e > a->elem)
      a->der = insertar(e, a->der);
   else
      a->num_repeticiones++;
   return a;
}

// Crea un arbol vacio
arbol creararbol(){
   return NULL;
}

// Devuelve 1 si el arbol esta vacio
int esarbolvacio(arbol a){
   return a == NULL;
}

// Borra todos los elementos de un arbol
arbol eliminararbol(arbol a){
   if (a != NULL){
      a->izq = eliminararbol(a->izq);
      a->der = eliminararbol(a->der);
      free(a);
   }
   return NULL;
}

// Imprime el contenido de un arbol
void visualizar(arbol a){
   if (a!=NULL){
      printf("(");
      if(a->izq != NULL){
         visualizar(a->izq);
      }
      printf(" %d ",a->elem);
      if(a->der != NULL){
         visualizar(a->der);
      }
      printf(")");
   } else {
      printf("()");
   }
}

// Precondición: el árbol no es nulo
posicion hijoizquierdo(arbol a) {
   return a->izq;
}

// Precondición: el árbol no es nulo
posicion hijoderecho(arbol a) {
   return a->der;
}

// Precondición: el árbol no es nulo
int elemento(posicion p) {
   return p->elem;
}

// Precondición: el árbol no es nulo
int numerorepeticiones(posicion p) {
   return p->num_repeticiones;
}

// Devuelve la posicion de un elemento dentro de un arbol
posicion buscar(int e, arbol a) {
   if ((a == NULL) || (a->elem == e)) return a;
   else if (a->elem > e) return buscar(e, a->izq);
   else return buscar(e, a->der);
}

// Devuelve la altura del arbol
int altura(arbol a) {
   if (a == NULL) return -1;
   return (1+MAX(altura(a->izq), altura(a->der)));
}

arbol vectortotree(arbol a, int v[], int n) {
   int i;
   for(i = 0; i<n; i++) a = insertar(v[i], a);
   return a;
}

/*----------FUNCIONES DE TEST----------*/

void testvectortotree() {
   arbol a;
   int v[100000];
   int i;

   printf("\nTest vectortotree\n");

   printf("Vector: ");
   for (i=0; i<5; i++) {
      v[i] = (rand() % 10) - 5;
      printf("%i ", v[i]);
   }
   printf("\n");

   a = creararbol();
   a = vectortotree(a, v, 5);
   visualizar(a);

   a = eliminararbol(a);
}

void testear(){
  arbol a;
  printf("CREAR ARBOL: ");

  a = creararbol();
  if (a == NULL) {
    printf("Arbol creado correctamente \n");
    printf("ARBOL VACIO: ");
    visualizar(a);
    printf("\n");
  } else {
    printf("\n******** TEST FALLADO ********\n");
    printf("'No ha sido posible crear el arbol'\n");
  }

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
  //printf("busco 6 y encuentro 6 repetido: %i veces\n", numerorepeticiones(buscar(6,a)));

  printf("borro todos los nodos liberando memoria\n");
  a = eliminararbol(a);
  printf("arbol: ");
  visualizar(a);
  printf("\n");
  printf("\nALTURA DE ARBOL: %i\n", altura(a));
}

void buscarvector(arbol a, int v[], int n) {
   int i;
   for(i = 0; i<n; i++) buscar(v[i], a);
}
