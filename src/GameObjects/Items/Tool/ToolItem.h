#pragma once
#include "../Item.h"
#include "../../Blocks/Block.h"
#include "../../../core/Scenes/GameScene.h"
class ToolItem :
    public Item
{
    SpriteController* sprite;
    ToolType destroyType;
    int useTime;
    int useTimeMax;
    int power;
    ToolItem(ToolItem& item);
public:
    ToolItem(Rectangle pos, std::string name,ToolType destroyType,int power);
    virtual ~ToolItem();
    virtual ToolItem* clone() { return new ToolItem(*this); }
    void update();
    bool use();
    void draw();
    void drawAt(Rectangle pos);
    virtual std::string getDesctription();
};

