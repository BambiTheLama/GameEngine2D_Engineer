#pragma once
#include "Element.h"

class RemoverEdytor {
public:
    virtual void removeItem() = 0;
};
class RemoveItem :
    public Element
{
    RemoverEdytor* edytor;
public:
    RemoveItem(Rectangle pos, RemoverEdytor* edytor);

    bool press();

    void draw();
};

