#pragma once
#include "../../core/Scenes/GameScene.h"
class MiniMap
{
	RenderTexture2D minimapBuffor;
	int w, h;
	GameObject* target;
public:
	MiniMap(GameObject* target);

	~MiniMap();

	void generateMiniMap();

	void draw();

};

