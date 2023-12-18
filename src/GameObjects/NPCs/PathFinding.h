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
	float posX, posY;
	int fx, fy;
	int sx, sy;
	int w, h;
	int objW, objH;
	bool hasPath = false;
	PathFindingNode*** nodes;
	PathFindingNode* getEndNode() { return nodes[fy][fx]; }
	PathFindingNode* getStartNode() { return nodes[sy][sx]; }
public:
	PathFinding(int x, int y, int w, int h, int objW = 1, int objH = 1, int posX = 0, int posY = 0);

	~PathFinding();
	void setNewEnd(Vector2 pos);
	void setNewEnd(Rectangle pos);
	void setNewStart(Vector2 pos);
	void setWall(Vector2 pos);
	void setWall(Rectangle pos);
	void removeWall(Vector2 pos);
	void calculateNodesNextTo(PathFindingNode* from, PathFindingNode* to, int v);
	void sortVector(std::vector<PathFindingNode*>& nodesToCheck);
	void addNode(std::vector<PathFindingNode*>& nodesToCheck, PathFindingNode* node);
	void calculateNextTo(int x, int y);
	void addNodesToVector(std::vector<PathFindingNode*>& nodesToCheck, int x, int y);
	void findPath();
	void setNewPos(float posX, float posY);
	Vector2 getPos() { return { (float)posX,(float)posY }; }
	void clearData();
	void draw();
	void draw(Vector2 pos, float zoom);
	bool isFindthPath() { return hasPath; }
	Vector2 getMoveVector();
	bool canPassTo(int x, int y);


};

