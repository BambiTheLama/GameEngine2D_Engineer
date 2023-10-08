#pragma once
#include "raylib.h"
#include "../../json.hpp"
#include "Collider.h"
#include <math.h>
class HitAble;
class DestroyAble;

class LinesCollider:
    public Collider
{
    int nPoints = 0;
    float rotation = 0;
    Vector2* points = NULL;
    Vector2* startPoints = NULL;
    Vector2 origin;
protected:
    LinesCollider(LinesCollider& lines);
public:
    LinesCollider(Vector2* collision, int n, CollisionsCheckType collisionType=CollisionsCheckType::All);

    LinesCollider(nlohmann::json j);

    ~LinesCollider();

    virtual void draw(GameObject* obj);

    void updateRotation(float rotation, Vector2 origin, Vector2 moveBy,bool leftSide=true);

    virtual int getHomManyLines() { return nPoints; }

    virtual Vector2* getLines() { return points; }

    virtual CollisionType getCollisionType() { return CollisionType::Lines; }

    virtual Rectangle getMaxRectangle();

    bool checkCollisionToObj(Collider* c, Vector2 thisPos, Vector2 otherPos);

};

