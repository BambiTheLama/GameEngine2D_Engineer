#pragma once
#include "../GameObject.h"
#include "../../json.hpp"

enum class FaceSide {
    left,right,up,down
};

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
    FaceSide faceSide;
    Item(Item& obj);
    virtual void setStackSize(int s){}
public:
    Item(Rectangle pos, std::string name);

    Item(nlohmann::json j, int ID);

    virtual ~Item();

    virtual void update(float deltaTime);

    virtual void draw();

    virtual void drawAt(Rectangle pos);

    virtual bool use(float deltaTime);

    virtual void updateAfterSwap() {};

    virtual void endUsing(){}

    virtual bool addToStack(Item* i) { return false; }

    virtual void addToStack(int i) {}

    virtual void removeFromStack(int i){}

    virtual int getStackSize() { return 1; }

    virtual int getStackMaxSize() { return 1; }

    virtual bool isStacable() { return false; }

    ObjectType getType() { return ObjectType::Item; }

    virtual ItemType getItemType() { return ItemType::Normal; }

    virtual Item* clone() { return new Item(*this); }

    virtual void setFaceSide(FaceSide side) { faceSide = side; }

    void addToPos(Vector2 move) { pos.x += move.x; pos.y += move.y; }

    virtual std::string getDesctription() { return ""; }

    virtual bool canChangeItem() { return true; }

    virtual void setEq(Eq *eq){}

    virtual void setInHand(bool inHand) { }

    virtual void saveToJson(nlohmann::json j);

    friend class Recipes;
};

