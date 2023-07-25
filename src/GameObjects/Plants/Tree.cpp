#include "Tree.h"
#include "../../core/Scenes/GameScene.h"
Tree::Tree(Tree& tree) :Plant(tree), Collider(tree)
{
	age = tree.age;
	maxAge = tree.maxAge;
}

Tree::Tree(Rectangle pos, std::string name) :Plant(pos, name,ToolType::Axe,10,10),
Collider({ 24.0f / 64 * pos.width,48.0f / 64 * pos.height,16.0f / 64 * pos.width,15.0f / 64 * pos.height })
{
	maxAge = sprite->howMuchFrames()-1;
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
	if (IsKeyDown(KEY_TAB))
		Collider::draw(this);
}
void Tree::setMovePos(Vector2 movePos)
{ 
	Rectangle collider = getCollisionPos();
	GameObject::setMovePos({ movePos.x + collider.x,movePos.y + collider.y });

}

void Tree::damageObject(int power, ToolType type)
{
	DestroyAble::damageObject(power, type);
	if (hp > 0)
		return;
	Rectangle pos = getCollisionPos(this);
	std::vector<Item*> items = getDrop();
	for (Item* i : items)
	{
		i->addToPos({ pos.x, pos.y });
		Game->addObject(i);
	}
	Game->deleteObject(this);
}