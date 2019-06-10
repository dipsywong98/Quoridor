#include "Agent.h"
#include "Game.h"
#include <algorithm>
#include <iostream>


Agent::Agent()
{
}


Agent::~Agent()
{
}

float Agent::decision(Game* pGame, int playerId, Action& bestAction, int depth, float alpha, float beta)
{
	// if(depth == 0)
	{
		int targetYp = 0;
		if (playerId == 0)
		{
			targetYp = SIZE - 1;
		}
		std::vector<Coord> moves = pGame->getPossibleChessMovements(playerId);
		for (auto&& m : moves)
		{
			if(m.y == targetYp)
			{
				bestAction = { playerId, Action::Type::kMove, m,false,pGame->pPlayers[playerId]->position };
				return 1000;
			}
		}
	}
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
		// std::cout << "depth " << depth << " value " << tmpScore << " this action " << action << " a "<<alpha<<" b"<<beta<<std::endl;
		pGame->revertAction(action);
		if(tmpScore > score && tmpScore != -12345678)
		{
			bestAction = action;
			score = tmpScore;
		}
		alpha = std::max(score, alpha);
		if (alpha >= beta) {
			// std::cout << "alpha cut a " << alpha << " b " << beta << std::endl;
			return alpha;
		}
	}
	if (score == -INFINITY) return 12345678;
	return score;
}

float Agent::evaluate(Game* pGame, int p)
{
	int q = 1 - p;
	int targetYp = 0;
	if(p == 0)
	{
		targetYp = SIZE - 1;
	}
	int targetYq = SIZE - 1 - targetYp;
	if(pGame->pPlayers[p]->position.y == targetYp)
	{
		return 1000;
	}

	if(pGame->pPlayers[q]->position.y == targetYq)
	{
		return 1000;
	}

	const auto& posp = pGame->pPlayers[p]->position;
	const auto& posq = pGame->pPlayers[q]->position;

	int mdp = abs(targetYp - posp.y); //manhattan distance to goal
	int mdq = abs(targetYq - posq.y);
	int plp = pGame->pathLength(p); //shortest path length to goal
	if (plp == -1) return 12345678; // dont select this
	int plq = pGame->pathLength(q);
	if (plq == -1) return 12345678;
	constexpr int plmax = SIZE * SIZE;

	return float(plmax - plp)/float(plmax) - 0.5*float(plmax - plq)/float(SIZE*SIZE);
}
