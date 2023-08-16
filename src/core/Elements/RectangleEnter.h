#pragma once
#include "Element.h"
#include <string>


class RectangleEnter :
    public Element
{
	Rectangle *rec;
	Rectangle enterRets[4];
	std::string name;
	int usingRec;
public:
	RectangleEnter(Rectangle pos,std::string name,Rectangle* rec);

	virtual ~RectangleEnter();

	virtual void update();

	virtual void updatePos();

	virtual bool press();

	virtual void unPress();

	virtual void draw();
};

