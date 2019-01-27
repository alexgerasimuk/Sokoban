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
	public:
	GLfloat eggTransition[2];
	Egg(GLfloat x, GLfloat z);
	void setPosition(GLfloat x, GLfloat z);
	int N = 100;                        // iloœæ punktów (okr¹g³oœæ jajka)
	Point **pointsTable;
	void GeneratingTab();
	~Egg();
};

