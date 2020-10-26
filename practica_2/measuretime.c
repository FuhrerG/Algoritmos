#include <stdio.h>
#include <sys/time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"
#include "algoritmos.h"
#include "measuretime.h"

//calcula el tiempo desde ... hasta ahora
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
void mostrar_tiempo(int n, double t, bool es_promedio, float subestimada,
  float ajustada, float sobreestimada) {
  if (es_promedio) printf("(*)");
  else printf("   ");
  printf("%12d %15.3f %17.6f %17.6f %17.6f\n", n, t, t/subestimada,
      t/ajustada, t/sobreestimada);
}

double t_promedio(void (*ordenar)(int v[],int n),
  void (*inicializar)(int v[],int n), int v[], int n){

  double t_inicio, t_fin, t_total_1, t_total_2, t_total;
  int prom;

  //Calculamos el tiempo medio de 1000 ordenaciones con sus inicializaciones
  t_inicio = microsegundos();
  for(prom = 0; prom < 1000; prom++){
    inicializar(v, n);
    ordenar(v, n);
  }
  t_fin = microsegundos();
  t_total_1 = (t_fin - t_inicio) / 1000;

  //Calculamos el tiempo medio de 1000 inicializaciones
  t_inicio = microsegundos();
  for(prom = 0; prom < 1000; prom++)
    inicializar(v, n);
  t_fin = microsegundos();
  t_total_2 = (t_fin - t_inicio) / 1000;

  //El tiempo medio de ordenacion es la resta del tiempo medio de las
  //ordenaciones menos el tiempo medio que ha llevado inicializar los vectores
  t_total = t_total_1 - t_total_2;

  return t_total;
}

// Función que mide los tiempos
void medir_tiempos(void (*ordenar)(int v[],int n), void (*inicializar)
  (int v[],int n), int selector[],float power[], int n1, int razon){

  double t_inicio, t_fin, t_total;
  int i, n, v[32000];
  bool conProm;

  for (i = 0; i<7; i++) {
    // Obtenemos el termino de la progresion geometrica
    n = n1 * pow(razon, i);
    //inicializamos el vector
    inicializar(v, n);
    // Obtenemos los tiempos de ejecución
    t_inicio = microsegundos();
    ordenar(v, n);
    t_fin = microsegundos();
    t_total = t_fin - t_inicio;
    conProm = false;

    // Si el valor es pequeño se hace un promedio
    if (t_total < 500) {
      t_total = t_promedio(ordenar, inicializar, v, n);
      conProm = true;
    }

    // Se muestran los tiempos
    mostrar_tiempo(n, t_total, conProm, divisor(selector[0], n, power[0]),
      divisor(selector[1], n, power[1]), divisor(selector[2], n, power[2]));
  }
  printf("\n*: Tiempo promedio de 1000 ejecuciones del algoritmo\n\n\n");
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
