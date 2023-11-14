#pragma once
#include "Scene.h"
#include "Game/ObjectHandler.h"
#include "../../json.hpp"
#include "Game/PerlinNoice.h"
#include <thread>
#include <mutex>
#define Game GameScene::getGameScene()

/// <summary>
/// Klasa od Sceny gry
/// </summary>
class GameScene :
    public Scene
{
    float zoom = 1;
    Camera2D camera;
    Vector2 cursorPos;
    Rectangle cameraPos;
    std::list<ObjectHandler*> handler;
    std::list<ObjectHandler*> handlersToDelete;
    std::list<GameObject*> toDelete;
    std::list<GameObject*> allObj;
    GameObject* cameraTarget;
    std::list<UserUI*> userUI;
    static GameScene* game;
    const int renderDystance = 2;
    std::string worldName;
    std::string chunksFile;
    std::thread mapLoader;
    bool endMapLoaderWork = false;
    bool loadingMap = false;
    int chunkX;
    int chunkY;
public:
    /// <summary>
    /// Konstruktor od sceny gry
    /// </summary>
    GameScene(std::string worldName="World1");
    /// <summary>
    /// Destruktor od sceny gry
    /// </summary>
    ~GameScene();
    /// <summary>
    /// Metoda startuj�ca gry wszystkie obiekty zostan� dodane na scen�
    /// </summary>
    void start();
    /// <summary>
    /// Aktualizacja wszystkich obiekt�w
    /// </summary>
    void update(float deltaTime);
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
    /// <param name="type">Typy obiekt�w kt�re maj� zostac zwr�cone</param>
    /// <returns>Lista obiekt�w w danym obszarze</returns>
    std::list<GameObject*> getObjects(Rectangle pos, ObjectToGet type = ObjectToGet::getAll);
    /// <summary>
    /// Aktualizuj� pozycj� obiektu
    /// </summary>
    /// <param name="obj">Obiekt do aktualizowania pozycji</param>
    void updatePos(GameObject* obj);
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
    /// Usuwa z pamieci bloki w podanej pozycji
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
    /// <summary>
    /// Dodaje do listy nowy Interfejs u�ytkownika
    /// </summary>
    /// <param name="ui">Interfejs do dodania</param>
    void addUserUI(UserUI* ui) { userUI.push_back(ui); }
    /// <summary>
    /// Usuwa do listy nowy Interfejs u�ytkownika
    /// </summary>
    /// <param name="ui">Interfejs do usuni�cia</param>
    void removeUserUI(UserUI* ui) { userUI.remove(ui); }

    void deleteChunksNotCloseToTarget();

    void loadChunksCloseToTarget();

    std::list<GameObject*> getObjToDraw();

    void printfChunk(GameObject* obj);
    void loadChunk(int x, int y);
    void generateChunk(int x, int y);
    void deleteChunk(ObjectHandler* h);
    void saveChunk(ObjectHandler* h);
    std::string chunkName(int x, int y);
    void mapLoaderFun();

};

