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
    std::list<GameObject*> getObjects(Rectangle pos, ObjectToGet type = ObjectToGet::getAll) { return handler->getObjects(pos, type); }
    /// <summary>
    /// Aktualizujê pozycjê obiektu
    /// </summary>
    /// <param name="obj">Obiekt do aktualizowania pozycji</param>
    void updatePos(GameObject* obj) { handler->updatePos(obj); }
    /// <summary>
    /// Zwraca pozycjê kursora na ekranie uwzglêdniej¹c w to przesuniêcie Camery oraz skalowanie jej
    /// </summary>
    /// <returns></returns>
    Vector2 getCursorPos() { return cursorPos; }
    /// <summary>
    /// Usuwa obiekty z struktury bez zwalniania z pamieci
    /// </summary>
    /// <param name="pos">pozycja z której usuwamy obiekty</param>
    void removeBlocks(Rectangle pos);
    /// <summary>
    /// Usuwa z pamieci bloki w podanej pozycji
    /// </summary>
    /// <param name="pos">Pozycja bloków do usuniecia z pamieci</param>
    void deleteBlocks(Rectangle pos);
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
    /// Zwraca wszystkie bloki na mapie
    /// </summary>
    /// <returns></returns>
    Block*** getAllBlocks() { return handler->getAllBlock(); }
    /// <summary>
    /// Zwraca ile jest bloków w wysokosci i szerokoœci
    /// </summary>
    /// <returns></returns>
    Vector2 getBlocksSize() { return { (float)handler->getBlockW(),(float)handler->getBlockH() }; }
};

