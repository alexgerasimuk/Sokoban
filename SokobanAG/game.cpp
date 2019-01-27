#include "game.h"

	void Mouse(int btn, int state, int x, int y)
	{

		if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			game::x_pos_old = x;         // przypisanie aktualnie odczytanej pozycji kursora
								   // jako pozycji poprzedniej
			game::y_pos_old = y;          // przypisanie aktualnie odczytanej pozycji kursora
									// jako pozycji poprzedniej

			status = 1;          // wci�ni�ty zosta� lewy klawisz myszy
		}
		else if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		{
			y_pos_old = y;
			status = 2;
		}
		else
			status = 0;          // nie zosta� wci�ni�ty �aden klawisz
	}

	void Motion(GLsizei x, GLsizei y)
	{
		delta_x = x - x_pos_old;     // obliczenie r�nicy po�o�enia kursora myszy
		delta_y = y - y_pos_old;
		x_pos_old = x;            // podstawienie bie��cego po�o�enia jako poprzednie
		y_pos_old = y;
		glutPostRedisplay();     // przerysowanie obrazu sceny
	}

	void renderTeapot(GLfloat x, GLfloat z)
	{
		glTranslatef(x, 0, z);
		glutSolidTeapot(3.0);
	}

	void RenderScene()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Czyszczenie okna aktualnym kolorem czyszcz�cym
		glLoadIdentity();
		// Czyszczenie macierzy bie??cej
		//	gluLookAt(viewer[0], viewer[1], viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		// Zdefiniowanie po�o�enia obserwatora

		if (status == 1)                     // je�li lewy klawisz myszy wci�ni�ty
		{
			theta += delta_x * pix2angle*M_PI / 180;    // modyfikacja k�ta obrotu o kat proporcjonalny
														// do r�nicy po�o�e� kursora myszy
			phi += delta_y * pix2angle*M_PI / 180;
		}
		else if (status == 2) {
			if (R > 0 || delta_y > 0.1) R += delta_y;
		}

		int kier = 1;
		if (cos(game::phi) < 0) kier = -1;

		gluLookAt((double)R*cos(theta)*cos(phi), (double)R*sin(phi), (double)R*sin(theta)*cos(phi), 0.0, 0.0, 0.0, 0.0, (double)kier, 0.0);
		//draw();
		Egg egg(0.0, 0.0);
		// Narysowanie jajka
		renderTeapot(potTransition[0], potTransition[1]);

		glFlush();
		// Przekazanie polece� rysuj�cych do wykonania
		glutSwapBuffers();
	}

	void specialKey(int key, int x, int y)
	{

		switch (key)
		{
		case GLUT_KEY_UP:
			potTransition[0] = potTransition[0] + 6.0;
			break;
		case GLUT_KEY_DOWN:
			potTransition[0] = potTransition[0] - 6.0;
			break;
		case GLUT_KEY_LEFT:
			potTransition[1] = potTransition[1] + 6.0;
			break;
		case GLUT_KEY_RIGHT:
			potTransition[1] = potTransition[1] - 6.0;
			break;
		default: break;
		}
		renderTeapot(potTransition[0], potTransition[1]);
		//RenderScene();
		glutPostRedisplay();
	}

	void addNewEgg(Egg newEgg)
	{
		existingEggs.push_back(newEgg);
	}

	GLbyte* LoadTGAImage(const char* FileName, GLint* ImWidth, GLint* ImHeight, GLint* ImComponents, GLenum* ImFormat)
	{
		// Struktura dla nag��wka pliku  TGA
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

		// Warto�ci domy�lne zwracane w przypadku b��du

		*ImWidth = 0;
		*ImHeight = 0;
		*ImFormat = GL_BGR_EXT;
		*ImComponents = GL_RGB8;
		pFile = fopen(FileName, "rb");
		if (pFile == NULL)
			return NULL;

		// Przeczytanie nag��wka pliku
		fread(&tgaHeader, sizeof(TGAHEADER), 1, pFile);

		// Odczytanie szeroko�ci, wysoko�ci i g��bi obrazu
		*ImWidth = tgaHeader.width;
		*ImHeight = tgaHeader.height;
		sDepth = tgaHeader.bitsperpixel / 8;

		// Sprawdzenie, czy g��bia spe�nia za�o�one warunki (8, 24, lub 32 bity)
		if (tgaHeader.bitsperpixel != 8 && tgaHeader.bitsperpixel != 24 && tgaHeader.bitsperpixel != 32)
			return NULL;

		// Obliczenie rozmiaru bufora w pami�ci
		lImageSize = tgaHeader.width * tgaHeader.height * sDepth;

		// Alokacja pami�ci dla danych obrazu
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
		// Definicja materia�u z jakiego zrobiony jest czajnik
		GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
		// wsp�czynniki ka =[kar,kag,kab] dla �wiat�a otoczenia

		GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
		// wsp�czynniki kd =[kdr,kdg,kdb] �wiat�a rozproszonego

		GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
		// wsp�czynniki ks =[ksr,ksg,ksb] dla �wiat�a odbitego

		GLfloat mat_shininess = { 10.0 };
		// wsp�czynnik n opisuj�cy po�ysk powierzchni


		// Zmienne dla obrazu tekstury
		GLbyte *pBytes;
		GLint ImWidth, ImHeight, ImComponents;
		GLenum ImFormat;


		// Definicja �r�d�a �wiat�a

		GLfloat light_position[] = { 0.0, 0.0, 5.0, 1.0 };
		// po�o�enie �r�d�a
		GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
		// sk�adowe intensywno�ci �wiecenia �r�d�a �wiat�a otoczenia
		// Ia = [Iar,Iag,Iab]
		GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
		// sk�adowe intensywno�ci �wiecenia �r�d�a �wiat�a powoduj�cego
		// odbicie dyfuzyjne Id = [Idr,Idg,Idb]
		GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
		// sk�adowe intensywno�ci �wiecenia �r�d�a �wiat�a powoduj�cego
		// odbicie kierunkowe Is = [Isr,Isg,Isb]
		GLfloat att_constant = { 1.0 };
		// sk�adowa sta�a ds dla modelu zmian o�wietlenia w funkcji
		// odleg�o�ci od �r�d�a
		GLfloat att_linear = (GLfloat) 0.05;
		// sk�adowa liniowa dl dla modelu zmian o�wietlenia w funkcji
		// odleg�o�ci od �r�d�a
		GLfloat att_quadratic = (GLfloat)  0.001;
		// sk�adowa kwadratowa dq dla modelu zmian o�wietlenia w funkcji
		// odleg�o�ci od �r�d�a

		// Ustawienie parametr�w materia�u i �r�d�a �wiat�a

		// Ustawienie patrametr�w materia�u
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
		// Teksturowanie b�dzie prowadzone tyko po jednej stronie �ciany
		glEnable(GL_FRONT_FACE);
		//  Przeczytanie obrazu tekstury z pliku o nazwie tekstura.tga
		pBytes = LoadTGAImage("images/bricks.tga", &ImWidth, &ImHeight, &ImComponents, &ImFormat);
		// Zdefiniowanie tekstury 2-D
		glTexImage2D(GL_TEXTURE_2D, 0, ImComponents, ImWidth, ImHeight, 0, ImFormat, GL_UNSIGNED_BYTE, pBytes);
		// Zwolnienie pami�ci
		free(pBytes);
		// W��czenie mechanizmu teksturowania
		glEnable(GL_TEXTURE_2D);
		// Ustalenie trybu teksturowania
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		// Okre�lenie sposobu nak�adania tekstur
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Ustawienie parametr�w �r�d�a
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, att_constant);
		glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, att_linear);
		glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, att_quadratic);

		// Ustawienie opcji systemu o�wietlania sceny
		glShadeModel(GL_SMOOTH); // w�aczenie �agodnego cieniowania
		glEnable(GL_LIGHTING);   // w�aczenie systemu o�wietlenia sceny
		glEnable(GL_LIGHT0);     // w��czenie �r�d�a o numerze 0
		glEnable(GL_DEPTH_TEST); // w��czenie mechanizmu z-bufora
	}

	void ChangeSize(GLsizei horizontal, GLsizei vertical)
	{
		pix2angle = 360.0 / (float)horizontal;  // przeliczenie pikseli na stopnie
		glMatrixMode(GL_PROJECTION);
		// Prze��czenie macierzy bie��cej na macierz projekcji

		glLoadIdentity();
		// Czyszcznie macierzy bie��cej

		gluPerspective(70, 1.0, 1.0, 30.0);
		// Ustawienie parametr�w dla rzutu perspektywicznego

		if (horizontal <= vertical)
			glViewport(0, (vertical - horizontal) / 2, horizontal, horizontal);
		else
			glViewport((horizontal - vertical) / 2, 0, vertical, vertical);
		// Ustawienie wielko�ci okna okna widoku (viewport) w zale�no�ci
		// relacji pomi�dzy wysoko�ci� i szeroko�ci� okna

		glMatrixMode(GL_MODELVIEW);
		// Prze��czenie macierzy bie��cej na macierz widoku modelu  

		glLoadIdentity();
		// Czyszczenie macierzy bie��cej
	}

	void main(void)
	{
		//srand(time(NULL));

		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
		glutInitWindowSize(300, 300);
		glutCreateWindow("Sokoban");
		//	GeneratingTab();

		glutDisplayFunc(RenderScene);
		// Okre�lenie, �e funkcja RenderScene b�dzie funkcj� zwrotn�
		// (callback function).  B�dzie ona wywo�ywana za ka�dym razem
		// gdy zajdzie potrzeba przerysowania okna
		glutReshapeFunc(ChangeSize);
		// Dla aktualnego okna ustala funkcj� zwrotn� odpowiedzialn�
		// za zmiany rozmiaru okna                      
		glutMouseFunc(Mouse);
		// Ustala funkcj� zwrotn� odpowiedzialn� za badanie stanu myszy
		glutMotionFunc(Motion);
		// Ustala funkcj� zwrotn� odpowiedzialn� za badanie ruchu myszy
		glutSpecialFunc(specialKey);

		MyInit();
		// Funkcja MyInit() (zdefiniowana powy�ej) wykonuje wszelkie
		// inicjalizacje konieczne  przed przyst�pieniem do renderowania
		glEnable(GL_DEPTH_TEST);
		// W��czenie mechanizmu usuwania niewidocznych element�w sceny
		glutMainLoop();
		// Funkcja uruchamia szkielet biblioteki GLUT
	}