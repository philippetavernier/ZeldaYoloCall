#include "Starter.hpp"
#include <Windows.h>
#include <string>

Starter::Starter() : _GameState(INTRO), precedentWindow(255), _currentTextSlide("NaN"), _x(0), link(sf::milliseconds(120), true, false), fadeThread(&Starter::fadeInAction, this), gameView(sf::Vector2f(350, 300), sf::Vector2f(300, 200)) {
	RessourceManager.invokeLog();

	placeHolderSprite = RessourceManager.invokeSprite(&placeHolder, "scenarios\\I_CINEMATIC\\placeHolder.png", 365, 10, true);
	CurrentSlideImage = RessourceManager.invokeSprite(&slideImage,  "scenarios\\I_CINEMATIC\\0.png", 332, 330, true);
	TriforceSprite    = RessourceManager.invokeSprite(&Triforce,    "tilesets\\triforce.png", 332, 330, true);
	SpriteLogoMain    = RessourceManager.invokeSprite(&logoMain,    "images\\logo.png", 80, -50, true);
	ShieldSprite      = RessourceManager.invokeSprite(&shield,      "scenarios\\I_CINEMATIC\\shieldFont.png", 0, 100, true);
	CadreSprite       = RessourceManager.invokeSprite(&cadre,       "images\\cadre.png", 580, 210, true);
    Cp1Sprite         = RessourceManager.invokeSprite(&Cp1,         "images\\copyright1.png", 480, 540, true);
    Cp2Sprite         = RessourceManager.invokeSprite(&Cp2,         "images\\copyright2.png", 0, 0, true);
		   
    RessourceManager.testAndLoad(texture.loadFromFile("src\\tilesets\\player.png"), "player.png");
    RessourceManager.testAndLoad(font.loadFromFile("src\\fonts\\menu.ttf"), "menu.ttf");

	SpriteLogoMain.setColor(sf::Color(255, 255, 255, 0));

	pressStart.setString("- Press space -");
	pressStart.setPosition(325, 470);
	pressStart.setFont(font);

	_introCaption  = "\n\n\n\n\n\n\n\n\n\n\n\n\n\nA long, long time ago the World was in an age of Chaos.\n\n\n\n\n";
	_introCaption += "\n\n\n\n\n\n\n\n\n\n\n\nIn the midst of this chaos, in a little kingdom in the land of Hyrule,\na legend was being handed down from generation to generation,\nthe legend of the 'Triforce'; three golden triangles possessing\nmystical powers.\n\n\n\n\n\n\n\n\n\n\n\n\nOne day, an evil army attacked this peaceful little kingdom\nand stole the Triforce of Power.\nThis army was led by Ganon, the powerful Prince of Darkness\nwho sought to plunge the World into fear and darkness under his rule.\nFearing his wicked rule, Zelda, the princess of this kingdom, split up\nthe Triforce of Wisdom into eight fragments\nand hide them throughout the realm to save the last remaining\nTriforce from the clutches of the evil Ganon.";
	_introCaption += "\n\n\n\n\n\n\n\n\n\nBut then... just as all hope had died, a young boy clothed in green\nappeared as if from nowhere.\n\nWielding a blade that repelled evil, he sealed the dark one away\nand gave the land light.\nThis boy, who travelled through time to save the land, was known as\nthe Hero of Time.\n\nThe boy's tale was passed down through generations until it became\nlegend. Years later, darkness restarted to fall down on the earth.\nBut this time, Zelda princess was the investigator.\nWhen the time to separate the triforce symbol from Zelda came,\nthe darkness inside her was unjailed too and the dark side\n of Zelda took control of her.\nWhat became of that kingdom...? None remain who know.\nThe memory of the kingdom vanished,\nbut its legend survived on the wind’s breath.\n\n\n Link, the hero of time was jailed in the hyrule castle for the rest of\n his life.\nA new profecy was dicovered, a new mission for Link started...";
}

#pragma region Triggers

void Starter::startNewGame() {
	RessourceManager.invokeSound("LA_Menu_Select.wav", 50);
	RessourceManager.console("Entering NewStarter menu ...", 5);
	_GameState = CINEMATIC;
}

void Starter::loadGame() {
	RessourceManager.invokeSound("LA_Menu_Select.wav", 50);
	RessourceManager.console("Entering the game ...", 5);
	_GameState = GAME;
}

void Starter::loadSettings() {
	RessourceManager.invokeSound("LA_Menu_Select.wav", 50);
	RessourceManager.console("Entering Settings menu ...", 5);
}

void Starter::exitGame(){
	RessourceManager.invokeSound("LA_Menu_Select.wav", 50);
	exit(0);
}
#pragma endregion

#pragma region Methodes d Introduction
void Starter::fadeInAction(){
	while (_alpha < 255){
		sleep(sf::milliseconds(90));
		CurrentSlideImage.setColor(sf::Color(255, 255, 255, _alpha));
		_alpha++;
	}
}

void Starter::changeIntroSlide(std::string tostr, short int textureId, unsigned short int timeBeforeFade, float pos_x, float pos_y, int t_pos_x, int t_pos_y){
	if (tostr != _currentTextSlide){
		CurrentSlideImage = RessourceManager.invokeSprite(&slideImage, "scenarios\\I_CINEMATIC\\" + tostr, pos_x, pos_y, true);
		CurrentSlideImage.setColor(sf::Color(255, 255, 255, 0));
		_alpha = 0;
		fadeThread.launch();
	}
}
#pragma endregion

void Starter::Run() {

	sf::RenderWindow render_window(sf::VideoMode(GetPrivateProfileInt("Graphics", "screenDimX", 0, "src\\iniFiles\\customCommands.ini"), GetPrivateProfileInt("Graphics", "screenDimY", 0, "src\\iniFiles\\customCommands.ini")), "Zelda : The Yolo Call");

	auto   window = sfg::Window::Create();
	auto buttonNG = sfg::Button::Create("New game...");
	     buttonNG->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&Starter::startNewGame, this));
	auto buttonLG = sfg::Button::Create("Load game...");
	     buttonLG->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&Starter::loadGame, this));
	auto buttonOPT = sfg::Button::Create("Settings");
	     buttonOPT->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&Starter::loadSettings, this));
	auto buttonQUIT= sfg::Button::Create("Exit");
	     buttonQUIT->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&Starter::exitGame, this));

	auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
	     box->Pack(buttonNG,   false);
	     box->Pack(buttonLG,   false);
	     box->Pack(buttonOPT,  false);
	     box->Pack(buttonQUIT, false);

	auto menuBar = sfg::Window::Create();
	     menuBar->Add(box);
	     menuBar->SetStyle(8);
	     menuBar->SetPosition(sf::Vector2f(610.f, 250.f));

	auto cinematicScrollBar = sfg::Window::Create();
	     cinematicScrollBar->SetStyle(8);
	     cinematicScrollBar->SetPosition(sf::Vector2f(357.f, 92.f));

	auto viewport_box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
	     viewport_box->Pack(sfg::Label::Create(_introCaption.c_str()));
	auto viewport = sfg::Viewport::Create();
	     viewport->SetRequisition(sf::Vector2f(430.f, 350.f));
	     viewport->GetVerticalAdjustment()->SetLower(-500.f);
	     viewport->GetVerticalAdjustment()->SetUpper(100000000.f);
	     viewport->Add(viewport_box);

	auto box2 = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.f);
	     box2->Pack(viewport, true, true);

	
	secondaryMenu.Add(cinematicScrollBar);
	cinematicScrollBar->Add(box2);
	generalMenu.Add(menuBar);

	render_window.resetGLStates();
	render_window.setFramerateLimit(60);
	
	NpcFactory *introLink = new NpcFactory(NpcFactory::CHICKEN, link, NpcFactory::Move::DOWN);
				introLink->virtualize(400, 817);
	 
					
	while (render_window.isOpen()) {
		while (render_window.pollEvent(event)){
			generalMenu.HandleEvent(event);
			secondaryMenu.HandleEvent(event_intro);

			if (event.type == sf::Event::Closed)		
				render_window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				render_window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S && _GameState == INTRO)
				_GameState = MENU;
			if (event.type == sf::Event::LostFocus)
				int foo = 1;
		}

		sf::Time frameTime = frameClock.restart();
		sf::Vector2f movement(0.f, 0.f);
		 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			currentAnimation = introLink->setOrientation(NpcFactory::UP);
			movement.y -= introLink->getDefaultSpeed();
			_noKeyWasPressed = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			currentAnimation = introLink->setOrientation(NpcFactory::DOWN);
			movement.y += introLink->getDefaultSpeed();
			_noKeyWasPressed = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			currentAnimation = introLink->setOrientation(NpcFactory::LEFT);
			movement.x -= introLink->getDefaultSpeed();
			_noKeyWasPressed = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			currentAnimation = introLink->setOrientation(NpcFactory::RIGHT);
			movement.x += introLink->getDefaultSpeed();
			_noKeyWasPressed = false;
		}

		if (_GameState == CINEMATIC && _nextSlide){
			fadeThread.terminate();
			++_x;
			RessourceManager.console("Changing Intro slide... ", 2);
			changeIntroSlide(std::to_string(_x) + ".png", _x, 20, 9, 90, 375, 300);
			_nextSlide = false;
		}

		if (_introDisableMove && _GameState == INTRO){
			_noKeyWasPressed = true;
			currentAnimation = introLink->setOrientation(NpcFactory::UP);
			movement.y -= introLink->getDefaultSpeed();
			_automoveCounter++;

			if (_automoveCounter == 276)
			{
				RessourceManager.console("Introduction [Stopped]", 0);
				_introDisableMove = false;
			}
		}


		link.play(*currentAnimation);
		link.move(movement * frameTime.asSeconds());

		if (!_introDisableMove && _GameState == INTRO){
			if (_alpha != 0){

				TriforceSprite.setColor(sf::Color(255, 255, 255, _alpha));
				Cp2Sprite.setColor(sf::Color(255, 255, 255, _alpha));
				_alpha--;
			}

			if (_alpha == 0 && _alpha_t != 240){
				SpriteLogoMain.setColor(sf::Color(255, 255, 255, _alpha_t));
				sleep(sf::microseconds(2000));
				if (_alpha_t < 255)
					_alpha_t++;
				if (_alpha_t > 200)
					currentAnimation = introLink->setOrientation(NpcFactory::DOWN);
			}
		}

		if (_noKeyWasPressed && !_introDisableMove)
			link.stop();

		_noKeyWasPressed = true;
		link.update(frameTime);

		beat = clk.getElapsedTime();
		render_window.clear();

		if (beat.asSeconds() > 1 && _GameState == INTRO)
			render_window.draw(pressStart);
		if (beat.asSeconds() > 3 && _GameState == INTRO)
			clk.restart();

		if (_GameState == CINEMATIC){
			if (clock.getElapsedTime().asMicroseconds() >= 2000){
				auto delta = static_cast<float>(clock.getElapsedTime().asMicroseconds()) / 1000000.f;
				viewport->GetVerticalAdjustment()->SetValue(viewport->GetVerticalAdjustment()->GetValue() + delta * 13.f);
				clock.restart();
			}
		}
		switch (_GameState){
		case INTRO:
			RessourceManager.invokeMusic("intro.ogg", 40, true);
			render_window.draw(SpriteLogoMain);
			render_window.draw(TriforceSprite);
			render_window.draw(Cp2Sprite);
			render_window.draw(Cp1Sprite);
			render_window.draw(link);
			break;

		case GAME:
			render_window.clear();
 
				
			render_window.draw(game.getMap("src\\tilesets\\9445.png", sf::Vector2u(16, 16), 16, 16));
			break;


		case MENU:
			RessourceManager.invokeMusic("menu.ogg", 40, true, 0);
			render_window.draw(ShieldSprite);
			render_window.draw(CadreSprite);
			generalMenu.Update(clock.restart().asSeconds());
			m_sfgui.Display(render_window);
			break;

		case CINEMATIC:
			if (_x == 0){ ClkTempo.restart(); RessourceManager.console("Clk refreshed.", 0); }
			RessourceManager.invokeMusic("introMusic.ogg", 40, false, 1);
			Timetempo = ClkTempo.getElapsedTime();
			float t = Timetempo.asSeconds();

			if (t > _x * 19 && t < (_x + 1) * 19.05 && _x < 6){
				RessourceManager.console("[Changing Intro slide] -> Actual is " + std::to_string(_x), 2);
				_nextSlide = true;
				sleep(sf::microseconds(200));
			}

			if (_x == 5)
				_GameState = GAME;

			render_window.draw(CurrentSlideImage);
			render_window.draw(placeHolderSprite);
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



