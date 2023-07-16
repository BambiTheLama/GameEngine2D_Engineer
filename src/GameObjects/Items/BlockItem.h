#pragma once
#include "Item.h"
class BlockItem :
    public Item
{
    int stackSize;
    int stackMaxSize;
    SpriteController* sprite;
    BlockItem(BlockItem& item);
public:
    BlockItem(Rectangle pos, std::string name, int stackSize);

    virtual ~BlockItem();

    virtual bool use();

    virtual void draw();

    virtual void drawAt(Rectangle pos);

    virtual void addToStack(int i) { stackSize += i; }

    virtual int getStackSize() { return stackSize; }

    virtual int getStackMaxSize() { return stackMaxSize; }

    virtual bool isStacable() { return true; }

    virtual BlockItem* clone() { return new BlockItem(*this); }
};

