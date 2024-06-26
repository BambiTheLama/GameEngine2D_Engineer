#include "AnimationController.h"
#include <iostream>
AnimationController::AnimationController(std::vector<SpriteController*> sprites)
{
	this->sprites = sprites;
	toDelete = false;
}

AnimationController::AnimationController(SpriteController* sprite)
{
	sprites.push_back(sprite);
	toDelete = true;
}
AnimationController::AnimationController(SpriteController** sprites, int n)
{
	for (int i = 0; i < n; i++)
		this->sprites.push_back(sprites[i]);
	toDelete = true;
}
AnimationController::AnimationController(AnimationController& animations)
{
	sprites = animations.sprites;
	toDelete = false;
}
AnimationController::~AnimationController()
{
	if (toDelete)
	{
		for (SpriteController* sprite : sprites)
			delete sprite;
		sprites.clear();
	}

}
void printRec(Rectangle rec)
{
	std::cout << rec.x << " " << rec.y << " " << rec.width << " " << rec.height << "\n";
}
void AnimationController::draw(Rectangle pos, int frame, int animationIndex, bool flipLeftRight, bool flipUpDown)
{
	if (animationIndex >= sprites.size() || animationIndex < 0)
		return;
	Texture2D texture = sprites[animationIndex]->getTexture();
	Rectangle spritePos = sprites[animationIndex]->getTextureFrame(frame);
	if (flipLeftRight)
		spritePos.width = -spritePos.width;
	if (flipUpDown)
		spritePos.height = -spritePos.height;

	DrawTexturePro(texture, spritePos, pos, { 0,0 }, 0, WHITE);
}

int AnimationController::getMaxFrames(int animationIndex)
{
	if (animationIndex >= sprites.size() || sprites.size() < 0)
		return 0;
	Texture2D texture = sprites[animationIndex]->getTexture();

	return texture.width / texture.height;
}