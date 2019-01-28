#include "game.h"

void Mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		x_pos_old = x;          // przypisanie aktualnie odczytanej pozycji kursora jako pozycji poprzedniej
		y_pos_old = y;          // przypisanie aktualnie odczytanej pozycji kursora jako pozycji poprzedniej
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

void renderTeapot(GLfloat x, GLfloat z)
{
	glTranslatef(x, 0, z);
	glutSolidTeapot(2.0);
}

void renderEgg(GLfloat x, GLfloat z)
{
	glTranslatef(x, 0, z);
	Egg egg(x, z);
	glutPostRedisplay();
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	if (status == 1)								// jeœli lewy klawisz myszy wciêniêty
	{
		theta += delta_x * pix2angle*M_PI / 180;    // modyfikacja k¹ta obrotu o kat proporcjonalny do ró¿nicy po³o¿eñ kursora myszy
		phi += delta_y * pix2angle*M_PI / 180;
	}
	else if (status == 2) {
		if (R > 0 || delta_y > 0.1) R += delta_y;
	}

	int kier = 1;
	if (cos(phi) < 0) kier = -1;

	gluLookAt((double)R*cos(theta)*cos(phi), (double)R*sin(phi), (double)R*sin(theta)*cos(phi), 0.0, 0.0, 0.0, 0.0, (double)kier, 0.0);

	level.renderFloor();
	egg.renderEgg();
	renderTeapot(potTransition[0], potTransition[1]);
	glFlush();
	glutSwapBuffers();
}

void specialKey(int key, int x, int y)
	{
		switch (key)
		{
		case GLUT_KEY_UP:
			currentMove = upM;
			checkForCollision(potTransition,existingEggs);
			potTransition[0] += 6.0;
			
			break;
		case GLUT_KEY_DOWN:
			currentMove = downM;
			checkForCollision(potTransition, existingEggs);
			potTransition[0] -= 6.0;
			
			break;
		case GLUT_KEY_LEFT:
			currentMove = leftM;
			checkForCollision(potTransition, existingEggs);
			potTransition[1] += 6.0;
			
			break;
		case GLUT_KEY_RIGHT:
			currentMove = rightM;
			checkForCollision(potTransition, existingEggs);
			potTransition[1] -= 6.0;
			
			break;
		default: break;
		}
		renderTeapot(potTransition[0], potTransition[1]);
		glutPostRedisplay();
		glutSwapBuffers();
	}

void checkForCollision(GLfloat potTransition[], vector<Egg> &existingEggs)
{
	switch(currentMove)
	{
	case upM:
		if(potTransition[0]+6.0 == egg.eggTransition[0] && potTransition[1] == egg.eggTransition[1])
		{
			//warunek z nastêpnym jajkiem za jajkiem do przesuniêcia
			//warunek z koñcem planszy
			egg.eggTransition[0] += 6;
		}
		break;
	case downM:
		if (potTransition[0] - 6.0 == egg.eggTransition[0] && potTransition[1] == egg.eggTransition[1])
		{
			//warunek z nastêpnym jajkiem za jajkiem do przesuniêcia
			//warunek z koñcem planszy
			egg.eggTransition[0] -= 6;
		}
		break;
	case leftM:
		if (potTransition[0] == egg.eggTransition[0] && potTransition[1] + 6.0 == egg.eggTransition[1])
		{
			//warunek z nastêpnym jajkiem za jajkiem do przesuniêcia
			//warunek z koñcem planszy
			egg.eggTransition[1] += 6;
		}
		break;
	case rightM:
		if (potTransition[0] == egg.eggTransition[0] && potTransition[1] - 6.0 == egg.eggTransition[1])
		{
			//warunek z nastêpnym jajkiem za jajkiem do przesuniêcia
			//warunek z koñcem planszy
			egg.eggTransition[1] -= 6;
		}
		break;
	default: 
		break;
}
	glutPostRedisplay();
}

GLbyte* LoadTGAImage(const char* FileName, GLint* ImWidth, GLint* ImHeight, GLint* ImComponents, GLenum* ImFormat)
	{
		// Struktura dla nag³ówka pliku  TGA
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
		GLbyte    *pbitsperpixel = NULL;

		// Wartoœci domyœlne zwracane w przypadku b³êdu

		*ImWidth = 0;
		*ImHeight = 0;
		*ImFormat = GL_BGR_EXT;
		*ImComponents = GL_RGB8;
		pFile = fopen(FileName, "rb");
		if (pFile == NULL)
			return NULL;

		// Przeczytanie nag³ówka pliku
		fread(&tgaHeader, sizeof(TGAHEADER), 1, pFile);

		// Odczytanie szerokoœci, wysokoœci i g³êbi obrazu
		*ImWidth = tgaHeader.width;
		*ImHeight = tgaHeader.height;
		sDepth = tgaHeader.bitsperpixel / 8;

		// Sprawdzenie, czy g³êbia spe³nia za³o¿one warunki (8, 24, lub 32 bity)
		if (tgaHeader.bitsperpixel != 8 && tgaHeader.bitsperpixel != 24 && tgaHeader.bitsperpixel != 32)
			return NULL;

		// Obliczenie rozmiaru bufora w pamiêci
		lImageSize = tgaHeader.width * tgaHeader.height * sDepth;

		// Alokacja pamiêci dla danych obrazu
		pbitsperpixel = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));

		if (pbitsperpixel == NULL)
			return NULL;
		if (fread(pbitsperpixel, lImageSize, 1, pFile) != 1)
		{
			free(pbitsperpixel);
			return NULL;
		}

		// Ustawienie formatu OpenGL
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
	// Definicja materia³u z jakiego zrobiony jest czajnik
	GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	// wspó³czynniki ka =[kar,kag,kab] dla œwiat³a otoczenia

	GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	// wspó³czynniki kd =[kdr,kdg,kdb] œwiat³a rozproszonego

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	// wspó³czynniki ks =[ksr,ksg,ksb] dla œwiat³a odbitego

	GLfloat mat_shininess = { 10.0 };
	// wspó³czynnik n opisuj¹cy po³ysk powierzchni


	// Zmienne dla obrazu tekstury
	GLbyte *pBytes;
	GLint ImWidth, ImHeight, ImComponents;
	GLenum ImFormat;


	// Definicja Ÿród³a œwiat³a

	GLfloat light_position[] = { 0.0, 0.0, 5.0, 1.0 };
	// po³o¿enie Ÿród³a
	GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	// sk³adowe intensywnoœci œwiecenia Ÿród³a œwiat³a otoczenia
	// Ia = [Iar,Iag,Iab]
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	// sk³adowe intensywnoœci œwiecenia Ÿród³a œwiat³a powoduj¹cego
	// odbicie dyfuzyjne Id = [Idr,Idg,Idb]
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	// sk³adowe intensywnoœci œwiecenia Ÿród³a œwiat³a powoduj¹cego
	// odbicie kierunkowe Is = [Isr,Isg,Isb]
	GLfloat att_constant = { 1.0 };
	// sk³adowa sta³a ds dla modelu zmian oœwietlenia w funkcji
	// odleg³oœci od Ÿród³a
	GLfloat att_linear = (GLfloat) 0.05;
	// sk³adowa liniowa dl dla modelu zmian oœwietlenia w funkcji
	// odleg³oœci od Ÿród³a
	GLfloat att_quadratic = (GLfloat)  0.001;
	// sk³adowa kwadratowa dq dla modelu zmian oœwietlenia w funkcji
	// odleg³oœci od Ÿród³a

	// Ustawienie parametrów materia³u i Ÿród³a œwiat³a

	// Ustawienie patrametrów materia³u
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
	// Teksturowanie bêdzie prowadzone tyko po jednej stronie œciany
	glEnable(GL_FRONT_FACE);
	//  Przeczytanie obrazu tekstury z pliku o nazwie tekstura.tga
	pBytes = LoadTGAImage("images/bricks.tga", &ImWidth, &ImHeight, &ImComponents, &ImFormat);
	// Zdefiniowanie tekstury 2-D
	glTexImage2D(GL_TEXTURE_2D, 0, ImComponents, ImWidth, ImHeight, 0, ImFormat, GL_UNSIGNED_BYTE, pBytes);
	// Zwolnienie pamiêci
	free(pBytes);
	// W³¹czenie mechanizmu teksturowania
	glEnable(GL_TEXTURE_2D);
	// Ustalenie trybu teksturowania
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// Okreœlenie sposobu nak³adania tekstur
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Ustawienie parametrów Ÿród³a
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, att_constant);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, att_linear);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, att_quadratic);

	// Ustawienie opcji systemu oœwietlania sceny
	glShadeModel(GL_SMOOTH); // w³aczenie ³agodnego cieniowania
	glEnable(GL_LIGHTING);   // w³aczenie systemu oœwietlenia sceny
	glEnable(GL_LIGHT0);     // w³¹czenie Ÿród³a o numerze 0
	glEnable(GL_DEPTH_TEST); // w³¹czenie mechanizmu z-bufora
}

void ChangeSize(GLsizei horizontal, GLsizei vertical)
{
	pix2angle = 360.0 / (float)horizontal;  // przeliczenie pikseli na stopnie
	glMatrixMode(GL_PROJECTION);
	// Prze³¹czenie macierzy bie¿¹cej na macierz projekcji

	glLoadIdentity();
	// Czyszcznie macierzy bie¿¹cej

	gluPerspective(70, 1.0, 4.0, 240.0);
	// Ustawienie parametrów dla rzutu perspektywicznego

	if (horizontal <= vertical)
		glViewport(0, (vertical - horizontal) / 2, horizontal, horizontal);
	else
		glViewport((horizontal - vertical) / 2, 0, vertical, vertical);
	// Ustawienie wielkoœci okna okna widoku (viewport) w zale¿noœci
	// relacji pomiêdzy wysokoœci¹ i szerokoœci¹ okna

	glMatrixMode(GL_MODELVIEW);
	// Prze³¹czenie macierzy bie¿¹cej na macierz widoku modelu  

	glLoadIdentity();
	// Czyszczenie macierzy bie¿¹cej
}

void main(void)
{
	//srand(time(NULL));

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Sokoban");
	//	GeneratingTab();

	glutDisplayFunc(RenderScene);
	// Okreœlenie, ¿e funkcja RenderScene bêdzie funkcj¹ zwrotn¹ (callback function).  Bêdzie ona wywo³ywana za ka¿dym razem gdy zajdzie potrzeba przerysowania okna
	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcjê zwrotn¹ odpowiedzialn¹ za zmiany rozmiaru okna                      
	glutMouseFunc(Mouse);
	// Ustala funkcjê zwrotn¹ odpowiedzialn¹ za badanie stanu myszy
	glutMotionFunc(Motion);
	// Ustala funkcjê zwrotn¹ odpowiedzialn¹ za badanie ruchu myszy
	glutSpecialFunc(specialKey);

	MyInit();
	// Funkcja MyInit() (zdefiniowana powy¿ej) wykonuje wszelkie inicjalizacje konieczne  przed przyst¹pieniem do renderowania
	glEnable(GL_DEPTH_TEST);
	// W³¹czenie mechanizmu usuwania niewidocznych elementów sceny
	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT
}