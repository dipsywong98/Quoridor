#pragma once
#define MAX_DEPTH 3
#include <vector>
#include "Action.h"
class Game;

class Agent
{
public:
	Agent();
	~Agent();
	/**
	 * playerId will try to take the negative max of pGame turns' decision
	 */
	float decision(Game* pGame, int playerId, Action& action, int depth, float alpha, float beta);

	/**
	 * evaluate the game state on behave of the player
	 */
	float evaluate(Game* pGame, int playerId);
};

