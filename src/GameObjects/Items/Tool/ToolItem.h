#pragma once
#include "../Item.h"
#include "../../Blocks/Block.h"
#include "../../../core/Scenes/GameScene.h"
class ToolItem :
    public Item , public LinesCollider
{
    SpriteController* sprite;
    ToolType destroyType;
    int useTime;
    int useTimeMax;
    int power;
    int damage = 5;
    Vector2 origin= { 0,0 };
    float rotation=0;
    bool isUsing = false;
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
    void setStartPoints(Vector2 startPoints[4]);
    virtual bool canChangeItem() { return useTime<=0; }
    virtual ItemType getItemType() { return ItemType::Weapon; }
    virtual void onCollisionHitable(HitAble* hit);
    virtual void onCollisionDestroyAble(DestroyAble* dest);
};

