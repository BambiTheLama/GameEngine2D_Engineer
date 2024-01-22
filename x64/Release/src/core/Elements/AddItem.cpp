#include "AddItem.h"
#include "../Scenes/ItemEdytor.h"
AddItem::AddItem(Rectangle pos, AdderEdytor* edytor):Element(pos)
{
	this->edytor = edytor;
}

bool AddItem::press()
{
	if (!CheckCollisionPointRec(GetMousePosition(), getPos()))
		return false;
	if(edytor)
		edytor->addItem();
	return true;
}

void AddItem::draw()
{
	Element::draw();
	Rectangle pos = getPos();
	DrawCircle(pos.x + pos.width / 2, pos.y + pos.height / 2, pos.width / 2, GRAY);
	DrawRectangle(pos.x + pos.width / 2 - 2, pos.y, 4, pos.height, BLACK);
	DrawRectangle(pos.x, pos.y + pos.height / 2 - 2, pos.width, 4, BLACK);
}