#include "water.h"
#include <GL/gl.h>
#include <math.h>

void init_water(Water *water)
{
    int x, y;
    for (x = 0; x < 45; x++)
    {
        for (y = 0; y < 45; y++)
        {
            water->waterPoints[x][y][0] = (x - 22) * 100;
            water->waterPoints[x][y][1] = (y - 22) * 100;
            water->waterPoints[x][y][2] = 0;
        }
    }

    water->amplitude = 0.5f;
    water->frequency = 2.0f;
    water->delta = 0.0f;
}

void update_water(Water *water, double elapsed_time)
{
    water->delta += water->frequency * (float)elapsed_time;

    int x, y;
    for (x = 0; x < 45; x++)
    {
        for (y = 0; y < 45; y++)
        {
            water->waterPoints[x][y][2] = water->amplitude * sin((x / 5.0f) * 2.0f * 3.141592654 + water->delta);
        }
    }
}

void render_water(Water *water)
{
    glPushMatrix();

    GLfloat water_mat_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat water_mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat water_mat_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat water_mat_shininess[] = { 50.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, water_mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, water_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, water_mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, water_mat_shininess);

    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0.0f, 0.0f, -0.5f);

    int x, y;
    glBegin(GL_QUADS);
    for (x = 0; x < 44; x++)
    {
        for (y = 0; y < 44; y++)
        {
            glNormal3f(0, 0, 1);

            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(x - 22, y - 22, water->waterPoints[x][y][2]);

            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(x + 1 - 22, y - 22, water->waterPoints[x + 1][y][2]);

            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(x + 1 - 22, y + 1 - 22, water->waterPoints[x + 1][y + 1][2]);

            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(x - 22, y + 1 - 22, water->waterPoints[x][y + 1][2]);
        }
    }
    glEnd();

    glPopMatrix();
}