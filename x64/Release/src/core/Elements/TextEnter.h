#pragma once
#include "Element.h"
#include <string>
class TextEnter :
    public Element
{

    std::string *text;
    std::string name;
    bool pressed = false;
    bool isOn = false;
public:
    TextEnter(Rectangle pos,std::string name,std::string *text);

    void update();

    bool press();

    void unPress();

    void draw();

};

