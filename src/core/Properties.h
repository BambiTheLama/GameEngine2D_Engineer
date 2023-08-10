#pragma once
#include "raylib.h"
#define textStandardSize 26
#define textStandardSize2 16
#define collidersToDraw Properties::getProperties()->getShowColliders()
void drawText(const char* text, int x, int y, int size, Color color);
Vector2 textSize(const char* text, int size, int spacing=0);
void DrawTextWithOutline(const char* text, int x, int y, int fontSize, Color textColor, Color outlineColor);
class Properties
{
	static Properties* properties;
	bool showColliders = false;
	Font font;
	Properties();
	~Properties();
public:
	static Properties* getProperties();

	void drawText(const char* text, int x, int y, int size, Color color);

	Vector2 textSize(const char* text, int size, int spacing);

	bool getShowColliders() const { return showColliders; }

	friend class Engine;
};

