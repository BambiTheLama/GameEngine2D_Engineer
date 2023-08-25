#pragma once
#include "CheckBox.h"
#include <list>
class CheckBoxOpenElements :
    public CheckBox
{

    bool openElements = false;
    Element* lastPress = NULL;

    Element* up = NULL;
    Element* down = NULL;

protected:
    Rectangle componetPos;
    std::list<Element*> elements;
public:
    CheckBoxOpenElements(Rectangle pos, std::string text, bool* isPress);

    ~CheckBoxOpenElements();

    void addElement(Element* e) { elements.push_back(e); updatePos();}

    void removeLastElement() { delete elements.back(); elements.pop_back(); updatePos();}

    void updatePos();

    virtual void update();

    virtual bool press();

    virtual void unPress();

    virtual void draw();

    virtual Rectangle getPos() const { return componetPos; }

    void setElementAbrow(Element* up) { this->up = up; }

    void setElementBellow(Element* down) { this->down = down; }
};

