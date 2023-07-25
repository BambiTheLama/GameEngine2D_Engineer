#include "DestroyAble.h"

bool isThisToolType(ToolType tool, ToolType requestTool)
{
	if ((int)requestTool >= 0)
		return  ((int)requestTool % (int)tool) == 0;
	return false;
}

DestroyAble::DestroyAble(ToolType request,int hp,int power)
{
	itemToolRequest = request;
	this->power = power;
	this->hp = hp;

}
DestroyAble::DestroyAble(DestroyAble& dest)
{
	itemToolRequest = dest.itemToolRequest;
	hp = dest.hp;
	power = dest.power;
}

void DestroyAble::damageObject(int power, ToolType type)
{
	if (!isThisToolType(type, itemToolRequest)) 
		return;
	if (this->power > 0)
		hp -= power / this->power;
	else
		hp = 0;
}