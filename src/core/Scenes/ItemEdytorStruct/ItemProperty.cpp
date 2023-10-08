#include "ItemProperty.h"

std::string itemClassDescription()
{
	std::string s="";
	s += std::to_string((int)ItemClass::StackItem) + " - StackItem";
	s += "\n" + std::to_string((int)ItemClass::ToolItem) + " - ToolItem";
	s += "\n" + std::to_string((int)ItemClass::Bow) + " - Bow";
	s += "\n" + std::to_string((int)ItemClass::Ammo) + " - Ammo";

	return s;
}

ItemProperty::ItemProperty()
{
	clearData();
	update();
}

ItemProperty::ItemProperty(nlohmann::json& j,int ID)
{
	clearData();
	if (!j.contains("Name"))
	{
		printf("NIE MA DANYCH DLA ITEMU O ID %d\n", ID);
		return;
	}
	this->ID = ID;
	name=j["Name"];
	itemClass = j["ItemClass"];;
	pos.x = j["Pos"][0];
	pos.y = j["Pos"][1];
	pos.width = j["Pos"][2];
	pos.height = j["Pos"][3];
	if (j.contains("Animated"))
		animated = j["Animated"];
	else
		animated = false;
	if (j.contains("LineCollsionN"))
	{
		hasLinesCollider = true;
		nPoints = j["LineCollsionN"];
		sizePointsBefore = nPoints;
		points = new Vector2[nPoints];
		for (int i = 0; i < nPoints; i++)
		{
			points[i] = { 0,0 };
		}
		if (j.contains("Points"))
		{
			for (int i = 0; i < j["Points"].size(); i++)
			{

				points[i].x= j["Points"][i][0];
				points[i].y= j["Points"][i][1];

			}
		}

	}
	if (j.contains("StackSize"))
	{
		isStacable = true;
		stackSize = j["StackSize"];
	}
	if (j.contains("UseTime"))
	{
		isUsingItem = true;
		useTime = j["UseTime"];
	}
	if (j.contains("Damage") && j.contains("InvisibleFrame"))
	{
		isDealingDamage = true;
		damage = j["Damage"];
		invisibleFrame = j["InvisibleFrame"];
	}
	if (j.contains("Power") && j.contains("DestoryType"))
	{
		isDestoryAble = true;
		power = j["Power"];
		destroyType = j["DestoryType"];
	}
	if (j.contains("Range") && j.contains("Projectals") && j.contains("Speed"))
	{
		isRangeWeapon = true;

		projectalRange = j["Range"];
		numberOfProjectal = j["Projectals"];
		projectalSpeed = j["Speed"];
		if (j.contains("AmmoType"))
			ammoType = j["AmmoType"];
		else
			ammoType = 0;
	}
	update();
	reLoadTexture();
}

ItemProperty::~ItemProperty()
{
	if (sprite)
		delete sprite;
}
void ItemProperty::update()
{
	ItemClass item = (ItemClass)itemClass;
	hasLinesCollider = false;
	isStacable = false;
	isUsingItem = false;
	isDealingDamage = false;
	isDestoryAble = false;
	isRangeWeapon = false;
	switch (item)
	{
	case ItemClass::StackItem:
		isStacable = true;
		break;
	case ItemClass::ToolItem:
		hasLinesCollider = true;
		isUsingItem = true;
		isDealingDamage = true;
		isDestoryAble = true;
		break;
	case ItemClass::Bow:
		isUsingItem = true;
		isDealingDamage = true;
		isRangeWeapon = true;
		break;
	case ItemClass::Ammo:
		hasLinesCollider = true;
		isStacable = true;
		isDealingDamage = true;
		isRangeWeapon = true;
		break;
	case ItemClass::EnumSize:
		break;
	default:
		break;
	}
}
void ItemProperty::clearData()
{
	if (sprite)
		delete sprite;
	sprite = NULL;
	name = "";
	pos = { 0,0,0,0 };
	///Od kolizji obiektu
	hasLinesCollider = false;
	nPoints = 0;
	if (points)
		delete points;
	points = NULL;
	///Czy mo¿na stakowaæ przedmioty
	isStacable = false;
	stackSize = 0;
	///Czy item jest do u¿ywania
	isUsingItem = false;
	useTime = 0;
	///Czy item zadaje obrarzenia
	isDealingDamage = false;
	damage = 0;
	invisibleFrame = 0;
	///czy item niszczy bloki
	isDestoryAble = false;
	power = 0;
	destroyType = (int)ToolType::NON;
	///Czy jest broni¹ daleko zasiêgow¹
	isRangeWeapon = false;
	projectalRange = 0;
	numberOfProjectal = 0;
	projectalSpeed = 0;
}
void ItemProperty::updatePointsToCollisions()
{
	if (points)
	{
		
		if (nPoints <= 0)
		{
			delete points;
			points = NULL;
			sizePointsBefore = 0;
			nPoints = 0;
			return;
		}

		Vector2 *points = new Vector2[nPoints];
		int n = sizePointsBefore < nPoints ? sizePointsBefore : nPoints;
		for (int i = 0; i < n; i++)
		{
			points[i] = this->points[i];
		}
		for (int i = n; i < nPoints; i++)
		{
			points[i] = { 0,0 };
		}
		delete this->points;
		this->points = points;
		sizePointsBefore = nPoints;
	}
	else
	{
		if (nPoints <= 0)
			return;
		points = new Vector2[nPoints];
		for (int i = 0; i < nPoints; i++)
		{
			points[i] = { 0,0 };
		}
		sizePointsBefore = nPoints;
	}

}
void ItemProperty::addPointToCollisions()
{
	if (nPoints <= 0)
	{
		nPoints = 1;
		points = new Vector2[1];
		points[0] = { 0,0 };
	}
	else
	{
		nPoints++;
		Vector2* points = new Vector2[nPoints];
		for (int i = 0; i < nPoints - 1; i++)
			points[i] = this->points[i];
		points[nPoints - 1] = { 0,0 };
		delete this->points;
		this->points = points;
	}
	sizePointsBefore = nPoints;
}

void ItemProperty::removePointToCollisions()
{
	if (nPoints <= 0)
	{
		nPoints = 0;
		points = NULL;
		sizePointsBefore = nPoints;
	}
	else
	{
		nPoints--;
		sizePointsBefore = nPoints;
		if (nPoints <= 0)
		{
			delete points;
			points = NULL;
			return;
		}
		Vector2* points = new Vector2[nPoints];
		for (int i = 0; i < nPoints; i++)
			points[i] = this->points[i];
		delete this->points;
		this->points = points;
	}

}

void ItemProperty::saveToJson(nlohmann::json& j)
{

	j["Name"] = name;
	j["ItemClass"] = itemClass;
	j["Pos"] = { pos.x,pos.y,pos.width,pos.height };
	if (animated)
		j["Animated"] = true;

	if (hasLinesCollider)
	{
		j["LineCollsionN"] = nPoints;

		for (int i = 0; i < nPoints; i++)
		{
			j["Points"][i][0] = (float)((int)(points[i].x*100))/100.0f;
			j["Points"][i][1] = (float)((int)(points[i].y*100))/100.0f;
		}
	}
	if (isStacable)
	{
		j["StackSize"] = stackSize;
	}
	if (isUsingItem)
	{
		j["UseTime"] = useTime;
	}
	if (isDealingDamage)
	{
		j["Damage"] = damage;
		j["InvisibleFrame"] = invisibleFrame;
		j["CollisionsCheckType"] = CollisionsCheckType::All;
	}
	if (isDestoryAble)
	{
		j["Power"] = power;
		j["DestoryType"] = destroyType;
		j["CollisionsCheckType"] = CollisionsCheckType::All;
	}
	if (isRangeWeapon)
	{
		j["Range"] = projectalRange;
		j["Projectals"] = numberOfProjectal;
		j["Speed"] = projectalSpeed;
		j["AmmoType"] = ammoType;
		j["CollisionsCheckType"] = CollisionsCheckType::All;
	}
	
}

void ItemProperty::setDataFrom(ItemProperty& item)
{
	if (item.sprite)
		sprite = new SpriteController(*item.sprite);
	else
		sprite = NULL;
	animated = item.animated;
	frame = item.frame;
	ID = item.ID;
	itemClass = item.itemClass;
	name = item.name;
	pos = item.pos;
	///Od kolizji obiektu
	hasLinesCollider = item.hasLinesCollider;
	nPoints = item.nPoints;
	if (item.points)
	{
		if (points)
			delete points;
		sizePointsBefore = nPoints;
		points = new Vector2[nPoints];
		for (int i = 0; i < nPoints; i++)
		{
			points[i] = item.points[i];
		}
	}
	///Czy mo¿na stakowaæ przedmioty
	isStacable = item.isStacable;
	stackSize = item.stackSize;
	///Czy item jest do u¿ywania
	isUsingItem = item.isUsingItem;
	useTime = item.useTime;
	///Czy item zadaje obrarzenia
	isDealingDamage = item.isDealingDamage;
	damage = item.damage;
	invisibleFrame = item.invisibleFrame;
	///czy item niszczy bloki
	isDestoryAble = item.isDestoryAble;
	power = item.power;
	destroyType = item.destroyType;
	///Czy jest broni¹ daleko zasiêgow¹
	isRangeWeapon = item.isRangeWeapon;
	projectalRange = item.projectalRange;
	numberOfProjectal = item.numberOfProjectal;
	projectalSpeed = item.projectalSpeed;
}

void ItemProperty::reLoadTexture()
{
	if (sprite)
	{
		delete sprite;
		sprite = NULL;
	}
	std::string path = "Resource/Items/" + name + ".png";
	sprite = new SpriteController(path.c_str());
	if (!sprite->isLoaded())
	{
		delete sprite;
		sprite = NULL;
	}

}

void ItemProperty::draw(Rectangle pos)
{
	DrawRectangleRec(pos, WHITE);
	DrawRectangleLinesEx(pos, 2, BLACK);
	if (sprite && sprite->isLoaded())
	{
		if (animated)
			sprite->draw(pos, frame);
		else
			sprite->draw(pos);
	}
	DrawTextWithOutline(TextFormat("%d\n",ID), pos.x, pos.y, textStandardSize, WHITE, BLACK);
		
}

bool ItemProperty::checkTexture()
{
	if (sprite)
	{
		std::string path = "Resource/Items/" + name + ".png"; 
		return sprite->comparePath(path);
	}
	return false;
}