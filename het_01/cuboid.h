#ifndef CUBOID_H
#define CUBOID_H

#include <stdbool.h>

typedef struct {
    float length;
    float width;
    float height;
} Cuboid;

void set_size(Cuboid* cuboid, float length, float width, float height);
float calc_volume(Cuboid cuboid);
float calc_surface(Cuboid cuboid);
bool has_square_face(Cuboid cuboid);
float read_sides(char *msg);

#endif /* CUBOID_H */