#include "algoritmos.h"

//algoritmo 1
int fib1( int n ) {
  if (n<2)
    return n;
  else{
    return fib1(n-1) + fib1(n-2);
  }
}

//algoritmo 2
int fib2( int n ) {
  int i = 1, j = 0, k;
  for (k = 1; k <= n; k++) {
    j = i + j;
    i = j - i;
  }
  return j;
}

//algoritmo 3
int fib3( int n ) {
  int i, j, k, h, t;
  i = 1; j = 0; k = 0; h = 1;
  while ( n > 0 ) {
    if ((n % 2) != 0) {
      t = j * h;
      j = (i * h) + (j * k) + t;
      i = (i * k) + t;
    }
    t = h * h;
    h = (2 * k * h) + t;
    k = (k * k) + t;
    n = n / 2;
  }
  return j;
}
