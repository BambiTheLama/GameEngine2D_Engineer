#include "Enemy.h"
#include "../../core/Scenes/GameScene.h"
Enemy::Enemy(Enemy& e):GameObject(e), RectangleCollider(e),HitAble(e)
{
	body = new CharacterBody(*e.body);
}
Enemy::Enemy():Enemy({1000,1000,48,80},{0,0,32,32},"DUMY")
{
	Rectangle pos = getPos();

}
Enemy::Enemy(Rectangle pos, Rectangle colliderBox,std::string name):GameObject(pos,name),RectangleCollider(colliderBox),HitAble(69)
{
	body = new CharacterBody("Resource/Character/Character_1/", pos.width, pos.width);
}

Enemy::~Enemy()
{
	delete path;
	delete body;
	delete item;
}

void Enemy::start()
{
	Game->addUserUI(this);
	path = new PathFinding(0, 0, range, range, pos.width, pos.height, 0, 0);
	item = Items->getObject(10);
	item->addItemToHand(this);
	Rectangle pos = getPos();

}

void Enemy::onDestory()
{
	Game->removeUserUI(this);
}

void Enemy::update(float deltaTime)
{


	HitAble::update(deltaTime);
	findPath();


	Rectangle pos = getPos();

	move(deltaTime);
	bodyUpdate(deltaTime);
	itemUpdate(deltaTime);

}
void Enemy::move(float deltaTime)
{
	Rectangle pos = getPos();
	Vector2 moveVector = getMoveVector();
	Vector2 newPos = { (pos.x + moveVector.x * deltaTime * speed),(pos.y + moveVector.y * deltaTime * speed) };

	setMovePos(newPos);
	Game->updatePos(this);
	if (isCollidingWithSomething())
		setMovePos({ pos.x,pos.y });
}
void Enemy::itemUpdate(float deltaTime)
{
	if (!item)
		return;
	Vector2 cursorPos = { pos.x + pos.width / 2,pos.y + pos.height / 2 };
	if (body)
		cursorPos = body->getHandPos();
	item->setMovePos(cursorPos);
	Rectangle targetPos = {};
	if (target)
		targetPos = target->getPos();
	Vector2 targerPoint = { targetPos.x + targetPos.width / 2,targetPos.y + targetPos.height };
	item->update(deltaTime, targerPoint);
	float dis = getDistanceToTarget();
	if (dis >= 0 && dis < 50)
		item->use(deltaTime, targerPoint);
}
void Enemy::bodyUpdate(float deltaTime)
{
	Rectangle pos = getPos();
	Vector2 moveVector = getMoveVector();
	Rectangle targetPos = {};
	if (moveVector.y != 0 || moveVector.x != 0)
	{
		if (moveVector.y > 0)
			body->updateCharacterSide(CharacterSide::Down);
		else if (moveVector.y < 0)
			body->updateCharacterSide(CharacterSide::Up);
		else if (moveVector.x > 0)
			body->updateCharacterSide(CharacterSide::Right);
		else if (moveVector.x < 0)
			body->updateCharacterSide(CharacterSide::Left);
		body->updateCharacterState(CharacterState::Run);
	}
	else
		body->updateCharacterState(CharacterState::Ide);


	if (target)
		targetPos = target->getPos();
	Vector2 targerPoint = { targetPos.x + targetPos.width / 2,targetPos.y + targetPos.height };
	body->update(deltaTime, targerPoint, pos);
}

void Enemy::findPath()
{
	target = NULL;
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
			target = o;
		}
		if (!o->isColliding())
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
	body->draw(pos);
	pos.y += pos.height + 10;
	pos.height = 10;
	HitAble::draw(pos);

	item->draw();

	if (collidersToDraw)
		RectangleCollider::draw(this);
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


float Enemy::getDistanceToTarget()
{
	if (!target)
		return -1;
	Rectangle targetPos = target->getPos();
	Rectangle pos = getPos();
	Vector2 p1 = { targetPos.x + targetPos.width / 2,targetPos.y + targetPos.height / 2 };
	Vector2 p2;
	if (body)
		p2 = body->getHandPos();
	else
		p2 = { pos.x + pos.width / 2,pos.y + pos.height / 2 };
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}