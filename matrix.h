#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>

typedef struct Matrix Matrix;
typedef double num;

// Return a heap-allocated Matrix
Matrix* m_init(int m, int n);
// Delete a matrix created with m_init
int m_delete(Matrix* matrix);
void m_print(Matrix* matrix);

Matrix* m_multiply(const Matrix* a, const Matrix* b);

num* m_elem_at(const Matrix* matrix, int n, int m);

#endif
