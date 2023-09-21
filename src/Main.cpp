#include <iostream>
#include "core/Engine.h"
#include <time.h>
#include <stdlib.h>
#include "json.hpp"
#include <fstream>
void test()
{
	const char* path = "ENG.json";
	nlohmann::json j;
	std::ifstream reader;
	reader.open(path);
	reader >> j;
	reader.close();
	std::ofstream writer;
	writer.open(path);
	std::cout << j.dump(2) << std::endl;
	writer << j.dump(2);
	writer.close();

}
	
int main()
{
	//test();
	Engine* engine = new Engine();
	engine->start();
	delete engine;
	

	return 0;
}