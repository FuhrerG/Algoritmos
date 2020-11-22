#include <stdio.h>
#include <sys/time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"
#include "abb.h"
#include "measuretime.h"

/**FUNCIONES PARA LA MEDICION DE TIEMPOS Y COTAS DE ALGORITMOS**/

// Calcula el tiempo desde ... hasta ahora
double microsegundos(){
  struct timeval t;
  if (gettimeofday(&t, NULL) < 0 )
    return 0.0;
  return (t.tv_usec + t.tv_sec * 1000000.0);
}

// Función que calcula el divisor en el cálculo de tiempos
float divisor(int seleccion, int n, float power){
  float result;
  switch(seleccion){
    case LOGN   : result = log(n);         break;
    case NLOGN  : result = n*log(n);       break;
    case NEXP   : result = pow (n,power);  break;
    case EXPN   : result = pow (power,n);  break;
    case SLOGN  : result = sqrt(log(n));   break;
    case LINEAL : result = n;              break;
  }
  return result;
}

// Función que muestra el string de la función que se va a usar
void division(int seleccion, float power) {
  switch(seleccion){
    case LOGN   : printf(" %17s", "t(n)/log(n)");               break;
    case NLOGN  : printf(" %17s", "t(n)/n*log(n)");             break;
    case NEXP   : printf(" %13s%3.2f", "t(n)/n^", power);       break;
    case EXPN   : printf(" %11s%3.2f%2s", "t(n)/", power,"^n"); break;
    case SLOGN  : printf(" %17s", "t(n)/V(log(n))");            break;
    case LINEAL : printf(" %17s", "t(n)/n");                    break;
  }
}

// Función que muestra los tiempos y las cotas
void mostrar_tiempo(int n, double t, float subestimada,
  float ajustada, float sobreestimada) {
  printf("   %12d %15.7f %17.10f %17.10f %17.10f\n", n, t, t/subestimada,
      t/ajustada, t/sobreestimada);
}

// Función que mide los tiempos
void medir_tiempos(double tiempos[12][3]) {
    double t_inicio, t_fin, t1, t2;
   int n, i, j, k;
   int v[512000];
   n = 500; j = 1; i = 1;
   arbol a = creararbol();
   while((i<8)&&(n<=512000)) {
      // Inicializamos el vector
      aleatorio(v, n);
      // Obtenemos los tiempos de insercion
      t_inicio = microsegundos();
      for(k = 0; k<n; k++) a = insertar(v[k], a);
      t_fin = microsegundos();

      t1 = t_fin - t_inicio;
      // Si el tiempo es pequeño se continua al siguiente ciclo
      if (t1 < 500) {n*=2; a = eliminararbol(a); continue;}

      // Obtenemos los tiempos de busqueda
      t_inicio = microsegundos();
      for(k = 0; k<n; k++) buscar(v[k], a);
      t_fin = microsegundos();

      t2 = t_fin - t_inicio;
      // Si el tiempo es pequeño se continua al siguiente ciclo
      if (t2 < 500)  {n*=2; a = eliminararbol(a); continue;}

      // Se insertan los tiempos en la tabla
      printf("%10i %10i %10i\n", n, (int) t1, (int) t2);
      tiempos[j][0] = n; tiempos[j][1] = t1; tiempos[j][2] = t2;
      // Se actualizan las variables
      ++j; n*=2; a = eliminararbol(a); i++;
   }
   tiempos[0][0] = i;;
   //printf("%d",i);
}

// Muestra la cabecera de las tablas
void mostrar_cabecera(int selector[], float power[]) {
  printf("%31s %17s %17s %17s\n", "", "Cota subestimada", "Cota ajustada",
    "Cota sobrestimada");
  printf("%15s %15s", "n", "t(n)");
  division(selector[0], power[0]);
  division(selector[1], power[1]);
  division(selector[2], power[2]);
  printf("\n");
}
