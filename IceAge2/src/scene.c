#include "scene.h"
#include "app.h"

#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene* scene)
{
    load_model(&(scene->housebig), "assets/models/house.obj");
    load_model(&(scene->housesmall), "assets/models/house.obj");
    load_model(&(scene->porsche), "assets/models/porsche.obj");
    load_model(&(scene->ground), "assets/models/ground.obj");
    scene->house_texture_id = load_texture("assets/textures/house.jpeg");
    scene->porsche_texture_id = load_texture("assets/textures/car.png");
    scene->ground_texture_id = load_texture("assets/textures/ground.png");

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
}

void set_lighting(float x)
{
    float ambient_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float diffuse_light[] = { x, x, x, 1.0f };
    float specular_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
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

void update_scene(Scene* scene)
{
    set_lighting(scene->light);
}

void render_scene(const Scene* scene)
{
    // housebig
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->house_texture_id);
    glScalef(0.2f, 0.2f, 0.2f);
    glRotated(90, 1, 0, 0);
    draw_model(&(scene->housebig));
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // housesmall
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->house_texture_id);
    glScalef(0.05f, 0.05f, 0.05f);
    glRotated(90, 1, 0, 0);
    glTranslatef(-100.0f, 0.0f, 100.0f);
    draw_model(&(scene->housesmall));
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // porsche
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->porsche_texture_id);
    glScalef(0.2f, 0.2f, 0.2f);
    glRotated(90.0f, 1.0f, 0.0f, 0.0f);
    draw_model(&(scene->porsche));
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // ground
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->ground_texture_id);
    glScalef(0.5, 0.5, 0.5);
    glRotated(90, 1, 0, 0);
    glTranslatef(-40, 0, 0);
    draw_model(&(scene->ground));
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
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
