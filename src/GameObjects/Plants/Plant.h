#pragma once
#include "../GameObject.h"
#include "../AddisionalTypes/AllTypes.h"
class Plant :
    public GameObject, public ItemsDrop
{
protected:
    Plant(Plant& obj);
    SpriteController* sprite=NULL;
public:
    Plant(Rectangle pos,std::string name);

    virtual ~Plant();

    virtual void update();

    virtual void draw();

    ObjectType getType() { return ObjectType::Plant; }

    virtual Plant* clone() { return new Plant(*this); }
};

