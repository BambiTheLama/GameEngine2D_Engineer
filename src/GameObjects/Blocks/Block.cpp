#include "Block.h"
#include "../../core/Scenes/GameScene.h"

Block::Block(Block& obj):GameObject(obj),DestroyAble(obj),ItemsDrop(obj)
{
	hp = obj.hp;
	power = obj.power;
	sprite = obj.sprite;
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
	GameScene* game = Game;
	if (game == NULL)
		return;
	Block* b=Game->getBlock({ pos.x + tileSize,pos.y,pos.width,pos.height });
	if (b != NULL)
		b->generateTexturePos();
	b=Game->getBlock({ pos.x - tileSize,pos.y,pos.width,pos.height });
	if (b != NULL)
		b->generateTexturePos();
	b=Game->getBlock({ pos.x,pos.y + tileSize,pos.width,pos.height });
	if (b != NULL)
		b->generateTexturePos();
	b=Game->getBlock({ pos.x,pos.y - tileSize,pos.width,pos.height });
	if (b != NULL)
		b->generateTexturePos();

}
void Block::start()
{
	generateTexturePos();
}

void Block::update()
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
		Game->deleteBlocks(getPos());
	}
	
}

bool isTheSameBlock(Rectangle pos, unsigned int ID)
{
	Block* block = Game->getBlock(pos);
	if (block != NULL)
	{
		return ID == block->getID();
	}
	return false;
}

void Block::generateTexturePos()
{
	Rectangle pos = getPos();
	unsigned int ID = getID();
	right = isTheSameBlock({ pos.x + tileSize,pos.y,pos.width,pos.height },ID);
	left = isTheSameBlock({ pos.x - tileSize,pos.y,pos.width,pos.height }, ID);
	down = isTheSameBlock({ pos.x,pos.y + tileSize,pos.width,pos.height }, ID);
	up = isTheSameBlock({ pos.x,pos.y - tileSize,pos.width,pos.height }, ID);

	float size = sprite->getTexture().width / 4;


	if (up) 
	{
		if (down)
		{
			if (left)
			{
				if (right) // PRAWO LEWO GÓRA DÓ£
				{
					texturePos.x = size;
					texturePos.y = size;
				}
				else //  LEWO GÓRA DÓ£
				{
					texturePos.x = size * 2;
					texturePos.y = size;
				}
			}
			else
			{
				if (right) // PRAWO GÓRA DÓ£
				{
					texturePos.x = 0;
					texturePos.y = size;
				}
				else //  GÓRA DÓ£
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
				if (right) // PRAWO LEWO GÓRA 
				{
					texturePos.x = size;
					texturePos.y = size * 2;
				}
				else // LEWO GÓRA 
				{
					texturePos.x = size * 2;
					texturePos.y = size * 2;
				}
			}
			else
			{
				if (right) // PRAWO GÓRA 
				{
					texturePos.y = size * 2;
					texturePos.x = 0;
				}
				else // GÓRA 
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
				if (right) // PRAWO LEWO DÓ£
				{
					texturePos.x = size;
					texturePos.y = 0;
				}
				else // LEWO DÓ£
				{
					texturePos.x = size * 2;
					texturePos.y = 0;
				}
			}
			else
			{
				if (right) // PRAWO DÓ£
				{
					texturePos.x = 0;
					texturePos.y = 0;
				}
				else // DÓ£
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