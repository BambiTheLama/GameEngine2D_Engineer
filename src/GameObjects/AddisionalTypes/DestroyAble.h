#pragma once
#include "raylib.h"
/// <summary>
/// Enum odpowiadajacy �e to jakie narz�dzie mo�e zniszczy� jaki blok
/// </summary>
enum class ToolType {

    All = 0,                //Mo�e wykopa� wszystko
    Axe = 2,                //Wszystko to co mo�e sikiera
    Shovel = 3,             //Wszystko to co mo�e �opata
    Pickaxe = 5,            //Wszystko to co mo�e kilof
    AxeShovel = 6,            //Wszystko to co mo�e sikiera i �opata
    AxePickaxe = 10,          //Wszystko to co mo�e sikiera i kilof
    ShovelPickaxe = 15,       //Wszystko to co mo�e �opata i kilof
    AxeShovelPickaxe = 30,   //Wszystko to co mo�e sikiera �opata i kilof
    NON = 1111111111              //Zadne narz�dzie nie mo�e wykopa�
};

bool isThisToolType(ToolType tool, ToolType requestTool);

class DestroyAble
{
protected:
    ToolType itemToolRequest;
    int power,hp;
    DestroyAble(DestroyAble& destroyable);
public:
    DestroyAble(ToolType toolToDestroy,int hp=1,int power=0);

    virtual void damageObject(int power, ToolType type);

    virtual Rectangle getCollisionPos() = 0;

    virtual bool isToolGoBack() { return false; }
};

