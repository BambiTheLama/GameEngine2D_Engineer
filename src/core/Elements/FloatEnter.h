#pragma once
#include "Element.h"
class FloatEnter :
    public Element
{
    float* val;
    std::string name;
    std::string floatVal="0";
    bool pressed=false;
public:
    FloatEnter(Rectangle pos, std::string name, float* val);

    virtual void update();

    virtual bool press();

    virtual void unPress();

    virtual void draw();
};

