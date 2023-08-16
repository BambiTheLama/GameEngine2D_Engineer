#include "ItemProperty.h"

ItemProperty::ItemProperty()
{

}

ItemProperty::ItemProperty(nlohmann::json& j, int ID)
{
	clearData();
	this->ID = ID;
	name=j[ID]["Name"];
	pos.x = j[ID]["Pos"][0];
	pos.y = j[ID]["Pos"][1];
	pos.width = j[ID]["Pos"][2];
	pos.height = j[ID]["Pos"][3];
	type = j[ID]["Type"];
	if (j[ID].contains("LineCollsionN"))
	{
		hasLinesCollider = true;
		nPoints = j[ID]["LineCollsionN"];
		points = new Vector2[nPoints];
		std::string s= "Point0";
		for(int i=0;i<nPoints;i++)
		{
			s = "Point" + std::to_string(i);
			if (j[ID].contains(s))
			{
				points[i].x = j[ID][s][0];
				points[i].y = j[ID][s][1];
			}
		}
	}
	if (j[ID].contains("StackSize"))
	{
		isStacable = true;
		stackSize = j[ID]["StackSize"];
	}
	if (j[ID].contains("UseTime"))
	{
		isUsingItem = true;
		useTime = j[ID]["UseTime"];
	}
	if (j[ID].contains("Damage") && j[ID].contains("InvisibleFrame"))
	{
		isDealingDamage = true;
		damage = j[ID]["Damage"];
		invisibleFrame = j[ID]["InvisibleFrame"];
	}
	if (j[ID].contains("Power") && j[ID].contains("DestoryType"))
	{
		isDestoryAble = true;
		power = j[ID]["Power"];
		destroyType = j[ID]["DestoryType"];
	}
	if (j[ID].contains("Range") && j[ID].contains("Projectals") && j[ID].contains("Speed"))
	{
		isRangeWeapon = true;

		projectalRange = j[ID]["Range"];
		numberOfProjectal = j[ID]["Projectals"];
		projectalSpeed = j[ID]["Speed"];
	}

}

ItemProperty::~ItemProperty()
{
	if (sprite != NULL)
		delete sprite;
}

void ItemProperty::clearData()
{

	sprite = NULL;
	name = "";
	pos = { 0,0,0,0 };

	type = ItemType::Normal;
	///Od kolizji obiektu
	hasLinesCollider = false;
	nPoints = 0;
	if (points != NULL)
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
	destroyType = ToolType::NON;
	///Czy jest broni¹ daleko zasiêgow¹
	isRangeWeapon = false;
	projectalRange = 0;
	numberOfProjectal = 0;
	projectalSpeed = 0;
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
}

void ItemProperty::removePointToCollisions()
{
	if (nPoints <= 0)
	{
		nPoints = 0;
		points = NULL;
	}
	else
	{
		nPoints--;
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
	j[ID]["Name"] = name;
	j[ID]["Pos"] = { pos.x,pos.y,pos.width,pos.height };
	j[ID]["Type"] = type;
	if (hasLinesCollider)
	{
		j[ID]["LineCollsionN"] = nPoints;
		for (int i = 0; i < nPoints; i++)
			j[ID]["Point" + std::to_string(i)] = { points[i].x,points[i].y };
	}
	if (isStacable)
	{
		j[ID]["StackSize"] = stackSize;
	}
	if (isUsingItem)
	{
		j[ID]["UseTime"] = useTime;
	}
	if (isDealingDamage)
	{
		j[ID]["Damage"] = damage;
		j[ID]["InvisibleFrame"] = invisibleFrame;
	}
	if (isDestoryAble)
	{
		j[ID]["Power"] = power;
		j[ID]["DestoryType"] = destroyType;
	}
	if (isRangeWeapon)
	{
		j[ID]["Range"] = projectalRange;
		j[ID]["Projectals"] = numberOfProjectal;
		j[ID]["Speed"] = projectalSpeed;
	}
}

void ItemProperty::setDataFrom(ItemProperty item)
{
	ID = item.ID;
	name = item.name;
	pos = item.pos;
	type = item.type;
	///Od kolizji obiektu
	hasLinesCollider = item.hasLinesCollider;
	nPoints = item.nPoints;
	if (item.points != NULL)
	{
		points = new Vector2[nPoints];
		for (int i = 0; i < nPoints; i++)
			points[i] = item.points[i];
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
	if (sprite != NULL)
	{
		delete sprite;
	}
	std::string path = "Resource/Items/" + name + ".png";
	sprite = new SpriteController(path.c_str());
}