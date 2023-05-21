#include "ray.h"

#include <math.h>
#include <stdio.h>

#include <GL/gl.h>

void init_ray(Ray *ray, float ndc_x, float ndc_y, vec3 position)
{
    // Retrieve the projection and model-view matrices
    GLfloat projection_matrix[16];
    GLfloat modelview_matrix[16];

    // ... Retrieve the matrices from your rendering pipeline ...
    glMatrixMode(GL_PROJECTION);
    glGetFloatv(GL_PROJECTION_MATRIX, projection_matrix);

    glMatrixMode(GL_MODELVIEW);
    glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix);

    for (int i = 0; i < 16; i++)
    {
        printf("%f ", projection_matrix[i]);
    }
    printf("\nthe modelview:\n");
    for (int j = 0; j < 16; j++)
    {
        printf("%f ", modelview_matrix[j]);
    }

    // Invert the projection matrix
    GLfloat inverted_projection_matrix[16];
    invert_matrix(projection_matrix, inverted_projection_matrix);
    printf("\nthe inverted projection:\n");
    for (int j = 0; j < 16; j++)
    {
        printf("%f ", inverted_projection_matrix[j]);
    }

    // Construct the clip space coordinates
    GLfloat clip_x = ndc_x;
    GLfloat clip_y = ndc_y;
    GLfloat clip_z = -1.0f;
    GLfloat clip_w = 1.0f;

    // Apply the inverse projection matrix
    
    GLfloat view_x = inverted_projection_matrix[0] * clip_x + inverted_projection_matrix[4] * clip_y + inverted_projection_matrix[8] * clip_z + inverted_projection_matrix[12] * clip_w;
    GLfloat view_y = inverted_projection_matrix[1] * clip_x + inverted_projection_matrix[5] * clip_y + inverted_projection_matrix[9] * clip_z + inverted_projection_matrix[13] * clip_w;
    GLfloat view_z = inverted_projection_matrix[2] * clip_x + inverted_projection_matrix[6] * clip_y + inverted_projection_matrix[10] * clip_z + inverted_projection_matrix[14] * clip_w;
    GLfloat view_w = inverted_projection_matrix[3] * clip_x + inverted_projection_matrix[7] * clip_y + inverted_projection_matrix[11] * clip_z + inverted_projection_matrix[15] * clip_w;

    // Divide by the w-component
    if (view_w != 0.0f)
    {
        view_x /= view_w;
        view_y /= view_w;
        view_z /= view_w;
    }

    // Apply the inverse modelview matrix
    GLfloat inverted_modelview_matrix[16];
    invert_matrix(modelview_matrix, inverted_modelview_matrix);
    GLfloat object_x = inverted_modelview_matrix[0] * view_x + inverted_modelview_matrix[4] * view_y + inverted_modelview_matrix[8] * view_z + inverted_modelview_matrix[12];
    GLfloat object_y = inverted_modelview_matrix[1] * view_x + inverted_modelview_matrix[5] * view_y + inverted_modelview_matrix[9] * view_z + inverted_modelview_matrix[13];
    GLfloat object_z = inverted_modelview_matrix[2] * view_x + inverted_modelview_matrix[6] * view_y + inverted_modelview_matrix[10] * view_z + inverted_modelview_matrix[14];

    printf("\nThe inverted modelview matrix:\n");
    for (int j = 0; j < 16; j++)
    {
        printf("%f ", inverted_modelview_matrix[j]);
    }
    printf("\n");
    printf("Object space coordinates: (%f, %f, %f)\n", object_x, object_y, object_z);

    printf("View space coordinates: (%f, %f, %f)\n", view_x, view_y, view_z);

    ray->direction_vector.x = object_x;
    ray->direction_vector.y = object_y;
    ray->direction_vector.z = object_z;

    ray->origin.x = position.x;
    ray->origin.y = position.y;
    ray->origin.z = position.z;

    printf("Ray origin: (%f, %f, %f)\n", ray->origin.x, ray->origin.y, ray->origin.z);

    printf("Ray  direction vector: (%f, %f, %f)\n", ray->direction_vector.x, ray->direction_vector.y, ray->direction_vector.z);

    // Normalize the direction vector
    float length = sqrt(ray->direction_vector.x * ray->direction_vector.x + ray->direction_vector.y * ray->direction_vector.y + ray->direction_vector.z * ray->direction_vector.z);
    ray->direction_vector.x /= length;
    ray->direction_vector.y /= length;
    ray->direction_vector.z /= length;

    printf("Normalized Ray direction vector: (%f, %f, %f)\n", ray->direction_vector.x, ray->direction_vector.y, ray->direction_vector.z);
}

int ray_box_intersection(Ray *ray, BoundingBox *box)
{
    vec3 inv_direction;
    inv_direction.x = 1.0f * ray->direction_vector.x;
    inv_direction.y = 1.0f * ray->direction_vector.y;
    inv_direction.z = 1.0f * ray->direction_vector.z;
    printf("Inverse calculated!\n");
    printf("inverse: %f %f %f \n", inv_direction.x, inv_direction.y, inv_direction.z);

    float t1 = (box->min.x - ray->origin.x) * inv_direction.x;
    float t2 = (box->max.x - ray->origin.x) * inv_direction.x;

    float t3 = (box->min.y - ray->origin.y) * inv_direction.y;
    float t4 = (box->max.y - ray->origin.y) * inv_direction.y;

    float t5 = (box->min.z - ray->origin.z) * inv_direction.z;
    float t6 = (box->max.z - ray->origin.z) * inv_direction.z;
    printf("tmin/max -es calculated\n");
    printf("ts: %f %f, %f %f, %f %f\n", t1, t2, t3, t4, t5, t6);

    float tmin = fmax(fmax(fmin(t1, t2), fmin(t3, t4)), fmin(t5, t6));
    float tmax = fmin(fmin(fmax(t1, t2), fmax(t3, t4)), fmax(t5, t6));
    // float tmin = fmax(fmax(t1, t3), t5);
    // float tmax = fmin(fmin(t2, t4), t6);
    printf("tmax and tmin determined\n");
    printf("%f tmax, %f tmin\n", tmax, tmin);

    if (tmax < 0.0f)
    {
        // Ray intersects the box, but it is behind us
        printf("Object is behind us.\n");
        return 0;
    }

    if (tmin > tmax)
    {
        printf("No intersection.\n");
        // Ray doesn't intersect the box
        return 0;
    }

    return 1;
}
