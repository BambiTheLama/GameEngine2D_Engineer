#pragma once
#include "../GameObject.h"
class TextParticle :
    public GameObject
{
    int time = 60;
    int timeMax = 60;
    TextParticle(TextParticle& e);
public:
    TextParticle(Rectangle pos, std::string name);

    virtual ~TextParticle();

    virtual void update();

    virtual void draw();

    ObjectType getType() { return ObjectType::Particle; }

    virtual TextParticle* clone() { return new TextParticle(*this); }
};

