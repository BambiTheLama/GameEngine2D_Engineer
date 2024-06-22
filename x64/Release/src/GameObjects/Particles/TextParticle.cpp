#include "TextParticle.h"
#include "../../core/Scenes/GameScene.h"

TextParticle::TextParticle(TextParticle& e):GameObject(e)
{

}

TextParticle::TextParticle(Rectangle pos, std::string name):GameObject(pos,name)
{

}

TextParticle::~TextParticle()
{

}


void TextParticle::update(float deltaTime)
{
	time-=deltaTime;
	pos.y-=deltaTime*64.0f;
	if (time <= 0)
	{
		Game->deleteObject(this);
	}
}

void TextParticle::draw()
{
	Color color = RED;
	Color color2 = BLACK;
	color.a = (256 * time) / timeMax;
	color2.a = (256 * time) / timeMax;
	DrawTextWithOutline(getName().c_str(), pos.x + pos.width / 2 - 1, pos.y + pos.height / 2,
		textStandardSize, color, color2);

}