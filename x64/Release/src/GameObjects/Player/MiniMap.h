#pragma once
#include "../../core/Scenes/GameScene.h"
class MiniMap
{

	int w, h;
	GameObject* target;
	RenderTexture2D minimapBuffor;
public:
	MiniMap(GameObject* target);

	~MiniMap();

	void generateMiniMap();

	void draw();

};

