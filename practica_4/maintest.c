#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include "utils.h"
#include "algoritmos.h"

int main() {
  int repeticiones;

  // Inicializamos la semilla de numeros aleatorios
  inicializar_semilla();

  // Testeamos los algoritmos
  testear();

  return 0;
}
