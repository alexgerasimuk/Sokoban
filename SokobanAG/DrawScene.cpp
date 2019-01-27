#include "DrawScene.h"

void DrawScene::Draw_OuterWall(GLuint texture, BOOL isDisplay)
{
	if (isDisplay)
	{
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);

		//wall 1  
		for (float a = 0.0; a <= 180.0; a = a + 10.0)
		{
			glColor3f(0.7, 0.7, 0.5);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(-10.0 + a, 0.0, 20.0);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(-10.0 + a, 50.0, 20.0);
			glTexCoord2f(1.0, 1.0);
			glVertex3f(0.0 + a, 50.0, 20.0);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(0.0 + a, 0.0, 20.0);
			glEnd();
		}

		//wall 2  
		for (float a = 0.0; a <= 320.0; a = a + 20.0)
		{
			glColor3f(0.7, 0.7, 0.5);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(180.0, 0.0, 0.0 - a);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(180.0, 50.0, 0.0 - a);
			glTexCoord2f(1.0, 1.0);
			glVertex3f(180.0, 50.0, 20.0 - a);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(180.0, 0.0, 20.0 - a);
			glEnd();
		}

		//wall 3  
		for (float a = 0.0; a <= 180.0; a = a + 10.0)
		{
			glColor3f(0.7, 0.7, 0.5);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(180.0 - a, 0.0, -320.0);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(180.0 - a, 50.0, -320.0);
			glTexCoord2f(1.0, 1.0);
			glVertex3f(170.0 - a, 50.0, -320.0);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(170.0 - a, 0.0, -320.0);
			glEnd();
		}


		//wall 4  
		for (float a = -10.0; a <= 320.0; a = a + 10.0)
		{
			glColor3f(0.7, 0.7, 0.5);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(-10.0, 0.0, 0.0 - a);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(-10.0, 50.0, 0.0 - a);
			glTexCoord2f(1.0, 1.0);
			glVertex3f(-10.0, 50.0, 10.0 - a);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(-10.0, 0.0, 10.0 - a);
			glEnd();
		}


		glDisable(GL_TEXTURE_2D);

		//LoadTexture::FreeCreatedTexture(texture);

		glPopMatrix();
	}
}

void DrawScene::Draw_Floor(GLuint texture, float f)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);


	glPushMatrix();

	for (float a = -10.0; a <= 170.0; a = a + 10.0)
	{
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(0.0 + a, 0.0, 10.0);
		glTexCoord2f(0.0, f);
		glVertex3f(0.0 + a, 0.0, 0.0);
		glTexCoord2f(f, f);
		glVertex3f(10.0 + a, 0.0, 0.0);
		glTexCoord2f(f, 0.0);
		glVertex3f(10.0 + a, 0.0, 10.0);
		glEnd();
	}

	for (float b = -10.0; b <= 320.0; b += 10.0)
	{
		for (float a = -10.0; a <= 170.0; a = a + 10.0)
		{
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(0.0 + a, 0.0, -(b - 10.0));
			glTexCoord2f(0.0, f);
			glVertex3f(0.0 + a, 0.0, -b);
			glTexCoord2f(f, f);
			glVertex3f(10.0 + a, 0.0, -b);
			glTexCoord2f(f, 0.0);
			glVertex3f(10.0 + a, 0.0, -(b - 10.0));
			glEnd();

		}
	}

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

//	LoadTexture::FreeCreatedTexture(texture);
}
