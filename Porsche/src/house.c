#include "house.h"

void init_house(House* house)
{
    load_model(&(house->firsthouse), "assets/models/house.obj");
    load_model(&(house->secondhouse), "assets/models/house.obj");
    load_model(&(house->thirdhouse), "assets/models/house.obj");
    load_model(&(house->fourthhouse), "assets/models/house.obj");
    house->house_texture_id = load_texture("assets/textures/house.jpg");
    house->secondhousey = -17.0f;
}

void render_house(House* house)
{
    // firsthouse
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, house->house_texture_id);
    glScalef(0.03f, 0.03f, 0.03f);
    glRotated(90, 1, 0, 0);
    glTranslatef(200.0f, -17.0f, -200.0f);
    draw_model(&(house->firsthouse));
    glPopMatrix();

    // secondhouse
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, house->house_texture_id);
    glScalef(0.04f, 0.04f, 0.04f);
    glRotated(90, 1, 0, 0);
    glTranslatef(-100.0f, house->secondhousey, 100.0f);
    draw_model(&(house->secondhouse));
    glPopMatrix();

    // thirdhouse
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, house->house_texture_id);
    glScalef(0.03f, 0.03f, 0.03f);
    glRotated(90, 1, 0, 0);
    glTranslatef(200.0f, -17.0f, 100.0f);
    draw_model(&(house->thirdhouse));
    glPopMatrix();

    // fourthhouse
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, house->house_texture_id);
    glScalef(0.03f, 0.03f, 0.03f);
    glRotated(90, 1, 0, 0);
    glTranslatef(-100.0f, -17.0f, -200.0f);
    draw_model(&(house->fourthhouse));
    glPopMatrix();
}