#pragma once
#include "Element.h"
class ItemEdytor;
class AddItem :
    public Element
{
    ItemEdytor* edytor;
public:
    AddItem(Rectangle pos, ItemEdytor* edytor);

    bool press();

    void draw();
};

