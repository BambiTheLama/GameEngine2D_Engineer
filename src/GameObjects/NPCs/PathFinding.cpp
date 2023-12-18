#include "PathFinding.h"

int PathFindingNode::w=1, PathFindingNode::h=1, PathFindingNode::startX=0, PathFindingNode::startY=0;

PathFindingNode::PathFindingNode(int x, int y)
{
	this->x = x;
	this->y = y;
}

void PathFindingNode::draw()
{
	Color c = { 0,0,0,50 };
	if (!canPassByIt)
		c = { 0,0,0,50 };
	else if (!used)
		c = { 0,82,172,50 };
	else
		c = { 0,127,255,50 };
	DrawRectangle(startX + x * w, startY + y * h, w, h, c);
	DrawRectangleLines(startX + x * w, startY + y * h, w, h, { 0,0,0,50 });
}

void PathFindingNode::drawPath()
{
	PathFindingNode* n = this;
	DrawRectangle(startX + n->x * w, startY + n->y * h, w, h, { 255,0,0,69 });
	while (n->fromNode)
	{
		DrawRectangle(startX + n->x * w, startY + n->y * h, w, h, { 255,255,0,69 });
		n = n->fromNode;
	}
	if(n)
		DrawRectangle(startX + n->x * w, startY + n->y * h, w, h, { 0,255,0,69 });

}

void PathFindingNode::clear()
{
	used = false;
	wasUsedToCalculet = false;
}

PathFinding::PathFinding(int x, int y, int w, int h, int objW, int objH, int posX, int posY)
{
	w /= objW;
	h /= objH;
	this->posX = posX - w / 2 * objW;
	this->posY = posY - h / 2 * objH;
	this->objH = objH;
	this->objW = objW;
	this->fx = x;
	this->fy = y;
	this->w = w;
	this->h = h;
	this->sx = w / 2;
	this->sy = h / 2;
	nodes = new PathFindingNode * *[h];
	for (int i = 0; i < h; i++)
	{
		nodes[i] = new PathFindingNode * [w];
		for (int j = 0; j < w; j++)
			nodes[i][j] = new PathFindingNode(j, i);
	}
	PathFindingNode::w = objW;
	PathFindingNode::h = objH;
	PathFindingNode::startX = posX;
	PathFindingNode::startY = posY;
}

PathFinding::~PathFinding()
{

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
			delete nodes[i][j];
		delete nodes[i];
	}

	delete nodes;
}

void PathFinding::setNewEnd(Vector2 pos)
{
	fx = (pos.x - posX) / objW;
	fy = (pos.y - posY) / objH;
}
void PathFinding::setNewEnd(Rectangle pos)
{
	fx = (pos.x + pos.width / 2 - posX) / objW;
	fy = (pos.y + pos.height / 2 - posY) / objH;
}

void PathFinding::setNewStart(Vector2 pos)
{
	float sx = (pos.x - posX) / objW;
	float sy = (pos.y - posY) / objH;

}

void PathFinding::setWall(Vector2 pos)
{
	int x = (pos.x - posX) / objW;
	int y = (pos.y - posY) / objH;
	if (x < 0 || x >= w || y < 0 || y >= h)
		return;
	nodes[y][x]->canPassByIt = false;
}

void PathFinding::setWall(Rectangle pos)
{
	int x = (pos.x - posX) / objW;
	int y = (pos.y - posY) / objH;
	if (x < 0 || x >= w || y < 0 || y >= h)
		return;
	int pw = (pos.width + pos.x - posX) / objW + ((int)(pos.width + pos.x - posX) % objW > 0 ? 1 : 0);
	int ph = (pos.height + pos.y - posY) / objH + ((int)(pos.height + pos.y - posY) % objH > 0 ? 1 : 0);
	for (int i = x; i < pw && i < w; i++)
		for (int j = y; j < ph && j < h; j++)
		{
			nodes[j][i]->canPassByIt = false;
		}

}

void PathFinding::removeWall(Vector2 pos)
{
	int x = (pos.x - posX) / objW;
	int y = (pos.y - posY) / objH;
	if (x < 0 || x >= w || y < 0 || y >= h)
		return;
	nodes[y][x]->canPassByIt = true;
}

void PathFinding::calculateNodesNextTo(PathFindingNode* from, PathFindingNode* to,int v)
{
	if (to->used && from->from + v >= to->from)
		return;
	
	if (to->wasUsedToCalculet)
		return;
	if (!to->used)
	{
		int dx = abs(to->x - fx) * 10;
		int dy = abs(to->y - fy) * 10;
		to->to = dx + dy;
		to->used = true;
		if (to->to == 0)
		{
			hasPath = true;
		}

	}
	to->from = from->from + v;
	to->cost = to->from + to->to;
	to->fromNode = from;
}

void PathFinding::sortVector(std::vector<PathFindingNode*>& nodesToCheck)
{
	for (int i = 0; i < nodesToCheck.size(); i++)
	{
		for (int j = 0; j < nodesToCheck.size() - 1; j++)
		{
			if (nodesToCheck[j]->cost < nodesToCheck[j + 1]->cost)
			{
				PathFindingNode* n = nodesToCheck[j];
				nodesToCheck[j] = nodesToCheck[j + 1];
				nodesToCheck[j + 1] = n;
			}
		}
	}

}

void PathFinding::addNode(std::vector<PathFindingNode*>& nodesToCheck, PathFindingNode* node)
{
	for (auto n : nodesToCheck)
		if (n == node)
			return;

	int at = 0;
	for (int i = 0; i < nodesToCheck.size(); i++)
	{
		if (nodesToCheck[i]->cost > node->cost)
		{
			at++;
			continue;
		}
		if (nodesToCheck[i]->cost == node->cost && nodesToCheck[i]->to <= node->to)
		{
			at++;
			continue;
		}

		break;
	}
	nodesToCheck.push_back(NULL);

	for (int i = nodesToCheck.size() - 1; i > at; i--)
	{
		nodesToCheck[i] = nodesToCheck[i - 1];
	}
	nodesToCheck[at] = node;
}

void PathFinding::calculateNextTo(int x, int y)
{
	nodes[y][x]->wasUsedToCalculet = true;
	if (y + 1 < h)
	{
		calculateNodesNextTo(nodes[y][x], nodes[y + 1][x], 10);
		if (x - 1 >= 0)
			calculateNodesNextTo(nodes[y][x], nodes[y + 1][x - 1], 14);
		if (x + 1 < w)
			calculateNodesNextTo(nodes[y][x], nodes[y + 1][x + 1], 14);
	}
	if (y - 1 >= 0)
	{
		calculateNodesNextTo(nodes[y][x], nodes[y - 1][x], 10);
		if (x - 1 >= 0)
			calculateNodesNextTo(nodes[y][x], nodes[y - 1][x - 1], 14);
		if (x + 1 < w)
			calculateNodesNextTo(nodes[y][x], nodes[y - 1][x + 1], 14);
	}
	if (x - 1 >= 0)
	{
		calculateNodesNextTo(nodes[y][x], nodes[y][x - 1], 10);
	}
	if (x + 1 < w)
	{
		calculateNodesNextTo(nodes[y][x], nodes[y][x + 1], 10);
	}


}
bool PathFinding::canPassTo(int x, int y)
{
	return y < h && y >= 0 && x >= 0 && x < w && !nodes[y][x]->wasUsedToCalculet && nodes[y][x]->canPassByIt;
}
void PathFinding::addNodesToVector(std::vector<PathFindingNode*>& nodesToCheck, int x, int y)
{

	if (canPassTo(x, y + 1))
	{
		addNode(nodesToCheck, nodes[y + 1][x]);
		if (canPassTo(x + 1, y) && canPassTo(x + 1, y + 1))
			addNode(nodesToCheck, nodes[y + 1][x + 1]);
		if (canPassTo(x - 1, y) && canPassTo(x - 1, y + 1))
			addNode(nodesToCheck, nodes[y + 1][x - 1]);

	}
	if (canPassTo(x, y - 1))
	{
		addNode(nodesToCheck, nodes[y - 1][x]);
		if (canPassTo(x + 1, y) && canPassTo(x + 1, y - 1))
			addNode(nodesToCheck, nodes[y - 1][x + 1]);
		if (canPassTo(x - 1, y) && canPassTo(x - 1, y - 1))
			addNode(nodesToCheck, nodes[y - 1][x - 1]);

	}
	if (canPassTo(x + 1, y))
	{
		addNode(nodesToCheck, nodes[y][x + 1]);
	}
	if (canPassTo(x - 1, y))
	{
		addNode(nodesToCheck, nodes[y][x - 1]);
	}
}

void PathFinding::findPath()
{
	hasPath = false;
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			nodes[i][j]->clear();

	std::vector<PathFindingNode*> nodesToCheck;

	calculateNextTo(sx, sy);
	addNodesToVector(nodesToCheck, sx, sy);

	while (nodesToCheck.size() > 0 && !hasPath)
	{
		PathFindingNode* n = nodesToCheck.back();
		nodesToCheck.pop_back();
		calculateNextTo(n->x, n->y);
		addNodesToVector(nodesToCheck, n->x, n->y);
	}
}

void PathFinding::setNewPos(float posX, float posY)
{
	this->posX = posX - w / 2 * objW;
	this->posY = posY - h / 2 * objH;

}

void PathFinding::clearData()
{
	hasPath = false;
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
		{
			nodes[i][j]->clear();
			nodes[i][j]->canPassByIt = true;
		}
			
}

void PathFinding::draw()
{
	PathFindingNode::w = objW;
	PathFindingNode::h = objH;
	PathFindingNode::startX = posX;
	PathFindingNode::startY = posY;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			nodes[i][j]->draw();
		}
	}
	getStartNode()->draw();
	getEndNode()->draw();
	if (hasPath)
		nodes[fy][fx]->drawPath();


}
void PathFinding::draw(Vector2 pos, float zoom)
{
	PathFindingNode::w = objW*zoom;
	PathFindingNode::h = objH*zoom;
	PathFindingNode::startX = pos.x;
	PathFindingNode::startY = pos.y;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			nodes[i][j]->draw();
		}
	}
	if (hasPath)
		getEndNode()->drawPath();


}

Vector2 PathFinding::getMoveVector()
{
	if (!hasPath)
		return { 0,0 };
	PathFindingNode* n=getEndNode();
	PathFindingNode* sn = getStartNode();
	while (n->fromNode && n->fromNode != sn)
	{
		n = n->fromNode;
	}
	if (!n->fromNode)
		return { 0,0 };
	Vector2 moveVectr = { 0,0 };

	if (n->y > sn->y)
		moveVectr.y = 1;
	else if(n->y < sn->y)
		moveVectr.y = -1;
	
	if (n->x > sn->x)
		moveVectr.x = 1;
	else if (n->x < sn->x)
		moveVectr.x = -1;

	return moveVectr;
}