#pragma once
#include "raylib.h"
class Collider
{
	Rectangle collision;
public:
	Collider(Rectangle col);

	Rectangle getCollision() { return collision; }

	bool checkCollison(Rectangle col) { return CheckCollisionRecs(col, collision); }

	bool checkCollison(Collider& col) { return CheckCollisionRecs(collision, col.collision); }
};

