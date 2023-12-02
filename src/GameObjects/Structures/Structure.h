#pragma once
#include "../GameObject.h"
#include "../AddisionalTypes/AllTypes.h"
class Structure :
    public GameObject, public ItemsDrop, public DestroyAble, public RectangleCollider
{
protected:
    Structure(Structure& obj);
    SpriteController* sprite=NULL;
public:
    Structure(Rectangle pos, std::string name, ToolType tool = ToolType::All, int hp = 1, int power = 0);

    Structure(Rectangle pos, std::string name, ToolType tool, int hp, int power,Rectangle collision);

    Structure(nlohmann::json& j);

    virtual ~Structure();

    virtual void update(float deltaTime);

    virtual void draw();

    ObjectType getType() { return ObjectType::Structure; }

    virtual Structure* clone() { return new Structure(*this); }

    virtual void damageObject(int power, ToolType type);

    virtual void saveToJson(nlohmann::json& j);

    virtual void readFromJson(nlohmann::json& j);

    virtual bool destoryAfterRenderClear() { return false; }
};

