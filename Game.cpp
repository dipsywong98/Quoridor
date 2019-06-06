#include "Game.h"
#include <cstring>
#include <queue>
#include "Node.h"

const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { -1, 0, 1, 0 };


Game::Game()
{
	pPlayers[0] = new Player(this, {SIZE / 2, 0}, WALL_CNT);
	pPlayers[1] = new Player(this, { SIZE / 2, SIZE - 1 }, WALL_CNT);
	memset(walls, 0, (2*SIZE - 1)*(2 * SIZE - 1));
}


Game::~Game()
{
	delete pPlayers[0];
	delete pPlayers[1];
}

bool Game::validateAndPlaceWall(int playerId, Coord position)
{
	bool isHorizontal;
	const int x = position.x;
	const int y = position.y;
	if(validateWallPlacement(position, isHorizontal))
	{
		if(pPlayers[playerId]->wallsLeft > 0)
		{
			if (isHorizontal)
			{
				walls[x][y] = walls[x + 1][y] = walls[x + 2][y] = true;
			}
			else
			{
				walls[x][y] = walls[x][y + 1] = walls[x][y + 2] = true;
			}
			--pPlayers[playerId]->wallsLeft;
			return true;
		}
	}
	return false;
}

bool Game::validateWallPlacement(Coord position, bool& isHorizontal)
{
	const int x = position.x;
	const int y = position.y;
	// one and only one of the x, y is odd
	if (x%2 + y%2 != 1) return false;

	isHorizontal = y % 2;

	//within placeable range
	if (x > (SIZE - 2)*2 + !isHorizontal || y > (SIZE - 2)*2 + isHorizontal || x < 0 || y < 0)return false;

	// places not occupied
	if(isHorizontal)
	{
		if (walls[x][y] || walls[x+ 1][y] || walls[x + 2][y])return false;
		walls[x][y] = walls[x + 1][y] = walls[x + 2][y] = true;
	}else
	{
		if (walls[x][y] || walls[x ][y+1] || walls[x ][y+2])return false;
		walls[x][y] = walls[x][y + 1] = walls[x][y + 2] = true;
	}
	bool pathExist = isPathExist(0) >= 0 && isPathExist(1) >= 0;

	if (isHorizontal)
	{
		walls[x][y] = walls[x + 1][y] = walls[x + 2][y] = false;
	}
	else
	{
		walls[x][y] = walls[x][y + 1] = walls[x][y + 2] = false;
	}
	return pathExist;
}

int Game::isPathExist(int playerId)
{
	const Coord& start = pPlayers[playerId]->position;
	int targetY = 0;
	if(playerId == 1)
	{
		targetY = SIZE - 1;
	}
	std::priority_queue<Node> queue;
	queue.emplace(start, 0, abs(start.y - targetY));
	bool visited[SIZE][SIZE];
	memset(visited, 0, SIZE*SIZE);
	visited[start.x][start.y] = true;
	while(!queue.empty())
	{
		const Node& node = queue.top();
		queue.pop();
		std::vector<Coord> neighbours = getWalkableNeightborNodes(node);
		for(auto&& n: neighbours)
		{
			if (visited[n.x][n.y])continue;
			if (abs(n.y - targetY) == 0)return node.sourceDistance + 1;
			queue.emplace(n, node.sourceDistance + 1, abs(n.y - targetY));
			visited[n.x][n.y] = true;
		}
	}

	return -1;
}

std::vector<Coord> Game::getWalkableNeightborNodes(const Coord& position)
{
	const int x = position.x;
	const int y = position.y;
	std::vector<Coord> nodes;
	for (int i = 0; i < 4; i++)
	{
		if (x + dx[i] < 0 || y + dy[i] < 0 || x + dx[i] >= SIZE || y + dy[i] >= SIZE)continue;
		if (walls[x * 2 + dx[i]][y * 2 + dy[i]])continue;
		nodes.emplace_back(x + dx[i], y + dy[i]);
	}
	return nodes;
}