#pragma once
#include "raylib.h"
class Particle
{
	int time;
	int timeMax;
	Rectangle pos;
	Color colorEnd;
	Color colorStart;
	Vector2 velosity;
	Particle(Particle& particle);
public:
	Particle(Rectangle pos,int time,Vector2 velosity,Color color,Color end={0,0,0,0});

	void update();

	void draw();

	bool canDestory() { return time < 0; }

	void moveTo(Vector2 pos) { this->pos.x = pos.x; this->pos.y = pos.y; }

	void setTime(int time) { this->time = time; timeMax = time; }

	void setVelosity(Vector2 velosity) { this->velosity = velosity; }

	Particle* clone() { return new Particle(*this); }

};

