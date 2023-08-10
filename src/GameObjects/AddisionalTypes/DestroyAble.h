#pragma once
#include "raylib.h"
/// <summary>
/// Enum odpowiadajacy ¿e to jakie narzêdzie mo¿e zniszczyæ jaki blok
/// </summary>
enum class ToolType {

    All = 0,                //Mo¿e wykopaæ wszystko
    Axe = 2,                //Wszystko to co mo¿e sikiera
    Shovel = 3,             //Wszystko to co mo¿e ³opata
    Pickaxe = 5,            //Wszystko to co mo¿e kilof
    AxeShovel = 6,            //Wszystko to co mo¿e sikiera i ³opata
    AxePickaxe = 10,          //Wszystko to co mo¿e sikiera i kilof
    ShovelPickaxe = 15,       //Wszystko to co mo¿e ³opata i kilof
    AxeShovelPickaxe = 30,   //Wszystko to co mo¿e sikiera ³opata i kilof
    NON = 1111111111              //Zadne narzêdzie nie mo¿e wykopaæ
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

