#include "Game.hpp"


Game::Game()
{}

TileMap Game::getMap(std::string tilePath, sf::Vector2u vector, unsigned int sX, unsigned int sY)
{
	 
	int level[200] =
	{
		145, 145, 145, 145, 145, 5, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
		0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
		0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
		0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
		2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
		0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
	};
 
	if (!map.load(tilePath, sf::Vector2u(16, 16), level, 16, 16))
	{
		RessourceManager.console("Fatal Error, Map can't be loaded.");
		exit(1);
	}

	return (map);
}

Game::~Game()
{}