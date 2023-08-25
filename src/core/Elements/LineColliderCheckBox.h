#pragma once
#include "CheckBoxOpenElements.h"
#include "../Scenes/ItemEdytorStruct/ItemProperty.h"
class LineColliderCheckBox :
    public CheckBoxOpenElements
{
    ItemProperty* prop;
    int last;
public:
    LineColliderCheckBox(Rectangle pos, std::string text, bool* isPress, ItemProperty* prop);

    void updateVectorPoints();

    virtual void update();

    virtual bool press();

    virtual void draw();
};

