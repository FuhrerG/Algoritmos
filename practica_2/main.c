/*
*
* Autores:
* - Daniel Jose Garcia Paz
* - Damian Botana Otero
*
* Para esta práctica se van a implementar, validar y utilizar dos algoritmos
* de ordenación. Concretamente ordenación por inserción y ordenación shell.
*
*/
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include "utils.h"
#include "algoritmos.h"
#include "datain.h"

int main() {
  int repeticiones;
  int stdout_copy = dup(1);

  inicializar_semilla();

  if (!testear())
    return 0;

  close(1);
  for ( repeticiones = 0; repeticiones < 5; repeticiones++ ){
    if (repeticiones == 4){
      dup2(stdout_copy, 1);
      close(stdout_copy);
    }
    tiempos();
  }
  return 0;
}
