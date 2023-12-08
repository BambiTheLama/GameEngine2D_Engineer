#pragma once
#include <vector>
#include <list>
#include "../../../GameObjects/GameObject.h"
#include "../../../GameObjects/AddisionalTypes/UserUI.h"
#include "../../../GameObjects/Blocks/Block.h"
#include "FourTree.h"
#include "json.hpp"
#include "PerlinNoice.h"
#include "FastNoiseLite.h"
#define chunkXPerFile 3
#define chunkYPerFile 2
#define tileSize 32
enum class ObjectToGet
{
    getAll,getBlocks,getNoBlocks
};

/// <summary>
/// Klasa odpowiedzialna za trzymanie wszystkich obiektów w miejnym miejscu
/// </summary>
class ObjectHandler
{
public:
    static const int h = 18, w = 32;
private:
    int x, y;
    int chunkX;
    int chunkY;
    std::list<GameObject*> objects=std::list<GameObject*>();
    std::list<GameObject*> objectsToAdd = std::list<GameObject*>();
    std::list<GameObject*> objectsToDelete = std::list<GameObject*>();
    std::list<GameObject*> objectsToRemove = std::list<GameObject*>();
    FourTree* tree = NULL;
    Block* blocks[h][w];
public:
    ObjectHandler(int chunkX, int chunkY, nlohmann::json j);
    ObjectHandler(int chunkX, int chunkY, float seed);
    ObjectHandler(int chunkX, int chunkY);
    /// <summary>
    /// Usuwa wszystkie obiekty co zosta³y w kolekcjach
    /// </summary>
    ~ObjectHandler();
    /// <summary>
    /// Czyœci wszytkie listy i usuwa obiekty z objects i obejctsToAdd
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
    /// <param name="pos">Pozycja obiektów</param>
    /// <returns>Lista z obiektami</returns>
    std::list<GameObject*> getObjects(Rectangle pos, ObjectToGet type = ObjectToGet::getAll);
    /// <summary>
    /// Obiekty ju¿ gotowe do rysowanie posortowane w kolejnoœci od najwy¿szego miejssca na mapie do najni¿szego
    /// </summary>
    /// <param name="pos">Pozycja obiektów do rysowania</param>
    /// <returns>lista obiektów gotowych do rysowania</returns>
    std::list<GameObject*> getObjectsToDraw(Rectangle pos);
    /// <summary>
    /// Usuwa i dodaje nowe obiekty do kolekcji
    /// </summary>
    void update(float deltaTime);
    /// <summary>
    /// Dodaje obiekt do kolekcji
    /// </summary>
    /// <param name="obj">Obiekt do dodania</param>
    void addObject(GameObject* obj);
    /// <summary>
    /// Usuwa obiekt z kolekcji 
    /// </summary>
    /// <param name="obj">Obiekt do usuniêcia</param>
    void removeObject(GameObject* obj);
    /// <summary>
    /// Aktualizujê pozycjê obiektu
    /// </summary>
    /// <param name="obj">Obiek którego pozycja ma byc zaktualizowana</param>
    void updatePos(GameObject* obj);
    /// <summary>
    /// Rusje drzewo drzewo
    /// </summary>
    void draw() { tree->draw(); }
    /// <summary>
    /// Dodaje blok do struktury w podanej pozycji 
    /// </summary>
    /// <param name="block">Block do dodania</param>
    /// <returns>czy uda³o siê postawiæ blok</returns>
    bool addBlock(Block* block);
    /// <summary>
    /// Usuwa blok z pamieci w podanej pozycji
    /// </summary>
    /// <param name="x">pozycja x bloku</param>
    /// <param name="y">pozcyja y bloku</param>
    void deleteBlock(int x, int y);
    /// <summary>
    /// Usuwa blok z struktury bez usuwania z pamiêci
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
    /// <param name="h">ilosc elementów w osi oy</param>
    void deleteBlocks(int x, int y, int w, int h);
    /// <summary>
    /// Zwraca lsite obiektów w podanej pozycji
    /// </summary>
    /// <param name="x">pozycja x</param>
    /// <param name="y">pozycja y</param>
    /// <param name="w">ilosc elementow wzgledem osi ox </param>
    /// <param name="h">ilosc elementow wzgledem osi oy </param>
    /// <returns>lista obiektów</returns>
    std::list<Block*> getBlocks(int x, int y, int w, int h);
    /// <summary>
    /// Zwraca jeden obiekt w podanej pozycji
    /// </summary>
    /// <param name="x">pozcyja x</param>
    /// <param name="y">pozcyja y</param>
    /// <returns>block do zwrócenia</returns>
    Block* getBlock(int x, int y);

    void reloadBlock();

    bool isObjAtThisChunk(GameObject* obj);

    bool hasObjectAtList(GameObject* obj);

    bool isObjAtThisChunk(Rectangle pos);

    void saveGame(nlohmann::json &j);

    int getChunkX() { return chunkX; }

    int getChunkY() { return chunkY; }

    void generateForestBiom(BlockFactory* factory, Vector2 pos, float waterV, float terrainV,int x,int y);
    void generateSnowBiom(BlockFactory* factory  , Vector2 pos, float waterV, float terrainV,int x,int y);
    void generateStoneBiom(BlockFactory* factory , Vector2 pos, float waterV, float terrainV,int x,int y);
    void generateDesertBiom(BlockFactory* factory, Vector2 pos, float waterV, float terrainV,int x,int y);
};

