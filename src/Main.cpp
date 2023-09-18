#include <iostream>
#include "core/Engine.h"
#include <time.h>
#include <stdlib.h>
#include "json.hpp"
#include <fstream>
void test()
{
	nlohmann::json j;
	std::ifstream reader;
	reader.open("ENG.json");
	reader >> j;
	std::cout << j.dump(2)<<std::endl;
}

int main()
{
	test();
	Engine* engine = new Engine();
	engine->start();
	delete engine;
	

	return 0;
}