#pragma once
#include "GameObject.h"
class Factory
{
public:
	/// <summary>
	/// Czyœci obiekty aktywuje destruktor
	/// </summary>
	virtual void clearFactory()=0;
	/// <summary>
	/// Zwraca kopiê obiektu którego podajemy ID
	/// </summary>
	/// <param name="ID">Ite itemu</param>
	/// <returns>Zwra kopiê itemu</returns>
	virtual GameObject* getObject(int ID)=0;
};

