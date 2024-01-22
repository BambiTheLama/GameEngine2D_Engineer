#include "CollidingBlock.h"


CollidingBlock::CollidingBlock(CollidingBlock& obj):Block(obj), RectangleCollider (obj)
{

}

CollidingBlock::CollidingBlock(Rectangle pos, ToolType requestType, int power, std::string name)
	:Block(pos, requestType, power, name), RectangleCollider({ 0,0,pos.width,pos.height })
{

}
