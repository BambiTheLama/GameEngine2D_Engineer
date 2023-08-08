#include "Enemy.h"
#include "../../core/Scenes/GameScene.h"
Enemy::Enemy(Enemy& e):GameObject(e),Collider(e),HitAble(e)
{

}
Enemy::Enemy():Enemy({3200,3200,64,64},{0,16,64,48},"DUMY")
{

}
Enemy::Enemy(Rectangle pos, Rectangle colliderBox,std::string name):GameObject(pos,name),Collider(colliderBox),HitAble(69)
{

}

Enemy::~Enemy()
{

}

void Enemy::update()
{
	HitAble::update();
}

void Enemy::draw()
{
	Rectangle pos = getPos();
	DrawRectangleRec(pos, BLUE);
	Collider::draw(this);
	pos.y += pos.height + 10;
	pos.height = 10;
	HitAble::draw(pos);
}

bool Enemy::dealDamage(int damage, int invisibileFrame)
{
	if (!HitAble::dealDamage(damage, invisibileFrame))
	{
		return false;
	}
	if (isObjectDead())
		Game->deleteObject(this);
	return true;
}

Rectangle Enemy::getCollisionPos()
{
	return Collider::getCollisionPos(this);
}