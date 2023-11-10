#pragma once
#include "Plant.h"

class Tree :
    public Plant
{
    int age = 0;
    int maxAge = 0;
    int woodID = 0;
    float timer = 60;
    Tree(Tree& tree);
public:
    Tree(Rectangle pos,std::string name);

    Tree(nlohmann::json& j);

    ~Tree();

    void start();

    void incrementAge();

    void update(float deltaTime);

    void draw();

    void updateDropFromAge();

    virtual void setMovePos(Vector2 movePos);

    virtual Tree* clone() { return new Tree(*this); }

    virtual void damageObject(int power, ToolType type);

    virtual bool isColliding() { return true; }

    virtual bool isToolGoBack() { return true; }

    void saveToJson(nlohmann::json& j);

    virtual void readFromJson(nlohmann::json& j);

    virtual bool destoryAfterRenderClear() { return false; }
};

