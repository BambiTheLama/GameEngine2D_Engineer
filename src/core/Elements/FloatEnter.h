#pragma once
#include "Element.h"


std::string floatToString(float f);
std::string stringValue(std::string s, int c);

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

