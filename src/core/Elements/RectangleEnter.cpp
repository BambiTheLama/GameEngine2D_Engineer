#include "RectangleEnter.h"

RectangleEnter::RectangleEnter(Rectangle pos, std::string name, Rectangle* rec) :Element(pos)
{
	this->rec = rec;
	this->name = name;
	int x = textSize(name.c_str(), textStandardSize).x;
	enterRets[0] = { pos.x+x,pos.y,(pos.width- x)/4,pos.height };
	for (int i = 1; i < 4; i++)
	{
		enterRets[i] = enterRets[i - 1];
		enterRets[i].x += enterRets[i].width;
	}
	usingRec = -1;

}

RectangleEnter::~RectangleEnter()
{

}
void chagneValue(float* p, int val)
{
	if (val < 0)
	{
		(*p) = (int)((*p) / 10);
	}
	else
	{
		(*p) = (*p) * 10 + val;

	}

}
void RectangleEnter::update()
{
	if (usingRec < 0 || !isAnyKeyPressed())
		return;
	int val = 0;
	int key=keyPressed();
	printf("%d\n", key);
	if (key >= '0' && key <= '9')
		val = key - '0';
	else if (IsKeyPressed(KEY_BACKSPACE))
	{
		val = -1;
	}
	else
		return;
	if (usingRec == 0)
		chagneValue(&rec->x, val);
	else if (usingRec == 1)
		chagneValue(&rec->y, val);
	else if (usingRec == 2)
		chagneValue(&rec->width, val);
	else if (usingRec == 3)
		chagneValue(&rec->height, val);

}

bool RectangleEnter::press()
{
	for (int i = 0; i < 4; i++)
	{
		if (CheckCollisionPointRec(GetMousePosition(), enterRets[i]))
		{
			usingRec = i;
			return true;
		}

	}
	usingRec = -1;
	return false;
}

void RectangleEnter::unPress()
{
	usingRec = -1;
}

void RectangleEnter::draw()
{
	Rectangle pos = getPos();
	Element::draw();
	DrawRectangleLinesEx(pos, 2, BLACK);
	drawText(name.c_str(), pos.x, pos.y, textStandardSize, BLACK);
	std::string data[4] = {"x:\n"+std::to_string((int)rec->x),"y:\n" + std::to_string((int)rec->y) ,
	"w:\n" + std::to_string((int)rec->width) ,"h:\n" + std::to_string((int)rec->height) };
	for (int i = 0; i < 4; i++)
	{
		DrawRectangleLinesEx(enterRets[i], 2, BLACK);

		drawText(data[i].c_str(), enterRets[i].x + 2, enterRets[i].y, textStandardSize, BLACK);
	}
}