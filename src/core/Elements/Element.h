#pragma once
#include "raylib.h"
#include "../Properties.h"
#include <string>
class Element {
	Rectangle pos;
protected:
	static float timer;
public:
	Element(Rectangle pos);

	virtual ~Element();

	virtual void update();

	virtual bool press();

	virtual void unPress();

	virtual void draw();

	virtual void updatePos(){}

	virtual Rectangle getPos() const { return pos; }

	void moveTo(Vector2 moveTo) { pos.x = moveTo.x; pos.y = moveTo.y; }

	void setPos(Rectangle pos) { this->pos = pos; }

	virtual void reloadData(){}

	static void addDeltaTime(float deltaTime) { timer += deltaTime; }

	static void resetTimer() { timer = 0; }
};