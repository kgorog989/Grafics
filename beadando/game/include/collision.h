#ifndef COLLISION_H
#define COLLISION_H

#include "utils.h"

typedef struct BoundingBox
{
    vec3 min;
    vec3 max;
    vec3 dimensions;
} BoundingBox;

/**
 * Calculate bounding box.
 */
void calculate_bounding_box(BoundingBox* box, const char* model_file, vec3 position, float size);

/**
 * Check if collision occured.
*/
int check_collision(BoundingBox* box1, BoundingBox* box2);

/**
 * Handle collision.
*/
void handle_collision(BoundingBox* box1, BoundingBox* box2, vec3* position, vec3* speed);

#endif /* COLLISION_H */
