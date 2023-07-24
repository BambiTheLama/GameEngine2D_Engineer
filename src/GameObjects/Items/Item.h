#pragma once
#include "../GameObject.h"

class Item :
    public GameObject
{
protected:
    Item(Item& obj);
public:
    Item(Rectangle pos, std::string name);

    virtual ~Item();

    virtual void update();

    virtual void draw();

    virtual void drawAt(Rectangle pos);

    virtual bool use();

    virtual void addToStack(int i){}

    virtual int getStackSize() { return 1; }

    virtual int getStackMaxSize() { return 1; }

    virtual bool isStacable() { return false; }

    ObjectType getType() { return ObjectType::Item; }

    virtual Item* clone() { return new Item(*this); }
};

