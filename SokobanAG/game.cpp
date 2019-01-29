#include "game.h"

void Mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		x_pos_old = x;          // przypisanie aktualnie odczytanej pozycji x kursora jako pozycji poprzedniej
		y_pos_old = y;          // przypisanie aktualnie odczytanej pozycji y kursora jako pozycji poprzedniej
		status = 1;				// wciêniêty zosta³ lewy klawisz myszy
	}
	else if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		y_pos_old = y;
		status = 2;
	}
	else
		status = 0;				// nie zosta³ wciêniêty ¿aden klawisz
}

void Motion(GLsizei x, GLsizei y)
{
	delta_x = x - x_pos_old;    // obliczenie ró¿nicy po³o¿enia kursora myszy
	delta_y = y - y_pos_old;
	x_pos_old = x;				// podstawienie bie¿¹cego po³o¿enia jako poprzednie
	y_pos_old = y;
	glutPostRedisplay();		// przerysowanie obrazu sceny
}

void specialKey(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_DOWN:
		currentMove = upM;		//zarejestrowanie zdarzenia naciœniêcia klawisza strza³ki w DÓ£, nazwa jest adekwatna do ruchu w pocz¹tkowym stanie kamery
		break;
	case GLUT_KEY_UP:
		currentMove = downM;	//zarejestrowanie zdarzenia naciœniêcia klawisza strza³ki w GÓRÊ, nazwa jest adekwatna do ruchu w pocz¹tkowym stanie kamery
		break;
	case GLUT_KEY_LEFT:
		currentMove = leftM;	//zarejestrowanie zdarzenia naciœniêcia klawisza strza³ki w lewo
		break;
	case GLUT_KEY_RIGHT:
		currentMove = rightM;	//zarejestrowanie zdarzenia naciœniêcia klawisza strza³ki w prawo
		break;
	default: currentMove = noop;	//domyœlnie ¿aden klawisz nie jest naciœniêty
	}
	glutPostRedisplay();		//zg³oszenie potrzeby odœwie¿enia obrazu
}

void renderTeapot(GLfloat x, GLfloat z)
{
	glTranslatef(x, -3.5, z);	//przemieszczenie obiektu o wektor (x,y,z)
	glutSolidTeapot(2.5);		//wyrysowanie imbryczka
	glTranslatef(-x, +3.5, -z);	//powrót z translacj¹ do stanu pocz¹tkowego
}

void renderEgg(GLfloat x, GLfloat z)
{
	glTranslatef(x, 0, z);		//przemieszczenie obiektu o wektor (x,y,z)
	egg.renderEgg();			//wyrysowanie jajka
	glTranslatef(-x, 0, -z);	//powrót z translacj¹ do stanu pocz¹tkowego
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	if (status == 1)
	{
		theta += delta_x * pix2angle*M_PI / 180;
		phi += delta_y * pix2angle*M_PI / 180;
	}
	else if (status == 2) {
		if (R > 0 || delta_y > 0.1) R += delta_y;
	}
	gluLookAt((double)R*cos(theta)*cos(phi), (double)R*sin(phi), (double)R*sin(theta)*cos(phi), 0.0, 0.0, 0.0, 0.0, cos(phi), 0.0);

	switch (currentMove)
	{
	case  upM:																						//w przypadku zarejestrowania naciœniêcia klawisza odpowiadaj¹cemu stanowi up:
		if (potTransition[0] + 6.0 == eggTransition[0] && potTransition[1] == eggTransition[1])		//sprawdŸ czy na pozycji na któr¹ chcesz siê przesun¹c jest ju¿ jajko
		{
			eggTransition[0] += 6;																	//jeœli tak przesuñ jajko
		}
		potTransition[0] += 6.0;																	//przesuñ imbryk
		break;
	case  downM:
		if (potTransition[0] - 6.0 == eggTransition[0] && potTransition[1] == eggTransition[1])
		{
			eggTransition[0] -= 6;
		}
		potTransition[0] -= 6.0;
		break;
	case  leftM:
		if (potTransition[0] == eggTransition[0] && potTransition[1] + 6.0 == eggTransition[1])
		{
			eggTransition[1] += 6;
		}
		potTransition[1] += 6.0;
		break;
	case  rightM:
		if (potTransition[0] == eggTransition[0] && potTransition[1] - 6.0 == eggTransition[1])
		{
			eggTransition[1] -= 6;
		}
		potTransition[1] -= 6.0;
		break;
	}
	currentMove = noop;

	glTexImage2D(GL_TEXTURE_2D, 0, ImComponents, ImWidth, ImHeight, 0, ImFormat, GL_UNSIGNED_BYTE, firstLevelTex);	// Zdefiniowanie tekstury 2-D
	level.renderFloor();																							//przemieszczenie obiektu i ponowne wyrysowanie 

	glTexImage2D(GL_TEXTURE_2D, 0, ImComponents, ImWidth, ImHeight, 0, ImFormat, GL_UNSIGNED_BYTE, teapotTex);// Zdefiniowanie tekstury 2-D
	renderTeapot(potTransition[0], potTransition[1]);

	glTexImage2D(GL_TEXTURE_2D, 0, ImComponents, ImWidth, ImHeight, 0, ImFormat, GL_UNSIGNED_BYTE, eggTex);
	renderEgg(eggTransition[0], eggTransition[1]);

	glFlush();
	glutSwapBuffers();
}

GLbyte* LoadTGAImage(const char* FileName, GLint* ImWidth, GLint* ImHeight, GLint* ImComponents, GLenum* ImFormat)
{
#pragma pack(1)            
	typedef struct
	{
		GLbyte    idlength;
		GLbyte    colormaptype;
		GLbyte    datatypecode;
		unsigned short    colormapstart;
		unsigned short    colormaplength;
		unsigned char     colormapdepth;
		unsigned short    x_orgin;
		unsigned short    y_orgin;
		unsigned short    width;
		unsigned short    height;
		GLbyte    bitsperpixel;
		GLbyte    descriptor;
	}TGAHEADER;
#pragma pack(8)

	FILE *pFile;
	TGAHEADER tgaHeader;
	unsigned long lImageSize;
	short sDepth;
	GLbyte *pbitsperpixel = NULL;

	*ImWidth = 0;
	*ImHeight = 0;
	*ImFormat = GL_BGR_EXT;
	*ImComponents = GL_RGB8;
	pFile = fopen(FileName, "rb");
	if (pFile == NULL)
		return NULL;

	fread(&tgaHeader, sizeof(TGAHEADER), 1, pFile);

	*ImWidth = tgaHeader.width;
	*ImHeight = tgaHeader.height;
	sDepth = tgaHeader.bitsperpixel / 8;

	if (tgaHeader.bitsperpixel != 8 && tgaHeader.bitsperpixel != 24 && tgaHeader.bitsperpixel != 32)
		return NULL;

	lImageSize = tgaHeader.width * tgaHeader.height * sDepth;

	pbitsperpixel = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));

	if (pbitsperpixel == NULL)
		return NULL;
	if (fread(pbitsperpixel, lImageSize, 1, pFile) != 1)
	{
		free(pbitsperpixel);
		return NULL;
	}
	switch (sDepth)
	{
	case 3:

		*ImFormat = GL_BGR_EXT;
		*ImComponents = GL_RGB8;
		break;

	case 4:

		*ImFormat = GL_BGRA_EXT;
		*ImComponents = GL_RGBA8;
		break;

	case 1:

		*ImFormat = GL_LUMINANCE;
		*ImComponents = GL_LUMINANCE8;
		break;
	};
	fclose(pFile);
	return pbitsperpixel;
}

void MyInit()
{
	GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess = { 10.0 };
	GLfloat light_position[] = { 0.0, 5.0, 0.0, 1.0 };
	GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat att_constant = { 1.0 };
	GLfloat att_linear = (GLfloat) 0.05;
	GLfloat att_quadratic = (GLfloat)  0.001;
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	firstLevelTex = LoadTGAImage("images/LEVEL1.tga", &ImWidth, &ImHeight, &ImComponents, &ImFormat);			//za³adowanie tekstur do bufora
	teapotTex = LoadTGAImage("images/folk.tga", &ImWidth, &ImHeight, &ImComponents, &ImFormat);
	eggTex = LoadTGAImage("images/brick3.tga", &ImWidth, &ImHeight, &ImComponents, &ImFormat);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, att_constant);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, att_linear);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, att_quadratic);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

void ChangeSize(GLsizei horizontal, GLsizei vertical)
{
	pix2angle = 360.0 / (float)horizontal;  // przeliczenie pikseli na stopnie
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, 1.0, 4.0, 240.0);
	if (horizontal <= vertical)
		glViewport(0, (vertical - horizontal) / 2, horizontal, horizontal);
	else
		glViewport((horizontal - vertical) / 2, 0, vertical, vertical);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Sokoban");

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutSpecialFunc(specialKey);

	MyInit();
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}
