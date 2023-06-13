#include "SpriteController.h"

std::vector<SpriteController*> SpriteController::sprites = std::vector<SpriteController*>();

SpriteController::SpriteController(const char* path)
{
	this->path = path;
	bool has = false;
	for(SpriteController* sprite:sprites)
		if (sprite->path.compare(path))
		{
			has = true;
			texture = sprite->texture;
		}
	
	if (!has)
	{
		texture = LoadTexture(path);
		if (texture.id > 0)
		{
			sprites.push_back(this);
		}
		
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