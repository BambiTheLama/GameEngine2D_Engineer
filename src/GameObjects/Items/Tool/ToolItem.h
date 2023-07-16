#pragma once
#include "../Item.h"

class ToolItem :
    public Item
{
    SpriteController* sprite;
    ToolItem(ToolItem& item);
public:
    ToolItem(Rectangle pos, std::string name);
    virtual ~ToolItem();
    virtual ToolItem* clone() { return new ToolItem(*this); }
    void draw();
    void drawAt(Rectangle pos);
};

