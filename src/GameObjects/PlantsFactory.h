#pragma once
#include "Factory.h"
#include "Plants/Plant.h"

#define Plants PlantsFactory::getFactory()

class PlantsFactory :
    public Factory
{
    static PlantsFactory* plantFactory;
    std::vector<Plant*> objects;
    PlantsFactory();
    ~PlantsFactory();
public:

    static PlantsFactory* getFactory();

    void clearFactory();

    Plant* getObject(int ID);
};

