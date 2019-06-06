#pragma once
#include "Coord.h"
struct Node : Coord
{
	Node(int x, int y, int sourceDistance, int targetDistance);
	Node(const Coord& position, int sourceDistance, int targetDistance);
	~Node();
	int sourceDistance;
	int targetDistance;

};

bool operator<(const Node& a, const Node& b);