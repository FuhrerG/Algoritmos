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

  // Inicializamos la semilla de numeros aleatorios
  inicializar_semilla();

  // Testeamos los algoritmos
  if (!testear())
    return 0;

  close(1);

  // Calculamos cotas y tiempos de la ejecucion de los algoritmos, imprimiendo
  // por pantalla solo la ultima tabla de valores
  for ( repeticiones = 0; repeticiones < 5; repeticiones++ ){
    if (repeticiones == 4){
      dup2(stdout_copy, 1);
      close(stdout_copy);
    }
    tiempos();
  }

  return 0;
}
