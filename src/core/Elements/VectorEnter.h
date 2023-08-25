#pragma once
#include "Element.h"
class VectorEnter :
    public Element
{
    Vector2* val;
    std::string name;
    std::string floatVal = "0";
    std::string floatVal2 = "0";
    Rectangle pos1;
    Rectangle pos2;
    bool pressed = false;
    bool left=false;
    std::string stringValue(std::string s, int c);
public:
    VectorEnter(Rectangle pos, std::string name, Vector2* val);

    void updateVal(Vector2* val);

    virtual void update();

    virtual bool press();

    virtual void updatePos();

    virtual void unPress();

    virtual void draw();
};

