#pragma once
#include "Scene.h"
#include "Game/ObjectHandler.h"
#include "json.hpp"
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
    std::list<ObjectHandler*> handlersToAdd;
    std::list<GameObject*> toDelete;
    std::list<GameObject*> allObj;
    GameObject* cameraTarget;
    std::list<UserUI*> userUI;
    static GameScene* game;
    const int renderDystance = 2;
    std::string worldName;
    std::string worldFile;
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
    /// Metoda startuj¹ca gry wszystkie obiekty zostan¹ dodane na scenê
    /// </summary>
    void start();
    /// <summary>
    /// Aktualizacja wszystkich obiektów
    /// </summary>
    void update(float deltaTime);
    /// <summary>
    /// Rysowanie wszystkich obiektów
    /// </summary>
    void draw();
    /// <summary>
    /// Dodaje obiekt do sceny
    /// </summary>
    /// <param name="obj">Obiekt do dodanias</param>
    void addObject(GameObject* obj);
    /// <summary>
    /// Usuwa obiekt z pamiêci oraz z kolekcji
    /// </summary>
    /// <param name="obj">Obiek do usuniêcia</param>
    void deleteObject(GameObject* obj);
    /// <summary>
    /// Usuwa obiekt z koliekcji nie usuwa samego obiektu
    /// </summary>
    /// <param name="obj">Obiekt do usuniêcia</param>
    void removeObject(GameObject* obj);
    /// <summary>
    /// Zwraca obiekty w podanym miejsu
    /// </summary>
    /// <param name="pos">Pozycja z której interesuj¹ nas obiekty</param>
    /// <param name="type">Typy obiektów które maj¹ zostac zwrócone</param>
    /// <returns>Lista obiektów w danym obszarze</returns>
    std::list<GameObject*> getObjects(Rectangle pos, ObjectToGet type = ObjectToGet::getAll);
    /// <summary>
    /// Aktualizujê pozycjê obiektu
    /// </summary>
    /// <param name="obj">Obiekt do aktualizowania pozycji</param>
    void updatePos(GameObject* obj);
    /// <summary>
    /// Zwraca pozycjê kursora na ekranie uwzglêdniej¹c w to przesuniêcie Camery oraz skalowanie jej
    /// </summary>
    /// <returns></returns>
    Vector2 getCursorPos() { return cursorPos; }
    /// <summary>
    /// Usuwa obiekty z struktury bez zwalniania z pamieci
    /// </summary>
    /// <param name="pos">pozycja z której usuwamy obiekty</param>
    void removeBlock(Rectangle pos);
    /// <summary>
    /// Usuwa z pamieci bloki w podanej pozycji
    /// </summary>
    /// <param name="pos">Pozycja bloków do usuniecia z pamieci</param>
    void deleteBlock(Rectangle pos);
    /// <summary>
    /// Dodaje obiekt
    /// </summary>
    /// <param name="block">blok który musi dodaæ</param>
    /// <returns>czy uda³o siê oddac blok</returns>
    bool addBlock(Block* block);
    /// <summary>
    /// Zwraca blok w danej pozycji
    /// </summary>
    /// <param name="pos">pozycja bloku</param>
    /// <returns>blok który chcieliœmy</returns>
    Block* getBlock(Rectangle pos);
    /// <summary>
    /// Zwraca liste obiektów bloków
    /// </summary>
    /// <param name="pos">pozycja z której ma zwróciæ bloki</param>
    /// <returns>lista bloków</returns>
    std::list<Block*> getBlocks(Rectangle pos);
    /// <summary>
    /// Zwraca scenê gry
    /// </summary>
    /// <returns>scena gry</returns>
    static GameScene* getGameScene() { return game; }
    /// <summary>
    /// Dodaje do listy nowy Interfejs u¿ytkownika
    /// </summary>
    /// <param name="ui">Interfejs do dodania</param>
    void addUserUI(UserUI* ui) { userUI.push_back(ui); }
    /// <summary>
    /// Usuwa do listy nowy Interfejs u¿ytkownika
    /// </summary>
    /// <param name="ui">Interfejs do usuniêcia</param>
    void removeUserUI(UserUI* ui) { userUI.remove(ui); }
    /// <summary>
    /// Usuwa wszystkie fragmety mapy ktore sa dalej od celu kamery
    /// </summary>
    void deleteChunksNotCloseToTarget();
    /// <summary>
    /// Wczytuje fragmety mapy bliskie obiektu na ktorym jest skupiona kamera
    /// </summary>
    void loadChunksCloseToTarget();
    /// <summary>
    /// Wczytuje odpowiedni fragmet mapy 
    /// </summary>
    /// <param name="x">Pozycja na osi OX kawalka mapy</param>
    /// <param name="y">Pozycja na osi OY kawalka mapy</param>
    void loadChunk(int x, int y);
    /// <summary>
    /// Generuje odpowiedni fragment
    /// </summary>
    /// <param name="x">Pozycja na osi OX kawalka mapy</param>
    /// <param name="y">Pozycja na osi OY kawalka mapy</param>
    void generateChunk(int x, int y);
    /// <summary>
    /// Dodaje do listy fragmentow mapy do usuniecia
    /// </summary>
    /// <param name="h">Obiekt odpowiedni za fragment mapy</param>
    void deleteChunk(ObjectHandler* h);
    /// <summary>
    /// Zapisuje fragment mapy
    /// </summary>
    /// <param name="h">Obiekt odpowiedni za fragment mapy</param>
    void saveChunk(ObjectHandler* h);
    /// <summary>
    /// Zwraca nazwe ktora odpowieda za dany fragment mapy
    /// </summary>
    /// <param name="x">Pozycja na osi OX kawalka mapy</param>
    /// <param name="y">Pozycja na osi OY kawalka mapy</param>
    /// <returns></returns>
    std::string chunkName(int x, int y);
    /// <summary>
    /// Funkcja odpowiedzialna za prace osobnego watku
    /// </summary>
    void mapLoaderFun();
    /// <summary>
    /// Konwertuje punk z pozycji w swiecie na pozycje na ekranie
    /// </summary>
    /// <param name="pos">Punkt do konwersji</param>
    /// <returns>Punkt po konwersji</returns>
    Vector2 worldToScreanPos(Vector2 pos) { return GetWorldToScreen2D(pos, camera); }
    /// <summary>
    /// Zwraca z jakim mnoznikiem odalenia aktualnie pracuje kamera
    /// </summary>
    /// <returns></returns>
    float getZoom() { return camera.zoom; }
    std::string getWorldName() { return worldName; }
    
};

