#pragma once
#include "../GameObject.h"
#include "Particle.h"
class ParticleSystem :
    public GameObject
{

protected:

    int n;
    float timeMin = 0;
    float timeMax = 0;
    Particle** particles;
    Vector2 velosityRandMin = { 0,0 };
    Vector2 velosityRandMax = { 0,0 };

    ParticleSystem(ParticleSystem& particleSystem);
public:
    ParticleSystem(Rectangle pos, std::string name, Particle* particle, int n = 10);

    void setTime(float timeMin, float timeMax) { this->timeMax = timeMax; this->timeMin = timeMin; }

    void setVelosity(Vector2 velosityMin, Vector2 velostyMax) { velosityRandMax = velostyMax; velosityRandMin = velosityMin; }

    ~ParticleSystem();

    virtual void start();

    virtual void update(float deltaTime);

    virtual void draw();

    ObjectType getType() { return ObjectType::Particle; }

    ParticleSystem* clone() { return new ParticleSystem(*this); }
};

