#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <byteswap.h>

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

/*
http://yann.lecun.com/exdb/mnist/
*/

int main() {
  Matrix* m = m_init(3, 3);
  m_print(m);
  m_delete(m);

  FILE* file = fopen("../data/train-images-idx3-ubyte", "r");

  int32_t buf = {};
  fread(&buf, sizeof(int32_t), 1, file);
  buf = bswap_32(buf);
  printf("magic=0x%x\n", buf);

  fread(&buf, sizeof(int32_t), 1, file);
  buf = bswap_32(buf);
  printf("images=%d\n", buf);

  fread(&buf, sizeof(int32_t), 1, file);
  buf = bswap_32(buf);
  printf("rows=%d\n", buf);

  fread(&buf, sizeof(int32_t), 1, file);
  buf = bswap_32(buf);
  printf("columns=%d\n", buf);

  return EXIT_SUCCESS;
}
