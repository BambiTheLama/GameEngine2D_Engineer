#pragma once
#include "Element.h"

class Remove :
    public Element
{
    int* val;
    int removeVal;
public:
    Remove(Rectangle pos, int* val, int removeVal=1);

    bool press();

    void draw();
};

