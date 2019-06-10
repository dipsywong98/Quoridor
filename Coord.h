#pragma once
#include <ostream>

struct Coord
{
	Coord();
	Coord(int x, int y);
	~Coord();
	int x, y;
};

bool operator!=(const Coord& a,const Coord& b);
bool operator==(const Coord& a,const Coord& b);
std::ostream& operator<<(std::ostream& os, const Coord& coord);
