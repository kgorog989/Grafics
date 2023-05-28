#include <stdio.h>
#include <math.h>

#include "app.h"

#include <SDL2/SDL_image.h>

void init_app(App *app, int width, int height)
{
    int error_code;
    int inited_loaders;

    app->is_running = false;

    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code != 0)
    {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return;
    }

    app->window = SDL_CreateWindow(
        "Cube!",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_OPENGL);
    if (app->window == NULL)
    {
        printf("[ERROR] Unable to create the application window!\n");
        return;
    }

    inited_loaders = IMG_Init(IMG_INIT_PNG);
    if (inited_loaders == 0)
    {
        printf("[ERROR] IMG initialization error: %s\n", IMG_GetError());
        return;
    }

    app->gl_context = SDL_GL_CreateContext(app->window);
    if (app->gl_context == NULL)
    {
        printf("[ERROR] Unable to create the OpenGL context!\n");
        return;
    }

    init_opengl();
    reshape(width, height);

    init_camera(&(app->camera));
    init_scene(&(app->scene));

    app->is_running = true;

    app->score = 0;

    app->show_help = false;
}

void init_opengl()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(0.1, 0.1, 0.1, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO)
    {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else
    {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(
        -.08, .08,
        -.06, .06,
        .1, 10);
}

void handle_app_events(App *app)
{
    SDL_Event event;
    static int mouse_x = 0;
    static int mouse_y = 0;
    int x;
    int y;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_ESCAPE:
                app->is_running = false;
                break;
            case SDL_SCANCODE_F1:
                app->show_help = true;
                break;
            case SDL_SCANCODE_W:
                set_camera_speed(&(app->camera), 1);
                break;
            case SDL_SCANCODE_S:
                set_camera_speed(&(app->camera), -1);
                break;
            case SDL_SCANCODE_A:
                set_camera_side_speed(&(app->camera), 1);
                break;
            case SDL_SCANCODE_D:
                set_camera_side_speed(&(app->camera), -1);
                break;
            case SDL_SCANCODE_SPACE:
                handle_friends(app);
                break;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_F1:
                app->show_help = false;
                break;
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_S:
                set_camera_speed(&(app->camera), 0);
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_D:
                set_camera_side_speed(&(app->camera), 0);
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&x, &y);
            rotate_camera(&(app->camera), mouse_x - x, mouse_y - y);
            mouse_x = x;
            mouse_y = y;
            break;
        case SDL_QUIT:
            app->is_running = false;
            break;
        default:
            break;
        }
    }
}

void update_app(App *app)
{
    double current_time;
    double elapsed_time;

    current_time = (double)SDL_GetTicks() / 1000;
    elapsed_time = current_time - app->uptime;
    app->uptime = current_time;

    update_camera(&(app->camera), elapsed_time);
    update_scene(&(app->scene));

    for (int i = 0; i < NUM_KID; i++)
    {
        int check_kid = check_collision(&(app->camera.box), &(app->scene.kids[i].box));
        if (check_kid == 1)
        {
            handle_collision(&(app->camera.box), &(app->scene.kids[i].box), &(app->camera.position), &(app->camera.speed));
        }
    }

    for (int i = 0; i < NUM_GHOST; i++)
    {
        int check_ghost = check_collision(&(app->camera.box), &(app->scene.ghosts[i].box));
        if (check_ghost == 1)
        {
            handle_collision(&(app->camera.box), &(app->scene.ghosts[i].box), &(app->camera.position), &(app->camera.speed));
        }
    }
}

void render_app(App *app)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    set_view(&(app->camera));
    render_scene(&(app->scene));
    glPopMatrix();

    if (app->camera.is_preview_visible)
    {
        show_texture_preview();
    }

    if (app->show_help)
    {
        show_help_menu(app);
    }

    SDL_GL_SwapWindow(app->window);
}

void destroy_app(App *app)
{
    if (app->gl_context != NULL)
    {
        SDL_GL_DeleteContext(app->gl_context);
    }

    if (app->window != NULL)
    {
        SDL_DestroyWindow(app->window);
    }

    SDL_Quit();
}

void show_help_menu(App *app)
{
    app->help_texture_id = load_texture("assets/textures/help_menu.png");
    glBindTexture(GL_TEXTURE_2D, app->help_texture_id);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    // glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1, 1, -3);
    glTexCoord2f(1, 0);
    glVertex3f(1, 1, -3);
    glTexCoord2f(1, 1);
    glVertex3f(1, -1, -3);
    glTexCoord2f(0, 1);
    glVertex3f(-1, -1, -3);
    glEnd();

    // glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void handle_friends(App *app)
{
    float distance;
    for (int i = 0; i < NUM_KID; i++)
    {
        distance = sqrt(pow(app->scene.kids[i].position.x - app->camera.position.x, 2) +
                        pow(app->scene.kids[i].position.y - app->camera.position.y, 2) +
                        pow(app->scene.kids[i].position.z - app->camera.position.z, 2));

        if (distance < 2 && app->scene.kids[i].are_friends == 0)
        {
            printf("Made a friend!\n");
            printf("distance %f\n", distance);
            app->scene.kids[i].are_friends = 1;
            app->score += KID_POINT;
            printf("points: %d\n", app->score);
        }
    }
    for (int i = 0; i < NUM_GHOST; i++)
    {
        distance = sqrt(pow(app->scene.ghosts[i].position.x - app->camera.position.x, 2) +
                        pow(app->scene.ghosts[i].position.y - app->camera.position.y, 2) +
                        pow(app->scene.ghosts[i].position.z - app->camera.position.z, 2));

        if (distance < 2 && app->scene.ghosts[i].are_friends == 0)
        {
            printf("Made a friend!\n");
            printf("distance %f\n", distance);
            app->scene.ghosts[i].are_friends = 1;
            app->score += GHOST_POINT;
            printf("points: %d\n", app->score);
        }
    }
}
