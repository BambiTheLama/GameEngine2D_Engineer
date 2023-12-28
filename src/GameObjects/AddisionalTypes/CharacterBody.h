#pragma once
#include "../../core/Controllers/SpriteController.h"

enum class CharacterSide
{
	Down = 0, Right, Up, Left
};

enum class CharacterState
{
	Ide,Run,Fight,Doge,Die
};

class CharacterBody
{
	Rectangle bodyPos;
	Rectangle legsPos;
	Rectangle headPos;
	SpriteController* body;
	SpriteController* legs;
	SpriteController* head;
	SpriteController* eyes;
	SpriteController* hair;
	Color bodyColor = RED;
	Color legsColor = WHITE;
	Color headColor = YELLOW;
	Color eyesColor = WHITE;
	Color hairColor = BROWN;
	int hairStyle = 1;
	int eyeStyle = 2;
	int headStyle = 0;
	CharacterSide side;
	CharacterState state;
	float frame=0;
	const float frameRate=1;
	float sizeW, sizeH;
	float rotateBy = 0;
	float moveBy = 0;
public:
	CharacterBody(std::string path,float sizeW,float sizeH);

	CharacterBody(CharacterBody &body);

	~CharacterBody();

	void updateDeltaTime(float deltaTime) { frame += deltaTime * frameRate; }

	void updateCharacterSide(CharacterSide side) { this->side = side; }

	void updateCharacterState(CharacterState state) { this->state = state; frame = 0; }

	void draw(Rectangle at);

	void drawHead(Rectangle at);

	void drawBody(Rectangle at);

	void drawLegs(Rectangle at);
};

