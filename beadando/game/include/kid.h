#ifndef KID_H
#define KID_H

#include "camera.h"
#include "texture.h"
#include "collision.h"

#include <obj/model.h>

#define NUM_KID 20
#define KID_POINT 3

typedef struct Kid
{
    Model model;
    GLuint texture_id;
    vec3 position;
    float size;
    BoundingBox box;
    int are_friends;
} Kid;


/**
 * Initialize the kid.
 */
void init_kid(Kid* kid);

/**
 * Render the ghost.
 */
void render_kid(const Kid* kid);


#endif /* KID_H */
