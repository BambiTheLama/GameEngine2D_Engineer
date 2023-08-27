#include "Projectal.h"
#include <iostream>
#include "../../core/Scenes/GameScene.h"

Projectal::Projectal(Projectal& obj):GameObject(obj),LinesCollider(obj)
{
	this->rotation = obj.rotation;
	this->range = obj.range;
	this->speed = obj.speed;

	delta = deltaFromDegree(rotation, speed);
	sprite = new SpriteController(*obj.sprite);
}

Projectal::Projectal(Rectangle pos, float speed, float rotation, float range,
	SpriteController* sprite, Vector2 *collision,int n, CollisionsCheckType collisionType)
	:GameObject(pos,""),LinesCollider(collisionType)
{
	this->rotation = rotation;
	this->range = range;
	this->speed = speed;

	delta = deltaFromDegree(rotation,speed);
	this->sprite = new SpriteController(*sprite);
	addLines(n, collision);
}

Projectal::~Projectal()
{
	if (sprite != NULL)
		delete sprite;
}

void Projectal::update(float deltaTime)
{
	//pos.x += delta.x * 64.0f * deltaTime;
	//pos.y += delta.y * 64.0f * deltaTime;
	//range -= speed * 64.0f * deltaTime;
	rotation+=deltaTime*36;
	if (IsKeyDown(KEY_TWO))
		rotation = 0;
	if (range <= 0)
	{
		Game->deleteObject(this);
	}
	else
	{
		Game->updatePos(this);
		LinesCollider::updateRotation(rotation, { pos.x ,pos.y }, { pos.x - pos.width / 2,pos.y - pos.height / 2 });
		LinesCollider::update(deltaTime);
	}

}

void Projectal::draw()
{
	Vector2 origin = { pos.width / 2,pos.height / 2 };
	Rectangle pos = getPos();
	DrawRectangleRec(pos, RED);
	pos.x -= pos.width / 2;
	pos.y -= pos.height / 2;
	DrawRectangleRec(pos, YELLOW);
	pos = getPos();
	DrawTexturePro(sprite->getTexture(), sprite->getTextureSize(), pos, origin, rotation, WHITE);
	LinesCollider::draw();
}

void Projectal::onCollisionHitable(HitAble* hit)
{
	hit->dealDamage(3, 0.1f);

}
void Projectal::onCollisionDestroyAble(DestroyAble* dest)
{
	dest->damageObject(0, ToolType::NON);
	if (dest->isToolGoBack())
		Game->deleteObject(this);

}