#pragma once
#include "../Item.h"
#include "../../Blocks/Block.h"
#include "../../../core/Scenes/GameScene.h"
#include "../../AddisionalTypes/AllTypes.h"

class ToolItem :
    public Item , public LinesCollider
{
    bool isUsing = false;
    bool inHand = false;
    bool leftSide = false;
    int power;
    float damage = 5;
    float invisibleFrame = 0.2;
    float useTime;
    float useTimeMax;
    float rotation = 0;
    const float rotationAngle = 280;
    Vector2 origin = { 0,0 };
    ToolType destroyType;
    SpriteController* sprite;
    static std::string description;
    Rectangle hittingObjectPos;
    Vector2 cursorPos;
    ToolItem(ToolItem& item);

public:
    ToolItem(nlohmann::json j);
    virtual ~ToolItem();
    virtual ToolItem* clone() { return new ToolItem(*this); }
    virtual void update(float deltaTime);
    virtual void update(float deltaTime, Vector2 cursorPos);
    virtual bool use(float deltaTime,Vector2 cursorPos);
    void draw();
    void drawAt(Rectangle pos);
    virtual std::string getDesctription();
    virtual bool canChangeItem() { return useTime<=0; }
    virtual ItemType getItemType() { return ItemType::Weapon; }
    virtual void onCollisionHitable(HitAble* hit);
    virtual void onCollisionDestroyAble(DestroyAble* dest);
    void setInHand(bool inHand) { this->inHand = inHand; }
    virtual void drawInterface();
    GameObject* getHittingObject(Vector2 cursor, bool isDestory = false);
    virtual void addItemToHand(GameObject* holdingObj);
    virtual void saveToJson(nlohmann::json& j);
    virtual void readFromJson(nlohmann::json& j);
    friend class ItemFactory;
};

