#ifndef GROUND_H
#define GROUND_H

#include <obj/model.h>
#include <GL/gl.h>
#include <obj/load.h>
#include <obj/draw.h>

typedef struct Ground
{
    Model ground;
    GLuint ground_texture_id;
} Ground;

void init_ground(Ground* ground);
void render_ground(Ground* ground);

#endif