#include "MiniMap.h"

MiniMap::MiniMap(GameObject *target)
{
	this->target = target;
}

MiniMap::~MiniMap()
{
	UnloadRenderTexture(minimapBuffor);
}
void MiniMap::generateMiniMap()
{

	BeginTextureMode(minimapBuffor);
	ClearBackground(WHITE);
	EndTextureMode();
}

void MiniMap::draw()
{
	Rectangle pos = { GetScreenWidth() - 330, 10, 320, 320 };
	DrawRectangle(pos.x-3,pos.y-3,pos.width+6,pos.height+6, BLACK);
	DrawTexturePro(minimapBuffor.texture, { 0,0,(float)w,-(float)h }, pos, { 0,0 }, 0, WHITE);
	Vector2 point = { pos.x + target->getPos().x / tileSize / w * pos.width, pos.y + target->getPos().y / tileSize / h * pos.height };
	
	DrawCircle(point.x, point.y, 4, RED);
}