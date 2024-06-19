#include "matrix.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

struct Matrix {
  int rows;
  int cols;
  num* mem;
};

num* m_elem_at(const Matrix* matrix, int row, int col) {
  // Bounds check
  if (row >= matrix->rows || col >= matrix->cols) {
    errno = EINVAL;
    return NULL;
  }

  return &matrix->mem[matrix->cols * row + col];
}

Matrix* m_multiply(const Matrix* A, const Matrix* B) {
  if (A->cols != B->rows) {
    errno = EINVAL;
    return NULL;
  }

  Matrix* result = m_init(A->rows, B->cols);

  for (int row = 0; row < result->rows; row++) {
    for (int col = 0; col < result->cols; col++) {
      *m_elem_at(result, row, col) = 0.0;

      for (int k = 0; k < A->cols; k++) {
        *m_elem_at(result, row, col) +=
            *m_elem_at(A, row, k) * *m_elem_at(B, k, col);
      }
    }
  }

  return result;
}

Matrix* m_init(int rows, int cols) {
  Matrix* matrix = malloc(sizeof(Matrix));
  if (matrix == NULL) {
    return NULL;
  }

  matrix->rows = rows;
  matrix->cols = cols;

  matrix->mem = calloc(rows * cols, sizeof(num));

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

  // if (matrix->M >= 10 || matrix->N >= 10) {
  //   printf("Matrix<%dx%d> too big to display!\n", matrix->M, matrix->N);
  //   return;
  // }

  for (int row = 0; row < matrix->rows; row++) {
    for (int col = 0; col < matrix->cols; col++) {
      num value = *m_elem_at(matrix, row, col);

      printf("%6.2f ", value);
    }
    printf("\n");
  }
}

void m_fill(Matrix* matrix, num (*function)(int, int)) {
  for (int i = 0; i < matrix->rows; i++) {
    for (int j = 0; j < matrix->cols; j++) {
      *m_elem_at(matrix, i, j) = function(i, j);
    }
  }
}
