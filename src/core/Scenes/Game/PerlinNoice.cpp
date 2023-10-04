#include "PerlinNoice.h"


float randomValue(int seed)
{
	seed = (seed << 13) ^ seed;
	return 1.0f - ((seed * (seed * seed * 2137 + 769221) + 2137612569) & 0x7FFFFFFF) / 1073741824.0f;
}

float lerp(float a, float b, float t)
{
	return a + t * (b - a);
}

float smoothInterpolation(float a, float b, float t)
{
	float ft = t * 3.1415927f;
	float f = (1.0f - cos(ft)) * 0.5f;
	return a * (1.0f - f) + b * f;
}


PerlinNoice::PerlinNoice(int w, int h, int scale)
{
	this->w = w;
	this->h = h;
	noiceTab2D = new float* [h];
	seed2D = new float* [h];
	for (int i = 0; i < h; i++)
	{
		seed2D[i] = new float[w];
		noiceTab2D[i] = new float[w];
	}
	if (scale <= 0)
		scale = 1;
	this->scale = scale;
	startX = -(w) / 2;
	startY = -(h) / 2;

}
PerlinNoice::~PerlinNoice()
{

	for (int i = 0; i < h; i++)
	{
		delete seed2D[i];
		delete noiceTab2D[i];
	}
	delete seed2D;
	delete noiceTab2D;
}
void PerlinNoice::generateSeed2D(unsigned int seed, int startX, int startY)
{
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			seed2D[i][j] = randomValue(((i + startY) * w + (j + startX)) * seed);
		}
	}
}
void PerlinNoice::generateNoise2D(int octavies, float scaling, unsigned int seed,int startX,int startY)
{
	generateSeed2D(seed, startX, startY);
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			float noiseValue = 0.0f;
			float scale = 1.0f;
			float scaleAccumulation = 0.0f;

			// Dla ka¿dej oktawy
			for (int octave = 0; octave < octavies; ++octave)
			{
				int sampleX0 = static_cast<int>(x / scale) % w;
				int sampleX1 = (sampleX0 + 1) % w;
				int sampleY0 = static_cast<int>(y / scale) % h;
				int sampleY1 = (sampleY0 + 1) % h;

				float interpolationX = static_cast<float>(x / scale) - sampleX0;
				float interpolationY = static_cast<float>(y / scale) - sampleY0;

				float sampleTopLeft = seed2D[sampleY0][sampleX0];
				float sampleTopRight = seed2D[sampleY0][sampleX1];
				float sampleBottomLeft = seed2D[sampleY1][sampleX0];
				float sampleBottomRight = seed2D[sampleY1][sampleX1];

				float interpolatedValueTop = smoothInterpolation(sampleTopLeft, sampleTopRight, interpolationX);
				float interpolatedValueBottom = smoothInterpolation(sampleBottomLeft, sampleBottomRight, interpolationX);

				noiseValue += lerp(interpolatedValueTop, interpolatedValueBottom, interpolationY) * scale;
				scaleAccumulation += scale;
				scale *= scaling;
			}

			noiceTab2D[y][x] = noiseValue / scaleAccumulation;
		}
	}
}

float PerlinNoice::getValue(int x, int y)
{
	x += (scale*w) / 2;
	y += (scale*h) / 2;
	if (x < 0 || y < 0 || x >= w * scale || y >= scale * h)
		return -1;
	int rx = x % scale;
	int x1 = x / scale;
	int x2 = x1 + ((rx > 0) ? 1 : 0);
	if (x2 >= w)
		x2 = w - 1;
	
	int ry = y % scale;
	int y1 = y / scale;
	int y2 = y1 + ((ry > 0) ? 1 : 0);
	if (y2 >= h)
		y2 = h - 1;
	return noiceTab2D[y1][x1] * (scale - rx + scale - ry) / (scale + scale) + noiceTab2D[y2][x2] * (rx + ry) / (scale + scale);
}