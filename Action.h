#pragma once
#include "Coord.h"
#include <ostream>


struct Action
{
	enum struct Type
	{
		kWall = 0,
		kMove,
	};
	int playerId;
	Type type;
	Coord position;
	bool isHorizontal;
	Coord prevPosition;
};

std::ostream& operator<<(std::ostream& os, const Action& action);
