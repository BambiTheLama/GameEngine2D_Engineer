#pragma once
#include "Element.h"
class Remove :
    public Element
{
    int* val;
public:
    Remove(Rectangle pos, int* val);

    bool press();

    void draw();
};

