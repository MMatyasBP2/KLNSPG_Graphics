#include "house.h"
#include "utils.h"

void init_house(House* house)
{
    load_model(&(house->firsthouse), "assets/models/house.obj");
    load_model(&(house->secondhouse), "assets/models/house.obj");
    load_model(&(house->thirdhouse), "assets/models/house.obj");
    load_model(&(house->fourthhouse), "assets/models/house.obj");
    
    house->house_texture_id = load_texture("assets/textures/house.jpg");

    house->v_firsthouse_trans = (vec3){200.0f, -17.0f, -200.0f};
    house->v_secondhouse_trans = (vec3){-100.0f, -17.0f, 100.0f};
    house->v_thirdhouse_trans = (vec3){200.0f, -17.0f, 100.0f};
    house->v_fourthhouse_trans = (vec3){-100.0f, -17.0f, -200.0f};

    house->v_firsthouse_scale = (vec3){0.03f, 0.03f, 0.03f};
    house->v_secondhouse_scale = (vec3){0.04f, 0.04f, 0.04f};
    house->v_thirdhouse_scale = (vec3){0.03f, 0.03f, 0.03f};
    house->v_fourthhouse_scale = (vec3){0.03f, 0.03f, 0.03f};
}

void render_house(House* house)
{
    render_a_house(house->v_firsthouse_trans, house->v_firsthouse_scale, house->firsthouse);
    render_a_house(house->v_secondhouse_trans, house->v_secondhouse_scale, house->secondhouse);
    render_a_house(house->v_thirdhouse_trans, house->v_thirdhouse_scale, house->thirdhouse);
    render_a_house(house->v_fourthhouse_trans, house->v_fourthhouse_scale, house->fourthhouse);
}

void render_a_house(vec3 trans, vec3 scale, House house)
{
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, 1);
    glScalef(scale.x, scale.y, scale.z);
    glRotated(90, 1, 0, 0);
    glTranslatef(trans.x, trans.y, trans.z);
    draw_model(&(house));
    glPopMatrix();
}