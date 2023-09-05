#pragma once
#include "Element.h"
class ItemEdytor;
class Add :
    public Element
{
    int* val;
    int addValue;
public: 
    Add(Rectangle pos,int *val, int addValue=1);

    bool press();
    
    void draw();
};

