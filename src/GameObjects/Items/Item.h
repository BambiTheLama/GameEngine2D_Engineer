#pragma once
#include "../GameObject.h"
#include "json.hpp"

enum class ItemType {
    Normal,
    Weapon,
    Ammo
};
class Eq;
class Item :
    public GameObject
{

protected:
    Item(Item& obj);
    std::string itemName;
    GameObject* holdingObj;
    virtual void setStackSize(int s){}

public:
    Item(Rectangle pos, std::string name);

    Item(nlohmann::json j);

    virtual ~Item();

    virtual void update(float deltaTime);

    virtual void update(float deltaTime,Vector2 curosrPos){}

    virtual void draw();

    virtual void drawAt(Rectangle pos);

    virtual void drawInterface(){}

    virtual bool use(float deltaTime, Vector2 curosrPos);

    virtual void updateAfterSwap() {};

    virtual void endUsing(){}

    virtual bool addToStack(Item* i) { return false; }

    virtual void addItemToHand(GameObject* holdingObj) { this->holdingObj = holdingObj; setInHand(true); }

    virtual int addToStack(int i) { return i; }

    virtual void removeFromStack(int i){}

    virtual int getStackSize() { return 1; }

    virtual int getStackMaxSize() { return 1; }

    virtual bool isStacable() { return false; }

    ObjectType getType() { return ObjectType::Item; }

    virtual ItemType getItemType() { return ItemType::Normal; }

    virtual Item* clone() { return new Item(*this); }

    void addToPos(Vector2 move) { pos.x += move.x; pos.y += move.y; }

    virtual std::string getDesctription() { return ""; }

    virtual bool canChangeItem() { return true; }

    virtual void setEq(Eq *eq){}

    virtual void setInHand(bool inHand) { }

    virtual void saveToJson(nlohmann::json &j);

    virtual void drawDescription(int x, int y);

    virtual Vector2 getItemDescriptionSize();

    virtual void loadLangue(nlohmann::json j);

    virtual std::string getName() { return itemName; }

    virtual bool destoryAfterRenderClear() { return false; }

    friend class Recipes;
};

