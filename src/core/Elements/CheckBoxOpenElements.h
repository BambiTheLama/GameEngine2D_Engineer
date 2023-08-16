#pragma once
#include "CheckBox.h"
#include <list>
class CheckBoxOpenElements :
    public CheckBox
{
    std::list<Element*> elements;
    bool openElements = false;
    Element* lastPress = NULL;
    Rectangle componetPos;
    Element* up = NULL;
    Element* down = NULL;
public:
    CheckBoxOpenElements(Rectangle pos, std::string text, bool* isPress);

    ~CheckBoxOpenElements();

    void addElement(Element* e) { elements.push_back(e); }

    void updatePos();

    virtual void update();

    virtual bool press();

    virtual void unPress();

    virtual void draw();

    virtual Rectangle getPos() const { return componetPos; }

    void setElementAbrow(Element* up) { this->up = up; }

    void setElementBellow(Element* down) { this->down = down; }
};

