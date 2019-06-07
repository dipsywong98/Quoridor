#pragma once
struct Coord
{
	Coord();
	Coord(int x, int y);
	~Coord();
	int x, y;
};

bool operator!=(const Coord& a,const Coord& b);
