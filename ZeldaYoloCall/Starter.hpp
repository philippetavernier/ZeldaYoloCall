#ifndef STARTER_INCLUDE
#define STARTER_INCLUDE

#include <Windows.h>
#include <GL/glew.h>
#include <SFGUI/Engines/BREW.hpp>
#include <SFGUI/Renderer.hpp>
#include <SFML/Graphics.hpp>
#include <SFGUI/Context.hpp>
#include <SFGUI/Window.hpp>
#include <SFML/System.hpp>
#include <SFGUI/SFGUI.hpp>
#include <SFML/Audio.hpp>
#include "AnimatedSprite.hpp"
#include "Invokation.hpp"
#include "NpcFactory.hpp"
#include "Game.hpp"

class Starter{
	enum{ INTRO, MENU, CINEMATIC, LOADStarter, SETTINGS, GAME, DEADSCREEN };

public:
	Starter();
	void startNewGame(void);
	void loadSettings(void);
	void loadGame(void);
	void exitGame(void);
	void Run(void);
	
private:
	Invokation RessourceManager;
 
	sfg::SFGUI m_sfgui;
	sfg::Desktop generalMenu, secondaryMenu;
	sfg::Box::Ptr m_scrolled_window_box;
	sfg::Label::Ptr m_label;
	std::string _introCaption;

	sf::Sprite CurrentSlideImage, SpriteLogoMain, TriforceSprite, ShieldSprite, Cp1Sprite, Cp2Sprite, CadreSprite, placeHolderSprite;
	sf::Texture texture, logoMain, Triforce, slideImage, cadre, Cp1, Cp2, shield, placeHolder;
	sf::Clock clk, clock, frameClock, ClkTempo;
	sf::Text pressStart, Current_textSlide;
	sf::Time time, beat, Timetempo;
	sf::Event event, event_intro;
	sf::SoundBuffer soundBuffer;
	sf::Music CurrentMusic;
	sf::Sound CurrentSound;
	sf::Thread fadeThread;
	sf::Mouse mouse;
	sf::Keyboard key;
	sf::Font font;

	//Animation
	Animation walkingAnimationRight, walkingAnimationDown, walkingAnimationLeft, walkingAnimationUp;
	Animation* currentAnimation;
	AnimatedSprite link;

	void changeIntroSlide(std::string, short int, unsigned short int, float, float, int, int);
	void fadeMusic(uint16_t = 0);
	void fadeInAction();

	std::string Starter::getIntroText(unsigned short int);

	bool _introDisableMove = true,
		 _showMainlogo     = true,
		 _hideTriforce     = false,
		 _blink            = true,
		 _nextSlide        = true,
		 _noKeyWasPressed  = true;

	sf::View gameView;
	Game game;

	unsigned int  _automoveCounter = 0, _alpha = 255, _alpha_t = 0;
	unsigned short int _GameState, precedentWindow, _x;
	bool first_run, fade_complete;
	std::string _currentTextSlide;
};

#endif