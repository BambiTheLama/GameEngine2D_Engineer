#pragma once
#include "Scene.h"
class TestScene :
    public Scene
{
public:
	TestScene();

	~TestScene();

	virtual void start();

	virtual void update(float deltaTime);

	virtual void draw();
};

