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
	float rotationRateHead = 0;
	float rotationRateLegs = 0;
	float rotationRateBody = 0;
	Rectangle handPos = { 0,0 ,32,32};
public:
	CharacterBody(std::string path,float sizeW,float sizeH);

	CharacterBody(CharacterBody &body);

	~CharacterBody();

	void update(float deltaTime,Vector2 cursor,Rectangle pos);

	void updateCharacterSide(CharacterSide side) { this->side = side; }

	void updateCharacterState(CharacterState state);

	void draw(Rectangle at);

	void drawHead(Rectangle pos, float rotate);

	void drawBody(Rectangle pos, float rotate);

	void drawLegs(Rectangle pos, float rotate);

	void drawHand(Rectangle pos, float rotation);

	void drawDie(Rectangle at);

	void diffElementsPos();

	float getEndY() { return legsPos.y; }

	Vector2 getHandPos() { return { handPos.x+handPos.width/2,handPos.y+handPos.height/2 }; }
};

