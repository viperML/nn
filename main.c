#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

#define unwrap(ptr)                                                            \
  if (ptr == NULL) {                                                           \
    perror("Failed to init");                                                  \
    exit(EXIT_FAILURE);                                                        \
  };

double sig(double x) {
  double exponent = exp(x);
  return exponent / (1 + exponent);
}

int main() {
  Matrix* m = m_init(3, 3);
  m_print(m);
  m_delete(m);

  return EXIT_SUCCESS;
}
