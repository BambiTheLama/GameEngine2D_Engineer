#include "Block.h"
#include "../../core/Scenes/GameScene.h"

Block::Block(Block& obj):GameObject(obj)
{
	requestType = obj.requestType;
	hp = obj.hp;
	power = obj.power;
	c = obj.c;
}

Block::Block(Rectangle pos, ToolType requestType,int power,Color c) :GameObject(pos)
{
	this->requestType = requestType;
	int hp = 10;
	this->power = power;
	this->c = c;
}
Block::~Block()
{

}

void Block::update()
{

}

void Block::draw()
{
	Rectangle pos = getPos();
	DrawRectangleRec(pos, c);
}

void Block::damageBlock(int power, ToolType tool)
{
	if (this->power > power || (tool != requestType && requestType != ToolType::All))return;
	
	hp -= power / (this->power * 0.5);
	if (hp <= 0)
	{
		Game->deleteBlocks(getPos());
	}
	
}

