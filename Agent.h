#pragma once
#include <vector>
#include "Action.h"

#define NORMAL_DEPTH 2
#define CAREFUL_DEPTH 3


class Game;

class Agent
{
public:
	Agent();
	~Agent();
	int MAX_DEPTH = 2;
	Action prevActs[2][2]={
		{{-1},{-1}},
		{{-1},{-1}}
		};
	float act(Game* pGame);
	/**
	 * playerId will try to take the negative max of pGame turns' decision
	 */
	float decision(Game* pGame, int playerId, Action& action, int depth, float alpha, float beta);

	/**
	 * evaluate the game state on behave of the player
	 */
	float evaluate(Game* pGame, int p);
};

