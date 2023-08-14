#pragma once
#include "Element.h"
#include <string>
class CheckBox :
    public Element
{
    bool *isPress;
    std::string text;
public:
    CheckBox(Rectangle pos, std::string text, bool* isPress);

    bool press();

    void draw();
};

