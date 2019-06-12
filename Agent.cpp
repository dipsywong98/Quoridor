#include "Agent.h"
#include "Game.h"
#include <ctime>
#include <algorithm>
#include <iostream>
#include "Log.h"

extern Log d;
extern Log js;

Agent::Agent()
{
	std::srand(unsigned(std::time(nullptr)));
}


Agent::~Agent()
{
}

float Agent::act(Game* pGame)
{
	const int p = pGame->turn;
	// if previous two actions are redundant, deepen the decision tree 
	if(prevActs[p][0].playerId == p && prevActs[p][1].playerId == p)
	{
		if(prevActs[p][0].type == Action::Type::kMove && prevActs[p][1].type == Action::Type::kMove)
		{
			if(prevActs[p][0].prevPosition == prevActs[p][1].position)
			{
				MAX_DEPTH = CAREFUL_DEPTH;
			}
		}
	}
	Action action;
	float score = decision(pGame, pGame->turn, action, 0, -INFINITY, INFINITY);
	MAX_DEPTH = NORMAL_DEPTH;
	prevActs[p][0] = prevActs[p][1];
	prevActs[p][1] = action;

	// execute action
	if (action.type == Action::Type::kWall)
	{
		pGame->validateAndPlaceWall(pGame->turn, action.position);
	}
	else
	{
		pGame->validateAndMoveChess(pGame->turn, action.position);
	}

	return score;
}

float Agent::decision(Game* pGame, int playerId, Action& bestAction, int depth, float alpha, float beta)
{
	bool isMaximizing = pGame->turn == playerId;
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

	int wallStart = actions.size();
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
	std::random_shuffle(actions.begin()+wallStart, actions.end());

	// js << "{\n";
	float score = -INFINITY;
	if (!isMaximizing) score = INFINITY;
	for(auto&& action: actions)
	{
		Action tmpAction;
		pGame->applyAction(action);
		float tmpScore = decision(pGame, 1 - playerId, tmpAction, depth + 1, alpha, beta);
		d << "depth " << depth << " value " << tmpScore << " this action " << action << " a "<<alpha<<" b "<<beta<<"\n";
		pGame->revertAction(action);

		if(isMaximizing)
		{
			if (tmpScore > score && tmpScore != 12345678)
			{
				bestAction = action;
				score = tmpScore;
			}
			alpha = std::max(score, alpha);
		}else
		{
			if (tmpScore < score && tmpScore != 12345678)
			{
				bestAction = action;
				score = tmpScore;
			}
			beta = std::min(score, beta);
		}
		if (alpha >= beta) {
			return alpha;
		}
	}

	if(isMaximizing)
	{
		if (score == -INFINITY) return 12345678;
	}else
	{
		if (score == INFINITY) return 12345678;
	}
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
		return -1000;
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

	return float(plmax - plp)/float(plmax) - float(plmax - plq)/float(SIZE*SIZE);
}
