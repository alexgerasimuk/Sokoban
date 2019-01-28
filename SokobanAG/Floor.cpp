#include "Floor.h"
#include <gl/glut.h>


Floor::Floor()
{
}

void Floor::renderFloor()
{
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(-15, -5, -15);
	glVertex3f(15, -5, -15);
	glVertex3f(15, -5, 15);
	glVertex3f(-15, -5, 15);
	glEnd();
	glutPostRedisplay();
}


Floor::~Floor()
{
}
