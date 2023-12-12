#pragma once
#include "raylib.h"
#include <string>
#include "json.hpp"
/// <summary>
/// Enum odpowiadajacy ¿e to jakie narzêdzie mo¿e zniszczyæ jaki blok
/// </summary>
enum class ToolType {
    NON = 0,            //Zadne narzêdzie nie mo¿e wykopaæ
    Axe,                //Wszystko to co mo¿e sikiera
    Shovel,             //Wszystko to co mo¿e ³opata
    Pickaxe,            //Wszystko to co mo¿e kilof
    AxeShovel,              //Wszystko to co mo¿e sikiera i ³opata
    AxePickaxe,             //Wszystko to co mo¿e sikiera i kilof
    ShovelPickaxe,          //Wszystko to co mo¿e ³opata i kilof
    AxeShovelPickaxe,       //Wszystko to co mo¿e sikiera ³opata i kilof
    All,                    //Mo¿e wykopaæ wszystko


    EnumSize
};
std::string toolTypeDescription();

bool isThisToolType(ToolType tool, ToolType requestTool);
enum class ObjectType;
class DestroyAble
{
protected:
    int power, hp;
    ToolType itemToolRequest;
    DestroyAble(DestroyAble& destroyable);
    void copyDataFrom(DestroyAble& dest);
public:
    DestroyAble(ToolType toolToDestroy,int hp=1,int power=0);

    DestroyAble(ObjectType type, int ID);

    virtual void damageObject(int power, ToolType type);

    bool isDestoryAbleBy(ToolType type);

    virtual bool isToolGoBack() { return false; }

    int getHp() { return hp; }
};

