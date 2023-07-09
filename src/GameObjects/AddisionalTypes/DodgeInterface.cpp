#include "DodgeInterface.h"

DodgeInterface::DodgeInterface(int dodgeTime, int dodgeCDR)
{
	this->dodgeTime = dodgeTime;
	this->dodgeCDR = dodgeCDR;
	this->dodgeCDRMax = dodgeCDR;
	this->dodgeTime = dodgeTime;
}

void DodgeInterface::update()
{
	if (dodgeTime > 0)
	{
		dodgeTime--;
	}
	else if (dodgeCDR > 0)
		dodgeCDR--;
}

bool DodgeInterface::doDodge(Vector2 deltaMove)
{
	if (dodgeCDR > 0)
		return false;
	this->deltaMove = deltaMove;

	return true;
}