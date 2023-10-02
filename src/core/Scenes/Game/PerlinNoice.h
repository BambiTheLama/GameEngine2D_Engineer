#pragma once
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "raylib.h"
/// <summary>
/// klasa generuj¹ szum perlina
/// </summary>
class PerlinNoice
{
	int h, w;
	float** noiceTab2D = NULL;
	float** seed2D = NULL;
	int scale;
	int startX, startY;
public:
	PerlinNoice(int w, int h,int scale=1);

	~PerlinNoice();

	void generateSeed2D(unsigned int seed, int startX, int startY);

	void generateNoise2D(int octavies,float scaling,unsigned int seed, int startX=0, int startY=0);

	float** getNoice() { return noiceTab2D; }

	int getW() { return w; }

	int getH() { return h; }

	float getValue(int x, int y);
};

