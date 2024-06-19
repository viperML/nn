#ifndef MATRIX_H
#define MATRIX_H

typedef struct Matrix Matrix;
typedef double num;

// Return a heap-allocated Matrix
Matrix* m_init(int rows, int cols);
// Delete a matrix created with m_init
int m_delete(Matrix* matrix);
void m_print(Matrix* matrix);

// result = A*B
Matrix* m_multiply(const Matrix* A, const Matrix* B);

num* m_elem_at(const Matrix* matrix, int row, int col);

void m_fill(Matrix* matrix, num (*function)(int, int));

#endif
