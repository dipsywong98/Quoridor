#include "Node.h"



Node::Node(int x, int y, int sourceDistance, int targetDistance): Coord(x,y), sourceDistance(sourceDistance), targetDistance(targetDistance)
{
}

Node::Node(const Coord& position, int sourceDistance, int targetDistance): Coord(position), sourceDistance(sourceDistance), targetDistance(targetDistance)
{
}



Node::~Node()
{
}

bool operator<(const Node& a, const Node& b)
{
	return a.sourceDistance + a.targetDistance < b.sourceDistance + b.targetDistance;
}
