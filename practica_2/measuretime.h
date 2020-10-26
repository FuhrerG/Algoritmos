#ifndef MEASURETIME
#define MEASURETIME

// SELECTOR DE DIVISORES PARA LAS COTAS:
#define LOGN 1
#define NLOGN 2
#define NEXP 3
#define EXPN 4
#define SLOGN 5
#define LINEAL 6

// Función que mide los tiempos
void medir_tiempos(void (*ordenar)(int v[],int n), void (*inicializar)
  (int v[],int n), int selector[],float power[], int n1, int razon);

// Muestra la cabecera de las tablas
void mostrar_cabecera(int selector[], float power[]);

#endif
