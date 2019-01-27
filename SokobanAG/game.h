#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#include<stdlib.h>
#include<Windows.h>
#include<math.h>
#include<iostream>
#include <random>
#include <chrono>
#include <cmath>
#include <functional>
#include <stdio.h>
#include<gl\glut.h>
#include<gl\Gl.h>
#include "Egg.h"

#define M_PI 3.14159265358979323846
using namespace std;

class game
{
	typedef float point3[3];

	static GLfloat theta = 0.0;   // k¹t obrotu obiektu
	static GLfloat phi = 0.0;
	static GLfloat pix2angle;     // przelicznik pikseli na stopnie

	static GLint status = 0;       // stan klawiszy myszy
								   // 0 - nie naciœniêto ¿adnego klawisza
								   // 1 - naciœniêty zostaæ lewy klawisz
								   // 2 - naciœniêty zosta³ prawy klawisz                              

	static int x_pos_old = 0;       // poprzednia pozycja kursora myszy

	static int delta_x = 0;        // ró¿nica pomiêdzy pozycj¹ bie¿¹c¹
								   // i poprzedni¹ kursora myszy

	static int y_pos_old = 0;       // poprzednia pozycja kursora myszy

	static int delta_y = 0;        // ró¿nica pomiêdzy pozycj¹ bie¿¹c¹
								   // i poprzedni¹ kursora myszy

	static GLfloat R = 5.0;         //poczatkowy promien
	static GLfloat viewer[] = { 0.0, 0.0, 5.0 };
	void Mouse(int btn, int state, int x, int y);
	void Motion(GLsizei x, GLsizei y);
	void RenderScene(void);
	void renderTeapot(GLfloat x, GLfloat z);
	static void specialKey(int key, int x, int y);
	void addNewEgg(Egg newEgg);

	GLbyte *LoadTGAImage(const char *FileName, GLint *ImWidth, GLint *ImHeight, GLint *ImComponents, GLenum *ImFormat);
	// Funkcja ustalaj¹ca stan renderowania
	void MyInit(void);
	void ChangeSize(GLsizei horizontal, GLsizei vertical);
	// G³ówny punkt wejœcia programu. Program dzia³a w trybie konsoli
	GLfloat potTransition[2];
	vector<Egg> existingEggs;
};
