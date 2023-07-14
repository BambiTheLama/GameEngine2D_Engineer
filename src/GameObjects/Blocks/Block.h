#pragma once
#include "../GameObject.h"
#include "../../core/Controllers/SpriteController.h"
#include "../AddisionalTypes/AllTypes.h"
#include <string>
enum class ToolType {
    All = 0, Axe = 2, Shovel = 3, Pickaxe = 5, NON=2137
};
class Block :
    public GameObject
{
protected:
    int hp, power;
    ToolType requestType;
    Block(Block& obj);
    SpriteController* sprite;
    Rectangle texturePos;
    bool right = true, left = true, down = true, up = true;
    
public:
    Block(Rectangle pos, ToolType requestType, int power, std::string path,std::string name);

    ~Block();

    virtual void start();

    virtual void update();

    virtual void draw();

    virtual void drawInMiniMap(int x, int y);

    virtual void damageBlock(int power, ToolType tool);

    ObjectType getType() { return ObjectType::Block; }

    virtual Block* clone() { return new Block(*this); }

    void generateTexturePos();
};

