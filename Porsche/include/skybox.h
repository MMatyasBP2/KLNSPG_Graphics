#ifndef SKYBOX_H
#define SKYBOX_H
 
#include <obj/load.h>
#include <obj/draw.h>
#include <GL/gl.h>
#include "texture.h"
 
typedef struct Skybox {
    GLuint skybox;
} Skybox;
 
void init_skybox(Skybox* skybox);
void render_skybox(const Skybox *skybox);
 
 
 
#endif /*SKYBOX_H*/