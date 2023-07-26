#pragma once
#include "../GameObject.h"
#include "Particle.h"
class ParticleSystem :
    public GameObject
{

protected:
    Particle** particles;
    int n;
    Vector2 velosityRandMin = { 0,0 };
    Vector2 velosityRandMax = { 0,0 };
    int timeMin = 0;
    int timeMax = 0;
    ParticleSystem(ParticleSystem& particleSystem);
public:
    ParticleSystem(Rectangle pos, std::string name, Particle* particle, int n = 10);

    void setTime(int timeMin, int timeMax) { this->timeMax = timeMax; this->timeMin = timeMin; }

    void setVelosity(Vector2 velosityMin, Vector2 velostyMax) { velosityRandMax = velostyMax; velosityRandMin = velosityMin; }

    ~ParticleSystem();

    virtual void start();

    virtual void update();

    virtual void draw();

    ObjectType getType() { return ObjectType::Particle; }

    ParticleSystem* clone() { return new ParticleSystem(*this); }
};

