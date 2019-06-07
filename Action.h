#pragma once
#include "Coord.h"


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

