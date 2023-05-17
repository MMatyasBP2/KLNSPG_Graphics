#ifndef WATER_H
#define WATER_H

#include <GL/gl.h>

typedef struct Water
{
    float waterPoints[45][45][3];
    float amplitude;
    float frequency;
    float delta;
    GLuint water_texture_id;
} Water;

void init_water(Water *water);
void update_water(Water *water, double elapsed_time);
void render_water(Water *water);
void set_water_settings();

#endif