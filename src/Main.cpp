#include <iostream>
#include "core/Engine.h"
#include <time.h>
#include <stdlib.h>

int main()
{

	Engine* engine = new Engine();
	engine->start();
	delete engine;
	

	return 0;
}