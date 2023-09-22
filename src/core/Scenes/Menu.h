#pragma once
#include "Scene.h"
#include "../Elements/Button.h"
#include <vector>
class Menu :
    public Scene
{
    std::vector<Button*> buttons;
public:
    Menu();

    ~Menu();

    void start();

    void update(float deltaTime);

    void draw();
};

