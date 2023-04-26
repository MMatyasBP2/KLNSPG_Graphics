#ifndef WATER_H
#define WATER_H


typedef struct Water
{
    float delta;
} Water;

void init_water(const Water *water);
void update_water(const Water *water, double elapsed_time);
void render_water(const Water *water);

#endif