#pragma once
#include <vector>
#include <list>
#include "../../../GameObjects/GameObject.h"
#include "../../../GameObjects/AddisionalTypes/UserUI.h"
#include "../../../GameObjects/Blocks/Block.h"
#include "FourTree.h"
#include "json.hpp"
#include "FastNoiseLite.h"
#define chunkXPerFile 1
#define chunkYPerFile 1
#define tileSize 32
/// <summary>
/// Typ obiektow jakie chcemy dostac
/// </summary>
enum class ObjectToGet
{
    getAll=0,       ///Zwraca wszystkie obiekty 
    getBlocks,      ///Zwraca tylko bloki z tablicy
    getNoBlocks     ///Zwraca obiekty z list ktore nie sa w tablicy
};

/// <summary>
/// Klasa odpowiedzialna za trzymanie wszystkich obiektów pewnego kawalka terenu w jednym miejscu
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
    /// <summary>
    /// Konstuktor ktory wczytuje dane z pliku json
    /// </summary>
    /// <param name="chunkX">Pozycja kawalka mapy wedlug osi OX</param>
    /// <param name="chunkY">Pozycja kawalka mapy wedlug osi OY</param>
    /// <param name="j">plik json</param>
    ObjectHandler(int chunkX, int chunkY, nlohmann::json j);
    /// <summary>
    /// Konstuktor ktory generuje teren na podstawie nasiona oraz pozycji
    /// </summary>
    /// <param name="chunkX">Pozycja kawalka mapy wedlug osi OX</param>
    /// <param name="chunkY">Pozycja kawalka mapy wedlug osi OY</param>
    /// <param name="seed">nasiono z ktorego powstaje teren</param>
    ObjectHandler(int chunkX, int chunkY, float seed=0);
    /// <summary>
    /// Usuwa wszystkie obiekty co zosta³y w kolekcjach
    /// </summary>
    ~ObjectHandler();
    /// <summary>
    /// Czyœci wszytkie listy i usuwa obiekty z objects i obejctsToAdd
    /// </summary>
    void clearLists();
    /// <summary>
    /// Metoda majaca na celu wystartowanie obiektow
    /// </summary>
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
    /// Metoda rysujaca wszyskie bloki po ktorych poruszaja sie obiekty na scenie
    /// </summary>
    void drawBlocks();
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
    /// <summary>
    /// Metoda ktora sprawia ze wszystkie bloki ustalaja swoja aktualna texture na nowo
    /// </summary>
    void reloadBlock();
    /// <summary>
    /// Srpawdza czy dany obiekt zalicza sie do tego kawalka terenu
    /// </summary>
    /// <param name="obj">Obiekt brany pod uwage</param>
    /// <returns></returns>
    bool isObjAtThisChunk(GameObject* obj);
    /// <summary>
    /// Sprawdza czy obiekt jest w liscie
    /// </summary>
    /// <param name="obj">Obiekt brany pod uwage</param>
    /// <returns></returns>
    bool hasObjectAtList(GameObject* obj);
    /// <summary>
    /// Srpawdza czy na tej pozycji bedzie sie obiekt zaliczal do tego kawalka terenu
    /// </summary>
    /// <param name="pos"></param>
    /// <returns></returns>
    bool isObjAtThisChunk(Rectangle pos);
    /// <summary>
    /// Zapisywanie kawalku mapy do liku typu json
    /// </summary>
    /// <param name="j"></param>
    void saveGame(nlohmann::json &j);
    /// <summary>
    /// Zwraca pozycje na osi OX kawalka terenu
    /// </summary>
    /// <returns></returns>
    int getChunkX() { return chunkX; }
    /// <summary>
    /// Zwraca pozycje na osi OY kawalka terenu
    /// </summary>
    /// <returns></returns>
    int getChunkY() { return chunkY; }
    /// <summary>
    /// Generuje kawalek terenu typu las
    /// </summary>
    /// <param name="factory">Fabryka blokow</param>
    /// <param name="pos">Pozycja na ktorej generujemy teren</param>
    /// <param name="waterV">Wartosc szumu determinujace wode i lady</param>
    /// <param name="terrainV">Wartosc szumu determinujaca obiekty typu "Structur"</param>
    /// <param name="x">X w tabliky blokow</param>
    /// <param name="y">Y w tablicy blokow</param>
    void generateForestBiom(BlockFactory* factory, Vector2 pos, float waterV, float terrainV,int x,int y);
    /// <summary>
    /// Generuje kawalek terenu typu zimowy z sniegiem
    /// </summary>
    /// <param name="factory">Fabryka blokow</param>
    /// <param name="pos">Pozycja na ktorej generujemy teren</param>
    /// <param name="waterV">Wartosc szumu determinujace wode i lady</param>
    /// <param name="terrainV">Wartosc szumu determinujaca obiekty typu "Structur"</param>
    /// <param name="x">X w tabliky blokow</param>
    /// <param name="y">Y w tablicy blokow</param>
    void generateSnowBiom(BlockFactory* factory  , Vector2 pos, float waterV, float terrainV,int x,int y);
    /// <summary>
    /// Generuje kawalek terenu typu kamienny 
    /// </summary>
    /// <param name="factory">Fabryka blokow</param>
    /// <param name="pos">Pozycja na ktorej generujemy teren</param>
    /// <param name="waterV">Wartosc szumu determinujace wode i lady</param>
    /// <param name="terrainV">Wartosc szumu determinujaca obiekty typu "Structur"</param>
    /// <param name="x">X w tabliky blokow</param>
    /// <param name="y">Y w tablicy blokow</param>
    void generateStoneBiom(BlockFactory* factory , Vector2 pos, float waterV, float terrainV,int x,int y);
    /// <summary>
    /// Generuje kawalek terenu typu pustynia
    /// </summary>
    /// <param name="factory">Fabryka blokow</param>
    /// <param name="pos">Pozycja na ktorej generujemy teren</param>
    /// <param name="waterV">Wartosc szumu determinujace wode i lady</param>
    /// <param name="terrainV">Wartosc szumu determinujaca obiekty typu "Structur"</param>
    /// <param name="x">X w tabliky blokow</param>
    /// <param name="y">Y w tablicy blokow</param>
    void generateDesertBiom(BlockFactory* factory, Vector2 pos, float waterV, float terrainV,int x,int y);
};

