#pragma once
#include <vector>
#include <list>
#include "../../../GameObjects/GameObject.h"
#include "../../../GameObjects/AddisionalTypes/UserUI.h"
#include "../../../GameObjects/Blocks/Block.h"
#include "FourTree.h"
#define tileSize 32
enum class ObjectToGet
{
    getAll,getBlocks,getNoBlocks
};

/// <summary>
/// Klasa odpowiedzialna za trzymanie wszystkich obiekt�w w miejnym miejscu
/// </summary>
class ObjectHandler
{
    std::list<GameObject*> objects=std::list<GameObject*>();
    std::list<GameObject*> objectsToAdd = std::list<GameObject*>();
    std::list<GameObject*> objectsToDelete = std::list<GameObject*>();
    std::list<GameObject*> objectsToRemove = std::list<GameObject*>();
    FourTree* tree = NULL;
    Block*** blocks = NULL;
    Rectangle pos;
    int h, w;
public:
    ObjectHandler(Rectangle pos);
    /// <summary>
    /// Usuwa wszystkie obiekty co zosta�y w kolekcjach
    /// </summary>
    ~ObjectHandler();
    /// <summary>
    /// Czy�ci wszytkie listy i usuwa obiekty z objects i obejctsToAdd
    /// </summary>
    void clearLists();

    void start();
    /// <summary>
    /// Zwraca wszystkie obiekty
    /// </summary>
    /// <returns>Lista z obiektami</returns>
    std::list<GameObject*> getObjects();
    /// <summary>
    /// Zwraca wszystkie obiekty w podanej pozycji
    /// </summary>
    /// <param name="pos">Pozycja obiekt�w</param>
    /// <returns>Lista z obiektami</returns>
    std::list<GameObject*> getObjects(Rectangle pos, ObjectToGet type = ObjectToGet::getAll);
    /// <summary>
    /// Obiekty ju� gotowe do rysowanie posortowane w kolejno�ci od najwy�szego miejssca na mapie do najni�szego
    /// </summary>
    /// <param name="pos">Pozycja obiekt�w do rysowania</param>
    /// <returns>lista obiekt�w gotowych do rysowania</returns>
    std::list<GameObject*> getObjectsToDraw(Rectangle pos);
    /// <summary>
    /// Usuwa i dodaje nowe obiekty do kolekcji
    /// </summary>
    void update();
    /// <summary>
    /// Usuwa obiekt z kolekcji oraz czysci go z pami�ci
    /// </summary>
    /// <param name="obj">Obiekt do usuniecia</param>
    void deleteObject(GameObject* obj);
    /// <summary>
    /// Dodaje obiekt do kolekcji
    /// </summary>
    /// <param name="obj">Obiekt do dodania</param>
    void addObject(GameObject* obj);
    /// <summary>
    /// Usuwa obiekt z kolekcji 
    /// </summary>
    /// <param name="obj">Obiekt do usuni�cia</param>
    void removeObject(GameObject* obj);
    /// <summary>
    /// Aktualizuj� pozycj� obiektu
    /// </summary>
    /// <param name="obj">Obiek kt�rego pozycja ma byc zaktualizowana</param>
    void updatePos(GameObject* obj) { tree->updatePos(obj); }
    /// <summary>
    /// Rusje drzewo drzewo
    /// </summary>
    void draw() { tree->draw(); }
    /// <summary>
    /// Dodaje blok do struktury w podanej pozycji 
    /// </summary>
    /// <param name="block">Block do dodania</param>
    /// <param name="x">pozycja x w kt�rej jest blok</param>
    /// <param name="y">pozcyja y w kt�rej jest blok</param>
    /// <returns>czy uda�o si� postawi� blok</returns>
    bool addBlock(Block* block, int x, int y);
    /// <summary>
    /// Usuwa blok z pamieci w podanej pozycji
    /// </summary>
    /// <param name="x">pozycja x bloku</param>
    /// <param name="y">pozcyja y bloku</param>
    void deleteBlock(int x, int y);
    /// <summary>
    /// Usuwa blok z struktury bez usuwania z pami�ci
    /// </summary>
    /// <param name="x">pozycja x bloku</param>
    /// <param name="y">pozcyja y bloku</param>
    void removeBlock(int x, int y);
    /// <summary>
    /// Usuwa bloki w podanej pozycji
    /// </summary>
    /// <param name="x">pozcyja x</param>
    /// <param name="y">pozcyja y</param>
    /// <param name="w">ilosc elementow w osi ox</param>
    /// <param name="h">ilosc element�w w osi oy</param>
    void deleteBlocks(int x, int y, int w, int h);
    /// <summary>
    /// Zwraca lsite obiekt�w w podanej pozycji
    /// </summary>
    /// <param name="x">pozycja x</param>
    /// <param name="y">pozycja y</param>
    /// <param name="w">ilosc elementow wzgledem osi ox </param>
    /// <param name="h">ilosc elementow wzgledem osi oy </param>
    /// <returns>lista obiekt�w</returns>
    std::list<Block*> getBlocks(int x, int y, int w, int h);
    /// <summary>
    /// Zwraca jeden obiekt w podanej pozycji
    /// </summary>
    /// <param name="x">pozcyja x</param>
    /// <param name="y">pozcyja y</param>
    /// <returns>block do zwr�cenia</returns>
    Block* getBlock(int x, int y);
    /// <summary>
    /// Szeroko�� na kt�rej s� bloki
    /// </summary>
    /// <returns></returns>
    int getBlockW() { return w; }
    /// <summary>
    /// Wysoko�� na kt�rej s� bloki
    /// </summary>
    /// <returns></returns>
    int getBlockH() { return h; }
    /// <summary>
    /// Zwraca wszystkei bloki
    /// </summary>
    /// <returns></returns>
    Block*** getAllBlock() { return blocks; }
};

