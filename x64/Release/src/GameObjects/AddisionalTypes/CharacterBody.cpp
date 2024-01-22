#include "CharacterBody.h"
#include "../GameObject.h"

CharacterBody::CharacterBody(std::string path,float sizeW,float sizeH)
{
	this->sizeH = sizeH;
	this->sizeW = sizeW;
	this->path = path;
	diffElementsPos();
	loadTextures();
}

CharacterBody::CharacterBody(CharacterBody& body)
{
	this->path = body.path;
	this->bodyPos = body.bodyPos;
	this->legsPos = body.legsPos;
	this->headPos = body.headPos;
	this->sizeH = body.sizeH;
	this->sizeW = body.sizeW;
	this->bodyColor = body.bodyColor;
	this->legsColor = body.legsColor;
	this->headColor = body.headColor;
	this->eyesColor = body.eyesColor;
	this->hairColor = body.hairColor;
	this->hairStyle = body.hairStyle;
	this->eyeStyle = body.eyeStyle;
	this->headStyle = body.headStyle;
	diffElementsPos();
	loadTextures();
}

CharacterBody::~CharacterBody()
{
	delete this->body;
	delete this->legs;
	delete this->hair;
	delete this->eyes;
	delete this->head;
}
void CharacterBody::update(float deltaTime, Vector2 cursor,Rectangle pos)
{ 

	frame += deltaTime * frameRate;
	if (this->state == CharacterState::Die)
		return;
	bool leftHand = (pos.x + pos.width / 2) > cursor.x;
	Vector2 start = { pos.x + pos.width / 2,pos.y + pos.height / 2 };
	if (leftHand)
		start.x -= pos.width / 4;
	else
		start.x += pos.width / 4;
	float rotation = cursorTarget(start, cursor);
	handPos = { sin(degreeToRadius(rotation)) * handPos.width/4 + start.x
		,-cos(degreeToRadius(rotation)) * handPos.height/4 + start.y
		,handPos.width
		,handPos.height };

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
		drawHand(handPos, 0);
	}
	else
		drawDie(at);

}

void CharacterBody::drawHand(Rectangle pos,float rotation)
{
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
	Texture2D texture = body->getTexture();
	Rectangle texturePos = { texture.width / 4.0f * (int)side,0.0f,texture.width / 4.0f,(float)texture.height };
	DrawTexturePro(texture, texturePos, pos, { 0,0 }, 0, bodyColor);

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
	float endH = getEndY();
	float speed = at.height*4;
	float f = (endH - legsPos.y) / speed;
	if (frame <= f)
		f = frame;
	drawLegs({ at.width / 4 * f * rotationRateLegs + legsPos.x + at.x,f * speed + legsPos.y + at.y,legsPos.width,legsPos.height }
	, rotationRateLegs * f * 60);
	f = (endH - bodyPos.y) / speed;
	if (frame <= f)
		f = frame;
	drawBody({ at.width / 4 * f * rotationRateBody + bodyPos.x + at.x,f * speed + bodyPos.y + at.y - moveBy * headPos.height / 64,bodyPos.width,bodyPos.height }
	, rotationRateBody * f * 60);
	f = (endH - headPos.y) / speed;
	if (frame <= f)
		f = frame;
	drawHead({ at.width / 4 * f * rotationRateHead + headPos.x + at.x,f * speed + headPos.y + at.y - moveBy * headPos.height / 32,headPos.width,headPos.height }
	, rotationRateHead * f * 60);
}

void CharacterBody::diffElementsPos() {
	headPos = { 0,0,sizeH,sizeH };
	bodyPos = { 0,sizeH * 7 / 16,sizeH,sizeH };
	legsPos = { 0,sizeH * 17 / 16,sizeH,sizeH };
	handPos = { 0,0 ,sizeH,sizeH };
}

void CharacterBody::loadTextures()
{
	if (body)
		delete body;
	body = new SpriteController(std::string(path + "Body.png").c_str());
	if (legs)
		delete legs;
	legs = new SpriteController(std::string(path + "Legs.png").c_str());
	if (hair)
		delete hair;
	hair = new SpriteController(std::string(path + "Hair.png").c_str());
	if (eyes)
		delete eyes;
	eyes = new SpriteController(std::string(path + "Eyes.png").c_str());
	if (head)
		delete head;
	head = new SpriteController(std::string(path + "Head.png").c_str());
}
void saveColorToJson(nlohmann::json& writer, Color c)
{
	writer[0] = c.r;
	writer[1] = c.g;
	writer[2] = c.b;
}
void CharacterBody::saveData(nlohmann::json& writer)
{
	writer["Body"]["Path"] = path;
	saveColorToJson(writer["Body"]["Colors"][0], bodyColor);
	saveColorToJson(writer["Body"]["Colors"][1], legsColor);
	saveColorToJson(writer["Body"]["Colors"][2], headColor);
	saveColorToJson(writer["Body"]["Colors"][3], eyesColor);
	saveColorToJson(writer["Body"]["Colors"][4], hairColor);
	writer["Body"]["Style"][0] = hairStyle;
	writer["Body"]["Style"][1] = eyeStyle;
	writer["Body"]["Style"][2] = headStyle;
	writer["Body"]["Size"][0] = sizeW;
	writer["Body"]["Size"][0] = sizeH;
}
Color readColorToJson(nlohmann::json& reader)
{
	return { reader[0] ,reader[1] ,reader[2] ,255 };
}
void CharacterBody::readData(nlohmann::json& reader)
{
	if (!reader.contains("Body"))
		return;
	reader["Body"]["Path"] = path;
	bodyColor = readColorToJson(reader["Body"]["Colors"][0]);
	legsColor = readColorToJson(reader["Body"]["Colors"][1]);
	headColor = readColorToJson(reader["Body"]["Colors"][2]);
	eyesColor = readColorToJson(reader["Body"]["Colors"][3]);
	hairColor = readColorToJson(reader["Body"]["Colors"][4]);
	hairStyle = reader["Body"]["Style"][0];
	eyeStyle = reader["Body"]["Style"][1];
	headStyle = reader["Body"]["Style"][2];
	sizeW = reader["Body"]["Size"][0];
	sizeH = reader["Body"]["Size"][0];
	diffElementsPos();
	loadTextures();
}