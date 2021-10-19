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
