#pragma once
#include "GameObject.h"
class Factory
{
public:
	/// <summary>
	/// Czy�ci obiekty aktywuje destruktor
	/// </summary>
	virtual void clearFactory()=0;
	/// <summary>
	/// Zwraca kopi� obiektu kt�rego podajemy ID
	/// </summary>
	/// <param name="ID">Ite itemu</param>
	/// <returns>Zwra kopi� itemu</returns>
	virtual GameObject* getObject(int ID)=0;
};

