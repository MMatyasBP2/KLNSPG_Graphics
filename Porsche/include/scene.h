#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include <obj/model.h>
#include <math.h>

#define NUM_RAINDROPS 1000

typedef struct Scene
{
    Material material;
 
    Model firsthouse;
    Model secondhouse;
    Model thirdhouse;
    Model fourthhouse;
    GLuint house_texture_id;
 
    Model porsche;
    GLuint porsche_texture_id;

    Model ground;
    GLuint ground_texture_id;
    
    float light;
    int showhelp;
    float secondhousey;
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
 * Draw help with F1
*/
void help();

void drawEnd();

/**
 * Draw water
*/
void draw_water();

#endif /* SCENE_H */
