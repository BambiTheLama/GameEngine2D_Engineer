#include "Properties.h"

Properties* Properties::properties = NULL;

void drawText(const char* text, int x, int y, int size, Color color)
{
	Properties::getProperties()->drawText(text, x, y, size, color);
}
Vector2 textSize(const char* text, int size, int spacing)
{
	return Properties::getProperties()->textSize(text, size, spacing);
}
Properties* Properties::getProperties()
{
	if (properties == NULL)
		properties = new Properties();
	return properties;
}
void DrawTextWithOutline(const char* text, int x, int y, int fontSize, Color textColor, Color outlineColor) {
	for (int ox = -1; ox <= 1; ox++) {
		for (int oy = -1; oy <= 1; oy++) {
			if (ox != 0 || oy != 0) {
				Properties::getProperties()->drawText(text, x + ox, y + oy, fontSize, outlineColor);
			}
		}
		Properties::getProperties()->drawText(text, x, y, fontSize, textColor);
	}
}
int key;
int keyPressed()
{
	return key;
}
bool isAnyKeyPressed()
{
	key = GetKeyPressed();
	if (key > 0)
		return true;
	return false;
}
void drawViewFinder(Rectangle pos, Color c)
{
	Properties::getProperties()->drawViewFinder(pos,c);
}

Properties::Properties()
{
	font = LoadFont("Resource/RobotoSlab-Regular.ttf");
	font.baseSize = 32;
	viewFinder = LoadTexture("Resource/ViewFinder.png");
}
Properties::~Properties()
{
	UnloadFont(font);
	if(viewFinder.id>=0)
		UnloadTexture(viewFinder);
	properties = NULL;
}
void Properties::drawText(const char* text, int x, int y, int size, Color color)
{
	DrawTextPro(font, text, { (float)x,(float)y }, { 0,0 }, 0, size,0 , color);
}

Vector2 Properties::textSize(const char* text, int size, int spacing)
{
	return MeasureTextEx(font, text, size, spacing);
}

void Properties::drawViewFinder(Rectangle pos, Color c)
{
	DrawTexturePro(viewFinder, { 0,0,(float)viewFinder.width,(float)viewFinder.height }, pos, { 0,0 }, 0, c);
}