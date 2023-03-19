#ifndef MATRIX_H
#define MATRIX_H

/**
 * Initializes an identity matrix.
 */
void init_identity_matrix(float matrix[3][3]);

/**
 * Initializes all elements of the matrix to zero.
 */
void init_zero_matrix(float matrix[3][3]);

/**
 * Print the elements of the matrix.
 */
void print_matrix(const float matrix[3][3]);

/**
 * Add matrices.
 */
void add_matrices(const float a[3][3], const float b[3][3], float c[3][3]);

/**
 * Multiply matrix with scalar.
 */
void scalar_multiply_matrix(float matrix[3][3], float scalar);

/**
 * Multiply matrices.
 */
void multiply_matrices(const float a[3][3], const float b[3][3], float c[3][3]);

/**
 * Perform a transformation defined by a matrix on a point in the Descartes coordinate system.
 */
void transform_point(const float matrix[3][3], const float point[3][1], float new_point[3][1]);

/**
 * Creates shifting matrix with an (x, y) vector.
 */
void shift_matrix(float matrix[3][3], float x, float y);

/**
 * Creates rotating matrix with an angle in radian.
 */
void rotate_matrix(float matrix[3][3], double angle);

/**
 * Creates a scaling matrix.
 */
void scale_matrix(float matrix[3][3], float scale_x, float scale_y);

#endif // MATRIX_H