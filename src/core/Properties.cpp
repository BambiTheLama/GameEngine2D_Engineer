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


Properties::Properties()
{
	font = LoadFont("Resource/ComicStans.ttf");
}
Properties::~Properties()
{
	UnloadFont(font);
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