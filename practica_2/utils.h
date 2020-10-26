#ifndef UTILS
#define UTILS

//Inicializa la semilla para los numeros aleatorios
void inicializar_semilla();

//genera un vector de numeros aleatorios entre n y -n
void aleatorio( int v[], int n );

//genera un vector de n numeros ordenados de forma ascendente
void ascendente( int v[], int n );

//genera un vector de n numeros ordenados de forma descendente
void descendente( int v[], int n );

//Calcula
void listar_vector( int v[], int n );

//Función que comprueba si un vector está ordenado
bool esta_ordenado(int v[],int n);


#endif
