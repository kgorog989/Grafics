#include "matrix.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void init_identity_matrix(float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
            matrix[i][j] = 0.0;

            if (i == j)
            {
                matrix[i][j] = 1.0;
            }
        }
    }
}

void init_zero_matrix(float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
            matrix[i][j] = 0.0;
        }
    }
}

void print_matrix(const float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
            printf("%4.4f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void add_matrices(const float a[3][3], const float b[3][3], float c[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}

void scalar_multiply_matrix(float matrix[3][3], float scalar)
{
    int i;
    int j;

    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
            matrix[i][j] = matrix[i][j] * scalar;
        }
    }
}

void multiply_matrices(const float a[3][3], const float b[3][3], float c[3][3])
{
    int i;
    int j;
    int k;

    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
            for (k = 0; k < 3; ++k)
            {
                c[i][k] += a[i][j] * b[j][k];
            }
        }
    }
}

void transform_point(const float matrix[3][3], const float point[3][1], float new_point[3][1])
{
    int i, j;

    for (i = 0; i < 3; i++)
    {
        new_point[i][0] = 0;
        for (j = 0; j < 3; j++)
        {
            new_point[i][0] += matrix[i][j] * point[j][0];
        }
    }
}

void shift_matrix(float matrix[3][3], float x, float y)
{
    init_identity_matrix(matrix);
    matrix[0][2] = x;
    matrix[1][2] = y;
}

void rotate_matrix(float matrix[3][3], double angle)
{
    init_identity_matrix(matrix);
    matrix[0][0] = cos(angle);
    matrix[1][0] = sin(angle);
    matrix[0][1] = (-sin(angle));
    matrix[1][1] = cos(angle);
}

void scale_matrix(float matrix[3][3], float scale_x, float scale_y)
{
    if (scale_x <= 0 || scale_y <= 0)
    {
        printf("\nError. Scaling parameters must be of positive value. \n");
        exit(-1);
    }

    init_identity_matrix(matrix);
    matrix[0][0] = scale_x;
    matrix[1][1] = scale_y;
}
