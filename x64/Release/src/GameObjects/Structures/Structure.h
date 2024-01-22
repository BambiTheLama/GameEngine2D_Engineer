#pragma once
#include "../GameObject.h"
#include "../AddisionalTypes/AllTypes.h"
class Structure :
    public GameObject, public ItemsDrop, public DestroyAble, public RectangleCollider
{
protected:
    Structure(Structure& obj);
    SpriteController* sprite=NULL;
    float damageTime=0.0f;
    const float damageTimeMax = 0.5f;
public:
    Structure(Rectangle pos, std::string name, ToolType tool = ToolType::All, int hp = 1, int power = 0);

    Structure(Rectangle pos, std::string name, ToolType tool, int hp, int power,Rectangle collision);

    virtual ~Structure();

    virtual void update(float deltaTime);

    virtual void draw();

    ObjectType getType() { return ObjectType::Structure; }

    virtual Structure* clone() { return new Structure(*this); }

    virtual void damageObject(int power, ToolType type);

    virtual void saveToJson(nlohmann::json& j);

    virtual void readFromJson(nlohmann::json& j);

    virtual bool destoryAfterRenderClear() { return false; }

    virtual void generateTexturePos(){}

    virtual void drawPlaceInterface(Vector2 pos);

    Rectangle animationPos(){
        Rectangle pos = getPos();
        if (damageTime > 0.0f)
        {
            float p = damageTime / damageTimeMax * pos.height / 8.0f;
            pos.x += p;
            pos.width -= p * 2;
            pos.y -= p;
            pos.height += p;
        }
        return pos;
    }
};

