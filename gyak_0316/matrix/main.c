#include "matrix.h"

#include <stdio.h>

#define PI 3.14159265

int main(int argc, char *argv[])
{
    float transformation_matrix[3][3];
    float a[3][3] = {
        {1.0f, -2.0f, 3.0f},
        {5.0f, -3.0f, 0.0f},
        {-2.0f, 1.0f, -4.0f}};
    float b[3][3];
    float c[3][3];
    float point[3][1] = {
        {10},
        {-3},
        {1}};
    float new_point[3][1] = {
        {0},
        {0},
        {1}};

    init_zero_matrix(b);
    b[1][1] = 8.0f;
    b[2][0] = -3.0f;
    b[2][2] = 5.0f;

    printf("Matrix A: \n");
    print_matrix(a);
    printf("Matrix B: \n");
    print_matrix(b);

    add_matrices(a, b, c);
    printf("Adding A and B: \n");
    print_matrix(c);

    scalar_multiply_matrix(c, 4.5);
    printf("Multiplying the previous matrix with 4.5: \n");
    print_matrix(c);

    init_zero_matrix(c);
    multiply_matrices(a, b, c);
    printf("Multiplying A and B: \n");
    print_matrix(c);

    shift_matrix(transformation_matrix, 3.0, 10.0);
    printf("Matrix to shift a point with a (3, 10) vector: \n");
    print_matrix(transformation_matrix);
    transform_point(transformation_matrix, point, new_point);
    printf("Shifting the (%f, %f) point: (%f, %f)\n", point[0][0], point[1][0], new_point[0][0], new_point[1][0]);

    rotate_matrix(transformation_matrix, PI / 2);
    printf("Matrix to rotate a point with a PI/2 (90 degree) angle: \n");
    print_matrix(transformation_matrix);
    transform_point(transformation_matrix, point, new_point);
    printf("Rotating the (%f, %f) point: (%f, %f)\n", point[0][0], point[1][0], new_point[0][0], new_point[1][0]);

    scale_matrix(transformation_matrix, 10, 30);
    printf("Matrix to scale a point (10 on x and 30 on y): \n");
    print_matrix(transformation_matrix);
    transform_point(transformation_matrix, point, new_point);
    printf("Scaling the (%f, %f) point: (%f, %f)\n", point[0][0], point[1][0], new_point[0][0], new_point[1][0]);

    return 0;
}
