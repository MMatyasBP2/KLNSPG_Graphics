#ifndef HOUSE_H
#define HOUSE_H

#include <GL/gl.h>
#include <obj/model.h>
#include <obj/load.h>
#include <obj/draw.h>
#include "texture.h"
#include "utils.h"

typedef struct House
{
    Model firsthouse;
    Model secondhouse;
    Model thirdhouse;
    Model fourthhouse;
    
    vec3 v_firsthouse_trans;
    vec3 v_secondhouse_trans;
    vec3 v_thirdhouse_trans;
    vec3 v_fourthhouse_trans;

    vec3 v_firsthouse_scale;
    vec3 v_secondhouse_scale;
    vec3 v_thirdhouse_scale;
    vec3 v_fourthhouse_scale;

    GLuint house_texture_id;
} House;

void init_house(House* house);
void render_house(House* house);

#endif