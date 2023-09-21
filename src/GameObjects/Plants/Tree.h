#pragma once
#include "Plant.h"

class Tree :
    public Plant, public RectangleCollider
{
    int age = 0;
    int maxAge = 0;
    float timer = 60;
    Tree(Tree& tree);
public:
    Tree(Rectangle pos,std::string name);

    ~Tree();

    void start();

    void incrementAge();

    void update(float deltaTime);

    void draw();

    virtual void setMovePos(Vector2 movePos);

    virtual Tree* clone() { return new Tree(*this); }

    virtual void damageObject(int power, ToolType type);

    bool isColliding() { return true; }

    virtual bool isToolGoBack() { return true; }
};

