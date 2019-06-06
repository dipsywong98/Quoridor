#include "Player.h"


Player::Player(Game* pGame, Coord position, int walls):pGame(pGame), position(position), wallsLeft(walls)
{
}

Player::~Player()
{
}
