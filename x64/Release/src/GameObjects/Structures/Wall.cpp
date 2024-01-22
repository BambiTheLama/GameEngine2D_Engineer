#include "Wall.h"
#include "../../core/Scenes/GameScene.h"
Wall::Wall(Wall& obj):Structure(obj)
{
}

Wall::Wall(Rectangle pos, std::string name, ToolType tool, int hp, int power)
	:Structure(pos, name, tool, hp, power)
{

}

Wall::~Wall()
{

}
void Wall::start()
{
	generateTexturePos();
	std::list<GameObject*> objects = Game->getObjects({ pos.x - pos.width,pos.y - pos.height,pos.width*3,pos.height*3 }, ObjectToGet::getNoBlocks);
	for (auto o : objects)
	{
		if (o->getType() != ObjectType::Structure)
			continue;
		Structure* s = dynamic_cast<Structure*>(o);
		if (!s)
			continue;
		s->generateTexturePos();
	}
}

void Wall::onDestory()
{
	Rectangle pos = getPos();
	updateWallAt({ pos.x - pos.width,pos.y - pos.height,pos.width * 3,pos.height * 3 });
}

void Wall::update(float deltaTime)
{
	Structure::update(deltaTime);
}

void Wall::draw()
{
	Rectangle pos = animationPos();
	Texture2D texture = sprite->getTexture();
	DrawTexturePro(texture, texturePosDown, pos, { 0,0 }, 0, WHITE);
	DrawTexturePro(texture, texturePosUp, { pos.x,pos.y - pos.height / 2,pos.width,pos.height / 2 }, { 0,0 }, 0, WHITE);
}

void Wall::damageObject(int power, ToolType type)
{
	Structure::damageObject(power, type);
}

void Wall::saveToJson(nlohmann::json& j)
{
	Structure::saveToJson(j);
	j["Orientation"][0] = up;
	j["Orientation"][1] = down;
	j["Orientation"][2] = left;
	j["Orientation"][3] = right;
}

void Wall::readFromJson(nlohmann::json& j)
{
	Structure::readFromJson(j);
	if (j.contains("Orientation"))
	{
		up = j["Orientation"][0];
		down = j["Orientation"][1];
		left = j["Orientation"][2];
		right = j["Orientation"][3];
	}

}
bool Wall::isWallAt(Vector2 pos)
{
	std::list<GameObject*> objects =Game->getObjects({ pos.x,pos.y,1,1 }, ObjectToGet::getNoBlocks);
	objects.remove(this);
	for (auto o : objects)
		if (o->getType() == ObjectType::Structure)
		{
			Wall* w = dynamic_cast<Wall*>(o);
			if(w)
				return true;
		}
	return false;
}
void Wall::updateWallAt(Rectangle updatePos)
{
	std::list<GameObject*> objects = Game->getObjects(updatePos, ObjectToGet::getNoBlocks);
	objects.remove(this);
	for (auto o : objects)
	{
		if (o->getType() != ObjectType::Structure)
			continue;
		Wall* w = dynamic_cast<Wall*>(o);
		if (!w)
			continue;
		w->generateTexturePos();
	}
}
void Wall::generateTexturePos()
{
	Rectangle pos = getPos();
	right = isWallAt({ pos.x + pos.width * 3.0f / 2.0f,pos.y + pos.height / 2.0f });
	left = isWallAt({ pos.x - pos.width / 2.0f,pos.y + pos.height / 2.0f });
	up = isWallAt({ pos.x + pos.width / 2 ,pos.y - pos.height / 2 });
	down = isWallAt({ pos.x + pos.width / 2,pos.y + pos.height * 3.0f / 2.0f });

	texturePosUp.x = 0;
	texturePosUp.y = 0;
	texturePosDown.x = 0;
	texturePosDown.y = 0;
	int size = 16;
	if (up)
	{
		if (down)
		{
			if (left)
			{
				if (right) // PRAWO LEWO GÓRA DÓ£
				{
					texturePosUp.x = size * 11;
					texturePosUp.y = size;
					texturePosDown.x = size * 11;
					texturePosDown.y = size;
					right = isWallAt({ pos.x + pos.width * 3.0f / 2.0f,pos.y + pos.height * 3.0f / 2.0f });
					left = isWallAt({ pos.x - pos.width / 2.0f,pos.y + pos.height * 3.0f / 2.0f });
					if (right && left)
					{
						texturePosDown.x = size * 11;
						texturePosDown.y = size;
					}
					else if (left)
					{
						texturePosDown.x = size * 12;
						texturePosDown.y = size;
					}
					else if (right)
					{
						texturePosDown.x = size * 10;
						texturePosDown.y = size;
					}
					else
					{
						texturePosDown.x = size * 8;
						texturePosDown.y = size;
					}
				}
				else //  LEWO GÓRA DÓ£
				{
					texturePosUp.x = size * 12;
					texturePosUp.y = size;

					left = isWallAt({ pos.x - pos.width / 2.0f,pos.y + pos.height * 3.0f / 2.0f });
					if (left)
					{
						texturePosDown.x = size * 12;
						texturePosDown.y = size;
					}
					else
					{
						texturePosDown.x = size * 8;
						texturePosDown.y = size;
					}
				}
			}
			else
			{
				if (right) // PRAWO GÓRA DÓ£
				{
					texturePosUp.x = size * 10;
					texturePosUp.y = size;
					right = isWallAt({ pos.x + pos.width * 3.0f / 2.0f,pos.y + pos.height * 3.0f / 2.0f });
					if (right)
					{
						texturePosDown.x = size * 10;
						texturePosDown.y = size;
					}
					else
					{
						texturePosDown.x = size * 8;
						texturePosDown.y = size;
					}

				}
				else //  GÓRA DÓ£
				{
					texturePosUp.x = size * 8;
					texturePosUp.y = size;
					texturePosDown.x = size * 8;
					texturePosDown.y = size;
				}
			}
		}
		else////////
		{
			if (left)
			{
				if (right) // PRAWO LEWO GÓRA 
				{
					texturePosUp.x = size * 11;
					texturePosUp.y = size * 2;
					texturePosDown.x = size * 4;
					texturePosDown.y = size;
				}
				else // LEWO GÓRA 
				{
					texturePosUp.x = size * 12;
					texturePosUp.y = size * 2;
					texturePosDown.x = size * 6;
					texturePosDown.y = size;
				}
			}
			else
			{
				if (right) // PRAWO GÓRA 
				{
					texturePosUp.x = size * 10;
					texturePosUp.y = size * 2;
					texturePosDown.x = size * 2;
					texturePosDown.y = size;
				}
				else // GÓRA 
				{
					texturePosUp.x = size * 8;
					texturePosUp.y = size * 2;
					texturePosDown.x = 0;
					texturePosDown.y = size;
				}
			}
		}
	}
	else
	{
		if (down)
		{
			if (left)
			{
				if (right) // PRAWO LEWO DÓ£
				{
					texturePosUp.x = size * 11;
					texturePosUp.y = 0;
					texturePosDown.x = size * 11;
					texturePosDown.y = size;
					right = isWallAt({ pos.x + pos.width * 3.0f / 2.0f,pos.y + pos.height * 3.0f / 2.0f });
					left = isWallAt({ pos.x - pos.width / 2.0f,pos.y + pos.height * 3.0f / 2.0f });
					if (right && left)
					{
						texturePosDown.x = size * 11;
						texturePosDown.y = size;
					}
					else if (left)
					{
						texturePosDown.x = size * 12;
						texturePosDown.y = size;
					}
					else if (right)
					{
						texturePosDown.x = size * 10;
						texturePosDown.y = size;
					}
					else
					{
						texturePosDown.x = size * 8;
						texturePosDown.y = size;
					}


				}
				else // LEWO DÓ£
				{
					texturePosUp.x = size * 12;
					texturePosUp.y = 0;
					left = isWallAt({ pos.x - pos.width / 2.0f,pos.y + pos.height * 3.0f / 2.0f });
					if (left)
					{
						texturePosDown.x = size * 12;
						texturePosDown.y = size;
					}
					else
					{
						texturePosDown.x = size * 8;
						texturePosDown.y = size;
					}
				}
			}
			else
			{
				if (right) // PRAWO DÓ£
				{
					texturePosUp.x = size * 10;
					texturePosUp.y = 0;
					right = isWallAt({ pos.x + pos.width * 3.0f / 2.0f,pos.y + pos.height * 3.0f / 2.0f });
					if (right)
					{
						texturePosDown.x = size * 10;
						texturePosDown.y = size;
					}
					else
					{
						texturePosDown.x = size * 8;
						texturePosDown.y = size;
					}
				}
				else // DÓ£
				{
					texturePosUp.x = size * 8;
					texturePosUp.y = 0;
					texturePosDown.x = size * 8;
					texturePosDown.y = size;
				}
			}
		}
		else/////////
		{
			if (left)
			{
				if (right) // LEWO PRAWO
				{
					texturePosUp.x = size * 4;
					texturePosUp.y = 0;
					texturePosDown.x = size * 4;
					texturePosDown.y = size;
				}
				else // LEWO
				{
					texturePosUp.x = size * 6;
					texturePosUp.y = 0;
					texturePosDown.x = size * 6;
					texturePosDown.y = size;
				}
			}
			else
			{
				if (right) // PRAWO
				{
					texturePosUp.x = size * 2;
					texturePosUp.y = 0;
					texturePosDown.x = size * 2;
					texturePosDown.y = size;
				}
				else // NIC
				{
					texturePosUp.x = 0;
					texturePosUp.y = 0;
					texturePosDown.x = 0;
					texturePosDown.y = size;
				}
			}
		}
	}
}