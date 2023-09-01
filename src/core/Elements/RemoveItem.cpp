#include "RemoveItem.h"
#include "../Scenes/ItemEdytor.h"
RemoveItem::RemoveItem(Rectangle pos, ItemEdytor* edytor) :Element(pos)
{
	this->edytor = edytor;
}

bool RemoveItem::press()
{
	if (!CheckCollisionPointRec(GetMousePosition(), getPos()))
		return false;
	edytor->removeItem();
	return true;
}

void RemoveItem::draw()
{
	Element::draw();
	Rectangle pos = getPos();
	DrawCircle(pos.x + pos.width / 2, pos.y + pos.height / 2, pos.width / 2, GRAY);
	DrawRectangle(pos.x, pos.y + pos.height / 2 - 2, pos.width, 4, BLACK);
}