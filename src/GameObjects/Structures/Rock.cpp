#include "Rock.h"
#include "../Particles/ParticleSystem.h"
#include "../../core/Scenes/GameScene.h"
Rock::Rock(Rock& rock) :Structure(rock)
{
	rockID = rock.rockID;
}
Rock::Rock(Rectangle pos, std::string name, int rockID):Structure(pos,name,ToolType::Pickaxe,10,10,{pos.width/8,pos.height/2,pos.width-pos.width/4,pos.height/2})
{
	this->rockID = rockID;
}

Rock::~Rock()
{

}

void Rock::start()
{

}

void Rock::update(float deltaTime)
{

}

void Rock::draw()
{
	sprite->draw(GameObject::getPos());
	if (collidersToDraw)
	{
		RectangleCollider::draw(this);
		DrawText(TextFormat("%d %d", chunkX, chunkY), getPos().x, getPos().y, 20, BLACK);
	}
}

void Rock::setMovePos(Vector2 movePos)
{
	Rectangle collider = RectangleCollider::getCollisionPos();
	GameObject::setMovePos({ movePos.x - collider.x,movePos.y - collider.y });
}

void Rock::damageObject(int power, ToolType type)
{

	int h = hp;
	DestroyAble::damageObject(power, type);
	Rectangle collider = RectangleCollider::getCollisionPos();
	Rectangle pos = GameObject::getPos();
	collider.x += pos.x;
	collider.y += pos.y;
	if (h != hp)
	{
		float velosity = 1.69;
		Particle* particle = new Particle({ 0,0,5,5 }, 1, { 2,4 }, { 20,20,20,255 }, { 69,69,69,0 });
		ParticleSystem* particleSystem = new ParticleSystem(collider, "", particle, 10);
		particleSystem->setTime(0.25f, 0.75f);
		particleSystem->setVelosity({ -velosity,-velosity }, { velosity,velosity });
		Game->addObject(particleSystem);
		clearItemsDrop();
		addItemToDrop(rockID, 5, h - hp, h - hp);
		spawnItem({ collider.x+collider.width/2,collider.y + collider.width / 2 });
	}
	if (hp > 0)
	{
		return;
	}
	clearItemsDrop();
	addItemToDrop(rockID, 100, 2, 3);
	spawnItem({ collider.x + collider.width / 2,collider.y + collider.width / 2 });
	Game->deleteObject(this);
}
void Rock::spawnItem(Vector2 pos)
{
	std::vector<Item*> items = getDrop();
	for (Item* i : items)
	{
		i->addToPos({ pos.x, pos.y });
		Game->addObject(i);
	}
}

void Rock::saveToJson(nlohmann::json& j)
{
	Structure::saveToJson(j);
}

void Rock::readFromJson(nlohmann::json& j)
{
	Structure::readFromJson(j);
}