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
    float zoom = 1;
    Camera2D camera;
    Vector2 cursorPos;
    Rectangle cameraPos;
    ObjectHandler* handler;
    GameObject* cameraTarget;
    std::list<UserUI*> userUI;
    static GameScene* game;
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
    std::list<GameObject*> getObjects(Rectangle pos, ObjectToGet type = ObjectToGet::getAll) { return handler->getObjects(pos, type); }
    /// <summary>
    /// Aktualizuj� pozycj� obiektu
    /// </summary>
    /// <param name="obj">Obiekt do aktualizowania pozycji</param>
    void updatePos(GameObject* obj) { handler->updatePos(obj); }
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
    /// <summary>
    /// Zwraca wszystkie bloki na mapie
    /// </summary>
    /// <returns></returns>
    Block*** getAllBlocks() { return handler->getAllBlock(); }
    /// <summary>
    /// Zwraca ile jest blok�w w wysokosci i szeroko�ci
    /// </summary>
    /// <returns></returns>
    Vector2 getBlocksSize() { return { (float)handler->getBlockW(),(float)handler->getBlockH() }; }
};

