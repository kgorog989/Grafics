#ifndef GHOST_H
#define GHOST_H

#include "camera.h"
#include "texture.h"
#include "collision.h"

#include <obj/model.h>

#define NUM_GHOST 20
#define GHOST_POINT 1

typedef struct Ghost
{
    Model model;
    GLuint texture_id;
    vec3 position;
    float size;
    BoundingBox box;
    int are_friends;
} Ghost;


/**
 * Initialize the ghost.
 */
void init_ghost(Ghost* ghost);

/**
 * Render the ghost.
 */
void render_ghost(const Ghost* ghost);

/**
 * Levitating animation.
*/
void levitate(Ghost* ghost);


#endif /* GHOST_H */
