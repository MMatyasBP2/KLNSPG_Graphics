#ifndef HOUSE_H
#define HOUSE_H

#include <obj/model.h>
#include <GL/gl.h>
#include <obj/load.h>
#include <obj/draw.h>

typedef struct House
{
    Model firsthouse;
    Model secondhouse;
    Model thirdhouse;
    Model fourthhouse;
    GLuint house_texture_id;
    float secondhousey;
} House;

void init_house(House* house);
void render_house(House* house);

#endif