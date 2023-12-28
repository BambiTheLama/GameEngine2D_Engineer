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
	headPos = { 0,-sizeH,sizeW,sizeW };
	bodyPos = { 0,-sizeH*7/16,sizeW,sizeW };
	legsPos = { 0,sizeH * 4 / 16,sizeW,sizeW };

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
}

CharacterBody::~CharacterBody()
{
	delete this->body;
	delete this->legs;
	delete this->hair;
	delete this->eyes;
	delete this->head;
}

void CharacterBody::draw(Rectangle at)
{

	this->rotateBy = 0; 
	this->moveBy = 0;
	if (state == CharacterState::Run)
		this->rotateBy = sin(frame * 3);
	else if (state == CharacterState::Ide)
		this->moveBy = sin(frame * 3);

	drawLegs(at);
	drawBody(at);
	drawHead(at);
}

void CharacterBody::drawHead(Rectangle at)
{
	Rectangle pos = { headPos.x + at.x,headPos.y + at.y - moveBy * headPos.height / 32,headPos.width,headPos.height };


	Texture2D texture = head->getTexture();
	Rectangle texturePos = { texture.width / 6.0f,0.0f,texture.width / 6.0f,(float)texture.height };;
	if (side == CharacterSide::Up || side == CharacterSide::Down)
		texturePos.x = texturePos.width * 2 * (int)headStyle;
	else
		texturePos.x = texturePos.width * 2 * (int)headStyle + texturePos.width;

	DrawTexturePro(texture, texturePos, pos, { 0,0 }, 0, headColor);

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
		DrawTexturePro(texture, texturePos, pos, { 0,0 }, 0, eyesColor);
	///Rysowanie wlosow
	texture = hair->getTexture();
	texturePos = { texture.width / 4.0f * (int)side,(float)(texture.height * hairStyle) / 6,texture.width / 4.0f,(float)texture.height / 6 };
	DrawTexturePro(texture, texturePos, pos, { 0,0 }, 0, hairColor);
}

void CharacterBody::drawBody(Rectangle at)
{
	Rectangle pos = { bodyPos.x + at.x,bodyPos.y + at.y - moveBy * headPos.height / 64,bodyPos.width,bodyPos.height };
	Texture2D texture = body->getTexture();
	Rectangle texturePos = { texture.width / 4.0f * (int)side,0.0f,texture.width / 4.0f,(float)texture.height };
	DrawTexturePro(texture, texturePos, pos, { 0,0 }, 0, bodyColor);

}

void CharacterBody::drawLegs(Rectangle at)
{
	Rectangle pos = { legsPos.x + at.x,legsPos.y + at.y,legsPos.width,legsPos.height };
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
			{ legsPos.x + at.x,pos.y -= pos.height / 16,pos.width,pos.height / 2 }, { 0,0 }, 0, legsColor);

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
	DrawTexturePro(texture, { texturePos.width * 3 ,0,texturePos.width ,texturePos.height / 2 }, pos, { 0,0 }, 0, legsColor);
	DrawTexturePro(texture, texturePos, pos2, { pos.width / 2,0 }, rotation, legsColor);
	DrawTexturePro(texture, texturePos, pos2, { pos.width / 2,0 }, -rotation, legsColor);

}