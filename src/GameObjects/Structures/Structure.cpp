#include "Structure.h"
#include "../../core/Scenes/GameScene.h"

Structure::Structure(Structure& plant):GameObject(plant),ItemsDrop(plant),DestroyAble(plant),RectangleCollider(plant)
{
	sprite = new SpriteController(*plant.sprite);
}


Structure::Structure(Rectangle pos,std::string name,ToolType tool,int hp,int power):
	Structure(pos,name,tool,hp,power,{0,0,pos.width,pos.height})
{
	std::string path = "Resource/Structure/" + name + ".png";
	sprite = new SpriteController(path.c_str());
}

Structure::Structure(Rectangle pos, std::string name, ToolType tool, int hp, int power,Rectangle collision) :
	GameObject(pos,name),ItemsDrop(),DestroyAble(tool,hp,power),RectangleCollider(collision)
{
	std::string path = "Resource/Structure/" + name + ".png";
	sprite = new SpriteController(path.c_str());
}

Structure::~Structure()
{
	delete sprite;
}

void Structure::update(float deltaTime)
{
	if(damageTime>0)
		damageTime -= deltaTime;
}

void Structure::draw()
{

	sprite->draw(animationPos());
}

void Structure::damageObject(int power, ToolType type)
{
	int h = hp;
	DestroyAble::damageObject(power, type);
	if (h != hp)
	{
		damageTime = damageTimeMax;
	}
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

void Structure::saveToJson(nlohmann::json& j)
{
	GameObject::saveToJson(j);
}

void Structure::readFromJson(nlohmann::json& j)
{
	GameObject::readFromJson(j);
}

void Structure::drawPlaceInterface(Vector2 pos)
{
	Rectangle col = getCollisionPos();
	float zoom = Game->getZoom();
	Rectangle drawPos = { pos.x,pos.y,col.width*zoom,col.height*zoom };
	drawViewFinder(drawPos);
}