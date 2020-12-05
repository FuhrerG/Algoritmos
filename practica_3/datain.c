#include <stdio.h>
#include <stdbool.h>

#include "datain.h"
#include "abb.h"
#include "measuretime.h"
#include "utils.h"

/***FUNCIONES DE ENTRADA DE DATOS PARA LAS TABLAS DE TIEMPOS***/

// Muestra las mediciones de tiempos de insercion en el arbol
void medicion_insercion( double v[8][3] ) {
   int selector[3];
   float power[3];
   int i;

   selector[0]=LINEAL;
   selector[1]=NEXP;
   selector[2]=NEXP;
   power[0]=0;
   power[1]=1.2;
   power[2]=1.4;

   printf("\n\n Tiempos en la inserción en el arbol\n\n");
   mostrar_cabecera(selector,power);
   for(i = 1; i<v[0][0]; i++) {
      mostrar_tiempo((int) v[i][0], v[i][1],
         divisor(selector[0], (int) v[i][0], power[0]),
         divisor(selector[1], (int) v[i][0], power[1]),
         divisor(selector[2], (int) v[i][0], power[2]),
         divisor(NLOGN, (int) v[i][0], 0));
   }
}

void medicion_busqueda( double v[8][3] ) {
   int selector[3];
   float power[3];
   int i;

   selector[0]=LINEAL;
   selector[1]=NEXP;
   selector[2]=NEXP;
   power[0]=0;
   power[1]=1.2;
   power[2]=1.4;

   printf("\n\n Tiempos en la búsqueda en el arbol\n\n");
   mostrar_cabecera(selector,power);
   for(i = 1; i<v[0][0]; i++) {
      mostrar_tiempo((int) v[i][0], v[i][2],
         divisor(selector[0], (int) v[i][0], power[0]),
         divisor(selector[1], (int) v[i][0], power[1]),
         divisor(selector[2], (int) v[i][0], power[2]),
         divisor(NLOGN, (int) v[i][0], 0));
   }
}

void tiempos(){
   double v[8][3];
   printf("\n%10s %10s %10s\n", "n", "t_ins(n)", "t_bus(n)");
   medir_tiempos(v);
   medicion_insercion(v);
   medicion_busqueda(v);
}
