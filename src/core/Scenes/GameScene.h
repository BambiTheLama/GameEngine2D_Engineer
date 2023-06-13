#pragma once
#include "Scene.h"
#include "Game/ObjectHandler.h"

#define Game GameScene::getGameScene()

/// <summary>
/// Klasa od Sceny gry
/// </summary>
class GameScene :
    public Scene
{
    static GameScene* game;
    ObjectHandler *heandler;
    Vector2 cursorPos;
    
public:
    /// <summary>
    /// Konstruktor od sceny gry
    /// </summary>
    GameScene();
    /// <summary>
    /// Destruktor od sceny gry
    /// </summary>
    ~GameScene();
    /// <summary>
    /// Aktualizacja wszystkich obiekt�w
    /// </summary>
    void update();
    /// <summary>
    /// Rysowanie wszystkich obiekt�w
    /// </summary>
    void draw();
    /// <summary>
    /// Dodaje obiekt do sceny
    /// </summary>
    /// <param name="obj">Obiekt do dodanias</param>
    void addObject(GameObject* obj);
    /// <summary>
    /// Usuwa obiekt z pami�ci oraz z kolekcji
    /// </summary>
    /// <param name="obj">Obiek do usuni�cia</param>
    void deleteObject(GameObject* obj);
    /// <summary>
    /// Usuwa obiekt z koliekcji nie usuwa samego obiektu
    /// </summary>
    /// <param name="obj">Obiekt do usuni�cia</param>
    void removeObject(GameObject* obj);
    /// <summary>
    /// Zwraca obiekty w podanym miejsu
    /// </summary>
    /// <param name="pos">Pozycja z kt�rej interesuj� nas obiekty</param>
    /// <returns>Lista obiekt�w w danym obszarze</returns>
    std::list<GameObject*> getObjects(Rectangle pos) { return heandler->getObject(pos); }
    /// <summary>
    /// Aktualizuj� pozycj� obiektu
    /// </summary>
    /// <param name="obj">Obiekt do aktualizowania pozycji</param>
    void updatePos(GameObject* obj) { heandler->updatePos(obj); }
    /// <summary>
    /// Zwraca pozycj� kursora na ekranie uwzgl�dniej�c w to przesuni�cie Camery oraz skalowanie jej
    /// </summary>
    /// <returns></returns>
    Vector2 getCursorPos() { return cursorPos; }
    /// <summary>
    /// Usuwa obiekty z struktury bez zwalniania z pamieci
    /// </summary>
    /// <param name="pos">pozycja z kt�rej usuwamy obiekty</param>
    void removeBlocks(Rectangle pos);
    /// <summary>
    /// Usuwa z pamieci elementy podane 
    /// </summary>
    /// <param name="pos">Pozycja blok�w do usuniecia z pamieci</param>
    void deleteBlocks(Rectangle pos);
    /// <summary>
    /// Dodaje obiekt
    /// </summary>
    /// <param name="block">blok kt�ry musi doda�</param>
    /// <returns>czy uda�o si� oddac blok</returns>
    bool addBlock(Block* block);
    /// <summary>
    /// Zwraca blok w danej pozycji
    /// </summary>
    /// <param name="pos">pozycja bloku</param>
    /// <returns>blok kt�ry chcieli�my</returns>
    Block* getBlock(Rectangle pos);
    /// <summary>
    /// Zwraca liste obiekt�w blok�w
    /// </summary>
    /// <param name="pos">pozycja z kt�rej ma zwr�ci� bloki</param>
    /// <returns>lista blok�w</returns>
    std::list<Block*> getBlocks(Rectangle pos);
    /// <summary>
    /// Zwraca scen� gry
    /// </summary>
    /// <returns>scena gry</returns>
    static GameScene* getGameScene() { return game; }
};

