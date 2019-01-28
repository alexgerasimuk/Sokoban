#include "Egg.h"
#include <cmath>
#define M_PI 3.14159265358979323846


Egg::Egg(GLfloat x, GLfloat z)
{
	setPosition(x,  z);
	float a = 0.7;
	GeneratingTab();
	for (int i = 0; i <= N; i++)
		for (int j = 0; j <= N; j++)
		{
			float u = (float)i / (float)N;
			float v = (float)j / (float)N;
			pointsTable[i][j].x = a*((-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * u*u - 45 * u)*cosf((float)M_PI*v));
			pointsTable[i][j].y = a*(160 * pow(u, 4) - 320 * pow(u, 3) + 160 * u*u);
			pointsTable[i][j].z =a* ((-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * u*u - 45 * u)*sinf((float)M_PI*v));
			pointsTable[i][j].xu = a*(-450 * pow(u, 4) + 900 * pow(u, 3) - 810 * u*u + 360 * u - 45)*cosf((float)M_PI*v);
			pointsTable[i][j].xv =a* (float)M_PI*(90 * pow(u, 5) - 225 * pow(u, 4) + 270 * pow(u, 3) - 180 * u*u + 45 * u)*sinf(M_PI*v);
			pointsTable[i][j].yu = a*(640 * pow(u, 3) - 960 * u*u + 320 * u);
			pointsTable[i][j].yv = 0.0;
			pointsTable[i][j].zu = a*(-450 * pow(u, 4) + 900 * pow(u, 3) - 810 * u*u + 360 * u - 45)*sinf((float)M_PI*v);
			pointsTable[i][j].zv = a*(-1 * (float)M_PI)*(90 * pow(u, 5) - 225 * pow(u, 4) + 270 * pow(u, 3) - 180 * u*u + 45 * u)*cosf((float)M_PI*v);



			pointsTable[i][j].nx = pointsTable[i][j].yu*pointsTable[i][j].zv - pointsTable[i][j].zu*pointsTable[i][j].yv;
			pointsTable[i][j].ny = pointsTable[i][j].zu*pointsTable[i][j].xv - pointsTable[i][j].xu*pointsTable[i][j].zv;
			pointsTable[i][j].nz = pointsTable[i][j].xu*pointsTable[i][j].yv - pointsTable[i][j].yu*pointsTable[i][j].xv;

			if (i > N / 2)
			{
				pointsTable[i][j].nx = -1.0*pointsTable[i][j].nx;
				pointsTable[i][j].ny = -1.0*pointsTable[i][j].ny;
				pointsTable[i][j].nz = -1.0*pointsTable[i][j].nz;
			}


			if (i == N / 2)
			{
				pointsTable[i][j].nx = 0.0;
				pointsTable[i][j].ny = 1.0;
				pointsTable[i][j].nz = 0.0;
			}

			if (i == 0 || i == N)
			{
				pointsTable[i][j].nx = 0.0;
				pointsTable[i][j].ny = -1.0;
				pointsTable[i][j].nz = 0.0;
			}


			float dlug = sqrt(pow(pointsTable[i][j].nx, 2) + pow(pointsTable[i][j].ny, 2) + pow(pointsTable[i][j].nz, 2));

			pointsTable[i][j].nx = pointsTable[i][j].nx / dlug;
			pointsTable[i][j].ny = pointsTable[i][j].ny / dlug;
			pointsTable[i][j].nz = pointsTable[i][j].nz / dlug;

		}	
}

void Egg::setPosition(GLfloat x, GLfloat z)
{
	eggTransition[0] = x;
	eggTransition[1] = z;
}

void Egg::renderEgg()
{
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
				glNormal3f(pointsTable[i][j].nx + eggTransition[0], pointsTable[i][j].ny, pointsTable[i][j].nz + eggTransition[1]);
				glVertex3f(pointsTable[i][j].x + eggTransition[0], pointsTable[i][j].y - 5.0f, pointsTable[i][j].z + eggTransition[1]);

				glTexCoord2d(i2, j2);
				glNormal3f(pointsTable[i + 1][j + 1].nx + eggTransition[0], pointsTable[i + 1][j + 1].ny, pointsTable[i + 1][j + 1].nz + eggTransition[1]);
				glVertex3f(pointsTable[i + 1][j + 1].x + eggTransition[0], pointsTable[i + 1][j + 1].y - 5.0f, pointsTable[i + 1][j + 1].z + eggTransition[1]);

				glTexCoord2d(i1, j2);
				glNormal3f(pointsTable[i][j + 1].nx + eggTransition[0], pointsTable[i][j + 1].ny, pointsTable[i][j + 1].nz + eggTransition[1]);
				glVertex3f(pointsTable[i][j + 1].x + eggTransition[0], pointsTable[i][j + 1].y - 5.0f, pointsTable[i][j + 1].z + eggTransition[1]);
				glEnd();

				glBegin(GL_TRIANGLES);

				glTexCoord2d(i1, j1);
				glNormal3f(pointsTable[i][j].nx + eggTransition[0], pointsTable[i][j].ny, pointsTable[i][j].nz + eggTransition[1]);
				glVertex3f(pointsTable[i][j].x + eggTransition[0], pointsTable[i][j].y - 5.0f, pointsTable[i][j].z + eggTransition[1]);


				glTexCoord2d(i2, j2);
				glNormal3f(pointsTable[i + 1][j + 1].nx + eggTransition[0], pointsTable[i + 1][j + 1].ny, pointsTable[i + 1][j + 1].nz + eggTransition[1]);
				glVertex3f(pointsTable[i + 1][j + 1].x + eggTransition[0], pointsTable[i + 1][j + 1].y - 5.0f, pointsTable[i + 1][j + 1].z + eggTransition[1]);


				glTexCoord2d(i2, j1);
				glNormal3f(pointsTable[i + 1][j].nx + eggTransition[0], pointsTable[i + 1][j].ny, pointsTable[i + 1][j].nz + eggTransition[1]);
				glVertex3f(pointsTable[i + 1][j].x + eggTransition[0], pointsTable[i + 1][j].y - 5.0f, pointsTable[i + 1][j].z + eggTransition[1]);
				glEnd();
			}
		}
	}
}

void Egg::GeneratingTab()
{
		pointsTable = new Point*[N + 1];
		for (int i = 0; i <= N; i++)
			pointsTable[i] = new Point[N + 1];
}
	
Egg::~Egg()
{
}
