#include "AnimationControler.h"

AnimationControler::AnimationControler(std::vector<SpriteController*> sprites)
{
	this->sprites = sprites;
}

AnimationControler::AnimationControler(SpriteController* sprite)
{
	sprites.push_back(sprite);
}
AnimationControler::AnimationControler(SpriteController** sprites, int n)
{
	for (int i = 0; i < n; i++)
		this->sprites.push_back(sprites[i]);
}
AnimationControler::~AnimationControler()
{
	for (SpriteController* sprite : sprites)
		delete sprite;
	sprites.clear();
}

void AnimationControler::draw(Rectangle pos, int frame, int animationIndex, bool flipLeftRight, bool flipUpDown)
{
	if (animationIndex >= sprites.size() || animationIndex < 0)
		return;
	Texture2D texture = sprites[animationIndex]->getTexture();
	float size = texture.height;
	Rectangle spritePos = { 0,frame * size,size * flipLeftRight ? -1 : 1,size * flipUpDown ? -1 : 1 };
	DrawTexturePro(texture, spritePos, pos, { 0,0 }, 0, WHITE);
}