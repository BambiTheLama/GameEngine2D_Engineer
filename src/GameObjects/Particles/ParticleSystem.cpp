#include "ParticleSystem.h"
#include "../../core/Scenes/GameScene.h"

ParticleSystem::ParticleSystem(ParticleSystem& particle):GameObject(particle)
{
	n = particle.n;
	particles = new Particle * [n];
	particles[0] = particle.particles[0];
	for (int i = 1; i < n; i++)
	{
		particles[i] = particles[0]->clone();
	}
	velosityRandMin = particle.velosityRandMin;
	velosityRandMax = particle.velosityRandMax;
	timeMin = particle.timeMin;
	timeMax = particle.timeMax;
}

ParticleSystem::ParticleSystem(Rectangle pos,std::string name, Particle* particle, int n):GameObject(pos,name)
{
	this->n = n;
	particles = new Particle * [n];
	particles[0] = particle;
	for (int i = 1; i < n; i++)
	{
		particles[i] = particle->clone();
	}
}

ParticleSystem::~ParticleSystem()
{
	for(int i=0;i<n;i++)
		if (particles[i] != NULL)
		{
			delete particles[i];
		}
	delete particles;
}

void ParticleSystem::start()
{
	for (int i = 0; i < n; i++)
		if (particles[i] != NULL)
		{
			float x = pos.x + rand() % (int)pos.width;
			float y = pos.y + rand() % (int)pos.height;
			particles[i]->moveTo({ x,y });
			int time = timeMin + rand() % (timeMax - timeMin);
			particles[i]->setTime(time);
			Vector2 velosty = {0,0};
			velosty.y = velosityRandMin.y + (rand() % (int)((velosityRandMax.y - velosityRandMin.y)*1000))/1000.0f;
			velosty.x = velosityRandMin.x + (rand() % (int)((velosityRandMax.x - velosityRandMin.x)*1000))/1000.0f;
			particles[i]->setVelosity(velosty);
		}

}

void ParticleSystem::update()
{
	int active = n;
	for (int i = 0; i < n; i++)
	{
		if (particles[i] != NULL)
		{
			particles[i]->update();
			if (particles[i]->canDestory())
			{
				active--;
				delete particles[i];
				particles[i] = NULL;
			}
		}
		else
			active--;
	}
	if (active <= 0)
		Game->deleteObject(this);


}

void ParticleSystem::draw()
{
	for (int i = 0; i < n; i++)
		if (particles[i] != NULL)
			particles[i]->draw();
}