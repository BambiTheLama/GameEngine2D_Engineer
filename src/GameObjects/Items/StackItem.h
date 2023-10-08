#pragma once
#include "Item.h"
class StackItem :
    public Item
{
    static std::string description;
protected:
    int stackSize;
    int stackMaxSize;
    SpriteController* sprite;
    StackItem(StackItem& item);
    virtual void setStackSize(int s) { stackSize = s; }
public:
    StackItem(Rectangle pos, std::string name, int stackSize);

    StackItem(nlohmann::json j);

    virtual ~StackItem();

    virtual bool use(float deltaTime);

    virtual void draw();

    virtual void drawAt(Rectangle pos);

    virtual bool addToStack(Item* i);

    virtual void addToStack(int i) { stackSize += i; }

    virtual void removeFromStack(int i) { stackSize -= i; }

    virtual int getStackSize() { return stackSize; }

    virtual int getStackMaxSize() { return stackMaxSize; }

    virtual bool isStacable() { return true; }

    virtual StackItem* clone() { return new StackItem(*this); }

    SpriteController* getSprite() { return sprite; }

    virtual std::string getDesctription();

    friend class ItemFactory;
};

