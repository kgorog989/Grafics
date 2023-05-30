#include "kid.h"

#include <obj/load.h>
#include <obj/draw.h>

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void init_kid(Kid* kid)
{
    kid->position.x = -20 + ((float)rand() / RAND_MAX) * 40;
    kid->position.y = -20 + ((float)rand() / RAND_MAX) * 40;
    kid->position.z = 0;
    kid->size = 0.9;
    kid->are_friends = 0;
    
    load_model(&(kid->model), "assets/models/Kid.obj");
    kid->texture_id = load_texture("assets/textures/Kid.png");

    calculate_bounding_box(&(kid->box), "assets/models/Kid.obj", kid->position, kid->size);

}

void render_kid(const Kid* kid)
{
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, kid->texture_id);
    glTranslatef(kid->position.x, kid->position.y, kid->position.z);
    glScalef(kid->size, kid->size, kid->size);
    draw_model(&(kid->model));
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}
