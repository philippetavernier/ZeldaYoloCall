#include <GL/glew.h>
#include <SFGUI/Engines/BREW.hpp>
#include <Windows.h>
#include "AnimatedSprite.hpp"
#include <SFGUI/Renderer.hpp>
#include <SFML/Graphics.hpp>
#include <SFGUI/Context.hpp>
#include <SFGUI/Window.hpp>
#include <SFGUI/SFGUI.hpp>
#include <SFML/Audio.hpp>


class Game {
public:
	Game();
	void startNewGame(void);
	void loadGame(void);
	void loadSettings(void);
	void Run(void);
	void exitGame(void);

private:
	sfg::SFGUI m_sfgui;
	//::ProgressBar progressBar;

	sf::RenderWindow render_window;
	AnimatedSprite animatedSprite;
	sfg::Desktop generalMenu;
	sfg::Desktop secondaryMenu;
	sfg::Box::Ptr m_scrolled_window_box;
	sfg::Label::Ptr m_label;
	std::string _introCaption;
	 
	sf::Mouse mouse;

	sf::Music CurrentMusic;
	sf::SoundBuffer soundBuffer;
	sf::Sound CurrentSound;

	sf::Time time;
	sf::Time beat;
	sf::Time Timetempo;

	sf::Text pressStart;
	sf::Text Current_textSlide;

	sf::Clock clk;
	sf::Clock clock;
	sf::Clock frameClock;
	sf::Clock ClkTempo;

	sf::Font font;
	sf::Event event;
	sf::Event event_intro;
	sf::Keyboard key;

	sf::Texture texture;
	sf::Texture logoMain;
	sf::Texture Triforce;
	sf::Texture slideImage;
	sf::Texture cadre;
	sf::Texture Cp1;
	sf::Texture Cp2;
	sf::Texture shield;

	sf::Sprite CurrentSlideImage;
	sf::Sprite SpriteLogoMain;
	sf::Sprite TriforceSprite;
	sf::Sprite ShieldSprite;
	sf::Sprite Cp1Sprite;
	sf::Sprite Cp2Sprite;
	sf::Sprite CadreSprite;
 
	void fadeMusic(uint16_t=0);
	void changeMusic(std::string, unsigned short int=50, bool=true, float=0);
	void changeIntroSlide(std::string, short int, unsigned short int, int, int, int, int);
	void invokeSound(std::string, unsigned short int);

	std::string Game::getIntroText(unsigned short int);
	std::string _currentMusicName, _currentTextSlide, _currentSoundName;

	bool _introDisableMove = true,
		     _showMainlogo = true,
		    _hideTriforce = false,
		            _blink = true,
		        _nextSlide = true,
		  _noKeyWasPressed = true;
	 
	unsigned int  _automoveCounter = 0, _alpha = 255, _alpha_t = 0;
	unsigned short int _activeWindow, precedentWindow, _x;
	float _speed = 80.f;


};

