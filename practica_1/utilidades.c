#include <stdio.h>
#include <sys/time.h>
#include <stdbool.h>
#include <math.h>
#include "utilidades.h"
#include "algoritmos.h"

//calcula el tiempo desde ... hasta ahora
double microsegundos() {
  struct timeval t;
  if (gettimeofday(&t, NULL) < 0 )
    return 0.0;
  return (t.tv_usec + t.tv_sec * 1000000.0);
}

//testea que todos los algoritmos arrojen los mismos resultados
bool test() {
  printf("ejecuta test\n\n");

  int i;
  for (i = 0; i < 15; i++) {
    if (fib1(i) != fib2(i) || fib2(i) != fib3(i)) {
      printf("error de test: los resultados de los algoritmos no coinciden\n");
      return false;
    }
  }
  return true;
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

// Función que mide los tiempos
void medir_tiempos(int (*fib)(int n), int selector[],float power[],
  int n1, int razon){

  double t_inicio, t_fin, t_total;
  int i, prom, n;
  bool conProm;

  for (i = 0; i<5; i++) {
    // Obtenemos el termino de la progresion geometrica
    n = n1 * pow(razon, i);
    // Obtenemos los tiempos de ejecución
    t_inicio = microsegundos();
    fib(n);
    t_fin = microsegundos();
    t_total = t_fin - t_inicio;
    conProm = false;

    // Si el valor es pequeño se hace un promedio
    if (t_total < 500) {
      t_inicio = microsegundos();
      for(prom = 0; prom < 1000; prom++){
        fib(n);
      }
      t_fin = microsegundos();
      t_total = (t_fin - t_inicio) / 1000;
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

// Funcion para gestionar mediciones de tiempo y creacion de tablas
void tiempos(){
  int selector[3];
  float power[3];

  //Cota subestimada  |  Cota ajustada        |        Cota sobreestimada
  selector[0]=EXPN;      selector[1]=EXPN;             selector[2]=EXPN;
  power[0]=1.1;          power[1]=(1 + sqrt(5))/ 2;    power[2]=2;
  printf("\tTIEMPOS ALGORITMO 1\n\n");
  mostrar_cabecera(selector, power);
  medir_tiempos(&fib1, selector, power, 2, 2);

  //Cota subestimada  |  Cota ajustada        |        Cota sobreestimada
  selector[0]=NLOGN;     selector[1]=NEXP;             selector[2]=NLOGN;
  power[0]=0;            power[1]=0.8;                 power[2]=0;
  printf("\tTIEMPOS ALGORITMO 2\n\n");
  mostrar_cabecera(selector, power);
  medir_tiempos(&fib2, selector, power, 1000, 10);

  //Cota subestimada  |  Cota ajustada        |        Cota sobreestimada
  selector[0]=SLOGN;     selector[1]=LOGN;             selector[2]=NEXP;
  power[0]=0;            power[1]=0;                   power[2]=0.5;
  printf("\tTIEMPOS ALGORITMO 3\n\n");
  mostrar_cabecera(selector, power);
  medir_tiempos(&fib3, selector, power, 1000, 10);
}
