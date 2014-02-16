#include "Utilities.h"
#include <Windows.h>
#include <string>
#include "Game.h"

enum{ INTRO, MENU, CINEMATIC, LOADGAME, NEWGAME, SETTINGS };

#pragma region Constructeur
Game::Game() : _activeWindow(INTRO), precedentWindow(255), _currentMusicName("Intro.ogg"), _currentTextSlide("NaN"), _x(0)
{
	initLog();

#pragma region Preload
	testRessource(logoMain.loadFromFile("src\\images\\logo.png"), "logo.jpg");
	testRessource(Triforce.loadFromFile("src\\tilesets\\triforce.png"), "triforce.jpg");
	testRessource(Cp1.loadFromFile("src\\images\\copyright1.png"), "copyright1.jpg");
	testRessource(Cp2.loadFromFile("src\\images\\copyright2.png"), "copyright2.jpg");
	testRessource(font.loadFromFile("src\\fonts\\menu.ttf"), "menu.ttf");
	testRessource(texture.loadFromFile("src\\tilesets\\player.png"), "player.png");
	testRessource(shield.loadFromFile("scenarios\\I_CINEMATIC\\darkZelda.png"), "darkZelda.png");
	testRessource(slideImage.loadFromFile("scenarios\\I_CINEMATIC\\0.png"), "0.png");
	testRessource(cadre.loadFromFile("src\\images\\cadre.png"), "cadre.png");
#pragma endregion
	
	logoMain.setSmooth(true);
	Triforce.setSmooth(true);
	shield.setSmooth(true);
	Cp1.setSmooth(true);
	Cp1.setSmooth(true);
	slideImage.setSmooth(true);
	cadre.setSmooth(true);

	TriforceSprite.setTexture(Triforce);
	SpriteLogoMain.setTexture(logoMain);
	Cp1Sprite.setTexture(Cp1);
	Cp2Sprite.setTexture(Cp2);
	ShieldSprite.setTexture(shield);
	CadreSprite.setTexture(cadre);

	TriforceSprite.setPosition(332, 330);
	SpriteLogoMain.setPosition(80, -50);
	ShieldSprite.setPosition(0, 100);
	Cp1Sprite.setPosition(100, 480);
	Cp1Sprite.setPosition(480, 540);
	CadreSprite.setPosition(580, 210);

	SpriteLogoMain.setColor(sf::Color(255, 255, 255, 0));

	pressStart.setString("- Press start -");
	pressStart.setFont(font);
	pressStart.setPosition(325, 470);
    
	_introCaption = "\n\n\n\n\n\n\n\n\n\n\n\n\n\nA long, long time ago the World was in an age of Chaos.\n\n\n\n\n";
	_introCaption += "\n\n\n\n\n\n\n\n\n\n\n\nIn the midst of this chaos, in a little kingdom in the land of Hyrule,\na legend was being handed down from generation to generation,\nthe legend of the 'Triforce'; three golden triangles possessing\nmystical powers.\n\n\n\n\n\n\n\n\n\n\n\n\nOne day, an evil army attacked this peaceful little kingdom\nand stole the Triforce of Power.\nThis army was led by Ganon, the powerful Prince of Darkness\nwho sought to plunge the World into fear and darkness under his rule.\nFearing his wicked rule, Zelda, the princess of this kingdom, split up\nthe Triforce of Wisdom into eight fragments\nand hide them throughout the realm to save the last remaining\n Triforce from the clutches of the evil Ganon.";

	_introCaption += " \n\n\n\n\n\n\n\n\n\nBut then... just as all hope had died, a young boy clothed in green\nappeared as if from nowhere.\n\nWielding a blade that repelled evil, he sealed the dark one away\nand gave the land light.\nThis boy, who travelled through time to save the land, was known as\nthe Hero of Time.\nThe boy's tale was passed down through generations until it became\nlegend. And then came a day when a fell wind began to blow\nacross the kingdom, and the great evil once again crept forth from\nthe depths of the earth.The people believed that the\nHero of Time would again come to save them.But the hero did not appear...\nWhat became of that kingdom...? None remain who know.\nThe memory of the kingdom vanished,\nbut its legend survived on the wind’s breath.";


}
#pragma endregion
 
#pragma region Methodes Musicales

void Game::fadeMusic(uint16_t c)
{
	std::cout << CurrentMusic.getVolume() << std::endl;
	if (c == 1)
	{
		prompt("Fading music IN... ", 2);
		for (float i = 0.f; i <= CurrentMusic.getVolume(); i += 1.f)
			CurrentMusic.setVolume(i);
	}
	else
	{
		for (float i = CurrentMusic.getVolume(); i >= 0; i -= 1.f)
		{
			prompt("Fading music OUT... - Value = " + (int)i  , 2);
			CurrentMusic.setVolume(i);
		}
			
	}
}

void Game::changeMusic(std::string MusicName, unsigned short int volume, bool isLooping, float offset)
{
	if (_currentMusicName != MusicName)
	{
		std::string oldName = _currentMusicName;

		_currentMusicName = MusicName;
		testRessource(CurrentMusic.openFromFile("src\\sounds\\" + MusicName), MusicName);

		CurrentMusic.setPlayingOffset(sf::seconds(offset));
		CurrentMusic.setLoop(isLooping);
		CurrentMusic.setVolume(volume);
		prompt("Changing music : OLD -> " + oldName + ", NEW -> " + _currentMusicName, 2);
		CurrentMusic.play();
	}
}

void Game::invokeSound(std::string SoundName, unsigned short int volume)
{
	if (_currentSoundName != SoundName)
	{
		_currentSoundName = SoundName;
		testRessource(soundBuffer.loadFromFile("src\\sounds\\peac\\" + SoundName), SoundName);
		CurrentSound.setBuffer(soundBuffer);
		CurrentSound.setVolume(volume);
		prompt("Invoking sound :" +  _currentMusicName, 2);
		CurrentSound.play();
	}
}
#pragma endregion

#pragma region Triggers
void Game::startNewGame() {
	invokeSound("LA_Menu_Select.wav", 50);
	prompt("Entering NewGame menu ...", 5);

	_activeWindow = CINEMATIC;
}
 
void Game::loadGame() {
	invokeSound("LA_Menu_Select.wav", 50);
	prompt("Entering loadGame menu ...", 5);
}

void Game::loadSettings() {
	invokeSound("LA_Menu_Select.wav", 50);
	prompt("Entering Settings menu ...", 5);
}

void Game::exitGame(){
	invokeSound("LA_Menu_Select.wav", 50);
	exit(0);
}
#pragma endregion

#pragma region Methodes d Introduction
 

void Game::changeIntroSlide(std::string tostr, short int textureId, unsigned short int timeBeforeFade, int pos_x, int pos_y, int t_pos_x,  int t_pos_y)
{	
	if (tostr != _currentTextSlide)
	{
		testRessource(slideImage.loadFromFile("scenarios\\I_CINEMATIC\\" + tostr), tostr);
		CurrentSlideImage.setPosition(pos_x, pos_y);
 
		CurrentSlideImage.setTexture(slideImage);
		 
	}
}
#pragma endregion

void Game::Run() {
	int scrX = GetPrivateProfileInt("Graphics", "screenDimX", 0, "src\\iniFiles\\customCommands.ini");
	int scrY = GetPrivateProfileInt("Graphics", "screenDimY", 0, "src\\iniFiles\\customCommands.ini");

	const int SCREEN_WIDTH = scrX;
	const int SCREEN_HEIGHT = scrY;

	sf::RenderWindow render_window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Zelda : The Yolo Call");
	auto window = sfg::Window::Create();

	auto buttonNG = sfg::Button::Create("New game...");
		 buttonNG->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&Game::startNewGame, this));

	auto buttonLG = sfg::Button::Create("Load game...");
		 buttonLG->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&Game::loadGame, this));

	auto buttonOPT = sfg::Button::Create("Settings");
	     buttonOPT->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&Game::loadSettings, this));

    auto buttonQUIT = sfg::Button::Create("Exit");
		 buttonQUIT->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&Game::exitGame, this));

    auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
	     box->Pack(buttonNG, false);
		 box->Pack(buttonLG, false);
		 box->Pack(buttonOPT, false);
		 box->Pack(buttonQUIT, false);

    auto menuBar = sfg::Window::Create();
		 menuBar->Add(box);
		 menuBar->SetStyle(8);
		 menuBar->SetPosition(sf::Vector2f(610.f, 250.f));

	auto cinematicScrollBar = sfg::Window::Create();
		 cinematicScrollBar->SetStyle(8);
		 cinematicScrollBar->SetPosition(sf::Vector2f(355.f, -50.f));

		 auto viewport = sfg::Viewport::Create();
		 
			  viewport->SetRequisition(sf::Vector2f(430.f, 350.f));
			  viewport->GetVerticalAdjustment()->SetLower(-500.f);
		      viewport->GetVerticalAdjustment()->SetUpper(100000000.f);

		 auto viewport_box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
		 

		 viewport_box->Pack(sfg::Label::Create(_introCaption.c_str()));
		  
		      viewport->Add(viewport_box);

		
		 auto box2 = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.f);
		      box2->Pack(viewport, true, true);


		 cinematicScrollBar->Add(box2);

	generalMenu.Add(menuBar);
	secondaryMenu.Add(cinematicScrollBar);

	render_window.resetGLStates();
	render_window.setFramerateLimit(60);

	Animation walkingAnimationDown;
	walkingAnimationDown.setSpriteSheet(texture);
	walkingAnimationDown.addFrame(sf::IntRect(268, 15, 18, 25));
	walkingAnimationDown.addFrame(sf::IntRect(0, 150, 18, 25));
	walkingAnimationDown.addFrame(sf::IntRect(52, 150, 18, 25));
	walkingAnimationDown.addFrame(sf::IntRect(80, 152, 18, 25));
	walkingAnimationDown.addFrame(sf::IntRect(52, 150, 18, 25));
	prompt("PlayerTile loaded : 25 %", 1);

	Animation walkingAnimationLeft;
	walkingAnimationLeft.setSpriteSheet(texture);
	walkingAnimationLeft.addFrame(sf::IntRect(246, 153, 20, 26));
	walkingAnimationLeft.addFrame(sf::IntRect(274, 153, 20, 26));
	walkingAnimationLeft.addFrame(sf::IntRect(304, 153, 20, 26));
	walkingAnimationLeft.addFrame(sf::IntRect(335, 153, 32, 32));
	prompt("PlayerTile loaded : 50 %", 1);

	Animation walkingAnimationRight;
	walkingAnimationRight.setSpriteSheet(texture);
	walkingAnimationRight.addFrame(sf::IntRect(32, 96, 32, 32));
	walkingAnimationRight.addFrame(sf::IntRect(64, 96, 28, 32));
	walkingAnimationRight.addFrame(sf::IntRect(32, 96, 32, 32));
	walkingAnimationRight.addFrame(sf::IntRect(0, 95, 32, 32));
	prompt("PlayerTile loaded : 75 %", 1);

	Animation walkingAnimationUp;
	walkingAnimationUp.setSpriteSheet(texture);
	walkingAnimationUp.addFrame(sf::IntRect(209, 90, 18, 28));
	walkingAnimationUp.addFrame(sf::IntRect(234, 90, 18, 28));
	walkingAnimationUp.addFrame(sf::IntRect(260, 90, 18, 28));
	walkingAnimationUp.addFrame(sf::IntRect(289, 90, 18, 28));
	prompt("PlayerTile loaded : 100 %", 1);

	Animation* currentAnimation = &walkingAnimationDown;
	AnimatedSprite animatedSprite(sf::seconds(0.12), true, false);
	animatedSprite.setPosition(400, 750);
  
	render_window.resetGLStates();

	while (render_window.isOpen()) {
		while (render_window.pollEvent(event))
		{
			        generalMenu.HandleEvent(event);
			secondaryMenu.HandleEvent(event_intro);

			if (event.type == sf::Event::Closed)
				render_window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				render_window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
				_activeWindow = MENU;
			if (event.type == sf::Event::LostFocus)
			{
				int foo = 1;
			}
				//Call pause
		}

		sf::Time frameTime = frameClock.restart();
		sf::Vector2f movement(0.f, 0.f);


		if (_activeWindow == CINEMATIC && _nextSlide)
		{
				_x++;
				prompt("Changing Intro slide... ", 2);
				changeIntroSlide(std::to_string(_x) + ".png", _x, 20, 9, 90, 375, 300);
				_nextSlide = false;
		}

		if (_introDisableMove && _activeWindow == INTRO)
		{
			_speed = 60.f;
			_noKeyWasPressed = true;
			currentAnimation = &walkingAnimationUp;
			movement.y -= _speed;
			_automoveCounter++;

			if (_automoveCounter == 276)
			{
				_speed = 52.f;
				prompt("Introduction [Stopped]", 0);
				_introDisableMove = false;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			currentAnimation = &walkingAnimationUp;
			movement.y -= _speed;
			_noKeyWasPressed = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			currentAnimation = &walkingAnimationDown;
			movement.y += _speed;
			_noKeyWasPressed = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			currentAnimation = &walkingAnimationLeft;
			movement.x -= _speed;
			_noKeyWasPressed = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			currentAnimation = &walkingAnimationRight;
			movement.x += _speed;
			_noKeyWasPressed = false;
		}

		animatedSprite.play(*currentAnimation);
		animatedSprite.move(movement * frameTime.asSeconds());
 
		if (!_introDisableMove && _activeWindow == INTRO)
		{
			if (_alpha != 0)
			{
				std::cout << _alpha << ",";
				TriforceSprite.setColor(sf::Color(255, 255, 255, _alpha));
				Cp2Sprite.setColor(sf::Color(255, 255, 255, _alpha));
				_alpha--;
			}

			if (_alpha == 0 && _alpha_t != 240)
			{
				SpriteLogoMain.setColor(sf::Color(255, 255, 255, _alpha_t));
				sleep(sf::microseconds(2000));
				if (_alpha_t < 255)
					_alpha_t++;
				if (_alpha_t > 200)
					currentAnimation = &walkingAnimationDown;
			}
		}

		if (_noKeyWasPressed && !_introDisableMove)
			animatedSprite.stop();

		_noKeyWasPressed = true;
		animatedSprite.update(frameTime);
		 
		beat = clk.getElapsedTime();
		render_window.clear();
 
		if (beat.asSeconds() > 1 && _activeWindow == INTRO)
			render_window.draw(pressStart);
		if (beat.asSeconds() > 3 && _activeWindow == INTRO)
			clk.restart();

		if (_activeWindow == CINEMATIC)
		{
		
			if (clock.getElapsedTime().asMicroseconds() >= 2000) {
				auto delta = static_cast<float>(clock.getElapsedTime().asMicroseconds()) / 1000000.f;
				viewport->GetVerticalAdjustment()->SetValue(viewport->GetVerticalAdjustment()->GetValue() + delta * 13.f);
				clock.restart();
			}
		}
		switch (_activeWindow)
		{

		case INTRO:
			changeMusic("intro.ogg", 40, true);
			render_window.draw(SpriteLogoMain);
			render_window.draw(TriforceSprite);
			render_window.draw(Cp2Sprite);
			render_window.draw(Cp1Sprite);
			render_window.draw(animatedSprite);
			break;

		case MENU:
		    changeMusic("fairyIntro.ogg", 40, true, 0);
			render_window.draw(ShieldSprite);
			render_window.draw(CadreSprite);
			generalMenu.Update(clock.restart().asSeconds());
			m_sfgui.Display(render_window);
			break;

		case CINEMATIC:
			if (_x == 0){ ClkTempo.restart(); prompt("Clk refreshed.", 0); }
	 
			      changeMusic("introMusic.ogg", 40, false, 1);
			          Timetempo = ClkTempo.getElapsedTime();
			float t = Timetempo.asSeconds();
		
			if (t > _x * 19 && t < (_x+1) * 19.05 && _x < 4)
			{
				prompt("[Changing Intro slide] -> Actual is " + std::to_string(_x), 2);
				_nextSlide = true;
				sleep(sf::microseconds(200));
			}
	 
			render_window.draw(CurrentSlideImage);
			render_window.draw(Current_textSlide);
			box->Show(false);
			generalMenu.RemoveAll();
			secondaryMenu.Update(clock.restart().asSeconds());
			m_sfgui.Display(render_window);
			break;
		}		
		
		render_window.display();
	}
}



