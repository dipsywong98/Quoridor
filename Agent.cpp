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
				if(pGame->isWallNoOverlap({i,j},isHorizontal))
				{
					actions.push_back({ playerId, Action::Type::kWall,{i,j},isHorizontal,{0,0} });
				}
				if(pGame->isWallNoOverlap({j,i},isHorizontal2))
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

float Agent::evaluate(Game* pGame, int p)
{
	int targetYp = 0;
	int q = 1 - p;
	if(p == 0)
	{
		targetYp = SIZE - 1;
	}
	int targetYq = SIZE - 1 - targetYp;
	if(pGame->pPlayers[p]->position.y == targetYp)
	{
		return INFINITY;
	}

	if(pGame->pPlayers[1-p]->position.y == targetYq)
	{
		return -INFINITY;
	}

	const auto& posp = pGame->pPlayers[p]->position;
	const auto& posq = pGame->pPlayers[q]->position;

	int mdp = abs(targetYp - posp.y); //manhattan distance to goal
	int mdq = abs(targetYq - posq.y);
	int plp = pGame->pathLength(p); //shortest path length to goal
	if (plp == -1) return -INFINITY; // dont select this
	int plq = pGame->pathLength(q);
	if (plq == -1) return -INFINITY;
	constexpr int plmax = SIZE * SIZE;

	return float(plmax - plp)/float(plmax) - 0.5*float(plmax - plq)/float(SIZE*SIZE);
}
