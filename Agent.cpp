#include "Agent.h"
#include "Game.h"
#include <algorithm>


Agent::Agent()
{
}


Agent::~Agent()
{
}

float Agent::decision(Game* pGame, int playerId, Action& bestAction, int depth, float alpha, float beta)
{
	if(depth>=MAX_DEPTH || pGame->isTerminate())
	{
		return evaluate(pGame, pGame->turn);
	}
	std::vector<Action> actions;

	std::vector<Coord> moves = pGame->getPossibleChessMovements(playerId);
	for (auto&& m : moves)
	{
		actions.push_back({ playerId, Action::Type::kMove,m,false,pGame->pPlayers[playerId]->position });
	}

	if(pGame->pPlayers[playerId]->wallsLeft>0)
	{
		for(int i=1; i < (SIZE - 1) * 2; i+=2)
		{
			for(int j=0; j<(SIZE-1)*2;j+=2)
			{
				bool isHorizontal, isHorizontal2;
				if(pGame->validateWallPlacement({i,j},isHorizontal))
				{
					actions.push_back({ playerId, Action::Type::kWall,{i,j},isHorizontal,{0,0} });
				}
				if(pGame->validateWallPlacement({j,i},isHorizontal2))
				{
					actions.push_back({ playerId, Action::Type::kWall,{j,i},isHorizontal2,{0,0} });
				}
			}
		}
	}

	float score = -INFINITY;
	for(auto&& action: actions)
	{
		Action tmpAction;
		pGame->applyAction(action);
		float tmpScore = -decision(pGame, 1 - playerId, tmpAction, depth + 1, -beta, -alpha);
		pGame->revertAction(action);
		if(tmpScore > score)
		{
			bestAction = action;
			score = tmpScore;
		}
		alpha = std::max(score, alpha);
		if (alpha >= beta) return alpha;
	}
	return score;
}

float Agent::evaluate(Game* pGame, int playerId)
{
	int targetY = 0;
	if(playerId == 0)
	{
		targetY = SIZE - 1;
	}
	if(pGame->pPlayers[playerId]->position.y == targetY)
	{
		return INFINITY;
	}

	if(pGame->pPlayers[1-playerId]->position.y == SIZE - 1 - targetY)
	{
		return -INFINITY;
	}

	return float(SIZE*SIZE - pGame->pathLength(playerId))/float(SIZE*SIZE) - 0.5*float(SIZE*SIZE - pGame->pathLength(playerId))/float(SIZE*SIZE);
}
