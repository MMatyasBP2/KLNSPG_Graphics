#ifndef WATER_H
#define WATER_H

typedef struct Water
{
    float waterPoints[45][45][3];
    float amplitude;
    float frequency;
    float delta;
} Water;

void init_water(Water *water);
void update_water(Water *water, double elapsed_time);
void render_water(Water *water);

#endif