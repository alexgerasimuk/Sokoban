#include "Egg.h"
#include "game.h"
#include <cmath>
#define M_PI 3.14159265358979323846


Egg::Egg(GLfloat x, GLfloat z)
{
	setPosition(x,  z);

	GeneratingTab();
	for (int i = 0; i <= N; i++)
		for (int j = 0; j <= N; j++)
		{
			float u = (float)i / (float)N;
			float v = (float)j / (float)N;
			tablica[i][j].x = ((-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * u*u - 45 * u)*cosf((float)M_PI*v));
			tablica[i][j].y = (160 * pow(u, 4) - 320 * pow(u, 3) + 160 * u*u);
			tablica[i][j].z = ((-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * u*u - 45 * u)*sinf((float)M_PI*v));
			tablica[i][j].xu = (-450 * pow(u, 4) + 900 * pow(u, 3) - 810 * u*u + 360 * u - 45)*cosf((float)M_PI*v);
			tablica[i][j].xv = (float)M_PI*(90 * pow(u, 5) - 225 * pow(u, 4) + 270 * pow(u, 3) - 180 * u*u + 45 * u)*sinf(M_PI*v);
			tablica[i][j].yu = (640 * pow(u, 3) - 960 * u*u + 320 * u);
			tablica[i][j].yv = 0.0;
			tablica[i][j].zu = (-450 * pow(u, 4) + 900 * pow(u, 3) - 810 * u*u + 360 * u - 45)*sinf((float)M_PI*v);
			tablica[i][j].zv = (-1 * (float)M_PI)*(90 * pow(u, 5) - 225 * pow(u, 4) + 270 * pow(u, 3) - 180 * u*u + 45 * u)*cosf((float)M_PI*v);



			tablica[i][j].nx = tablica[i][j].yu*tablica[i][j].zv - tablica[i][j].zu*tablica[i][j].yv;
			tablica[i][j].ny = tablica[i][j].zu*tablica[i][j].xv - tablica[i][j].xu*tablica[i][j].zv;
			tablica[i][j].nz = tablica[i][j].xu*tablica[i][j].yv - tablica[i][j].yu*tablica[i][j].xv;

			if (i > N / 2)
			{
				tablica[i][j].nx = -1.0*tablica[i][j].nx;
				tablica[i][j].ny = -1.0*tablica[i][j].ny;
				tablica[i][j].nz = -1.0*tablica[i][j].nz;
			}


			if (i == N / 2)
			{
				tablica[i][j].nx = 0.0;
				tablica[i][j].ny = 1.0;
				tablica[i][j].nz = 0.0;
			}

			if (i == 0 || i == N)
			{
				tablica[i][j].nx = 0.0;
				tablica[i][j].ny = -1.0;
				tablica[i][j].nz = 0.0;
			}


			float dlug = sqrt(pow(tablica[i][j].nx, 2) + pow(tablica[i][j].ny, 2) + pow(tablica[i][j].nz, 2));

			tablica[i][j].nx = tablica[i][j].nx / dlug;
			tablica[i][j].ny = tablica[i][j].ny / dlug;
			tablica[i][j].nz = tablica[i][j].nz / dlug;

		}
	// MAJAC PUNKTY RYSUJEMY JAJKO


	for (int i = 0; i <= N; i++)
		for (int j = 0; j <= N; j++)
		{
			float i1 = (float)i / (float)N;
			float i2 = (float)(i + 1) / (float)N;
			float j1 = (float)j / (float)N;
			float j2 = (float)(j + 1) / (float)N;

			if (i <= (N - 1))
			{
				if (j <= (N - 1))
				{

					glBegin(GL_TRIANGLES);

					glTexCoord2d(i1, j1);
					//glTexCoord2d(0.0f, 0.0f);
					glNormal3f(tablica[i][j].nx, tablica[i][j].ny, tablica[i][j].nz);
					glVertex3f(tablica[i][j].x, tablica[i][j].y - 5.0f, tablica[i][j].z);

					glTexCoord2d(i2, j2);
					//glTexCoord2d(1.0f, 1.0f);
					glNormal3f(tablica[i + 1][j + 1].nx, tablica[i + 1][j + 1].ny, tablica[i + 1][j + 1].nz);
					glVertex3f(tablica[i + 1][j + 1].x, tablica[i + 1][j + 1].y - 5.0f, tablica[i + 1][j + 1].z);

					glTexCoord2d(i1, j2);
					//glTexCoord2d(0.0f, 1.0f);
					glNormal3f(tablica[i][j + 1].nx, tablica[i][j + 1].ny, tablica[i][j + 1].nz);
					glVertex3f(tablica[i][j + 1].x, tablica[i][j + 1].y - 5.0f, tablica[i][j + 1].z);
					glEnd();

					glBegin(GL_TRIANGLES);

					glTexCoord2d(i1, j1);
					//glTexCoord2d(0.0f, 0.0f);
					glNormal3f(tablica[i][j].nx, tablica[i][j].ny, tablica[i][j].nz);
					glVertex3f(tablica[i][j].x, tablica[i][j].y - 5.0f, tablica[i][j].z);


					glTexCoord2d(i2, j2);
					//glTexCoord2d(1.0f, 1.0f);
					glNormal3f(tablica[i + 1][j + 1].nx, tablica[i + 1][j + 1].ny, tablica[i + 1][j + 1].nz);
					glVertex3f(tablica[i + 1][j + 1].x, tablica[i + 1][j + 1].y - 5.0f, tablica[i + 1][j + 1].z);


					glTexCoord2d(i2, j1);
					//glTexCoord2d(1.0f, 0.0f);
					glNormal3f(tablica[i + 1][j].nx, tablica[i + 1][j].ny, tablica[i + 1][j].nz);
					glVertex3f(tablica[i + 1][j].x, tablica[i + 1][j].y - 5.0f, tablica[i + 1][j].z);
					glEnd();
				}
			}
		}
}

void Egg::setPosition(GLfloat x, GLfloat z)
{
	eggTransition[0] = x;
	eggTransition[1] = z;
}

void Egg::GeneratingTab()
{
		tablica = new Point*[N + 1];
		for (int i = 0; i <= N; i++)
			tablica[i] = new Point[N + 1];
}
	
Egg::~Egg()
{
}
