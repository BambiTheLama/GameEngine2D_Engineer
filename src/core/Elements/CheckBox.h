#pragma once
#include "Element.h"
#include <string>
class CheckBox :
    public Element
{
protected:
    bool *isPress;
    std::string text;
public:
    CheckBox(Rectangle pos, std::string text, bool* isPress);

    virtual bool press();

    virtual void draw();
};

