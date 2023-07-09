#include "ShootingWeapon.h"
#include "../../../core/Scenes/GameScene.h"
#include "../../Projectals/Projectal.h"

ShootingWeapon::ShootingWeapon(ShootingWeapon& obj):Weapon(obj)
{
	orgin = obj.orgin;
	projectal = obj.projectal->clone();
}

ShootingWeapon::ShootingWeapon(Rectangle pos) :Weapon(pos)
{
	orgin = { pos.width / 2, pos.height};
	Rectangle bulletPos = { pos.x - 8,pos.y - 8 , 16,16 };
	projectal = new Projectal(bulletPos, rotation, 1000);
}

ShootingWeapon::~ShootingWeapon()
{
	if(projectal!=NULL)
		delete projectal;
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

	Projectal *pro = projectal->clone();
	pro->setRotation(rotation);
	pro->setMovePos({ pos.x - 8,pos.y - 8 });
	Game->addObject(pro);

	CDR = CDRMAX;

	return true;
}