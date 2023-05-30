#include "scene.h"

#include <obj/load.h>
#include <obj/draw.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init_scene(Scene *scene)
{
    glEnable(GL_FOG);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    GLfloat fog_color[] = {0.1f, 0.9f, 0.5f, 1.0f};
    glFogfv(GL_FOG_COLOR, fog_color);
    glFogf(GL_FOG_START, 1);
    glFogf(GL_FOG_END, 20);
    glFogf(GL_FOG_DENSITY, 1.5);

    srand((unsigned)time(NULL));

    for (int i = 0; i < NUM_GHOST; i++)
    {
        init_ghost(&(scene->ghosts[i]));
    }

    for (int i = 0; i < NUM_KID; i++)
    {
        init_kid(&(scene->kids[i]));
    }

    for (int i = 0; i < NUM_KID - 1; i++)
    {
        for (int j = 1; j < NUM_KID; j++)
        {
            if (check_collision(&(scene->kids[i].box), &(scene->kids[j].box)) == 1)
            {
                handle_collision(&(scene->kids[i].box), &(scene->kids[j].box), &(scene->kids[i].position));
            }
            
        }
        
    }

    for (int i = 0; i < NUM_GHOST - 1; i++)
    {
        for (int j = 1; j < NUM_GHOST; j++)
        {
            if (check_collision(&(scene->ghosts[i].box), &(scene->ghosts[j].box)) == 1)
            {
                handle_collision(&(scene->ghosts[i].box), &(scene->ghosts[j].box), &(scene->ghosts[i].position));
            }
            
        }
        
    }

    for (int i = 0; i < NUM_GHOST; i++)
    {
        for (int j = 0; j < NUM_KID; j++)
        {
            if (check_collision(&(scene->ghosts[i].box), &(scene->kids[j].box)) == 1)
            {
                handle_collision(&(scene->ghosts[i].box), &(scene->kids[j].box), &(scene->ghosts[i].position));
            }
            
        }
        
    }
    

    scene->material.ambient.red = 0.7;
    scene->material.ambient.green = 0.7;
    scene->material.ambient.blue = 0.7;

    scene->material.diffuse.red = 0.7;
    scene->material.diffuse.green = 0.7;
    scene->material.diffuse.blue = 0.7;

    scene->material.specular.red = 0.2;
    scene->material.specular.green = 0.2;
    scene->material.specular.blue = 0.2;

    scene->material.shininess = 3.0;
}

void set_lighting()
{
    double current_time;
    current_time = (double)SDL_GetTicks() / 1000;
    float ambient_value = 1.0f;
    float diffuse_value = sin(current_time);
    float ambient_light[] = {ambient_value, ambient_value, ambient_value, ambient_value};
    float diffuse_light[] = {diffuse_value, diffuse_value, diffuse_value, diffuse_value};
    float specular_light[] = {1.0f, 1.0f, 1.0f, 1.0f};
    float position[] = {0.0f, 0.0f, 1.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    GLfloat lmodel_ambient[] = {0.9, 0.9, 0.9, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
}

void set_material(const Material *material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue};

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue};

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene *scene)
{
    for (int i = 0; i < NUM_GHOST; i++)
    {
        levitate(&(scene->ghosts[i]));
    }
}

void render_scene(const Scene *scene)
{
    set_lighting();
    draw_origin();
    draw_ground();

    for (int i = 0; i < NUM_KID; i++)
    {
        render_kid(&(scene->kids[i]));
    }

    for (int i = 0; i < NUM_GHOST; i++)
    {
        render_ghost(&(scene->ghosts[i]));
    }

}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}

void draw_ground()
{
    glBegin(GL_QUADS);

    glColor3f(0.9f, 0.9f, 0.9f);
    glVertex3f(-20.0f, -20.0f, 0.0f);
    glVertex3f(-20.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, -20.0f, 0.0f);

    glColor3f(0.9f, 0.9f, 0.9f);
    glVertex3f(0.0f, -20.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(20.0f, 0.0f, 0.0f);
    glVertex3f(20.0f, -20.0f, 0.0f);

    glColor3f(0.9f, 0.9f, 0.9f);
    glVertex3f(-20.0f, 0.0f, 0.0f);
    glVertex3f(-20.0f, 20.0f, 0.0f);
    glVertex3f(0.0f, 20.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);

    glColor3f(0.9f, 0.9f, 0.9f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 20.0f, 0.0f);
    glVertex3f(20.0f, 20.0f, 0.0f);
    glVertex3f(20.0f, 0.0f, 0.0f);

    glEnd();
}
