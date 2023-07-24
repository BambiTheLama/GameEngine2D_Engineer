#include "Tree.h"

Tree::Tree(Tree& tree) :Plant(tree), Collider(tree)
{
	age = tree.age;
	maxAge = tree.maxAge;
}

Tree::Tree(Rectangle pos, std::string name) :Plant(pos, name), Collider({22.0f / 64 * pos.width,48.0f / 64 * pos.height,20.0f / 64 * pos.width,15.0f / 64 * pos.height })
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