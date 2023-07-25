#include "Plant.h"
#include "../../core/Scenes/GameScene.h"

Plant::Plant(Plant& plant):GameObject(plant),ItemsDrop(plant),DestroyAble(plant)
{
	sprite = new SpriteController(*plant.sprite);
}


Plant::Plant(Rectangle pos,std::string name,ToolType tool,int hp,int power):
	GameObject(pos,name),DestroyAble(tool,hp,power)
{
	std::string path = "Resource/Plants/" + name + ".png";
	sprite = new SpriteController(path.c_str());
}

Plant::~Plant()
{
	delete sprite;
}

void Plant::update()
{

}

void Plant::draw()
{
	sprite->draw(getPos());
}

void Plant::damageObject(int power, ToolType type)
{
	DestroyAble::damageObject(power, type);
	if (hp > 0)
		return;
	Rectangle pos = getPos();
	std::vector<Item*> items = getDrop();
	for (Item* i : items)
	{
		i->addToPos({ pos.x, pos.y });
		Game->addObject(i);
	}
	Game->deleteObject(this);
}