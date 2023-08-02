#pragma once
#include "../GameObject.h"

enum class FaceSide {
    left,right,up,down
};

class Item :
    public GameObject
{
protected:
    FaceSide faceSide;
    Item(Item& obj);
    virtual void setStackSize(int s){}
public:
    Item(Rectangle pos, std::string name);

    virtual ~Item();

    virtual void update();

    virtual void draw();

    virtual void drawAt(Rectangle pos);

    virtual bool use();

    virtual bool addToStack(Item* i) { return false; }

    virtual void addToStack(int i) {}

    virtual void removeFromStack(int i){}

    virtual int getStackSize() { return 1; }

    virtual int getStackMaxSize() { return 1; }

    virtual bool isStacable() { return false; }

    ObjectType getType() { return ObjectType::Item; }

    virtual Item* clone() { return new Item(*this); }

    void setFaceSide(FaceSide side) { faceSide = side; }

    void addToPos(Vector2 move) { pos.x += move.x; pos.y += move.y; }

    virtual std::string getDesctription() { return ""; }

    friend class Recipes;
};

