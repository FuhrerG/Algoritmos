#include <stdio.h>
#include <sys/time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define UMBRAL 10
#define REPETIR 15

// SELECTOR DE DIVISORES PARA LAS COTAS:
#define LOGN 1
#define NLOGN 2
#define NEXP 3
#define EXPN 4
#define SLOGN 5
#define LINEAL 6

/*****UTILIDADES PARA LA INICIALIZACION DE VECTORES*****/

// Inicializa la semilla para los numeros aleatorios
void inicializar_semilla(){
  srand(time(NULL));
}

// Genera un vector de numeros aleatorios entre n y -n
void aleatorio( int v[], int n ){
  int i, m = 2 * n + 1;
  for ( i = 0; i < n; i++ )
    v[i] = (rand() % m) - n;
}

// Genera un vector de n numeros ordenados de forma ascendente
void ascendente( int v[], int n ){
  int i;
  for ( i = 0; i < n; i++ )
    v[i] = i;
}

// Genera un vector de n numeros ordenados de forma descendente
void descendente( int v[], int n ){
  int i;
  for ( i = 0 ; i < n ; i++ )
    v[i] = n - i;
}

/******UTILIDADES DE TESTEO*******/

// Función que muestra todo el contenido de un vector
void listar_vector( int v[], int n ) {
   int i;

   printf("[ ");
   for (i = 0; i < n; ++i) {
      printf("%2d ", v[i]);
   }
   printf("]\n");
}

// Función que comprueba si un vector está ordenado
bool esta_ordenado(int v[],int n){
   int i;

   for (i=0;i<(n-1);i++){ //Se recorre el vector
      if(v[i]>v[(i+1)]){ //Si el siguiente elemento es menor que el actual
         return false; //El vector no está ordenado
      }
   }
   return true;//Si no, el vector está ordenado
}

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

// Algoritmo QuickSort Auxiliar
void rapida_aux(int v[], int izq, int der){
  int x, i, j, pivote, inter;

  if (izq + UMBRAL <= der){
    x = rand() % (der - izq + 1) + izq;
    pivote = v[x];
    inter = v[x];
    v[x] = v[izq];
    v[izq] = inter;
    i = izq + 1;
    j = der;

    while (i <= j) {
      while ((i <= der) && (v[i] < pivote))
        i++;

      while (v[j] > pivote)
        j--;

      if (i <= j) {
        inter = v[i];
        v[i] = v[j];
        v[j] = inter;
        i++;
        j--;
      }
    }

    inter = v[izq];
    v[izq] = v[j];
    v[j] = inter;
    rapida_aux(v, izq, j-1);
    rapida_aux(v, j+1, der);
  }
}

void ord_rapida(int v[], int n) {
  rapida_aux(v, 0, n-1);
  if (UMBRAL > 1)
    ord_ins(v, n);
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
  check = test(&ord_rapida,&ascendente,n) && check;

  printf("\n+++Test de Ordenación por insercion con vector ordenado "
    "descendentemente\n\n");
  check = test(&ord_rapida,&descendente,n) && check;

  printf("\n+++Test de Ordenación por insercion con el vector "
    "desordenado\n\n");
  check = test(&ord_rapida,&aleatorio,n) && check;

  printf("\n+++Test de Ordenación por insercion con vector "
    "ordenado ascendentemente\n\n");
  check = test(&ord_ins,&ascendente,n) && check;

  printf("\n+++Test de Ordenación por insercion con vector ordenado "
    "descendentemente\n\n");
  check = test(&ord_ins,&descendente,n) && check;

  printf("\n+++Test de Ordenación por insercion con el vector "
    "desordenado\n\n");
  check = test(&ord_ins,&aleatorio,n) && check;

  return check;

}

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
void mostrar_tiempo(int n, double t, bool es_promedio, float subestimada,
  float ajustada, float sobreestimada) {
  if (es_promedio) printf("(*)");
  else printf("   ");
  printf("%12d %15.7f %17.10f %17.10f %17.10f\n", n, t, t/subestimada,
      t/ajustada, t/sobreestimada);
}

// Función que mide el tiempo promedio de 1000 repeticiones
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
  (int v[],int n), int selector[],float power[], int n, int razon){

  double t_inicio, t_fin, t_total;
  int i, *v;
  bool conProm;

  for (i = 0; i < REPETIR; i++) {
    if((v = calloc(n, sizeof(int)))==NULL){
      perror("error al asignar la memoria");
      exit(1);
    }

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

    mostrar_tiempo(n, t_total, conProm, divisor(selector[0], n, power[0]),
      divisor(selector[1], n, power[1]), divisor(selector[2], n, power[2]));
      // Obtenemos el termino de la progresion geometrica
      n *= 2;
      free(v);
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

/***FUNCIONES DE ENTRADA DE DATOS PARA LAS TABLAS DE TIEMPOS***/

// Pasa los datos y llama a las funciones para el calculo de los tiempos de
// ordenacion de vectores ordenados de manera ascendente
void tiempos_asc(int n){
  int selector[3];
  float power[3];

  printf("\tVECTOR CON ORDENACION ASCENDENTE\n\n");

  selector[0] = LINEAL;
  selector[1] = NLOGN;
  selector[2] = NEXP;
  power[0] = 0;
  power[1] = 0 ;
  power[2] = 1.2;

  mostrar_cabecera(selector, power);
  medir_tiempos(&ord_rapida, &ascendente, selector, power, n, 2);
}

// Pasa los datos y llama a las funciones para el calculo de los tiempos de
// ordenacion de vectores ordenados de manera descendente
void tiempos_des(int n){
  int selector[3];
  float power[3];

  printf("\tVECTOR CON ORDENACION DESCENDENTE\n\n");

  selector[0]=LINEAL;
  selector[1]=NLOGN;
  selector[2]=NEXP;
  power[0]=0;
  power[1]=0;
  power[2]=1.2;

  mostrar_cabecera(selector, power);
  medir_tiempos(&ord_rapida, &descendente, selector, power, n, 2);
}

// Pasa los datos y llama a las funciones para el calculo de los tiempos de
// ordenacion de vectores ordenados de manera aleatoria
void tiempos_ale(int n){
  int selector[3];
  float power[3];

  printf("\tVECTOR CON ORDENACION ALEATORIA\n\n");

  selector[0]=LINEAL;
  selector[1]=NLOGN;
  selector[2]=NEXP;
  power[0]=0;
  power[1]=0;
  power[2]=1.2;

  mostrar_cabecera(selector, power);
  medir_tiempos(&ord_rapida, &aleatorio, selector, power, n, 2);
}

void tiempos(){
  int n;
  n = 1000;
  printf("--------------------------------------------------------------\n");
  printf("\tUMBRAL %d\n", UMBRAL);
  printf("--------------------------------------------------------------\n\n");
  tiempos_asc(n);
  tiempos_des(n);
  tiempos_ale(n);
}

int main() {
  int repeticiones;

  // Inicializamos la semilla de numeros aleatorios
  inicializar_semilla();

  // Testeamos los algoritmos
  if (!testear())
    return 0;

  // Calculamos cotas y tiempos de la ejecucion de los algoritmos, imprimiendo
  // por pantalla solo la ultima tabla de valores
  for ( repeticiones = 0; repeticiones < 3; repeticiones++ )
    tiempos();

  return 0;
}
