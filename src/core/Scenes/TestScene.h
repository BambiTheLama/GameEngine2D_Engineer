#pragma once
#include "Scene.h"
#include "Game/PerlinNoice.h"

class TestScene :
    public Scene
{
    int x = 0;
    int y = 0;
    float scale = 1.6;
    int octet = 9;
    int seed = 12;
    PerlinNoice* noice;
    PerlinNoice* noice2;
    PerlinNoice* noice3;
    bool firstLayer = true;
    bool secendLayer = true;
    bool thirdLayer = true;
    RenderTexture2D buffor;
public:
    TestScene();

    ~TestScene();

    void start();

    void reloadNoice();

    void update(float deltaTime);

    void draw();
};

