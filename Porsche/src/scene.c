#include "scene.h"
#include "app.h"

#include <obj/load.h>
#include <obj/draw.h>

float waterPoints[45][45][3];
int wiggleCount = 0;
float hold;

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
    scene->ground_texture_id = load_texture("assets/textures/ground.png");

    // init water points
	int x, y;
	for (x = 0; x < 45; x++)
	{
		for (y = 0; y < 45; y++)
		{
			waterPoints[x][y][0] = (x / 5.0f) - 4.5f;
			waterPoints[x][y][1] = (y / 5.0f) - 4.5f;
			waterPoints[x][y][2] = sin((((x / 5.0f) * 40.0f) / 360.0f) * 3.141592654 * 2.0f);
		}
	}

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
    glTranslatef(-12.0f, 0.6f, -20.0f);
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

    draw_water();
}

void help()
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
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
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}

void drawEnd()
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
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
    glEnable(GL_LIGHTING);
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

void draw_water()
{
	int x, y;
	float float_x, float_y, float_xb, float_yb;

	glColor3f(0.0f, 0.0f, 1.0f);
	glPushMatrix();
	glDisable(GL_LIGHTING);
    glTranslatef(0.0f, 0.0f, -0.5f);
	glScalef(50.0f, 50.0f, 0.5f);

	glBegin(GL_QUADS);
	{
		for (x = 0; x < 44; x++)
		{
			for (y = 0; y < 44; y++)
			{
				float_x = (x) / 44.0f;
				float_y = (y) / 44.0f;
				float_xb = (x + 1) / 44.0f;
				float_yb = (y + 1) / 44.0f;

				glTexCoord2f(float_x, float_y);
				glVertex3f(waterPoints[x][y][0], waterPoints[x][y][1], waterPoints[x][y][2]);

				glTexCoord2f(float_x, float_yb);
				glVertex3f(waterPoints[x][y + 1][0], waterPoints[x][y + 1][1], waterPoints[x][y + 1][2]);

				glTexCoord2f(float_xb, float_yb);
				glVertex3f(waterPoints[x + 1][y + 1][0], waterPoints[x + 1][y + 1][1], waterPoints[x + 1][y + 1][2]);

				glTexCoord2f(float_xb, float_y);
				glVertex3f(waterPoints[x + 1][y][0], waterPoints[x + 1][y][1], waterPoints[x + 1][y][2]);
			}
		}
	}
	glEnd();

	if (wiggleCount == 10)
	{
		for (y = 0; y < 45; y++)
		{
			hold = waterPoints[0][y][2];
			for (x = 0; x < 44; x++)
			{
				waterPoints[x][y][2] = waterPoints[x + 1][y][2];
			}
			waterPoints[44][y][2] = hold;
		}
		wiggleCount = 0;
	}
	wiggleCount++;

	glEnable(GL_LIGHTING);
	glPopMatrix();
}