#ifndef KID_H
#define KID_H

#include "camera.h"
#include "texture.h"
#include "collision.h"

#include <obj/model.h>

typedef struct Kid
{
    Model model;
    GLuint texture_id;
    vec3 position;
    float size;
    BoundingBox box;
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
