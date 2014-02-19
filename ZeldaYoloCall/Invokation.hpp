#ifndef INVOKATION_INCLUDE
#define INVOKATION_INCLUDE

#include <iostream>
#include <Windows.h>
#include <GL/glew.h>
#include <SFGUI/Engines/BREW.hpp>
#include "AnimatedSprite.hpp"
#include <SFGUI/Renderer.hpp>
#include <SFML/Graphics.hpp>
#include <SFGUI/Context.hpp>
#include <SFGUI/Window.hpp>
#include <SFML/System.hpp>
#include <SFGUI/SFGUI.hpp>
#include <SFML/Audio.hpp>

class Invokation
{
	public:
		Invokation();

		void invokeMusic(std::string, unsigned short int = 50, bool = true, float = 0);
		void changeIntroSlide(std::string, short int, unsigned short int, float, float, int, int);
		void invokeSound(std::string, unsigned short int);
		void testAndLoad(bool, std::string);
		void console(std::string, unsigned int=0);
		void invokeLog(void);

		sf::Music getMusic();
		sf::Sound getSound();
		sf::SoundBuffer getSoundBuffer();

	private:
		std::string _currentMusicName,
					_currentTextSlide,
					_currentSoundName,
					_oldMusicName;

		sf::Music _currentMusic;
		sf::SoundBuffer _soundBuffer;
		sf::Sound _currentSound;


};



#endif