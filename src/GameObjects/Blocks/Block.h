#pragma once
#include "../GameObject.h"
#include "../../core/Controllers/SpriteController.h"
#include "../AddisionalTypes/AllTypes.h"
#include <string>
/// <summary>
/// Enum odpowiadajacy ¿e to jakie narzêdzie mo¿e zniszczyæ jaki blok
/// </summary>
enum class ToolType {
    NON = -1,               //Zadne narzêdzie nie mo¿e wykopaæ
    All = 0,                //Mo¿e wykopaæ wszystko
    Axe = 2,                //Wszystko to co mo¿e sikiera
    Shovel = 3,             //Wszystko to co mo¿e ³opata
    Pickaxe = 5,            //Wszystko to co mo¿e kilof
    AxeShovel=6,            //Wszystko to co mo¿e sikiera i ³opata
    AxePickaxe=10,          //Wszystko to co mo¿e sikiera i kilof
    ShovelPickaxe=15,       //Wszystko to co mo¿e ³opata i kilof
    AxeShovelPickaxe = 30   //Wszystko to co mo¿e sikiera ³opata i kilof
};
/// <summary>
/// Sprawdzenie czy mo¿na rozwaliæ ten obiekt danym narzêdziem
/// </summary>
/// <param name="tool">Narzêdzie które u¿ywamy</param>
/// <param name="requestTool">Narzêdzie które jest potrzebne</param>
/// <returns>Czy mo¿emy zniszczyæ tym narzêdziem</returns>
bool isThisToolType(ToolType tool, ToolType requestTool);

/// <summary>
/// Klasa od bloków naszej gry
/// </summary>
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
    Block(Rectangle pos, ToolType requestType, int power, std::string name);

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

