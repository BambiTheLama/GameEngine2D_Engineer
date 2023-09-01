#include "DestroyAble.h"

std::string toolTypeDescription()
{
	std::string s="";
	s += std::to_string((int)(ToolType::NON)) + " - This Tool cant destory anything";
	s += "\n"+ std::to_string((int)(ToolType::Axe)) +" - This Tool can destory that need axe";
	s += "\n"+ std::to_string((int)(ToolType::Shovel)) +" - This Tool can destory that need shovel";
	s += "\n"+ std::to_string((int)(ToolType::Pickaxe)) +" - This Tool can destory that need pickaxe";
	s += "\n"+ std::to_string((int)(ToolType::AxeShovel)) +" - This Tool can destory that need axe and shovel";
	s += "\n"+ std::to_string((int)(ToolType::AxePickaxe)) +" - This Tool can destory that need axe and pickaxe";
	s += "\n"+ std::to_string((int)(ToolType::ShovelPickaxe)) +" - This Tool can destory that need shovel and pickaxe";
	s += "\n"+ std::to_string((int)(ToolType::AxeShovelPickaxe)) +" - This Tool can destory that need axe shovel and pickaxe";
	s += "\n"+ std::to_string((int)(ToolType::All)) +" - This Tool can destory that need ALL TOOL";
	return s;
}

bool isAxeNeed(ToolType t)
{
	return t == ToolType::Axe || t == ToolType::AxePickaxe || t == ToolType::AxeShovel 
		|| t == ToolType::AxeShovelPickaxe;
}
bool isShovelNeed(ToolType t)
{
	return t == ToolType::Shovel || t == ToolType::ShovelPickaxe || t == ToolType::AxeShovel
		|| t == ToolType::AxeShovelPickaxe;
}
bool isPickaxeNeed(ToolType t)
{
	return t == ToolType::Pickaxe || t == ToolType::AxePickaxe || t == ToolType::ShovelPickaxe
		|| t == ToolType::AxeShovelPickaxe;
}
bool isThisToolType(ToolType tool, ToolType requestTool)
{
	if (requestTool == ToolType::All)
		return true;
	if (requestTool == ToolType::NON)
		return false;
	if (tool == ToolType::All)
		return true;
	if (tool == ToolType::NON)
		return false;
	bool requestB = isAxeNeed(requestTool);
	bool toolB = isAxeNeed(tool);
	if (requestB && toolB == requestB)
		return true;
	requestB = isShovelNeed(requestTool);
	toolB = isShovelNeed(tool);
	if (requestB && toolB == requestB)
		return true;
	requestB = isPickaxeNeed(requestTool);
	toolB = isPickaxeNeed(tool);
	if (requestB && toolB == requestB)
		return true;
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