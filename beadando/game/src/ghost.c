#include "ghost.h"

#include <obj/load.h>
#include <obj/draw.h>

#include <SDL2/SDL.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void init_ghost(Ghost* ghost)
{
    ghost->position.x = -20 + ((float)rand() / RAND_MAX) * 40;
    ghost->position.y = -20 + ((float)rand() / RAND_MAX) * 40;
    ghost->position.z = 0.5;
    ghost->size = 0.1;
    ghost->are_friends = 0;
    
    load_model(&(ghost->model), "assets/models/SheetGhost.obj");
    ghost->texture_id = load_texture("assets/textures/SheetGhost.png");

    calculate_bounding_box(&(ghost->box), "assets/models/SheetGhost.obj", ghost->position, ghost->size);

}

void render_ghost(const Ghost* ghost)
{
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, ghost->texture_id);
    glTranslatef(ghost->position.x, ghost->position.y, ghost->position.z);
    glScalef(ghost->size, ghost->size, ghost->size);
    draw_model(&(ghost->model));
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}

void levitate(Ghost* ghost)
{
    double current_time;
    current_time = (double)SDL_GetTicks() / 1000;
    ghost->position.z = sin(current_time) / 6 + 0.5;
}
