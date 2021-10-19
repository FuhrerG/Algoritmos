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
#include "test.h"

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
