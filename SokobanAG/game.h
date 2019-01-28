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
#include "Floor.h"

#define M_PI 3.14159265358979323846
using namespace std;

	typedef float point3[3];
	enum moves
	{
		upM = 1,
		downM = 2,
		leftM = 3,
		rightM = 4
	};
	static int currentMove;
	static GLfloat theta = 0.0;     // k�t obrotu obiektu
	static GLfloat phi = 0.0;
	static GLfloat pix2angle;       // przelicznik pikseli na stopnie
	static GLint status = 0;        // stan klawiszy myszy
								    // 0 - nie naci�ni�to �adnego klawisza
								    // 1 - naci�ni�ty zosta� lewy klawisz
								    // 2 - naci�ni�ty zosta� prawy klawisz                              
	static Floor level;
	Egg egg(0.0, 0.0);

	static int x_pos_old = 0;       // poprzednia pozycja kursora myszy
	static int delta_x = 0;         // r�nica pomi�dzy pozycj� bie��c� i poprzedni� kursora myszy
	static int y_pos_old = 0;       // poprzednia pozycja kursora myszy
	static int delta_y = 0;			// r�nica pomi�dzy pozycj� bie��c� i poprzedni� kursora myszy
	static GLfloat R = 15.0;        //poczatkowy promien
	static GLfloat viewer[] = { 0.0, 0.0, 5.0 };

	void Mouse(int btn, int state, int x, int y);
	void Motion(GLsizei x, GLsizei y);
	void RenderScene(void);
	void renderTeapot(GLfloat x, GLfloat z);
	void renderEgg(GLfloat x, GLfloat z);
	void specialKey(int key, int x, int y);
	void checkForCollision(GLfloat potTransition[] , vector <Egg> &existingEggs);

	GLbyte *LoadTGAImage(const char *FileName, GLint *ImWidth, GLint *ImHeight, GLint *ImComponents, GLenum *ImFormat);
	void MyInit();
	void ChangeSize(GLsizei horizontal, GLsizei vertical);
	GLfloat potTransition[2] = { 6.0, 0.0 };
	vector <Egg> existingEggs;