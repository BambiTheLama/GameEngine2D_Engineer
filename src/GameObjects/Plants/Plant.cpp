#include "Plant.h"
#include "../../core/Scenes/GameScene.h"

Plant::Plant(Plant& plant):GameObject(plant),ItemsDrop(plant),DestroyAble(plant),RectangleCollider(plant)
{
	sprite = new SpriteController(*plant.sprite);
}


Plant::Plant(Rectangle pos,std::string name,ToolType tool,int hp,int power):
	Plant(pos,name,tool,hp,power,{0,0,pos.width,pos.height})
{
	std::string path = "Resource/Plants/" + name + ".png";
	sprite = new SpriteController(path.c_str());
}

Plant::Plant(Rectangle pos, std::string name, ToolType tool, int hp, int power,Rectangle collision) :
	GameObject(pos,name),ItemsDrop(),DestroyAble(tool,hp,power),RectangleCollider(collision)
{
	std::string path = "Resource/Plants/" + name + ".png";
	sprite = new SpriteController(path.c_str());
}

Plant::Plant(std::string chunk, std::string objDataPlace, nlohmann::json& j)
	:GameObject(chunk,objDataPlace,j), ItemsDrop(getType(), getID()), DestroyAble(getType(), getID()), RectangleCollider(getType(), getID())
{

}

Plant::~Plant()
{
	delete sprite;
}

void Plant::update(float deltaTime)
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

void Plant::saveToJson(std::string chunk, std::string objDataPlace, nlohmann::json& j)
{
	GameObject::saveToJson(chunk, objDataPlace, j);
}

void Plant::readFromJson(std::string chunk, std::string objDataPlace, nlohmann::json& j)
{
	GameObject::readFromJson(chunk, objDataPlace, j);
}