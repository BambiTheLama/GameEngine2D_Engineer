#pragma once
#include "Scene.h"
#include "raylib.h"
#include <vector>
#include <list>
#include "../Elements/Element.h"
#include "../Elements/AddItem.h"
#include "../Elements/RemoveItem.h"
#include "../../GameObjects/Crafting/Recipes.h"
/// <summary>
/// Kalsa odpowiedzialna za scene z tworzeniem nowych receptur w grze
/// </summary>
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
    /// <summary>
    /// Konstuktor domyslny
    /// </summary>
    RecipesEdytor();
    /// <summary>
    /// Destruktor domyslny
    /// </summary>
    ~RecipesEdytor();
    /// <summary>
    /// Wczytywanie danych z pliku
    /// </summary>
    void loadDataFromFile();
    /// <summary>
    /// Zapisywanie danych do pliku
    /// </summary>
    void saveData();

    void start();

    void draw();

    void update(float deltaTime);
    /// <summary>
    /// Wczytuje nowa recepture o podanym id
    /// </summary>
    /// <param name="i"></param>
    void loadNewItemRecepies(int i);
    /// <summary>
    /// Wczytuje nowa konponet receptury
    /// </summary>
    /// <param name="i"></param>
    void loadNewItemComponet(int i);
    /// <summary>
    /// Usuwa komponet receptury
    /// </summary>
    /// <param name="i"></param>
    void removeItemComponet(int i);
    /// <summary>
    /// Zwraca pozycje z listy bocznej o podanym ID
    /// </summary>
    /// <param name="i"></param>
    /// <returns></returns>
    Rectangle getRecepiesElementsPos(int i);
    /// <summary>
    /// Zwraca pozycja komponetow receptury o podanym ID
    /// </summary>
    /// <param name="i"></param>
    /// <returns></returns>
    Rectangle getRecepiesComponetPos(int i);
    /// <summary>
    /// Sprawdza czy zostalo klikniete w elementy receptur
    /// </summary>
    /// <returns></returns>
    bool checkPressRecepiesElements();
    /// <summary>
    /// Sprawdza czy zostalo klikniete w komponety receptur
    /// </summary>
    /// <returns></returns>
    bool checkPressRecepiesComponets();
    /// <summary>
    /// Dodaje nowy komponet do receptury
    /// </summary>
    void addRecepyComponet();
    /// <summary>
    /// Usuwa item z receptur
    /// </summary>
    void removeItem();
    /// <summary>
    /// Dodaje item do receptur
    /// </summary>
    void addItem();

};

