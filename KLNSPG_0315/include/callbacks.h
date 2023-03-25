#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "game.h"
#include <GL/glut.h>

Game game;
void display();
void reshape(GLsizei width, GLsizei height);
void motion(int x, int y);
void mouseClick(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);
void idle();

#endif /* CALLBACKS_H */