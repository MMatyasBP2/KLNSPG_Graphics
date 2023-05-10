#include "app.h"
#include <SDL2/SDL_image.h>

void init_app(App* app, int width, int height)
{
    int error_code;
    int inited_loaders;

    app->is_running = false;

    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code != 0) {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return;
    }

    app->window = SDL_CreateWindow(
        "Find the Porsche!",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_OPENGL);
    if (app->window == NULL) {
        printf("[ERROR] Unable to create the application window!\n");
        return;
    }

    inited_loaders = IMG_Init(IMG_INIT_PNG);
    if (inited_loaders == 0) {
        printf("[ERROR] IMG initialization error: %s\n", IMG_GetError());
        return;
    }

    app->gl_context = SDL_GL_CreateContext(app->window);
    if (app->gl_context == NULL) {
        printf("[ERROR] Unable to create the OpenGL context!\n");
        return;
    }

    init_opengl();
    reshape(width, height);

    init_camera(&(app->camera));
    init_scene(&(app->scene));

    app->is_running = true;
    app->house_state = HOUSE_STATIONARY;
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
    if (ratio > VIEWPORT_RATIO) {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else {
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
        .1, 1000
    );
}

void handle_app_events(App* app)
{
    SDL_Event event;
    static bool is_mouse_down = false;
    static int mouse_x = 0;
    static int mouse_y = 0;
    int x;
    int y;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_ESCAPE:
                app->is_running = false;
                break;
            case SDL_SCANCODE_W:
                if (app->scene.enablemovement == 1)
                    set_camera_speed(&(app->camera), 1);
                break;
            case SDL_SCANCODE_S:
                if (app->scene.enablemovement == 1)
                    set_camera_speed(&(app->camera), -1);
                break;
            case SDL_SCANCODE_A:
                if (app->scene.enablemovement == 1)
                    set_camera_side_speed(&(app->camera), 1);
                break;
            case SDL_SCANCODE_D:
                if (app->scene.enablemovement == 1)
                    set_camera_side_speed(&(app->camera), -1);
                break;
            case SDL_SCANCODE_KP_PLUS:
                app->scene.light += 0.1f;
                break;
            case SDL_SCANCODE_KP_MINUS:
                app->scene.light -= 0.1f;
                break;
            case SDL_SCANCODE_F1:
                if (app->scene.showhelp == 0)
                    app->scene.showhelp = 1;
                else
                {
                    app->scene.showhelp = 0;
                    glFrustum(
                        -.08, .08,
                        -.06, .06,
                        .1, 6000);
                }
                break;
            case SDL_SCANCODE_1:
                app->house_state = HOUSE_MOVING_UP;
                break;
            case SDL_SCANCODE_2:
                app->house_state = HOUSE_MOVING_DOWN;
                break;
            case SDL_SCANCODE_3:
                if (app->scene.fogenable == 0)
                {
                    glEnable(GL_FOG);
                    app->scene.fogenable = 1;
                }
                else
                {
                    glDisable(GL_FOG);
                    app->scene.fogenable = 0;
                }
                app->scene.fogposition += 0.02f * app->scene.fogdirection; // Lassabb mozgás: csökkentett érték (0.02f)

                // Ha eléri a köd a felső vagy az alsó határt, változtassuk meg az irányt
                // Magasabb határérték: 20.0f (az eredeti 10.0f helyett)
                if (app->scene.fogposition >= 20.0f || app->scene.fogposition <= -20.0f)
                {
                    app->scene.fogdirection *= -1.0f;
                }

                GLfloat fogColor[] = {0.5f, 0.5f, 0.5f, 1.0f};
                glFogfv(GL_FOG_COLOR, fogColor);
                glFogi(GL_FOG_MODE, GL_LINEAR);
                glFogf(GL_FOG_START, app->scene.fogposition);
                glFogf(GL_FOG_END, app->scene.fogposition + 10.0f);
                break;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.scancode) {
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
        case SDL_MOUSEBUTTONDOWN:
            is_mouse_down = true;
            break;
        case SDL_MOUSEMOTION:
            if (app->scene.enablemovement == 1)
            {
                SDL_GetMouseState(&x, &y);
                if (is_mouse_down) {
                    rotate_camera(&(app->camera), mouse_x - x, mouse_y - y);
                }
                mouse_x = x;
                mouse_y = y;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            is_mouse_down = false;
            break;
        case SDL_QUIT:
            app->is_running = false;
            break;
        default:
            break;
        }
    }
}

void update_app(App* app)
{
    double current_time;
    double elapsed_time;

    current_time = (double)SDL_GetTicks() / 1000;
    elapsed_time = current_time - app->uptime;
    app->uptime = current_time;

    update_camera(&(app->camera), elapsed_time);
    update_scene(&(app->scene), elapsed_time);
    update_water(&(app->water), elapsed_time);

    if ((app->camera.position.x < -17.662912) || (app->camera.position.x > 17.487240))
        app->camera.position.x -= 0.2;

    if ((app->camera.position.y < -17.662912) || (app->camera.position.y > 17.662912))
        app->camera.position.y -= 0.2;

    if (calc_collision(&(app->camera), 5.223761, -3.462567, 2.5, 2.5) == 1)
    {
        app->camera.position.x -= 0.2;
        app->camera.position.y -= 0.2;
    }
 
    if (calc_collision(&(app->camera), 5.355745, 5.742432, 2.6, 2.6) == 1)
    {
        app->camera.position.x -= 0.2;
        app->camera.position.y -= 0.2;
    }

    if (calc_collision(&(app->camera), -3.569052, 5.748179, 2.5, 2.5) == 1)
    {
        app->camera.position.x -= 0.2;
        app->camera.position.y -= 0.2;
    }

    if (calc_collision(&(app->camera), -5.083924, -4.747217, 0.3f, 0.3f) == 1)
	{
        app->camera.position.x -= 0.2;
        app->camera.position.y -= 0.2;
        app->scene.endgame = 1;
        app->scene.enablemovement = 0;
	}
}

int calc_collision(Camera *camera, float posX, float posY, float boxSizeX, float boxSizeY)
{
 
    if ((camera->position.x > posX - boxSizeX) && (camera->position.x < posX + boxSizeX))
        if ((camera->position.y > posY - boxSizeY) && (camera->position.y < posY + boxSizeY))
            return 1;
    return 0;
}

void render_app(App* app)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    set_view(&(app->camera));
    render_scene(&(app->scene));
    glPopMatrix();

    if (app->camera.is_preview_visible)
        show_texture_preview();

    if (app->scene.showhelp == 1)
        help(&(app->scene));

    if (app->house_state == HOUSE_MOVING_UP && app->scene.secondhousey < 100.0f)
        app->scene.secondhousey += 0.1f;
    else if (app->house_state == HOUSE_MOVING_UP)
        app->house_state = HOUSE_STATIONARY;
    

    if (app->house_state == HOUSE_MOVING_DOWN && app->scene.secondhousey > -17.0f)
        app->scene.secondhousey -= 0.1f;
    else if (app->house_state == HOUSE_MOVING_DOWN)
        app->house_state = HOUSE_STATIONARY;

    SDL_GL_SwapWindow(app->window);
}

void destroy_app(App* app)
{
    if (app->gl_context != NULL) {
        SDL_GL_DeleteContext(app->gl_context);
    }

    if (app->window != NULL) {
        SDL_DestroyWindow(app->window);
    }

    SDL_Quit();
}
