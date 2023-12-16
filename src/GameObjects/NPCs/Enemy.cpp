#include "Enemy.h"
#include "../../core/Scenes/GameScene.h"
Enemy::Enemy(Enemy& e):GameObject(e), RectangleCollider(e),HitAble(e)
{

}
Enemy::Enemy():Enemy({1000,1000,64,64},{0,16,64,48},"DUMY")
{
	path = new PathFinding(0, 0, range, range, 64, 64, 0, 0);

}
Enemy::Enemy(Rectangle pos, Rectangle colliderBox,std::string name):GameObject(pos,name),RectangleCollider(colliderBox),HitAble(69)
{

}

Enemy::~Enemy()
{
	delete path;
}

void Enemy::start()
{
	Game->addUserUI(this);
}

void Enemy::onDestory()
{
	Game->removeUserUI(this);
}

void Enemy::update(float deltaTime)
{
	if (deltaTime > 0.03)
		deltaTime = 0.03;
	HitAble::update(deltaTime);
	findPath();
	Rectangle pos = getPos();
	Vector2 moveVector = getMoveVector();

	Vector2 newPos = { pos.x + moveVector.x * deltaTime * speed,pos.y + moveVector.y * deltaTime * speed };


	setMovePos(newPos);
	Game->updatePos(this);
	if (isCollidingWithSomething())
		setMovePos({ pos.x,pos.y });

}

void Enemy::findPath()
{
	Rectangle pos = getPos();
	path->clearData();
	path->setNewPos(pos.x, pos.y);
	path->setNewEnd(Vector2{ pos.x, pos.y });
	Rectangle rangePos = { pos.x - range / 2,pos.y - range / 2,range + pos.width,range + pos.height };
	std::list<GameObject*> objescts = Game->getObjects(rangePos, ObjectToGet::getNoBlocks);
	for (auto o : objescts)
	{
		if (o->getType() == ObjectType::Player)
		{
			path->setNewEnd(o->getPos());
		}
		if (o->getType() != ObjectType::Structure)
			continue;
		Collider* c = dynamic_cast<Collider*>(o);
		if (!c)
			continue;

		Rectangle colPos = c->getCollisionPos();
		Rectangle pos = o->getPos();
		colPos.x += pos.x;
		colPos.y += pos.y;
		path->setWall(colPos);
	}
	path->findPath();
}

Vector2 Enemy::getMoveVector()
{
	if (path->isFindthPath())
		return path->getMoveVector();
	return { 0,0 };
}

void Enemy::draw()
{
	Rectangle pos = getPos();
	DrawRectangleRec(pos, BLUE);
	RectangleCollider::draw(this);
	pos.y += pos.height + 10;
	pos.height = 10;
	HitAble::draw(pos);
	//path->draw();
}

void Enemy::drawInterface()
{
	if (PathFindingShow)
		path->draw(Game->worldToScreanPos(path->getPos()), Game->getZoom());
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