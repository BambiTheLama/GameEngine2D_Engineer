#pragma once
#include "../Item.h"
#include "../../Blocks/Block.h"
#include "../../../core/Scenes/GameScene.h"
class ToolItem :
    public Item , public LinesCollider
{
    bool isUsing = false;
    bool inHand = false;
    int power;
    int damage = 5;
    float invisibleFrame = 0.2;
    float useTime;
    float useTimeMax;
    float rotation = 0;
    Vector2 origin = { 0,0 };
    ToolType destroyType;
    SpriteController* sprite;

    ToolItem(ToolItem& item);
public:
    ToolItem(Rectangle pos, std::string name,ToolType destroyType=ToolType::NON,int power=0);
    virtual ~ToolItem();
    virtual ToolItem* clone() { return new ToolItem(*this); }
    void update(float deltaTime);
    bool use(float deltaTime);
    void draw();
    void drawAt(Rectangle pos);
    virtual void setFaceSide(FaceSide side) { if(useTime<=0)faceSide = side; }
    virtual std::string getDesctription();
    void setStartPoints(Vector2 startPoints[4]);
    virtual bool canChangeItem() { return useTime<=0; }
    virtual ItemType getItemType() { return ItemType::Weapon; }
    virtual void onCollisionHitable(HitAble* hit);
    virtual void onCollisionDestroyAble(DestroyAble* dest);
    void setInHand(bool inHand) { this->inHand = inHand; }
};

