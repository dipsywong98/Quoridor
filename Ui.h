#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"

#define GRID_WIDTH 50
#define WALL_WIDTH 10

class Ui
{
public:
	Ui();
	~Ui();
	void main();
	void render();

	/**
	 * return whether is a wall location
	 */
	bool screenCoord2WallCoord(const sf::Vector2i& position, Coord& wallCoord, bool& isHorizontal);


	const float baseSize = SIZE * GRID_WIDTH + (SIZE - 1)*WALL_WIDTH;
	sf::RenderWindow* pWindow;
	sf::Vector2i cursorPos;
	Game* pGame;
};

