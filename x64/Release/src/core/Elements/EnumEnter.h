#pragma once
#include "IntEnter.h"
class EnumEnter :
    public IntEnter
{
    std::string description;
    int size = 0;
public:
    EnumEnter(Rectangle pos, std::string name, int* val,int size,std::string description);

    virtual void update();

    virtual bool press();

    virtual void draw();
};

