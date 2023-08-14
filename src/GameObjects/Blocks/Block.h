#pragma once
#include "../GameObject.h"
#include "../../core/Controllers/SpriteController.h"
#include "../AddisionalTypes/AllTypes.h"
#include <string>

/// <summary>
/// Sprawdzenie czy mo¿na rozwaliæ ten obiekt danym narzêdziem
/// </summary>
/// <param name="tool">Narzêdzie które u¿ywamy</param>
/// <param name="requestTool">Narzêdzie które jest potrzebne</param>
/// <returns>Czy mo¿emy zniszczyæ tym narzêdziem</returns>


/// <summary>
/// Klasa od bloków naszej gry
/// </summary>
class Block :
    public GameObject, public DestroyAble, public ItemsDrop
{
protected:
    bool right = true, left = true, down = true, up = true;
    Rectangle texturePos;
    SpriteController* sprite;
    Block(Block& obj);



    
public:
    Block(Rectangle pos, ToolType requestType, int power, std::string name);

    ~Block();

    virtual void start();

    virtual void update(float deltaTime);

    virtual void draw();

    virtual void drawInMiniMap(int x, int y);

    virtual void damageObject(int power, ToolType tool);

    ObjectType getType() { return ObjectType::Block; }

    virtual Block* clone() { return new Block(*this); }

    virtual Rectangle getCollisionPos() { return pos; }

    void generateTexturePos();
};

