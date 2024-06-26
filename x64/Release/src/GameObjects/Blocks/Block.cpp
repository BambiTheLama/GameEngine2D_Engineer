#include "Block.h"
#include "../../core/Scenes/GameScene.h"
#include "../BlockFactory.h"

Block::Block(Block& obj):GameObject(obj),DestroyAble(obj),ItemsDrop(obj)
{
	hp = obj.hp;
	power = obj.power;
	sprite = new SpriteController(*obj.sprite);
	texturePos = obj.texturePos;
}

Block::Block(Rectangle pos, ToolType requestType, int power, std::string name) :GameObject(pos,name),DestroyAble(requestType)
{
	hp = 10;
	this->power = power;
	std::string path= "Resource/Blocks/" + name + ".png";
	sprite = new SpriteController(path.c_str());
	texturePos.width = sprite->getTexture().width/4;
	texturePos.height = sprite->getTexture().height/4;
}
Block::~Block()
{
	Rectangle pos = getPos();
	if(sprite)
		delete sprite;
	GameScene* game = Game;

	if (game == NULL)
		return;
}
void Block::start()
{
	generateTexturePos();
}

void Block::update(float deltaTime)
{

}

void Block::draw()
{
	Rectangle pos = getPos();

	DrawTexturePro(sprite->getTexture(), texturePos, pos, { 0,0 }, 0, WHITE);
	if (collidersToDraw)
		DrawRectangleLinesEx(pos, 2, BLACK);
}

void Block::drawInMiniMap(int x, int y)
{
	DrawTexturePro(sprite->getTexture(), texturePos, { (float)x,(float)y,1,1 }, { 0,0 }, 0, WHITE);
}

void Block::damageObject(int power, ToolType tool)
{
	if (!isThisToolType(tool, itemToolRequest))
		return;
	if (this->power > 0)
		hp -= power / (this->power);
	else
		hp = 0;
	if (hp <= 0)
	{
		Rectangle pos = getPos();
		Game->deleteBlock(getPos());
	}
	
}

bool isTheSameBlock(Rectangle pos, unsigned int ID)
{
	Block* block = Game->getBlock(pos);
	if (block)
	{
		return ID == block->getID();
	}
	return false;
}

void Block::generateTexturePos()
{
	if (sprite->getTexture().width <= 32)
	{
		texturePos = { 0,0,(float)sprite->getTexture().width,(float)sprite->getTexture().height };
		return;
	}
	Rectangle pos = getPos();
	unsigned int ID = getID();
	float size = sprite->getTexture().width / 4;
	bool right = true, left = true, down = true, up = true;
	right = isTheSameBlock({ pos.x + tileSize + pos.width / 2,pos.y,1,1 }, ID);
	left = isTheSameBlock({ pos.x - tileSize + pos.width / 2,pos.y,1,1 }, ID);
	down = isTheSameBlock({ pos.x,pos.y + tileSize + pos.height / 2,1,1 }, ID);
	up = isTheSameBlock({ pos.x,pos.y - tileSize + pos.height / 2,1,1 }, ID);




	if (up) 
	{
		if (down)
		{
			if (left)
			{
				if (right) // PRAWO LEWO G�RA Dӣ
				{
					texturePos.x = size;
					texturePos.y = size;
				}
				else //  LEWO G�RA Dӣ
				{
					texturePos.x = size * 2;
					texturePos.y = size;
				}
			}
			else
			{
				if (right) // PRAWO G�RA Dӣ
				{
					texturePos.x = 0;
					texturePos.y = size;
				}
				else //  G�RA Dӣ
				{
					texturePos.x = size * 3;
					texturePos.y = size;
				}
			}
		}
		else////////
		{
			if (left)
			{
				if (right) // PRAWO LEWO G�RA 
				{
					texturePos.x = size;
					texturePos.y = size * 2;
				}
				else // LEWO G�RA 
				{
					texturePos.x = size * 2;
					texturePos.y = size * 2;
				}
			}
			else
			{
				if (right) // PRAWO G�RA 
				{
					texturePos.y = size * 2;
					texturePos.x = 0;
				}
				else // G�RA 
				{
					texturePos.x = size * 3;
					texturePos.y = size * 2;
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
				if (right) // PRAWO LEWO Dӣ
				{
					texturePos.x = size;
					texturePos.y = 0;
				}
				else // LEWO Dӣ
				{
					texturePos.x = size * 2;
					texturePos.y = 0;
				}
			}
			else
			{
				if (right) // PRAWO Dӣ
				{
					texturePos.x = 0;
					texturePos.y = 0;
				}
				else // Dӣ
				{
					texturePos.x = size*3;
					texturePos.y = 0;
				}
			}
		}
		else/////////
		{
			if (left)
			{
				if (right) // LEWO PRAWO
				{
					texturePos.x = size;
					texturePos.y = size * 3;
				}
				else // LEWO
				{
					texturePos.x = size * 2;
					texturePos.y = size * 3;
				}
			}
			else
			{
				if (right) // PRAWO
				{
					texturePos.x = 0;
					texturePos.y = size * 3;
				}
				else // NIC
				{
					texturePos.x = size * 3;
					texturePos.y = size * 3;
				}
			}
		}
	}

}