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
	SpriteController* sprite, Vector2 collision[4], CollisionsCheckType collisionType)
	:GameObject(pos,""),LinesCollider(collisionType)
{
	this->rotation = rotation;
	this->range = range;
	this->speed = speed;

	delta = deltaFromDegree(rotation,speed);
	this->sprite = new SpriteController(*sprite);
	addLines(4, collision);
}

Projectal::~Projectal()
{
	if (sprite != NULL)
		delete sprite;
}

void Projectal::update()
{
	pos.x += delta.x;
	pos.y += delta.y;
	range -= speed;
	float k = ((rotation) * (PI / 180.0f));

	if (range <= 0)
	{
		Game->deleteObject(this);
	}
	else
	{
		Game->updatePos(this);
		LinesCollider::updateRotation(k, { pos.x ,pos.y }, { pos.x - pos.width / 2,pos.y - pos.height / 2 });
		LinesCollider::update();
	}

}

void Projectal::draw()
{
	Vector2 origin = { pos.width / 2,pos.height / 2 };
	DrawTexturePro(sprite->getTexture(), sprite->getTextureSize(), pos, origin, rotation-45, WHITE);
	LinesCollider::draw();
}

void Projectal::onCollisionHitable(HitAble* hit)
{
	hit->dealDamage(3, 5);

}
void Projectal::onCollisionDestroyAble(DestroyAble* dest)
{
	dest->damageObject(0, ToolType::NON);
	if (dest->isToolGoBack())
		Game->deleteObject(this);

}