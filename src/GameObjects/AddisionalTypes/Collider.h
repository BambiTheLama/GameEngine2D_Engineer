#pragma once
#include "raylib.h"
#include <vector>
#include "../GameObject.h"

enum class CollisionType
{
	Rec, Lines, Circle,NON
};

enum class CollisionsCheckType
{
	NON, HitAbleOnly, DestoryAbleOnly, All, EnumSize
};
class HitAble;
class DestroyAble;

class Collider
{
	std::list<GameObject*> objectsToIgnore;
	CollisionsCheckType type;
protected:
	Collider(Collider& col);
public:
	Collider(CollisionsCheckType type=CollisionsCheckType::NON);

	Collider(nlohmann::json j);

	virtual bool checkCollisionToObj(Collider* c, Vector2 thisPos, Vector2 otherPos);

	bool isCollidingWithSomething();

	virtual void draw(GameObject* obj){}

	virtual Rectangle getCollisionPos() { return{ 0,0,0,0 }; }

	virtual int getHomManyLines() { return 0; }

	virtual Vector2* getLines() { return NULL; }

	virtual int getRadius() { return 0; }

	virtual Vector2 getCirlcePoint() { return { 0,0 }; }

	virtual CollisionType getCollisionType() { return CollisionType::NON; }

	virtual void update(float deltaTime, GameObject* obj);

	virtual void onCollisionHitable(HitAble* hit){}

	virtual void onCollisionDestroyAble(DestroyAble* dest){}

	virtual Rectangle getMaxRectangle() { return { 0,0,0,0 }; }

	void addObjToIgnore(GameObject* ignore);

	void removeObjectToIgnore(GameObject* ignore);

	void clearListToIgnore();
};

bool checkCollision(GameObject* obj);
struct LineData {
	float x1, x2, y1, y2;
	float a, b;
	void calculateAB();

	bool checkLines(LineData l);
};
bool checkCollision(Vector2* points, int n, Rectangle pos);
bool checkCollision(Vector2* points, int n, Vector2* points2, int n2);
float distance(float x1, float y1, float x2, float y2);
bool collideLineCircle(Vector2 v, float radius, Vector2 p1, Vector2 p2);
bool collideLinesCircle(Vector2 v, float radius, Vector2* points, int n);