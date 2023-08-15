#pragma once
#include "Element.h"
class FloatEnter :
    public Element
{
    float& val;
public:
    FloatEnter(Rectangle pos, std::string name, float& val);


};

