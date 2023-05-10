#ifndef APP_H
#define APP_H

#include "camera.h"
#include "scene.h"
#include "water.h"
#include <SDL2/SDL.h>
#include <stdbool.h>

#define VIEWPORT_RATIO (16.0 / 9.0)
#define VIEWPORT_ASPECT 100.0

typedef enum
{
    HOUSE_STATIONARY,
    HOUSE_MOVING_UP,
    HOUSE_MOVING_DOWN
} HouseState;


typedef struct App
{
    SDL_Window* window;
    SDL_GLContext gl_context;
    bool is_running;
    double uptime;
    Camera camera;
    Scene scene;
    Water water;
    HouseState house_state;
} App;

/**
 * Initialize the application.
 */
void init_app(App* app, int width, int height);

/**
 * Initialize the OpenGL context.
 */
void init_opengl();

/**
 * Reshape the window.
 */
void reshape(GLsizei width, GLsizei height);

/**
 * Handle the events of the application.
 */
void handle_app_events(App* app);

/**
 * Update the application.
 */
void update_app(App* app);

/**
 * Render the application.
 */
void render_app(App* app);

/**
 * Destroy the application.
 */
void destroy_app(App* app);

int calc_collision(Camera *camera, float posX, float posY, float boxSizeX, float boxSizeY);

#endif /* APP_H */
