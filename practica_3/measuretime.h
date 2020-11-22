#ifndef MEASURETIME
#define MEASURETIME

// SELECTOR DE DIVISORES PARA LAS COTAS:
#define LOGN 1
#define NLOGN 2
#define NEXP 3
#define EXPN 4
#define SLOGN 5
#define LINEAL 6

float divisor(int seleccion, int n, float power);

void mostrar_tiempo(int n, double t, float subestimada,
  float ajustada, float sobreestimada);

// Función que mide los tiempos
void medir_tiempos(double tiempos[12][3]);

// Muestra la cabecera de las tablas
void mostrar_cabecera(int selector[], float power[]);

#endif
