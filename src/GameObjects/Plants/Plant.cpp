#include "Plant.h"
#include "../../core/Scenes/GameScene.h"

Plant::Plant(Plant& plant):GameObject(plant),ItemsDrop(plant),DestroyAble(plant)
{
	sprite = new SpriteController(*plant.sprite);
}


Plant::Plant(Rectangle pos,std::string name):GameObject(pos,name),DestroyAble(ToolType::All)
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
	if (!isThisToolType(type, itemToolRequest))return;
	Rectangle pos = getPos();
	std::vector<Item*> items = getDrop();
	for (Item* i : items)
	{
		i->addToPos({ pos.x, pos.y });
		Game->addObject(i);
	}

}