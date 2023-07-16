#include "CollidingBlock.h"


CollidingBlock::CollidingBlock(CollidingBlock& obj):Block(obj),Collider(obj)
{

}

CollidingBlock::CollidingBlock(Rectangle pos, ToolType requestType, int power, std::string name)
	:Block(pos, requestType, power, name), Collider({ 0,0,pos.width,pos.height })
{

}
