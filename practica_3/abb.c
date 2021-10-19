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
