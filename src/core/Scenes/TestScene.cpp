#include "TestScene.h"
#include <iostream>
#include "../Properties.h"
#include "../Engine.h"
#include "Menu.h"
TestScene::TestScene()
{
	SetExitKey(0);
	int s = 10;
	int w = 1600, h = 900;
	bool firstLayer = true;
	noice = new PerlinNoice(w/s, h/s, s);
	bool secendLayer = true;
	noice2 = new PerlinNoice(w/s, h/s, s);
	bool thirdLayer = true;
	noice3 = new PerlinNoice(w/s, h/s, s);
	noice->generateNoise2D(octet, scale, seed, x, y);
	noice2->generateNoise2D(octet, scale, seed+69, x, y);
	noice3->generateNoise2D(octet, scale, seed+2137, x, y);
	buffor = LoadRenderTexture(1900, 900);
	reloadNoice();
}

TestScene::~TestScene()
{
	delete noice;
	delete noice2;
	delete noice3;
	UnloadRenderTexture(buffor);
}

void TestScene::start()
{

}
void TestScene::reloadNoice()
{
	printf("RELOAD\n");
	noice->generateNoise2D(octet, scale, seed, x, y);
	noice2->generateNoise2D(octet, scale, seed + 69, x, y);
	noice3->generateNoise2D(octet, scale, seed + 2137, x, y);
	BeginTextureMode(buffor);
	ClearBackground(WHITE);
	int w = noice->getW();
	int h = noice->getH();
	for (int x = 0; x < 1600; x++)
		for (int y = 0; y < 900; y++)
		{
			float v = firstLayer ? ((noice->getValue(x  - 800, y - 450) + 1.0f) / 2.0f * 255) : 0;
			float v2 = secendLayer?((noice2->getValue(x - 800, y - 450) + 1.0f) / 2.0f * 255):0;
			float v3 = thirdLayer?((noice3->getValue(x  - 800, y - 450) + 1.0f) / 2.0f * 255):0;
			//printf("%lf    %lf\n", perlin[y][x],v);
			DrawRectangle(x, y, 1, 1, { (unsigned char)v,(unsigned char)v2,(unsigned char)v3,255 });
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
	if (IsKeyPressed(KEY_ONE))
		firstLayer = !firstLayer;
	if (IsKeyPressed(KEY_TWO))
		secendLayer = !secendLayer;
	if (IsKeyPressed(KEY_THREE))
		thirdLayer = !thirdLayer;
}

void TestScene::draw()
{
	DrawTexture(buffor.texture, 0, 0, WHITE);
	DrawTextWithOutline(TextFormat("(%d) (%d)\n(%lf)\n%d\n%d %d %d", x, y, scale, octet,firstLayer,secendLayer,thirdLayer), 0, 0, 30, WHITE, BLACK);
}