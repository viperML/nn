#include <byteswap.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>

#include "matrix.h"

#define unwrap(ptr)                                                            \
  if (ptr == NULL) {                                                           \
    char* s;                                                                   \
    asprintf(&s, "Failed to init @ %s:%d", __FILE__, __LINE__);                \
    perror(s);                                                                 \
    exit(EXIT_FAILURE);                                                        \
  };

double sig(double x) {
  double exponent = exp(x);
  return exponent / (1 + exponent);
}

num fill_stuff(int i, int j) { return sig(i); }

#define fread_or_exit(ptr, size, nmemb, stream)                                \
  {                                                                            \
    size_t b_read = fread(ptr, size, nmemb, stream);                           \
    if (b_read != ((nmemb))) {                                                 \
      printf("Failed to read from file! @ %s:%d\n", __FILE__, __LINE__);       \
      exit(EXIT_FAILURE);                                                      \
    }                                                                          \
  }

/*
http://yann.lecun.com/exdb/mnist/
*/

const int32_t MAGIC_IMAGE = 2051;
const int32_t MAGIC_LABEL = 2049;

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("Usage: %s <data>\n", argv[0]);
    printf("  Where data is a folder containing the MNIST dataset\n");
    return EX_USAGE;
  }

  int foo = 3;

  char* data_train_path = NULL;
  asprintf(&data_train_path, "%s/train-images-idx3-ubyte", argv[1]);
  FILE* file = fopen(data_train_path, "r");

  {
    int32_t buf = 0;
    fread_or_exit(&buf, sizeof(int32_t), 1, file); // magic
    buf = bswap_32(buf);
    if (buf != MAGIC_IMAGE) {
      printf("Bad file magic\n");
      return EX_DATAERR;
    }

    fread_or_exit(&buf, sizeof(int32_t), 1, file); // n samples, 60k
    fread_or_exit(&buf, sizeof(int32_t), 1, file); // rows, 28
    fread_or_exit(&buf, sizeof(int32_t), 1, file); // columns, 28
  }

  // Matrix* train_data = m_init(layer_0_size, n_samples);
  // m_print(train_data);

  Matrix* N_0 = m_init(28 * 28, 1);
  Matrix* N_1 = m_init(18, 1);
  Matrix* N_2 = m_init(18, 1);
  Matrix* N_3 = m_init(10, 1);

  Matrix* W_1 = m_init(18, 28 * 28);
  Matrix* W_2 = m_init(18, 18);
  Matrix* W_3 = m_init(18, 10);

  srandom(0);

  int iter = 0;
  for (int row = 0; row < 28; row++) {
    for (int col = 0; col < 28; col++) {
      uint8_t buf = 0;
      fread_or_exit(&buf, sizeof(uint8_t), 1, file);

      *m_elem_at(N_0, iter, 0) = (double)buf;
      iter++;
    }
  }

  m_print(N_0);
  m_fill(W_1, fill_stuff);
  m_print(W_1);

  Matrix* res = m_multiply(W_1, N_0);
  unwrap(res);
  m_print(res);

  return EXIT_SUCCESS;
}
