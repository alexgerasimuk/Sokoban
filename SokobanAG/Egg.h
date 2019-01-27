#pragma once
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

struct Point {
	float x, y, z, nx, ny, nz, xv, xu, yv, yu, zv, zu;
};

class Egg
{
	GLfloat eggTransition[2];
public:
	Egg(GLfloat x, GLfloat z);
	void setPosition(GLfloat x, GLfloat z);
	int N = 100;                        // ilo�� punkt�w (okr�g�o�� jajka)
	Point **tablica;
	void GeneratingTab();
	~Egg();
};

