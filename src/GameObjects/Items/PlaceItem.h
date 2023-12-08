#pragma once
#include "StackItem.h"
class PlaceItem :
    public StackItem
{
    int structID;
protected:
    PlaceItem(PlaceItem& item);
public:
    PlaceItem(Rectangle pos, std::string name, int stackSize, int structID);

    PlaceItem(nlohmann::json j);

    virtual ~PlaceItem();

    virtual bool use(float deltaTime);

    virtual StackItem* clone() { return new PlaceItem(*this); }

    virtual void drawInterface();

    Vector2 getWordMousePos();
};

