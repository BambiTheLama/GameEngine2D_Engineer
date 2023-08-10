#pragma once
#include "raylib.h"
#define textStandardSize 26
#define textStandardSize2 16
void drawText(const char* text, int x, int y, int size, Color color);
Vector2 textSize(const char* text, int size, int spacing=0);
void DrawTextWithOutline(const char* text, int x, int y, int fontSize, Color textColor, Color outlineColor);
class Properties
{
	static Properties* properties;
	Font font;
	Properties();
	~Properties();
public:
	static Properties* getProperties();

	void drawText(const char* text, int x, int y, int size, Color color);

	Vector2 textSize(const char* text, int size, int spacing);

	friend class Engine;
};

