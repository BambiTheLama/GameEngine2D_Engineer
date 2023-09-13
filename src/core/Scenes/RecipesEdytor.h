#pragma once
#include "Scene.h"
#include "raylib.h"
#include <vector>
#include <list>
#include "../Elements/Element.h"
#include "../Elements/AddItem.h"
#include "../Elements/RemoveItem.h"
#include "../../GameObjects/Crafting/Recipes.h"

class RecipesEdytor :
    public Scene, public AdderEdytor, public RemoverEdytor
{
    Recipes* usingRecepies = NULL;
    int recepiesId=-1;
    std::vector<Recipes*> recepies;
    std::list<Element*> elements;
    Element* lastPressed = NULL;
    int firstRecepies = 0;
    Rectangle recepiesStartPos = {1200,169,64,64};
    const int recepiesElementsInRow = 4;
    const int recepiesElementsRow = 7;
    const int spacing = 10;
    Rectangle recepiesComponetPos = {80,80,64,64};
    ItemToRecipes recepy;
    int usingComponet = -1;
    const int recepiesComponetInRow = 6;
    const int elementSize = 64;
    Rectangle itemBuildingPos = {0,100,128,128};

    Rectangle finalItemBuildingPos = { 0,100,128,128 };
    int craftingStation = 0;
public:
    RecipesEdytor();

    ~RecipesEdytor();

    void loadDataFromFile();

    void saveData();

    void start();

    void draw();

    void update(float deltaTime);

    void loadNewItemRecepies(int i);

    void loadNewItemComponet(int i);

    void removeItemComponet(int i);

    Rectangle getRecepiesElementsPos(int i);

    Rectangle getRecepiesComponetPos(int i);

    bool checkPressRecepiesElements();

    bool checkPressRecepiesComponets();

    void addRecepyComponet();

    void removeItem();

    void addItem();

};

