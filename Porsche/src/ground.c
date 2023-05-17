#include "ground.h"

void init_ground(Ground* ground)
{
    load_model(&(ground->ground), "assets/models/ground.obj");
    ground->ground_texture_id = load_texture("assets/textures/ground.webp");
}

void render_ground(Ground* ground)
{
    // ground
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, ground->ground_texture_id);
    glScalef(0.5, 0.5, 0.5);
    glRotated(90, 1, 0, 0);
    glTranslatef(0, 0, 0);
    draw_model(&(ground->ground));
    glPopMatrix();
}