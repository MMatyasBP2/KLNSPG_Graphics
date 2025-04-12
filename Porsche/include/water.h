#ifndef WATER_H
#define WATER_H

#include <GL/gl.h>
#include "texture.h"

#define MAX_VORTICES 1
#define WATER_TEXTURE_PATH "assets/textures/water.jpg"

typedef struct Vortex {
    float x, y;
    float phase;
} Vortex;

typedef struct Water {
    float waterPoints[45][45][3];
    float amplitude;
    float frequency;
    float delta;
    GLuint water_texture_id;
    Vortex vortices[MAX_VORTICES];
} Water;

void init_water(Water *water);
void update_water(Water *water, double elapsed_time);
void render_water(Water *water);
void set_water_settings();
float de_casteljau(float t, float p0, float p1, float p2, float p3);

#endif