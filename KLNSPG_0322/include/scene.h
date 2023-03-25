#ifndef SCENE_H
#define SCENE_H

#include "camera.h"

typedef struct Scene
{
    // NOTE: Place for model structures and texture ids.
} Scene;

void init_scene(Scene* scene);
void draw_scene(const Scene* scene);
void draw_origin();

#endif /* SCENE_H */
