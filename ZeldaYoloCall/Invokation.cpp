#include "Invokation.hpp"
#include "Utilities.h"
#include <iostream>

Invokation::Invokation() : _currentMusicName("Intro.ogg"), _currentTextSlide(""), _currentSoundName("")
{}

void Invokation::testAndLoad(bool state, std::string name)
{
	if (!state)
	{
		console("Failed to load ressource : " + name, 1);
		std::getchar();
		exit(-1);
	}
	else
		console(name + " Loaded 100 %", 1);
}

void Invokation::invokeMusic(std::string MusicName, unsigned short int volume, bool isLooping, float offset)
{
	if (_currentMusicName != MusicName)
	{
		_oldMusicName = _currentMusicName;
		_currentMusicName = MusicName;
		testAndLoad(_currentMusic.openFromFile("src\\sounds\\" + MusicName), MusicName);
		_currentMusic.setPlayingOffset(sf::seconds(offset));
		_currentMusic.setLoop(isLooping);
		_currentMusic.setVolume(volume);
		console("Changing music : OLD -> " + _oldMusicName + ", NEW -> " + _currentMusicName, 2);
		_currentMusic.play();
	}
}

void Invokation::invokeSound(std::string SoundName, unsigned short int volume)
{
	if (_currentSoundName != SoundName)
	{
		_currentSoundName = SoundName;
		testAndLoad(_soundBuffer.loadFromFile("src\\sounds\\peac\\" + SoundName), SoundName);
		_currentSound.setBuffer(_soundBuffer);
		_currentSound.setVolume(volume);
		console("Invoking sound : " + SoundName, 2);
		_currentSound.play();
	}
}

	void Invokation::console(std::string str, unsigned int type)
	{
		std::string keychain;

		switch (type)
		{
		case 0:
			keychain = "[Other] ";
			break;
		case 1:
			keychain = "[Texture] ";
			break;
		case 2:
			keychain = "[Music] ";
			break;
		case 3:
			keychain = "[Sound] ";
			break;
		case 4:
			keychain = "[Info]";
			break;
		case 5:
			keychain = "[Alert]";
			break;
		default:
			keychain = "";
		}
		keychain += str;
		std::cout << keychain << std::endl;
	}

	void Invokation::invokeLog(void)
	{
		console("=========================================");
		console("====   Popolino's LogSplat  (v1.0)   ====");
		console("=========================================\n");
		console("       ** [LOADING COMPONENTS] **\n");
	}

