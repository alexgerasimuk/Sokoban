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
	int N = 100;                        // iloœæ punktów (okr¹g³oœæ jajka)
	Point **pointsTable;
	Egg();
	~Egg();
	void renderEgg();					//funkcja wyrysowuj¹ca jajko
};

