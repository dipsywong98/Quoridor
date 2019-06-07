#pragma once
#define SIZE 7
#define WALL_CNT 10
#include "Player.h"
#include <vector>

/**
 * Chess Coordinate system:
 * 0 || 1 || 2 || 3 || 4 || 5 || 6 -> X
 *===||===||===||===||===||===||===
 * 1 || ...
 * ==|| ...
 * 2 || ...
 * ==|| ...
 * ...
 * 6 || ...
 * |
 * v
 * Y
 * 
 * (3,0) and (3,6) are the initial points
 * 
 * Wall coordinate system will occupy the little square also
 * For instance the Vertical walls coordinate system
 * x is the big squares for the chess
 * 
 * 0 |1| 2 |3| 4 |5| 6 |7| 8 |9| 10 |11| 12 -> X
 * 1=||===| |===| |===| |===| |===| |===
 * 2 || ...
 * 3=|| ...
 * 4 || ...
 * 5=|| ...
 * ...
 * 12 || ...
 * |
 * v
 * Y
 */

class Game
{
public:
	Game();
	~Game();

	/**
	 * the position is the left or top of wall in wall coordinate
	 * return whether successfully placed the wall
	 */
	bool validateAndPlaceWall(int playerId, Coord position);


	/**
	 * the position is the left or top of wall in wall coordinate
	 * return whether the wall can place within the game field
	 * and the place is not occupied by other walls
	 * and check is path defined
	 */
	bool validateWallPlacement(Coord position, bool& isHorizontal);

	/**
	 * for A* path finding, return the length of path
	 * -1 for no path
	 */
	int isPathExist(int playerId);
	std::vector<Coord> getWalkableNeightborNodes(const Coord& position);
	bool isWalkable(int x, int y, int direction);

	/**
	 *
	 */
	std::vector<Coord> getPossibleChessMovements(int playerId);
	bool validateChessMove(int playerId, const Coord& position);

	bool walls[2 * SIZE-1][2 * SIZE - 1]; // walls
	Player* pPlayers[2];
	bool turn = 0;
};

