#include "CollidingBlock.h"


CollidingBlock::CollidingBlock(CollidingBlock& obj):Block(obj),Collider(obj)
{

}

CollidingBlock::CollidingBlock(Rectangle pos, ToolType requestType, int power, std::string path)
	:Block(pos, requestType, power, path), Collider({ 0,0,pos.width,pos.height })
{

}
