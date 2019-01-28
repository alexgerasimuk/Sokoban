#include "Floor.h"
#include <gl/glut.h>


Floor::Floor()
{
}

void Floor::renderFloor()
{
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-15, -5, -15);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(15, -5, -15);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(15, -5, 15);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-15, -5, 15);
	glEnd();
	glutPostRedisplay();
}

void Floor::setTexture()
{
	glBegin(GL_TRIANGLES);

//	glNormal3f(0.5f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-15, -5, -15);

//	glNormal3f(...);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(15, -5, -15);

//	glNormal3f(...);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(15, -5, 15);
	
//	glNormal3f(...);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(-15, -5, 15);

	glEnd();
}


Floor::~Floor()
{
}
