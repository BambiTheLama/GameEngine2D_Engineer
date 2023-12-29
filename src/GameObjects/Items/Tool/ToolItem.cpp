#include "ToolItem.h"
#include "../../AddisionalTypes/AllTypes.h"
#include "../../BlockFactory.h"
#include "../../Blocks/Block.h"
std::string ToolItem::description = "";

ToolItem::ToolItem(ToolItem& item) :Item(item),LinesCollider(item)
{
	sprite = new SpriteController(*item.sprite);
	this->useTimeMax=item.useTimeMax;
	useTime = 0;
	this->destroyType = item.destroyType;
	this->damage = item.damage;
	this->origin = item.origin;
	this->power = item.power;
}

ToolItem::ToolItem(nlohmann::json j):Item(j),LinesCollider(j)
{

	std::string path = "Resource/Items/" + std::string(j["Name"]) + ".png";
	sprite = new SpriteController(path.c_str());
	useTime = 0;
	origin = { 0,pos.width };
	if (j.contains("UseTime"))
		useTimeMax = j["UseTime"];
	else
		useTimeMax = 0.5;
	if (j.contains("Damage"))
		damage = j["Damage"];
	else
		damage = 1;

	if (j.contains("Power"))
		power = j["Power"];
	else
		power = 30;
	if (j.contains("DestoryType"))
		destroyType = (ToolType)j["DestoryType"];
	else
		destroyType = ToolType::NON;	
}

ToolItem::~ToolItem()
{
	delete sprite;
}

void ToolItem::update(float deltaTime, Vector2 cursorPos)
{
	this->cursorPos = cursorPos;
	if (useTime > 0)
	{
		useTime -= deltaTime;
		if (useTime <= 0)
			isUsing = false;
	}
	if (!isUsing)
	{
		GameObject* o = getHittingObject(cursorPos);
		if (!o)
			hittingObjectPos = { 0,0,-10,-10 };
		return;
	}


	Rectangle pos = getPos();

	if (leftSide)
	{
		origin.x = pos.width;
		rotation -= deltaTime / useTimeMax * rotationAngle;
	}
	else
	{
		origin.x = 0;
		rotation += deltaTime / useTimeMax * rotationAngle;
	}

	LinesCollider::updateRotation(rotation, { 0,  0 }, { 0,-pos.height }, !leftSide);

	LinesCollider::update(deltaTime, holdingObj, { pos.width ,pos.height  });
}

void ToolItem::update(float deltaTime)
{
	update(deltaTime, Game->getCursorPos());
}



bool ToolItem::use(float deltaTime,Vector2 cursorPos)
{
	if (useTime>0)
		return false;
	isUsing = true;
	useTime = useTimeMax;
	//leftSide = false;
	rotation = cursorTarget({ pos.x,pos.y }, cursorPos);
	if (leftSide)
		rotation += 180;
	else
		rotation -= 180;
	GameObject* o = getHittingObject(cursorPos,true);

	return true;
}
void ToolItem::draw()
{
	if (!inHand)
	{
		sprite->draw(getPos(), 0);
		return;
	}
	if (useTime <= 0)
	{
		return;
	}
	Rectangle textureSize = sprite->getTextureSize();
	Rectangle pos = getPos();


	if (leftSide)
		textureSize.width = -textureSize.width;

	DrawTexturePro(sprite->getTexture(), textureSize, pos, origin, rotation, WHITE);
	if (collidersToDraw)
		LinesCollider::draw(this);
	

}

void ToolItem::drawInterface()
{
	Rectangle pos = hittingObjectPos;
	Vector2 toScrean = Game->worldToScreanPos({ pos.x,pos.y });
	pos.x = toScrean.x;
	pos.y = toScrean.y;
	pos.width *= Game->getZoom();
	pos.height *= Game->getZoom();
	drawViewFinder(pos);
}
GameObject* ToolItem::getHittingObject(Vector2 cursor,bool isDestory)
{
	Rectangle cursorPos = { cursor.x,cursor.y,1,1 };
	std::list<GameObject*> objs = Game->getObjects(cursorPos, ObjectToGet::getNoBlocks);
	for (auto o : objs)
	{
		if (o->getType() != ObjectType::Structure)
			continue;
		Collider* c = dynamic_cast<Collider*>(o);
		if (!c)
			continue;
		Rectangle pos = o->getPos();
		Rectangle colPos = c->getCollisionPos();
		colPos.x += pos.x;
		colPos.y += pos.y;
		if (!CheckCollisionRecs(cursorPos, colPos))
			continue;
		DestroyAble* d = dynamic_cast<DestroyAble*>(o);
		if (!d)
			continue;
		if (!d->isDestoryAbleBy(destroyType))
			continue;
		hittingObjectPos = c->getCollisionPos();

		hittingObjectPos.x += pos.x;
		hittingObjectPos.y += pos.y;
		if(isDestory)
			d->damageObject(power, destroyType);
		return o;
	}
	objs = Game->getObjects(cursorPos, ObjectToGet::getBlocks);
	for (auto o : objs)
	{
		if (!CheckCollisionRecs(cursorPos, o->getPos()))
			continue;
		DestroyAble* d = dynamic_cast<DestroyAble*>(o);
		if (!d)
			continue;

		if (d->isDestoryAbleBy(destroyType))
		{
			hittingObjectPos = o->getPos();
			if (isDestory)
			{
				d->damageObject(power, destroyType);
				if (d->getHp() <= 0)
				{

					Block* b = Blocks->getObject((int)BlockID::Hole);
					if (b)
					{
						b->setMovePos({ hittingObjectPos.x,hittingObjectPos.y });
						if (!Game->addBlock(b))
							delete b;
					}


				}
			}
			return o;
		}


	}
	return NULL;
}

void ToolItem::addItemToHand(GameObject* holdingObj)
{
	Item::addItemToHand(holdingObj);
	addObjToIgnore(holdingObj);
}

void ToolItem::drawAt(Rectangle pos)
{
	DrawTexturePro(sprite->getTexture(), sprite->getTextureSize(), pos, { 0,0 }, 0, WHITE);
	DrawRectangle(pos.x, pos.y, pos.width, pos.height*useTime/useTimeMax, { 159,159,159,159 });
}
std::string ToolItem::getDesctription()
{
	return std::string(TextFormat(description.c_str(), getName().c_str(), damage, power, useTimeMax));
}

void ToolItem::onCollisionHitable(HitAble* hit)
{
	hit->dealDamage(damage, invisibleFrame);
}
void ToolItem::onCollisionDestroyAble(DestroyAble* dest)
{

}