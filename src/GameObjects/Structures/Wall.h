#pragma once
#include "Structure.h"


class Wall :
    public Structure
{
    bool right = true, left = true, down = true, up = true;
    Rectangle texturePosUp = { 0,0,32,16 };
    Rectangle texturePosDown = { 0,0,32,32 };
protected:
    Wall(Wall& obj);
public:
    Wall(Rectangle pos, std::string name, ToolType tool = ToolType::All, int hp = 1, int power = 0);

    virtual ~Wall();

    virtual void start();

    virtual void update(float deltaTime);

    virtual void draw();

    virtual void damageObject(int power, ToolType type);

    virtual void saveToJson(nlohmann::json& j);

    virtual void readFromJson(nlohmann::json& j);

    void generateTexturePos();

    void updateWallAt(Rectangle updatePos);

    bool isWallAt(Vector2 pos);

    virtual Wall* clone() { return new Wall(*this); }

    virtual bool isColliding() { return true; }
};

