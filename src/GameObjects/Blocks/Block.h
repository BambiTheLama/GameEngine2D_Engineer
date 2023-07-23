#pragma once
#include "../GameObject.h"
#include "../../core/Controllers/SpriteController.h"
#include "../AddisionalTypes/AllTypes.h"
#include <string>
/// <summary>
/// Enum odpowiadajacy �e to jakie narz�dzie mo�e zniszczy� jaki blok
/// </summary>
enum class ToolType {
    NON = -1,               //Zadne narz�dzie nie mo�e wykopa�
    All = 0,                //Mo�e wykopa� wszystko
    Axe = 2,                //Wszystko to co mo�e sikiera
    Shovel = 3,             //Wszystko to co mo�e �opata
    Pickaxe = 5,            //Wszystko to co mo�e kilof
    AxeShovel=6,            //Wszystko to co mo�e sikiera i �opata
    AxePickaxe=10,          //Wszystko to co mo�e sikiera i kilof
    ShovelPickaxe=15,       //Wszystko to co mo�e �opata i kilof
    AxeShovelPickaxe = 30   //Wszystko to co mo�e sikiera �opata i kilof
};
/// <summary>
/// Sprawdzenie czy mo�na rozwali� ten obiekt danym narz�dziem
/// </summary>
/// <param name="tool">Narz�dzie kt�re u�ywamy</param>
/// <param name="requestTool">Narz�dzie kt�re jest potrzebne</param>
/// <returns>Czy mo�emy zniszczy� tym narz�dziem</returns>
bool isThisToolType(ToolType tool, ToolType requestTool);

/// <summary>
/// Klasa od blok�w naszej gry
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

