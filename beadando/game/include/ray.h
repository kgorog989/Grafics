#ifndef RAY_H
#define RAY_H

#include "utils.h"
#include "collision.h"

typedef struct Ray
{
    vec3 origin;
    vec3 direction_vector;
} Ray;

/**
 * Initialize ray casted by a mouse click
*/
void init_ray(Ray* ray, float ndc_x, float ndc_y, vec3 position);

/**
 * Check if a ray intersects with a bounding box
*/
int ray_box_intersection(Ray* ray, BoundingBox* box);

#endif /* RAY_H */
