#include "TestScene.h"
#include <iostream>
#include "../Properties.h"
#include "../Engine.h"
#include "Menu.h"
TestScene::TestScene()
{
	SetExitKey(0);
	int s = 2;
	int w = 1600, h = 900;
	buffor = LoadRenderTexture(1900, 900);
	reloadNoice();
}

TestScene::~TestScene()
{
	UnloadRenderTexture(buffor);
}

void TestScene::start()
{

}
void TestScene::reloadNoice()
{
	FastNoiseLite noise;
	int seed = 666;

	noise.SetSeed(seed + 1);
	noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
	noise.SetFrequency(0.0010102f);
	noise.SetFractalType(FastNoiseLite::FractalType_FBm);
	noise.SetFractalOctaves(4);
	noise.SetFractalGain(6.315f);
	noise.SetFractalLacunarity(0.46f);
	noise.SetFractalWeightedStrength(-0.34f);

	printf("RELOAD\n");
	BeginTextureMode(buffor);
	ClearBackground(WHITE);
	for (int x = 0; x < 1600; x++)
		for (int y = 0; y < 900; y++)
		{
			float v = noise.GetNoise(this->x+(float)x, this->y+(float)y);
			if (v > 1)
				v = 1;
			else if (v < -1)
				v = -1;
			v += 1;
			v /= 2;
			v *= 255;
			DrawRectangle(x, y, 1, 1, { (unsigned char)v,(unsigned char)v,(unsigned char)v,255 });
		}
	EndTextureMode();
}

void TestScene::update(float deltaTime)
{
	if (IsKeyReleased(KEY_ESCAPE))
	{
		Engine::setScene(new Menu());
		return;
	}
	if (IsKeyPressed(KEY_W))
		y--;
	if (IsKeyPressed(KEY_S))
		y++;
	if (IsKeyPressed(KEY_A))
		x--;
	if (IsKeyPressed(KEY_D))
		x++;
	if (IsKeyPressed(KEY_R))
		reloadNoice();
	if (IsKeyPressed(KEY_DOWN))
		scale -= 0.1;
	if (IsKeyPressed(KEY_UP))
		scale += 0.1;
	if (IsKeyPressed(KEY_LEFT))
		octet--;
	if (IsKeyPressed(KEY_RIGHT))
		octet++;
}

void TestScene::draw()
{
	DrawTexture(buffor.texture, 0, 0, WHITE);
	DrawTextWithOutline(TextFormat("(%d) (%d)\n(%lf)\n%d\n", x, y, scale, octet), 0, 0, 30, WHITE, BLACK);
}