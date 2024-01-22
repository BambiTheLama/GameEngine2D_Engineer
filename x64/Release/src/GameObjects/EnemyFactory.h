#pragma once
#include "Factory.h"
#include "Enemy/Enemy.h"
class EnemyFactory :
    public Factory
{
    static EnemyFactory* factory;
	std::vector<Enemy*> objects;
	EnemyFactory();
	~EnemyFactory();
public:
	static EnemyFactory* getFactory();

	void clearFactory();

	Enemy* getObject(int ID);

	int getSize() { return objects.size(); }
};

