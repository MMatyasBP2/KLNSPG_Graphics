#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include "water.h"
#include "skybox.h"
#include "house.h"
#include "car.h"
#include "ground.h"
#include <obj/model.h>
#include <math.h>

typedef struct Scene
{
    Material material;

    Car car;
    House house;
    Water water;
    Ground ground;
    Skybox skybox;

    float light;
    int showhelp;
    int endgame;
    int enablemovement;
    int fogenable;
    float fogposition;
    float fogdirection;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting(float x);

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Update the scene.
 */
void update_scene(Scene* scene, double elapsed_time);

/**
 * Render the scene objects.
 */
void render_scene(const Scene* scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

/**
 * Draw help with F1
*/
void help(Scene *scene);

void drawEnd(Scene *scene);

/**
 * Draw water
*/
void draw_water();

#endif /* SCENE_H */
