#include "cuboid.h"
#include <stdio.h>
#include <math.h>

void set_size(Cuboid* cuboid, float length, float width, float height) {
    cuboid->length = length;
    cuboid->width = width;
    cuboid->height = height;
}

float calc_volume(Cuboid cuboid) {
    return cuboid.length * cuboid.width * cuboid.height;
}

float calc_surface(Cuboid cuboid) {
    return 2 * (cuboid.length * cuboid.width + cuboid.width * cuboid.height + cuboid.height * cuboid.length);
}

bool has_square_face(Cuboid cuboid) {
    if (cuboid.length == cuboid.width * cuboid.height ||
        cuboid.width == cuboid.length * cuboid.height ||
        cuboid.height == cuboid.length * cuboid.width) 
    {
        return true;
    }

    return false;
}

float read_sides(char *msg)
{
    float num;
    bool ok;
    
    do
    {
        ok = true;
        puts(msg);
        if (scanf("%f", &num) != 1)
        {
            printf("Bad input format!\n");
            ok = false;
            while (getchar() != '\n');
        }
    } while (!ok);

    return num;
}