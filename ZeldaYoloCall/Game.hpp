#ifndef __GAME_INCLUDE
#define __Game_INCLUDE

#include <iostream>
#include <Windows.h>
#include <GL/glew.h>
#include "AnimatedSprite.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "Invokation.hpp"
#include "TiledMap.h"

struct Game
{
	public:
		Game();
		~Game();

		TileMap getMap(std::string, sf::Vector2u, unsigned int, unsigned int);
		bool isPlaying();
		sf::RenderWindow setGameState(sf::RenderWindow, unsigned short int);
		


	private:
		Invokation RessourceManager;
		TileMap map;
};



#endif