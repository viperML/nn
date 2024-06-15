#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

#define unwrap(ptr)                                                            \
  if (ptr == NULL) {                                                           \
    perror("Failed to init");                                                  \
    exit(EXIT_FAILURE);                                                        \
  };

int main() {
  Matrix* matrix_a = m_init(2, 4);
  *m_elem_at(matrix_a, 0, 0) = 3.0;
  *m_elem_at(matrix_a, 0, 1) = 2.0;
  *m_elem_at(matrix_a, 0, 2) = 1.0;
  *m_elem_at(matrix_a, 0, 3) = 5.0;
  *m_elem_at(matrix_a, 1, 0) = 9.0;
  *m_elem_at(matrix_a, 1, 1) = 1.0;
  *m_elem_at(matrix_a, 1, 2) = 3.0;
  *m_elem_at(matrix_a, 1, 3) = 0.0;
  printf("=> A:\n");
  m_print(matrix_a);

  printf("=> B:\n");
  Matrix* matrix_b = m_init(4, 3);
  *m_elem_at(matrix_b, 0, 0) = 2.0;
  *m_elem_at(matrix_b, 0, 1) = 9.0;
  *m_elem_at(matrix_b, 0, 2) = 0.0;
  *m_elem_at(matrix_b, 1, 0) = 1.0;
  *m_elem_at(matrix_b, 1, 1) = 3.0;
  *m_elem_at(matrix_b, 1, 2) = 5.0;
  *m_elem_at(matrix_b, 2, 0) = 2.0;
  *m_elem_at(matrix_b, 2, 1) = 4.0;
  *m_elem_at(matrix_b, 2, 2) = 7.0;
  *m_elem_at(matrix_b, 3, 0) = 8.0;
  *m_elem_at(matrix_b, 3, 1) = 1.0;
  *m_elem_at(matrix_b, 3, 2) = 5.0;
  m_print(matrix_b);

  Matrix* matrix_c = m_multiply(matrix_a, matrix_b);
  printf("=> C:\n");
  m_print(matrix_c);

  m_delete(matrix_a);
  m_delete(matrix_b);
  m_delete(matrix_c);

  return EXIT_SUCCESS;
}
