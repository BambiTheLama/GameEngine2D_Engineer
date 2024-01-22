#pragma once
#include "Scene.h"
#include "../Elements/Button.h"
#include <vector>
/// <summary>
/// Klasa odpowiedziala na sceny z menu glownym
/// </summary>
class Menu :
    public Scene
{
    std::vector<Button*> buttons;
    Texture2D menuTexture;
public:
    /// <summary>
    /// Konstuktor domyslny
    /// </summary>
    Menu();
    /// <summary>
    /// Destruktor domyslny
    /// </summary>
    ~Menu();

    void start();

    void update(float deltaTime);

    void draw();
};

