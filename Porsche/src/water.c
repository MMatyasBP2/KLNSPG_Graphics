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
            water->waterPoints[x][y][0] = x - 22;
            water->waterPoints[x][y][1] = y - 22;
            water->waterPoints[x][y][2] = 0;
        }
    }

    water->amplitude = 0.5f;
    water->frequency = 2.0f;
    water->delta = 0.0f;

    water->water_texture_id = load_texture("assets/textures/water.jpg");
}

void update_water(Water *water, double elapsed_time)
{
    water->delta += water->frequency * (float)elapsed_time;

    int x, y;
    for (x = 0; x < 45; x++)
    {
        for (y = 0; y < 45; y++)
            water->waterPoints[x][y][2] = water->amplitude * sin((x / 5.0f) * 2.0f * M_PI + water->delta);
    }
}

void render_water(Water *water)
{
    int x, y;

    set_water_settings();
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, water->water_texture_id);
    glTranslatef(0.0f, 0.0f, -0.5f);
    glBegin(GL_QUADS);
    for (x = 0; x < 44; x++)
    {
        for (y = 0; y < 44; y++)
        {
            GLfloat nx = water->waterPoints[x + 1][y][2] - water->waterPoints[x][y][2];
            GLfloat ny = water->waterPoints[x][y + 1][2] - water->waterPoints[x][y][2];
            GLfloat nz = 1.0f;

            GLfloat len = sqrt(nx * nx + ny * ny + nz * nz);
            nx /= len;
            ny /= len;
            nz /= len;
            
            glNormal3f(nx, ny, nz);

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

void set_water_settings()
{
    GLfloat water_mat_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat water_mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat water_mat_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat water_mat_shininess[] = { 50.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, water_mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, water_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, water_mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, water_mat_shininess);
}