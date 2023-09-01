#pragma once
#include "Element.h"
class Add :
    public Element
{
    int* val;
public: 
    Add(Rectangle pos,int *val);

    bool press();
    
    void draw();
};

