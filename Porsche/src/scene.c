#include "scene.h"
#include "app.h"

#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene* scene)
{
    load_model(&(scene->firsthouse), "assets/models/house.obj");
    load_model(&(scene->secondhouse), "assets/models/house.obj");
    load_model(&(scene->thirdhouse), "assets/models/house.obj");
    load_model(&(scene->fourthhouse), "assets/models/house.obj");
    load_model(&(scene->porsche), "assets/models/porsche.obj");
    load_model(&(scene->ground), "assets/models/ground.obj");
    scene->house_texture_id = load_texture("assets/textures/house.jpg");
    scene->porsche_texture_id = load_texture("assets/textures/car.png");
    scene->ground_texture_id = load_texture("assets/textures/ground.webp");
    scene->water_texture_id = load_texture("assets/textures/water.jpg");

    init_water(&(scene->water));

    scene->material.ambient.red = 0.0;
    scene->material.ambient.green = 0.0;
    scene->material.ambient.blue = 0.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 0.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 0.0;
    scene->light = 1.0f;
    scene->secondhousey = -17.0f;
    scene->showhelp = 0;
    scene->endgame = 0;
    scene->enablemovement = 1;
    scene->fogenable = 0;
    scene->fogposition = 0.0f;
    scene->fogdirection = 1.0f;
}

void set_lighting(float intensity)
{
    float ambient_light[] = { 0.2f * intensity, 0.2f * intensity, 0.2f * intensity, 1.0f };
    float diffuse_light[] = { 1.0f * intensity, 1.0f * intensity, 1.0f * intensity, 1.0f };
    float specular_light[] = { 0.5f * intensity, 0.5f * intensity, 0.5f * intensity, 1.0f };
    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene* scene, double elapsed_time)
{
    set_lighting(scene->light);
    update_water(&(scene->water), elapsed_time);
}

void render_scene(const Scene* scene)
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // firsthouse
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->house_texture_id);
    glScalef(0.03f, 0.03f, 0.03f);
    glRotated(90, 1, 0, 0);
    glTranslatef(200.0f, -17.0f, -200.0f);
    draw_model(&(scene->firsthouse));
    glPopMatrix();

    // secondhouse
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->house_texture_id);
    glScalef(0.04f, 0.04f, 0.04f);
    glRotated(90, 1, 0, 0);
    glTranslatef(-100.0f, scene->secondhousey, 100.0f);
    draw_model(&(scene->secondhouse));
    glPopMatrix();

    // thirdhouse
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->house_texture_id);
    glScalef(0.03f, 0.03f, 0.03f);
    glRotated(90, 1, 0, 0);
    glTranslatef(200.0f, -17.0f, 100.0f);
    draw_model(&(scene->thirdhouse));
    glPopMatrix();

    // fourthhouse
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->house_texture_id);
    glScalef(0.03f, 0.03f, 0.03f);
    glRotated(90, 1, 0, 0);
    glTranslatef(-100.0f, -17.0f, -200.0f);
    draw_model(&(scene->fourthhouse));
    glPopMatrix();

    // porsche
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->porsche_texture_id);
    glScalef(0.7f, 0.7f, 0.7f);
    glRotated(90.0f, 1.0f, 0.0f, 0.0f);
    glTranslatef(-8.0f, 0.58f, 7.0f);
    draw_model(&(scene->porsche));
    glPopMatrix();

    // ground
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->ground_texture_id);
    glScalef(0.5, 0.5, 0.5);
    glRotated(90, 1, 0, 0);
    glTranslatef(0, 0, 0);
    draw_model(&(scene->ground));
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->water_texture_id);
    glTranslatef(0.0f, 0.0f, -0.5f);
    render_water(&(scene->water));
    glPopMatrix();

    if (scene->endgame == 1)
        drawEnd(scene);

    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
}

void help(Scene *scene)
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_FOG);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, load_texture("assets/textures/help.jpg"));

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3d(-2, 1.5, -3);
    glTexCoord2f(1, 0);
    glVertex3d(2, 1.5, -3);
    glTexCoord2f(1, 1);
    glVertex3d(2, -1.5, -3);
    glTexCoord2f(0, 1);
    glVertex3d(-2, -1.5, -3);
    glEnd();
    if (scene->fogenable == 1)
        glEnable(GL_FOG);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}

void drawEnd(Scene *scene)
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_FOG);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, load_texture("assets/textures/end.jpg"));

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3d(-2, 1.5, -3);
    glTexCoord2f(1, 0);
    glVertex3d(2, 1.5, -3);
    glTexCoord2f(1, 1);
    glVertex3d(2, -1.5, -3);
    glTexCoord2f(0, 1);
    glVertex3d(-2, -1.5, -3);
    glEnd();
    if (scene->fogenable == 1)
        glEnable(GL_FOG);
    glEnable(GL_DEPTH_TEST);
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}