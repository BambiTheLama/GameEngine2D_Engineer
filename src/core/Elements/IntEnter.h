#pragma once
#include "Element.h"
class IntEnter :
    public Element
{
protected:
    int* val;
    std::string name;
    bool pressed = false;
public:
    IntEnter(Rectangle pos, std::string name, int* val);

    virtual void update();

    virtual bool press();

    virtual void unPress();

    virtual void draw();
};

