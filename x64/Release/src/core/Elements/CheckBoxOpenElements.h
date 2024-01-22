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
    bool hide;
protected:
    Rectangle componetPos;
    std::list<Element*> elements;
public:
    CheckBoxOpenElements(Rectangle pos, std::string text, bool* isPress,bool hide=true);

    ~CheckBoxOpenElements();

    void addElement(Element* e) { elements.push_back(e); updatePos();}

    void removeLastElement() { delete elements.back(); elements.pop_back(); updatePos();}

    void updatePos();

    virtual void update();

    virtual bool press();

    virtual void unPress();

    virtual void draw();

    virtual Rectangle getPos() const 
    { 
        if (*isPress || !hide)
            return componetPos;
        else
            return { componetPos.x,componetPos.y,componetPos.width,0 };
    }

    void setElementAbrow(Element* up) { this->up = up; }

    void setElementBellow(Element* down) { this->down = down; }

    virtual void reloadData();
};

