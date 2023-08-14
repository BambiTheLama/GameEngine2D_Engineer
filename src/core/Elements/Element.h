#pragma once
#include "raylib.h"
#include "../Properties.h"
class Element {
	bool showElement = true;
	Rectangle pos;

public:
	Element(Rectangle pos);

	virtual ~Element();

	virtual void update();

	virtual bool press();

	virtual void unPress();

	virtual void draw();

	virtual void setShowElement(bool show) { showElement = show; }

	Rectangle getPos() const { return pos; }
};