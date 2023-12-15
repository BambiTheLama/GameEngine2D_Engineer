#pragma once
#include "raylib.h"
#include <vector>
struct PathFindingNode
{
	static int w, h, startX, startY;
	int x, y;
	bool used = false;
	bool wasUsedToCalculet = false;
	bool canPassByIt = true;
	int cost=0, to=0, from=0;
	PathFindingNode* fromNode=NULL;

	PathFindingNode(int x, int y);
	
	void draw();

	void drawPath();

	void clear();
};
class PathFinding
{
	int posX, posY;
	int fx, fy;
	int sx, sy;
	int w, h;
	int objW, objH;
	bool hasPath = false;
	PathFindingNode*** nodes;
public:
	PathFinding(int x, int y, int w, int h, int objW = 1, int objH = 1, int posX = 0, int posY = 0);

	~PathFinding();
	void setNewEnd(Vector2 pos);
	void setNewStart(Vector2 pos);
	void setWall(Vector2 pos);
	void setWall(Rectangle pos);
	void removeWall(Vector2 pos);
	void calculateNodesNextTo(PathFindingNode* from, PathFindingNode* to);
	void sortVector(std::vector<PathFindingNode*>& nodesToCheck);
	void addNode(std::vector<PathFindingNode*>& nodesToCheck, PathFindingNode* node);
	void calculateNextTo(int x, int y);
	void addNodesToVector(std::vector<PathFindingNode*>& nodesToCheck, int x, int y);
	void findPath();
	void setNewPos(int posX, int posY);
	void clearData();
	void draw();


};

