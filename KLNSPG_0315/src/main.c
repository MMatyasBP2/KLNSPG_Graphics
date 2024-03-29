#include "callbacks.h"
#include "init.h"
#include <GL/glut.h>
#include <stdio.h>

void set_callbacks()
{
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(motion);
    glutKeyboardFunc(keyboard);
	glutMouseFunc(mouseClick);
    glutIdleFunc(idle);
}

int main(int argc, char* argv[])
{
    int window;
	
    glutInit(&argc, argv);

    glutInitWindowSize(640, 480);     
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    window = glutCreateWindow("Simplified Pong Game");
    glutSetWindow(window);

    init_opengl();
    set_callbacks();

    glutMainLoop();

    return 0;
}