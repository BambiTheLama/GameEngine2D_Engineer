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


void TextParticle::update()
{
	time--;
	pos.y--;
	if (time <= 0)
	{
		Game->deleteObject(this);
	}
}

void TextParticle::draw()
{
	Color color=RED;
	color.a = (256 * time) / timeMax;
	drawText(getName().c_str(), pos.x+pos.width/2, pos.y+pos.height/2, textStandardSize, color);
}