#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <random>
#include <chrono>
#include <cmath>
#include <functional>
#include <stdio.h>
#include <gl/glut.h>
#include "Egg.h"
#include "Floor.h"

#define M_PI 3.14159265358979323846
using namespace std;

typedef float point3[3];
enum moves						//mo�liwe opcje przy naci�ni�ciu strza�ek na klawiaturze
{
	noop = 0,
	upM = 1,
	downM = 2,
	leftM = 3,
	rightM = 4
};


static int currentMove = noop;
static GLfloat theta = 0.0;								// k�t obrotu obiektu
static GLfloat phi = 3.14 / 4;
static GLfloat pix2angle;								// przelicznik pikseli na stopnie
static GLint status = 0;								// stan klawiszy myszy
														// 0 - nie naci�ni�to �adnego klawisza
														// 1 - naci�ni�ty zosta� lewy klawisz
														// 2 - naci�ni�ty zosta� prawy klawisz                              
static Floor level;
Egg egg;

static int x_pos_old = 0;								// poprzednia pozycja kursora myszy
static int delta_x = 0;         						// r�nica pomi�dzy pozycj� bie��c� i poprzedni� kursora myszy
static int y_pos_old = 0;       						// poprzednia pozycja kursora myszy
static int delta_y = 0;									// r�nica pomi�dzy pozycj� bie��c� i poprzedni� kursora myszy
static GLfloat R = 15.0;       							//poczatkowy promien
static GLfloat viewer[] = { 0.0, 10.0, 10.0 };
GLbyte *firstLevelTex, *teapotTex, *eggTex;
GLint ImWidth, ImHeight, ImComponents;
GLenum ImFormat;

void Mouse(int btn, int state, int x, int y);			//funkcja obs�uguj�ca zdarzenia z myszy
void Motion(GLsizei x, GLsizei y);						//funkcja �ledz�ca ruch myszy
void RenderScene(void);
void renderTeapot(GLfloat x, GLfloat z);				//funkcja przemieszczaj�ca grafik� i wyrysowuj�ca imbryk
void renderEgg(GLfloat x, GLfloat z);					//funkcja przemieszczaj�ca grafik� i wyrysowuj�ca jajko
void specialKey(int key, int x, int y);					//funkcja obs�uguj�ca zdarzenia z klawiatury

GLbyte *LoadTGAImage(const char *FileName, GLint *ImWidth, GLint *ImHeight, GLint *ImComponents, GLenum *ImFormat);
void MyInit();
void ChangeSize(GLsizei horizontal, GLsizei vertical);

GLfloat potTransition[2] = { -6.0, 0.0 };				//macierz przechowuj�ca aktualne po�o�enie imbryczka
GLfloat eggTransition[2] = { 6.0,  0.0 };				//macierz przechowuj�ca aktualne po�o�enie jajka
