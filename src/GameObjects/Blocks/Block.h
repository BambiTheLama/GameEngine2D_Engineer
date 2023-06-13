#pragma once
#include "../GameObject.h"
enum class ToolType {
    All = 0, Axe = 2, Shovel = 3, Pickaxe = 6
};
class Block :
    public GameObject
{
protected:
    int hp,power;
    ToolType requestType;
    Color c;
    Block(Block& obj);

    
public:
    Block(Rectangle pos, ToolType requestType, int power, Color c);

    ~Block();

    virtual void update();

    virtual void draw();

    virtual void damageBlock(int power, ToolType tool);

    ObjectType getType() { return ObjectType::Block; }

    virtual Block* clone() { return new Block(*this); }

    virtual bool isColliding() { return true; }

};

