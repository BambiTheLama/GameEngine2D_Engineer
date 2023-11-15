#pragma once
#include "Scene.h"
#include "Game/PerlinNoice.h"
#include "FastNoiseLite.h"
class TestScene :
    public Scene
{
    int x = 0;
    int y = 0;

    float scale = 0.01;
    int octet = 9;
    int seed = 12;
    RenderTexture2D buffor;
public:
    TestScene();

    ~TestScene();

    void start();

    void reloadNoice();

    void update(float deltaTime);

    void draw();
};

