#pragma once
#include "../Item.h"
#include "../../Blocks/Block.h"
#include "../../../core/Scenes/GameScene.h"
class ToolItem :
    public Item
{
    SpriteController* sprite;
    ToolType destroyType;
    int useTime;
    int useTimeMax;
    int power;
    int damage = 5;
    Vector2 origion= { 0,pos.width };
    float rotation=0;
    Vector2 points[4];
    ToolItem(ToolItem& item);
public:
    ToolItem(Rectangle pos, std::string name,ToolType destroyType=ToolType::NON,int power=0);
    virtual ~ToolItem();
    virtual ToolItem* clone() { return new ToolItem(*this); }
    void update();
    bool use();
    void draw();
    void drawAt(Rectangle pos);
    virtual void setFaceSide(FaceSide side) { if(useTime<=0)faceSide = side; }
    virtual std::string getDesctription();
};

