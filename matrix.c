#include "matrix.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

struct Matrix {
  int M;
  int N;
  num* mem;
};

num* m_elem_at(const Matrix* matrix, int m, int n) {
  return &matrix->mem[matrix->N * m + n];
}

Matrix* m_multiply(const Matrix* A, const Matrix* B) {
  if (A->N != B->M) {
    errno = EINVAL;
    return NULL;
  }

  int n = A->N;

  Matrix* res = m_init(A->M, B->N);

  for (int i = 0; i < res->M; i++) {
    for (int j = 0; j < res->N; j++) {
      *m_elem_at(res, i, j) = 0.0;

      for (int k = 0; k < n; k++) {
        *m_elem_at(res, i, j) += *m_elem_at(A, i, k) * *m_elem_at(B, k, j);
      }
    }
  }

  return res;
}

Matrix* m_init(int m, int n) {
  Matrix* matrix = malloc(sizeof(Matrix));
  if (matrix == NULL) {
    return NULL;
  }

  matrix->M = m;
  matrix->N = n;

  matrix->mem = calloc(m * n, sizeof(num));

  if (matrix->mem == NULL) {
    return NULL;
  }

  return matrix;
}

int m_delete(Matrix* matrix) {
  free(matrix->mem);
  free(matrix);
  return 0;
}

void m_print(Matrix* matrix) {
  if (matrix == NULL) {
    printf("Matrix unintialized!\n");
    return;
  }
  for (int m = 0; m < matrix->M; m++) {
    for (int n = 0; n < matrix->N; n++) {
      num value = *m_elem_at(matrix, m, n);

      printf("%6.2f ", value);
    }
    printf("\n");
  }
}
