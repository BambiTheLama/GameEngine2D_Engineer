#pragma once
#include "../GameObject.h"
class TextParticle :
    public GameObject
{
    float time = 1.0f;
    float timeMax = 1.0f;
    TextParticle(TextParticle& e);
public:
    TextParticle(Rectangle pos, std::string name);

    virtual ~TextParticle();

    virtual void update(float deltaTime);

    virtual void draw();

    ObjectType getType() { return ObjectType::Particle; }

    virtual TextParticle* clone() { return new TextParticle(*this); }

    virtual bool destoryAfterRenderClear() { return true; }
};

