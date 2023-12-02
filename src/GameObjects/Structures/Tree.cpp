#include "Tree.h"
#include "../../core/Scenes/GameScene.h"
#include "../Particles/ParticleSystem.h"
Tree::Tree(Tree& tree) :Structure(tree)
{
	age = tree.age;
	maxAge = tree.maxAge;
	updateDropFromAge();
	woodID = tree.woodID;
	saplingID = tree.saplingID;
}

Tree::Tree(Rectangle pos, std::string name, int woodID, int saplingID) :
	Structure(pos, name,ToolType::Axe,10,10, { 24.0f / 64 * pos.width,48.0f / 64 * pos.height,
		16.0f / 64 * pos.width,15.0f / 64 * pos.height })

{
	maxAge = sprite->getHowMuchFrames()-1;
	addItemToDrop(0, 100, 1, 2);
	updateDropFromAge();
	this->woodID = woodID;
	this->saplingID = saplingID;

}
Tree::Tree(nlohmann::json& j)
	:Structure(j)
{
	age = j["Age"][0];
	maxAge = j["Age"][1];
	timer = j["Timer"];
	updateDropFromAge();
}

Tree::~Tree() 
{
}

void Tree::start()
{

}

void Tree::incrementAge()
{
	if (age >= maxAge)
	{
		age = maxAge;
		return;
	}
	age++;
	updateDropFromAge();

}

void Tree::update(float deltaTime)
{
	if (timer > 0 && age<maxAge)
	{
		timer-=deltaTime;
		if (timer <= 0)
		{
			incrementAge();
			timer = 60;
		}
	}
}

void Tree::updateDropFromAge()
{
	clearItemsDrop();
	if (age == 0)
	{
		addItemToDrop(woodID, 100, 1, 1);
		addItemToDrop(saplingID, 5, 0, 1);
	}
	else if (age == 1)
	{
		addItemToDrop(woodID, 100, 2, 4);
		addItemToDrop(saplingID, 80, 1, 1);
	}
	else if (age == 2)
	{
		addItemToDrop(woodID, 100, 5, 8);
		addItemToDrop(saplingID, 100, 1, 1);
		addItemToDrop(saplingID, 50, 1, 1);
	}

}

void Tree::draw()
{
	sprite->draw(GameObject::getPos(), age);
	if (collidersToDraw)
	{
		RectangleCollider::draw(this);
	}


}
void Tree::setMovePos(Vector2 movePos)
{ 
	Rectangle collider = RectangleCollider::getCollisionPos();
	GameObject::setMovePos({ movePos.x - collider.x,movePos.y - collider.y });
}

void Tree::damageObject(int power, ToolType type)
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
		Particle* particle=new Particle({0,0,5,5},1,{2,4},{77,26,1,255},{255,170,30,0});
		ParticleSystem* particleSystem = new ParticleSystem(collider, "", particle, 10);
		particleSystem->setTime(0.25f, 0.75f);
		particleSystem->setVelosity({ -velosity,-velosity }, { velosity,velosity });
		Game->addObject(particleSystem);
	}
	if (hp > 0)
	{
		return;
	}
	std::vector<Item*> items = getDrop();
	for (Item* i : items)
	{
		i->addToPos({ collider.x, collider.y });
		Game->addObject(i);
	}
	Game->deleteObject(this);
}

void Tree::saveToJson(nlohmann::json& j)
{
	Structure::saveToJson(j);
	j["Age"][0] = age;
	j["Age"][1] = maxAge;
	j["Timer"] = (int)timer;
}

void Tree::readFromJson(nlohmann::json& j)
{
	Structure::readFromJson(j);
	age = j["Age"][0];
	maxAge = j["Age"][1];
	timer = j["Timer"];
	updateDropFromAge();
}