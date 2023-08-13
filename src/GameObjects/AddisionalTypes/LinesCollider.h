#pragma once
#include "raylib.h"
#include <math.h>
class HitAble;
class DestroyAble;
enum class CollisionsCheckType
{
    NON,HitAbleOnly,DestoryAbleOnly,All
};
class LinesCollider
{
    int nPoints = 0;
    float rotation = 0;
    Vector2* points = NULL;
    Vector2* startPoints = NULL;
    CollisionsCheckType type;
protected:
    LinesCollider(LinesCollider& lines);
public:
    LinesCollider(CollisionsCheckType type);
    ~LinesCollider();
    void addLines(int n, Vector2* points);
    void draw();
    void updateRotation(float rotation, Vector2 origin, Vector2 pos,bool leftSide=true);
    void update();
    virtual void onCollisionHitable(HitAble* hit);
    virtual void onCollisionDestroyAble(DestroyAble* dest);
};

