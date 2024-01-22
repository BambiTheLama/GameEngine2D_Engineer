#pragma once
#include "Block.h"
class CollidingBlock :
    public Block, public RectangleCollider
{
    CollidingBlock(CollidingBlock& obj);
public:
    CollidingBlock(Rectangle pos, ToolType requestType, int power, std::string name);

    virtual CollidingBlock* clone() { return new CollidingBlock(*this); }

    virtual bool isColliding() { return true; }
};

