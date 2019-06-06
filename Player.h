#pragma once
#include "Coord.h"

class Game;

class Player
{
public:
	Player(Game* pGame, Coord position, int walls);
	~Player();
	Game* pGame;
	int wallsLeft;
	Coord position;
};

