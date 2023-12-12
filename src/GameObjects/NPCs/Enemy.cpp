#include "Enemy.h"
#include "../../core/Scenes/GameScene.h"
Enemy::Enemy(Enemy& e):GameObject(e), RectangleCollider(e),HitAble(e)
{

}
Enemy::Enemy():Enemy({1000,1000,64,64},{0,16,64,48},"DUMY")
{

}
Enemy::Enemy(Rectangle pos, Rectangle colliderBox,std::string name):GameObject(pos,name),RectangleCollider(colliderBox),HitAble(69)
{

}

Enemy::~Enemy()
{

}

void Enemy::update(float deltaTime)
{
	HitAble::update(deltaTime);
}

void Enemy::draw()
{
	Rectangle pos = getPos();
	DrawRectangleRec(pos, BLUE);
	RectangleCollider::draw(this);
	pos.y += pos.height + 10;
	pos.height = 10;
	HitAble::draw(pos);
}

bool Enemy::dealDamage(float damage, float invisibileFrame)
{
	if (!HitAble::dealDamage(damage, invisibileFrame))
	{
		return false;
	}
	if (isObjectDead())
		Game->deleteObject(this);
	return true;
}
void Enemy::saveToJson(nlohmann::json& j)
{
	GameObject::saveToJson(j);
	HitAble::saveToJson(j);

}

void Enemy::readFromJson(nlohmann::json& j)
{
	GameObject::readFromJson(j);
	HitAble::readFromJson(j);
	
}