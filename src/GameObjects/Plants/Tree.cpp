#include "Tree.h"
#include "../../core/Scenes/GameScene.h"
#include "../Particles/ParticleSystem.h"
Tree::Tree(Tree& tree) :Plant(tree), Collider(tree)
{
	age = tree.age;
	maxAge = tree.maxAge;
}

Tree::Tree(Rectangle pos, std::string name) :Plant(pos, name,ToolType::Axe,10,10),
Collider({ 24.0f / 64 * pos.width,48.0f / 64 * pos.height,16.0f / 64 * pos.width,15.0f / 64 * pos.height })
{
	maxAge = sprite->getHowMuchFrames()-1;
	addItemToDrop(0, 100, 1, 2);
	itemToolRequest = ToolType::Axe;

}

Tree::~Tree() 
{
}

void Tree::start()
{
	//printf("DODAJE DRZEWO %lf %lf\n", pos.x, pos.y);
}

void Tree::incrementAge()
{
	if (age >= maxAge)
	{
		age = maxAge;
		return;
	}
	age++;
	addItemToDrop(0, 100, 4, 6);
	//printf("ROSNÊ %lf %lf\n", pos.x, pos.y);

}

void Tree::update()
{
	if (timer > 0 && age<maxAge)
	{
		timer--;
		if (timer <= 0)
		{
			incrementAge();
			timer = 60;
		}
	}
}

void Tree::draw()
{
	sprite->draw(getPos(), age);
	if (collidersToDraw)
	{
		Collider::draw(this);
	}


}
void Tree::setMovePos(Vector2 movePos)
{ 
	Rectangle collider = getCollisionPos();
	GameObject::setMovePos({ movePos.x + collider.x,movePos.y + collider.y });

}

void Tree::damageObject(int power, ToolType type)
{
	int h = hp;
	DestroyAble::damageObject(power, type);
	if (h != hp)
	{
		Rectangle pos = getCollisionPos();
		Particle* particle=new Particle({0,0,5,5},40,{2,4},{77,26,1,255},{255,170,30,0});
		ParticleSystem* particleSystem = new ParticleSystem(pos, "", particle, 10);
		particleSystem->setTime(30, 60);
		particleSystem->setVelosity({ -1,-1 }, { 1,1 });
		Game->addObject(particleSystem);
	}
	if (hp > 0)
	{
		return;
	}

	Rectangle pos = getCollisionPos();
	std::vector<Item*> items = getDrop();
	for (Item* i : items)
	{
		i->addToPos({ pos.x, pos.y });
		Game->addObject(i);
	}
	Game->deleteObject(this);
}