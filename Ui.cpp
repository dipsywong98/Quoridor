#include "Ui.h"
#include <iostream>


Ui::Ui()
{
	pGame = new Game();
	int windowSize = SIZE * (GRID_WIDTH + WALL_WIDTH);
	pWindow = new sf::RenderWindow(sf::VideoMode(windowSize, windowSize), "Quoridor");
}


Ui::~Ui()
{
	delete pGame;
}

void Ui::main()
{
	while (pWindow->isOpen())
	{
		sf::Event event;
		while (pWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				pWindow->close();
			if (event.type == sf::Event::MouseMoved)
			{
				cursorPos = sf::Mouse::getPosition(*pWindow);
			}
		}
		render();
	}
}

void Ui::render()
{
	pWindow->clear();
	sf::RectangleShape baseShape({baseSize,baseSize });
	baseShape.setFillColor(sf::Color::Blue);
	pWindow->draw(baseShape);
	for(int i=0;i<SIZE; i++)
	{
		for(int j=0; j<SIZE; j++)
		{
			sf::RectangleShape gridShape({ GRID_WIDTH, GRID_WIDTH });
			gridShape.setFillColor(sf::Color::White);
			gridShape.setPosition(i*(GRID_WIDTH + WALL_WIDTH), j*(GRID_WIDTH + WALL_WIDTH));
			pWindow->draw(gridShape);
		}
	}
	Coord wallCoord;
	bool isHorizontal;
	if(screenCoord2WallCoord(cursorPos, wallCoord, isHorizontal))
	{
		sf::Vector2<float> wallShapeSize;
		if(isHorizontal)
		{
			wallShapeSize = { 2 * GRID_WIDTH + WALL_WIDTH, WALL_WIDTH };
		}else
		{
			wallShapeSize = { WALL_WIDTH, 2 * GRID_WIDTH + WALL_WIDTH };
		}
		sf::RectangleShape wallShape(wallShapeSize);
		wallShape.setFillColor(sf::Color::Red);
		float wsX = (wallCoord.x / 2)*(GRID_WIDTH + WALL_WIDTH) + !isHorizontal * GRID_WIDTH;
		float wsY = (wallCoord.y / 2)*(GRID_WIDTH + WALL_WIDTH) + isHorizontal*GRID_WIDTH;
		std::cout << wsX << " " << wsY << std::endl;
		wallShape.setPosition(wsX, wsY);
		pWindow->draw(wallShape);
	}
	pWindow->display();
}

bool Ui::screenCoord2WallCoord(const sf::Vector2i& position, Coord& wallCoord, bool& isHorizontal)
{
	int x = position.x;
	int y = position.y;
	if (x > baseSize || y > baseSize)return false;
	x %= GRID_WIDTH + WALL_WIDTH;
	y %= GRID_WIDTH + WALL_WIDTH;

	isHorizontal = x < GRID_WIDTH && y > GRID_WIDTH;
	bool isWallSlot = x > GRID_WIDTH && y < GRID_WIDTH || isHorizontal;
	if (!isWallSlot)return false;
	wallCoord.x = 2*(position.x / (GRID_WIDTH + WALL_WIDTH)) + !isHorizontal;
	wallCoord.y = 2*(position.y / (GRID_WIDTH + WALL_WIDTH)) + isHorizontal;
	return true;
}
