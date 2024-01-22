#include "Particle.h"

Particle::Particle(Particle& particle)
{
	pos = particle.pos;
	time = particle.time;
	velosity = particle.velosity;
	colorStart = particle.colorStart;
	colorEnd = particle.colorEnd;
	timeMax = time;
}

Particle::Particle(Rectangle pos, float time, Vector2 velosity,Color start,Color end)
{
	this->pos = pos;
	this->time = time;
	this->velosity = velosity;
	this->colorStart = start;
	this->colorEnd = end;
	timeMax = time;
}

void Particle::update(float deltaTime)
{
	time-=deltaTime;
	pos.x += velosity.x*deltaTime*64;
	pos.y += velosity.y*deltaTime*64;
}
Color blendColor(Color c1, Color c2, float p)
{

	return { (unsigned char)(c1.r * p + c2.r * (1.0f - p)),
	(unsigned char)(c1.g * p + c2.g * (1.0f - p)),
		(unsigned char)(c1.b * p + c2.b * (1.0f - p)),
		(unsigned char)(c1.a * p + c2.a * (1.0f - p))
	};
}
void Particle::draw()
{
	DrawRectangleRec(pos, blendColor(colorStart, colorEnd, (float)time / (float)timeMax));
}