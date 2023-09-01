#pragma once
#include "Element.h"
class ItemEdytor;
class RemoveItem :
    public Element
{
    ItemEdytor* edytor;
public:
    RemoveItem(Rectangle pos, ItemEdytor* edytor);

    bool press();

    void draw();
};

