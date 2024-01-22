#include "SpriteController.h"
#include <iostream>
std::vector<SpriteController*> SpriteController::sprites = std::vector<SpriteController*>();

SpriteController::SpriteController(const char* path)
{
	this->path = (std::string)path;
	for (SpriteController* sprite : sprites)
		if (sprite->path.compare(path) == 0)
		{
			texture = sprite->texture;
			return;
		}
	texture = LoadTexture(path);
	if (texture.id > 0)
	{
		sprites.push_back(new SpriteController(*this));
	}
}

SpriteController::SpriteController(SpriteController& controller)
{
	this->path = controller.path;
	this->texture = controller.texture;
}

SpriteController::~SpriteController()
{
	
}

void SpriteController::closeSprites()
{
	for (SpriteController* sprite : sprites)
	{
		UnloadTexture(sprite->texture);
		delete sprite;
	}


	sprites.clear();
}
Rectangle SpriteController::getTextureFrame(int frame) 
{ 
	Rectangle pos = { 0,0,(float)texture.height,(float)texture.height };
	int frames = getHowMuchFrames();
	if (frames > 0)
		pos.x = (float)texture.height * (frame % frames);
	return pos;
}
void SpriteController::draw(Rectangle pos)
{
	DrawTexturePro(texture, getTextureSize(), pos, {0,0}, 0, WHITE);
}

void SpriteController::draw(Rectangle pos, int frame)
{
	DrawTexturePro(texture, getTextureFrame(frame), pos, { 0,0 }, 0, WHITE);
}

