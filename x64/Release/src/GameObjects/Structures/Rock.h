#pragma once
#include "Structure.h"
class Rock :
    public Structure
{
    int rockID = 0;
    Rock(Rock& rock);
public:
    Rock(Rectangle pos, std::string name, int rockID = 0);

    ~Rock();

    void start();

    void update(float deltaTime);

    void draw();

    virtual void setMovePos(Vector2 movePos);

    virtual void damageObject(int power, ToolType type);

    void spawnItem(Vector2 pos);

    void saveToJson(nlohmann::json& j);

    virtual void readFromJson(nlohmann::json& j);

    virtual Rock* clone() { return new Rock(*this); }

    virtual bool isColliding() { return true; }

    virtual bool isToolGoBack() { return true; }

    virtual bool destoryAfterRenderClear() { return false; }
};

