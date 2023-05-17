#include "skybox.h"
 
void init_skybox(Skybox *skybox)
{
    skybox->skybox = load_texture("assets/textures/cloud.jpg");
}
 
void render_skybox(const Skybox *skybox)
{
 
    glDepthFunc(GL_LESS);
    glBindTexture(GL_TEXTURE_2D, skybox->skybox);
    glBegin(GL_QUADS);
    glTexCoord2f(1, 1);
    glVertex3f(-100.0f, -100.0f, -100.0f);
 
    glTexCoord2f(1, 0);
    glVertex3f(-100.0f, -100.0f, 100.0f);
 
    glTexCoord2f(0, 0);
    glVertex3f(100.0f, -100.0f, +100.0f);
 
    glTexCoord2f(0, 1);
    glVertex3f(100.0f, -100.0f, -100.0f);
    glEnd();
 
    glBindTexture(GL_TEXTURE_2D, skybox->skybox);
    glBegin(GL_QUADS);
    glTexCoord2f(1, 1);
    glVertex3f(100.0f, 100.0f, -100.0f);
 
    glTexCoord2f(1, 0);
    glVertex3f(100.0f, 100.0f, 100.0f);
 
    glTexCoord2f(0, 0);
    glVertex3f(-100.0f, 100.0f, +100.0f);
 
    glTexCoord2f(0, 1);
    glVertex3f(-100.0f, 100.0f, -100.0f);
    glEnd();
 
    glBindTexture(GL_TEXTURE_2D, skybox->skybox);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-100.0f, 100.0f, 100.0f);
 
    glTexCoord2f(0, 1);
    glVertex3f(100.0f, 100.0f, 100.0f);
 
    glTexCoord2f(1, 1);
    glVertex3f(100.0f, -100.0f, 100.0f);
 
    glTexCoord2f(1, 0);
    glVertex3f(-100.0f, -100.0f, 100.0f);
    glEnd();
 
    glBindTexture(GL_TEXTURE_2D, skybox->skybox);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1);
    glVertex3f(-100.0f, 100.0f, -100.0f);
 
    glTexCoord2f(0, 0);
    glVertex3f(100.0f, 100.0f, -100.0f);
 
    glTexCoord2f(1, 0);
    glVertex3f(100.0f, -100.0f, -100.0f);
 
    glTexCoord2f(1, 1);
    glVertex3f(-100.0f, -100.0f, -100.0f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, skybox->skybox);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1);
    glVertex3f(-100.0f, -100.0f, -100.0f);
 
    glTexCoord2f(0, 0);
    glVertex3f(-100.0f, -100.0f, 100.0f);
 
    glTexCoord2f(1, 0);
    glVertex3f(-100.0f, 100.0f, +100.0f);
 
    glTexCoord2f(1, 1);
    glVertex3f(-100.0f, 100.0f, -100.0f);
    glEnd();
 
    glBindTexture(GL_TEXTURE_2D, skybox->skybox);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1);
    glVertex3f(100.0f, 100.0f, -100.0f);
 
    glTexCoord2f(0, 0);
    glVertex3f(100.0f, 100.0f, 100.0f);
 
    glTexCoord2f(1, 0);
    glVertex3f(100.0f, -100.0f, +100.0f);
 
    glTexCoord2f(1, 1);
    glVertex3f(100.0f, -100.0f, -100.0f);
    glEnd();
}