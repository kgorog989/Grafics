#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include "ghost.h"
#include "kid.h"

#include <SDL2/SDL.h>

#include <obj/model.h>

#include <math.h>

typedef struct Scene
{
    Ghost ghosts[NUM_GHOST];
    Kid kids[NUM_KID];
    Material material;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting();

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Update the scene.
 */
void update_scene(Scene* scene);

/**
 * Render the scene objects.
 */
void render_scene(const Scene* scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

/**
 * Draw the ground.
*/
void draw_ground();


#endif /* SCENE_H */
