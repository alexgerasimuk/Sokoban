#include "Floor.h"

Floor::Floor()
{
}

void Floor::renderFloor()
{
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);

	glNormal3f(0.0, 1.0, 0.0);		//stworzenie wektora normalnego do powierzchni, niezb�dnego do obliczenia k�ta odbicia �wiat�a
	glTexCoord2f(0.0, 0.0);			//wybranie wierzcho�ka tekstury, kt�ry b�dzie na�o�ony na odpowiedni punkt obiektu
	glVertex3f(-15, -5, -15);		//wskazanie punktu obieketu, na kt�rym b�dzie umieszczony wskazany punkt tekstury

	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(15, -5, -15);

	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(15, -5, 15);

	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-15, -5, 15);

	glEnd();
}

Floor::~Floor()
{
}
