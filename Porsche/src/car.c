#include "car.h"

void init_car(Car* car)
{
    load_model(&(car->porsche), "assets/models/porsche.obj");
    car->porsche_texture_id = load_texture("assets/textures/car.png");
}

void render_car(Car* car)
{
    // porsche
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, car->porsche_texture_id);
    glScalef(0.7f, 0.7f, 0.7f);
    glRotated(90.0f, 1.0f, 0.0f, 0.0f);
    glTranslatef(-8.0f, 0.58f, 7.0f);
    draw_model(&(car->porsche));
    glPopMatrix();
}