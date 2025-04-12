#include "water.h"
#include <GL/gl.h>
#include <math.h>

void init_water(Water *water)
{
    for (int x = 0; x < 45; x++) {
        for (int y = 0; y < 45; y++) {
            water->waterPoints[x][y][0] = x - 22;
            water->waterPoints[x][y][1] = y - 22;
            water->waterPoints[x][y][2] = 0;
        }
    }

    water->amplitude = 1.0f;
    water->frequency = 2.0f;
    water->delta = 0.0f;

    water->vortices[0].x = 22.0f;
    water->vortices[0].y = 22.0f;
    water->vortices[0].phase = 0.0f;

    for (int i = 1; i < MAX_VORTICES; i++) {
        water->vortices[i].x = -100.0f;
    }

    water->water_texture_id = load_texture(WATER_TEXTURE_PATH);
}

void update_water(Water *water, double elapsed_time)
{
    water->delta += elapsed_time * 0.5f;

    float center_x = 22.0f;
    float center_y = 22.0f;

    water->vortices[0].x = center_x;
    water->vortices[0].y = center_y;

    for (int x = 0; x < 45; x++)
    {
        for (int y = 0; y < 45; y++)
        {
            float wave_phase = (float)y / 45.0f * 2.0f * M_PI;
            float t = fmod(water->delta * 0.2f + wave_phase, 1.0f);

            float p0 = 0.0f;
            float p1 = 0.8f * sin(wave_phase + water->delta);
            float p2 = 0.8f * cos(wave_phase - water->delta);
            float p3 = 0.0f;

            float wave_height = de_casteljau(t, p0, p1, p2, p3) * water->amplitude * 2.0f;

            float vortex_effect = 0.0f;

            for (int i = 0; i < 1; i++)
            {
                float dx = x - water->vortices[i].x;
                float dy = y - water->vortices[i].y;
                float radius = sqrtf(dx * dx + dy * dy);

                if (radius < 20.0f)
                {
                    float angle = atan2f(dy, dx);
                    float swirl = sinf(water->delta * 1.5f + angle * 4.0f + radius * 0.5f);
                    float falloff = 1.0f / (1.0f + radius * 0.3f);
                    vortex_effect += swirl * falloff * 2.5f;

                    if (radius < 5.0f)
                    {
                        float depth = -cosf(radius * 1.2f - water->delta * 1.0f);
                        float depth_fade = 1.0f - (radius / 5.0f);
                        vortex_effect += depth * depth_fade * 3.5f;
                    }
                }
            }

            water->waterPoints[x][y][2] = wave_height + vortex_effect;
        }
    }
}

float de_casteljau(float t, float p0, float p1, float p2, float p3)
{
    float q0 = (1 - t) * p0 + t * p1;
    float q1 = (1 - t) * p1 + t * p2;
    float q2 = (1 - t) * p2 + t * p3;

    float r0 = (1 - t) * q0 + t * q1;
    float r1 = (1 - t) * q1 + t * q2;

    return (1 - t) * r0 + t * r1;
}

void render_water(Water *water)
{
    int x, y;

    set_water_settings();
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, water->water_texture_id);
    glTranslatef(38.0f, 0.0f, -1.5f);

    float tex_offset = fmod(water->delta * 0.05f, 1.0f);

    glBegin(GL_QUADS);
    for (x = 0; x < 44; x++)
    {
        for (y = 0; y < 44; y++)
        {
            GLfloat nx = water->waterPoints[x + 1][y][2] - water->waterPoints[x][y][2];
            GLfloat ny = water->waterPoints[x][y + 1][2] - water->waterPoints[x][y][2];
            GLfloat nz = 1.0f;

            GLfloat len = sqrt(nx * nx + ny * ny + nz * nz);
            nx /= len; ny /= len; nz /= len;
            glNormal3f(nx, ny, nz);

            glTexCoord2f((x + tex_offset) / 45.0f, (y + tex_offset) / 45.0f);
            glVertex3f(x - 22, y - 22, water->waterPoints[x][y][2]);

            glTexCoord2f((x + 1 + tex_offset) / 45.0f, (y + tex_offset) / 45.0f);
            glVertex3f(x + 1 - 22, y - 22, water->waterPoints[x + 1][y][2]);

            glTexCoord2f((x + 1 + tex_offset) / 45.0f, (y + 1 + tex_offset) / 45.0f);
            glVertex3f(x + 1 - 22, y + 1 - 22, water->waterPoints[x + 1][y + 1][2]);

            glTexCoord2f((x + tex_offset) / 45.0f, (y + 1 + tex_offset) / 45.0f);
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