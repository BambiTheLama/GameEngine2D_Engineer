#pragma once
#include "Element.h"

class AdderEdytor {
public:
    virtual void addItem() = 0;
};

class AddItem :
    public Element
{
    AdderEdytor* edytor;
public:
    AddItem(Rectangle pos, AdderEdytor* edytor);

    bool press();

    void draw();
};

