#pragma once
#include<stdlib.h>
#include<math.h>
#include<iostream>
#include <random>
#include <chrono>
#include <cmath>
#include <functional>
#include <stdio.h>
#include <gl/glut.h>

struct Point {
	float x, y, z, nx, ny, nz, xv, xu, yv, yu, zv, zu;
};

class Egg
{
public:
	int N = 100;                        // ilo�� punkt�w (okr�g�o�� jajka)
	Point **pointsTable;
	Egg();
	~Egg();
	void renderEgg();					//funkcja wyrysowuj�ca jajko
};

