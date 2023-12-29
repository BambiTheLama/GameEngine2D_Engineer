#include "CharacterBody.h"

CharacterBody::CharacterBody(std::string path,float sizeW,float sizeH)
{
	this->body = new SpriteController(std::string(path+"Body.png").c_str());
	this->legs = new SpriteController(std::string(path+"Legs.png").c_str());
	this->hair = new SpriteController(std::string(path+"Hair.png").c_str());
	this->eyes = new SpriteController(std::string(path+"Eyes.png").c_str());
	this->head = new SpriteController(std::string(path+"Head.png").c_str());
	this->sizeH = sizeH;
	this->sizeW = sizeW;
	diffElementsPos();

}

CharacterBody::CharacterBody(CharacterBody& body)
{
	this->body = new SpriteController(*body.body);
	this->legs = new SpriteController(*body.legs);
	this->hair = new SpriteController(*body.hair);
	this->eyes = new SpriteController(*body.eyes);
	this->head = new SpriteController(*body.head);
	this->bodyPos = body.bodyPos;
	this->legsPos = body.legsPos;
	this->headPos = body.headPos;
	this->sizeH = body.sizeH;
	this->sizeW = body.sizeW;
	diffElementsPos();
}

CharacterBody::~CharacterBody()
{
	delete this->body;
	delete this->legs;
	delete this->hair;
	delete this->eyes;
	delete this->head;
}
void CharacterBody::update(float deltaTime) 
{ 
	frame += deltaTime * frameRate; 
}

void CharacterBody::updateCharacterState(CharacterState state)
{ 

	if (state != this->state)
	{
		if (this->state == CharacterState::Die)
		{
			diffElementsPos();
		}
		else if (state == CharacterState::Die)
		{
			rotationRateHead = (rand() % 20001 - 10000) / 10000.0f;
			rotationRateLegs = (rand() % 20001 - 10000) / 10000.0f;
			rotationRateBody = (rand() % 20001 - 10000) / 10000.0f;
		}
		this->state = state; frame = 0;
	}
}
void CharacterBody::draw(Rectangle at)
{

	this->rotateBy = 0; 
	this->moveBy = 0;
	if (state == CharacterState::Run)
	{
		this->rotateBy = sin(frame * 3);
		this->moveBy = sin(frame * 1);
	}

	else if (state == CharacterState::Ide)
	{
		this->moveBy = sin(frame * 3);
	}

	if (state != CharacterState::Die)
	{
		drawLegs({ legsPos.x + at.x,legsPos.y + at.y,legsPos.width,legsPos.height }, 0);
		drawBody({ bodyPos.x + at.x,bodyPos.y + at.y - moveBy * headPos.height / 64,bodyPos.width,bodyPos.height }, rotateBy);
		drawHead({ headPos.x + at.x,headPos.y + at.y - moveBy * headPos.height / 32,headPos.width,headPos.height }, rotateBy * 3);
		
		drawHand({ handPos.x + at.x,handPos.y + at.y,handPos.width , handPos.height }, 0);
	}
	else
		drawDie(at);

}

void CharacterBody::drawHand(Rectangle pos,float rotation)
{
	pos.x += pos.width / 2;
	pos.y += pos.height / 2;
	pos.height /= 2;
	Texture2D texture = legs->getTexture();
	Rectangle texturePos = { texture.width * 3 / 4.0f,0,texture.width / 4.0f,(float)texture.height / 2 };
	DrawTexturePro(texture, texturePos, pos, {pos.width / 2,pos.height / 2}, rotation, headColor);
}

void CharacterBody::drawHead(Rectangle pos,float rotate)
{
	pos.x += pos.width / 2;
	pos.y += pos.height / 2;

	Texture2D texture = head->getTexture();
	Rectangle texturePos = { texture.width / 6.0f,0.0f,texture.width / 6.0f,(float)texture.height };;
	if (side == CharacterSide::Up || side == CharacterSide::Down)
		texturePos.x = texturePos.width * 2 * (int)headStyle;
	else
		texturePos.x = texturePos.width * 2 * (int)headStyle + texturePos.width;

	DrawTexturePro(texture, texturePos, pos, { pos.width / 2,pos.height / 2 }, rotate, headColor);

	///Rysowanie oczu
	texture = eyes->getTexture();
	texturePos = { texture.width / 6.0f,0.0f,texture.width / 6.0f,(float)texture.height };
	if (side == CharacterSide::Up || side == CharacterSide::Down)
		texturePos.x = texturePos.width * 2 * (int)eyeStyle;
	else if (side == CharacterSide::Right)
		texturePos.x = texturePos.width * 2 * (int)eyeStyle + texturePos.width;
	else
	{
		texturePos.x = texturePos.width * 2 * (int)eyeStyle + texturePos.width;
		texturePos.width *= -1;
	}
	if (side != CharacterSide::Up)
		DrawTexturePro(texture, texturePos, pos, { pos.width / 2,pos.height / 2 }, rotate, eyesColor);
	///Rysowanie wlosow
	texture = hair->getTexture();
	texturePos = { texture.width / 4.0f * (int)side,(float)(texture.height * hairStyle) / 6,texture.width / 4.0f,(float)texture.height / 6 };
	DrawTexturePro(texture, texturePos, pos, { pos.width/2,pos.height/2 }, rotate, hairColor);
}

void CharacterBody::drawBody(Rectangle pos, float rotate)
{
	pos.x += pos.width / 2;
	pos.y += pos.height / 2;
	Texture2D texture = body->getTexture();
	Rectangle texturePos = { texture.width / 4.0f * (int)side,0.0f,texture.width / 4.0f,(float)texture.height };
	DrawTexturePro(texture, texturePos, pos, { pos.width / 2,pos.height / 2 }, rotate, bodyColor);

}

void CharacterBody::drawLegs(Rectangle pos, float rotate)
{
	Texture2D texture = legs->getTexture();
	Rectangle texturePos = { 0.0f,0.0f,texture.width / 4.0f,(float)texture.height };
	if (side == CharacterSide::Up || side == CharacterSide::Down)
	{
		float moveBy=pos.height/4 * this->rotateBy;

		texturePos.x = texturePos.width * 2;
		if (side == CharacterSide::Up)
			moveBy *= -1;
		DrawTexturePro(texture, texturePos, { pos.x - pos.width / 8,pos.y,pos.width,pos.height - moveBy }, { 0,0 }, 0, legsColor);
		DrawTexturePro(texture, texturePos, { pos.x + pos.width / 8,pos.y,pos.width,pos.height + moveBy }, { 0,0 }, 0, legsColor);
		
		DrawTexturePro(texture, { texturePos.width * 3 ,texturePos.height / 2,texturePos.width ,texturePos.height / 2 },
			{ pos.x,pos.y -= pos.height / 16,pos.width,pos.height / 2 }, { 0,0 }, 0, legsColor);

		return;	
	}
	else if (side == CharacterSide::Right)
		texturePos.x = 0;
	else
	{
		texturePos.x = texturePos.width * 1;
	}
	float rotation = 0;
	rotation =  40 * this->rotateBy;
	Rectangle pos2 = { pos.x + pos.width / 2,pos.y,pos.width,pos.height };
	pos.height /= 2;
	pos.y -= pos.height / 7;
	//DrawTexturePro(texture, { texturePos.width * 3 ,0,texturePos.width ,texturePos.height / 2 }, pos, { 0,0 }, 0, legsColor);
	DrawTexturePro(texture, texturePos, pos2, { pos.width / 2,0 }, rotation, legsColor);
	DrawTexturePro(texture, texturePos, pos2, { pos.width / 2,0 }, -rotation, legsColor);

}

void CharacterBody::drawDie(Rectangle at)
{
	float endH = getEndH();
	float speed = at.height*4;
	float f = (endH - legsPos.y) / speed;
	if (frame <= f)
		f = frame;
	drawLegs({ at.width/4*f*rotationRateLegs+legsPos.x + at.x,f*speed+legsPos.y + at.y,legsPos.width,legsPos.height }, rotationRateLegs * f*60);
	f = (endH - bodyPos.y) / speed;
	if (frame <= f)
		f = frame;
	drawBody({ at.width / 4 *f*rotationRateBody+bodyPos.x + at.x,f*speed+bodyPos.y + at.y - moveBy * headPos.height / 64,bodyPos.width,bodyPos.height }, rotationRateBody * f * 60);
	f = (endH - headPos.y) / speed;
	if (frame <= f)
		f = frame;
	drawHead({ at.width / 4 *f*rotationRateHead+headPos.x + at.x,f*speed+headPos.y + at.y - moveBy * headPos.height / 32,headPos.width,headPos.height }, rotationRateHead * f * 60);
	f = (endH - handPos.y) / speed;
	if (frame <= f)
		f = frame;
	drawHand({ handPos.x + at.x,handPos.y + at.y,handPos.width , handPos.height }, rotationRateHead * f * 60);
}

void CharacterBody::diffElementsPos() {
	headPos = { 0,-sizeH,sizeW,sizeW };
	bodyPos = { 0,-sizeH * 7 / 16,sizeW,sizeW };
	legsPos = { 0,sizeH * 3 / 16,sizeW,sizeW };
}