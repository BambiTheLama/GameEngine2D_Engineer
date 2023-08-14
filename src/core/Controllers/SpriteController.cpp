#include "SpriteController.h"
#include <iostream>
std::vector<SpriteController*> SpriteController::sprites = std::vector<SpriteController*>();

SpriteController::SpriteController(const char* path)
{
	this->path = path;
	for(SpriteController* sprite:sprites)
		if (sprite->path.compare(path)==0)
		{
			std::cout << path << " = " << sprite->path << "\n";
			texture = sprite->texture;
			return;
		}
	texture = LoadTexture(path);
	if (texture.id > 0)
	{
		sprites.push_back(this);
	}
}

SpriteController::SpriteController(SpriteController& controller)
{
	this->path = controller.path;
	this->texture = controller.texture;
}

void SpriteController::closeSprites()
{
	for (SpriteController* sprite : sprites)
		UnloadTexture(sprite->texture);

	sprites.clear();
}

void SpriteController::draw(Rectangle pos)
{
	DrawTexturePro(texture, getTextureSize(), pos, {0,0}, 0, WHITE);
}

void SpriteController::draw(Rectangle pos, int frame)
{
	DrawTexturePro(texture, getTextureFrame(frame), pos, { 0,0 }, 0, WHITE);
}

