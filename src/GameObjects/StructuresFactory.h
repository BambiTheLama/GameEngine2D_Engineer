#pragma once
#include "Factory.h"
#include "Structures/Structure.h"

#define Structures StructuresFactory::getFactory()

class StructuresFactory :
    public Factory
{
    static StructuresFactory* structuresFactory;
    std::vector<GameObject*> objects;
    StructuresFactory();
    ~StructuresFactory();
public:

    static StructuresFactory* getFactory();

    void clearFactory();

    GameObject* getObject(int ID);
};

