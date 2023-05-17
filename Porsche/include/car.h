#ifndef CAR_H
#define CAR_H

#include <obj/model.h>
#include <GL/gl.h>
#include <obj/load.h>
#include <obj/draw.h>
#include "texture.h"

typedef struct Car
{
    Model porsche;
    GLuint porsche_texture_id;
} Car;

void init_car(Car* car);
void render_car(Car* car);

#endif