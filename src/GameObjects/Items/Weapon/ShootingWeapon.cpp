#include "ShootingWeapon.h"
#include "../../../core/Scenes/GameScene.h"
#include "../../Projectals/Projectal.h"

ShootingWeapon::ShootingWeapon(ShootingWeapon& obj):Weapon(obj)
{
	orgin = obj.orgin;
}

ShootingWeapon::ShootingWeapon(Rectangle pos) :Weapon(pos)
{
	orgin = { pos.width / 2, pos.height};
}

ShootingWeapon::~ShootingWeapon()
{

}
void ShootingWeapon::update()
{
	Weapon::update();
	Rectangle pos = getPos();
	rotation = cursorTarget({ pos.x ,pos.y });
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CDR <= 0)
	{
		use();
	}
}
void ShootingWeapon::draw()
{
	Rectangle pos = getPos();
	DrawRectanglePro(pos, orgin, rotation, BLUE);
}
bool ShootingWeapon::use()
{
	if(CDR>0)
		return false;
	Rectangle pos = getPos();
	Rectangle bulletPos = { pos.x-8,pos.y-8 , 16,16 };

	Game->addObject(new Projectal(bulletPos, rotation, 1000));


	//CDR = CDRMAX;
	return true;
}