#include <stdbool.h>
#include <stdio.h>
#include "test.h"
#include "algoritmos.h"

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
