#include "utils.h"

#include <math.h>
#include <string.h>

#include <GL/gl.h>

double degree_to_radian(double degree)
{
	return degree * M_PI / 180.0;
}

int invert_matrix(const float *src, float *dest)
{
	float temp[16];
	float mat[4][8];
	int i, j, k, pivot;
	float temp_val, factor, pivot_value;

	// Copy the source matrix to a temporary matrix
	memcpy(temp, src, sizeof(float) * 16);

	// Augment the temporary matrix with an identity matrix
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 8; j++)
		{
			mat[i][j] = (j < 4) ? temp[i + j * 4] : ((i == (j - 4)) ? 1.0f : 0.0f);
		}
	}

	// Gaussian elimination
	for (i = 0; i < 4; i++)
	{
		// Find the pivot row
		pivot = i;
		for (j = i + 1; j < 4; j++)
		{
			if (fabs(mat[j][i]) > fabs(mat[pivot][i]))
				pivot = j;
		}

		// Row swapping if necessary
		if (pivot != i)
		{
			for (k = 0; k < 8; k++)
			{
				temp_val = mat[i][k];
				mat[i][k] = mat[pivot][k];
				mat[pivot][k] = temp_val;
			}
		}

		// Perform row operations
		for (j = 0; j < 4; j++)
		{
			if (j != i)
			{
				factor = mat[j][i] / mat[i][i];
				for (k = 0; k < 8; k++)
				{
					mat[j][k] -= factor * mat[i][k];
				}
			}
		}
	}

	// Divide each row by its pivot value
	for (i = 0; i < 4; i++)
	{
		pivot_value = mat[i][i];
		if (pivot_value == 0.0f)
		{
			// Matrix is singular, cannot be inverted
			return 0;
		}
		for (j = 0; j < 8; j++)
		{
			mat[i][j] /= pivot_value;
		}
	}

	// Copy the inverted matrix to the destination matrix
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			dest[i + j * 4] = mat[i][j + 4];
		}
	}

	return 1;
}

void convert_to_NDC(int x, int y, float *ndc_x, float *ndc_y)
{
	// NDC coordinates
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	int viewport_width = viewport[2];
	int viewport_height = viewport[3];
	*ndc_x = (2.0f * (float)x) / (float)viewport_width - 1.0f;
	*ndc_y = 1.0f - (2.0f * (float)y) / (float)viewport_height;
	
}
