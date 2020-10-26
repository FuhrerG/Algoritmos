/*
*
* Autores:
* - Daniel Jose Garcia Paz
* - Damian
*
* Prueba de diferentes algoritmos para el calculo del n-esimo elemento
* de la sucesion de Fibonacci.
*
*/
#include <stdbool.h>
#include "utilidades.h"
#include "algoritmos.h"

int main() {
  int repeticiones;
  if (!test())
    return 0;
  for (repeticiones = 0; repeticiones < 5; repeticiones++) {
    tiempos();
  }
  return 0;
}
