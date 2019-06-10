#include "Coord.h"



Coord::Coord():x(0),y(0)
{
}


Coord::Coord(int x, int y):x(x),y(y)
{
}


Coord::~Coord()
{
}

bool operator!=(const Coord& a, const Coord& b)
{
	return a.x != b.x || a.y != b.y;
}

bool operator==(const Coord& a, const Coord& b)
{
	return a.x == b.x && a.y == b.y;
}

std::ostream& operator<<(std::ostream& os, const Coord& coord)
{
	os << coord.x << ", " << coord.y;
	return os;
}
