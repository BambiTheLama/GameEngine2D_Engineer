#pragma once
#include "GameObject.h"
#include <list>
class Factory
{

protected:
	static std::list<Factory*> factories;
	void removeFactory(Factory* factory);
	static void deleteAllFactory();
public:
	Factory();

	virtual ~Factory();
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
	friend class Engine;
	friend class GameScene;
};

