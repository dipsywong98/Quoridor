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
	float decision(Action& action);
	float negamax(Game* pGame, int depth);
	float evaluate(Game* pGame);
};

