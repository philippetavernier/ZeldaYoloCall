#include "Starter.hpp"
#include <Windows.h>
#include <string>

Starter::Starter() : _GameState(INTRO), precedentWindow(255), _currentTextSlide("NaN"), _x(0), animatedSprite(sf::milliseconds(120), true, false), fadeThread(&Starter::fadeInAction, this)
{ 
	RessourceManager.invokeLog();

#pragma region Preload

	RessourceManager.testAndLoad(shield.loadFromFile("scenarios\\I_CINEMATIC\\darkZelda.png"), "darkZelda.png");
	RessourceManager.testAndLoad(Triforce.loadFromFile("src\\tilesets\\triforce.png"), "triforce.jpg");
	RessourceManager.testAndLoad(Cp1.loadFromFile("src\\images\\copyright1.png"), "copyright1.jpg");
	RessourceManager.testAndLoad(Cp2.loadFromFile("src\\images\\copyright2.png"), "copyright2.jpg");
	RessourceManager.testAndLoad(slideImage.loadFromFile("scenarios\\I_CINEMATIC\\0.png"), "0.png");
	RessourceManager.testAndLoad(texture.loadFromFile("src\\tilesets\\player.png"), "player.png");
	RessourceManager.testAndLoad(logoMain.loadFromFile("src\\images\\logo.png"), "logo.jpg");
	RessourceManager.testAndLoad(cadre.loadFromFile("src\\images\\cadre.png"), "cadre.png");
	RessourceManager.testAndLoad(font.loadFromFile("src\\fonts\\menu.ttf"), "menu.ttf");

	slideImage.setSmooth(true);
	  Triforce.setSmooth(true);
	  logoMain.setSmooth(true);
	    shield.setSmooth(true);
	     cadre.setSmooth(true);
	       Cp1.setSmooth(true);
	       Cp1.setSmooth(true);

	TriforceSprite.setTexture(Triforce);
	SpriteLogoMain.setTexture(logoMain);
	ShieldSprite.setTexture(shield);
	CadreSprite.setTexture(cadre);
	Cp1Sprite.setTexture(Cp1);
	Cp2Sprite.setTexture(Cp2);

	TriforceSprite.setPosition(332, 330);
	SpriteLogoMain.setPosition(80, -50);
	CadreSprite.setPosition(580, 210);
	ShieldSprite.setPosition(0, 100);
	Cp1Sprite.setPosition(100, 480);
	Cp1Sprite.setPosition(480, 540);

	SpriteLogoMain.setColor(sf::Color(255, 255, 255, 0));

	pressStart.setString("- Press start -");
	pressStart.setPosition(325, 470);
	pressStart.setFont(font);

	_introCaption = "\n\n\n\n\n\n\n\n\n\n\n\n\n\nA long, long time ago the World was in an age of Chaos.\n\n\n\n\n";
	_introCaption += "\n\n\n\n\n\n\n\n\n\n\n\nIn the midst of this chaos, in a little kingdom in the land of Hyrule,\na legend was being handed down from generation to generation,\nthe legend of the 'Triforce'; three golden triangles possessing\nmystical powers.\n\n\n\n\n\n\n\n\n\n\n\n\nOne day, an evil army attacked this peaceful little kingdom\nand stole the Triforce of Power.\nThis army was led by Ganon, the powerful Prince of Darkness\nwho sought to plunge the World into fear and darkness under his rule.\nFearing his wicked rule, Zelda, the princess of this kingdom, split up\nthe Triforce of Wisdom into eight fragments\nand hide them throughout the realm to save the last remaining\nTriforce from the clutches of the evil Ganon.";
	_introCaption += " \n\n\n\n\n\n\n\n\n\nBut then... just as all hope had died, a young boy clothed in green\nappeared as if from nowhere.\n\nWielding a blade that repelled evil, he sealed the dark one away\nand gave the land light.\nThis boy, who travelled through time to save the land, was known as\nthe Hero of Time.\n\nThe boy's tale was passed down through generations until it became\nlegend. Years later, darkness restarted to fall down on the earth.\nBut this time, Zelda princess was the investigator.\nWhen the time to separate the triforce symbol from Zelda came,\nthe darkness inside her was unjailed too and the dark side\n of Zelda took control of her.\nWhat became of that kingdom...? None remain who know.\nThe memory of the kingdom vanished,\nbut its legend survived on the wind’s breath.\n\n\n Link, the hero of time was jailed in the hyrule castle for the rest of\n his life.\nA new profecy was dicovered, a new mission for Link started...";

#pragma endregion
}


#pragma region Triggers

void Starter::startNewGame() {
	RessourceManager.invokeSound("LA_Menu_Select.wav", 50);
	RessourceManager.console("Entering NewStarter menu ...", 5);
	_GameState = CINEMATIC;
}

void Starter::loadGame() {
	RessourceManager.invokeSound("LA_Menu_Select.wav", 50);
	RessourceManager.console("Entering loadStarter menu ...", 5);
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
void Starter::fadeInAction()
{
	while (_alpha < 255)
	{
		sleep(sf::milliseconds(90));
		CurrentSlideImage.setColor(sf::Color(255, 255, 255, _alpha));
		_alpha++;
	}
}

void Starter::changeIntroSlide(std::string tostr, short int textureId, unsigned short int timeBeforeFade, float pos_x, float pos_y, int t_pos_x, int t_pos_y)
{
	if (tostr != _currentTextSlide)
	{
		RessourceManager.testAndLoad(slideImage.loadFromFile("scenarios\\I_CINEMATIC\\" + tostr), tostr);
		CurrentSlideImage.setTexture(slideImage);
		CurrentSlideImage.setColor(sf::Color(255, 255, 255, 0));
		CurrentSlideImage.setPosition(pos_x, pos_y);
		_alpha = 0;
		fadeThread.launch();
	}
}
#pragma endregion

void Starter::Run() {

	sf::RenderWindow render_window(sf::VideoMode(GetPrivateProfileInt("Graphics", "screenDimX", 0, "src\\iniFiles\\customCommands.ini"), GetPrivateProfileInt("Graphics", "screenDimY", 0, "src\\iniFiles\\customCommands.ini")), "Zelda : The Yolo Call");

	auto window = sfg::Window::Create();
	auto buttonNG = sfg::Button::Create("New game...");
	buttonNG->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&Starter::startNewGame, this));
	auto buttonLG = sfg::Button::Create("Load game...");
	buttonLG->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&Starter::loadGame, this));
	auto buttonOPT = sfg::Button::Create("Settings");
	buttonOPT->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&Starter::loadSettings, this));
	auto buttonQUIT = sfg::Button::Create("Exit");
	buttonQUIT->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&Starter::exitGame, this));

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

	auto viewport_box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
	viewport_box->Pack(sfg::Label::Create(_introCaption.c_str()));
	auto viewport = sfg::Viewport::Create();
	viewport->SetRequisition(sf::Vector2f(430.f, 350.f));
	viewport->GetVerticalAdjustment()->SetLower(-500.f);
	viewport->GetVerticalAdjustment()->SetUpper(100000000.f);
	viewport->Add(viewport_box);

	auto box2 = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.f);
	box2->Pack(viewport, true, true);

	cinematicScrollBar->Add(box2);

	generalMenu.Add(menuBar);
	secondaryMenu.Add(cinematicScrollBar);

	render_window.resetGLStates();
	render_window.setFramerateLimit(60);

	walkingAnimationRight.setSpriteSheet(texture);
	walkingAnimationDown.setSpriteSheet(texture);
	walkingAnimationLeft.setSpriteSheet(texture);
	walkingAnimationUp.setSpriteSheet(texture);

	walkingAnimationDown.addFrame(sf::IntRect(268, 15, 18, 25));
	walkingAnimationDown.addFrame(sf::IntRect(0, 150, 18, 25));
	walkingAnimationDown.addFrame(sf::IntRect(52, 150, 18, 25));
	walkingAnimationDown.addFrame(sf::IntRect(80, 152, 18, 25));
	walkingAnimationDown.addFrame(sf::IntRect(52, 150, 18, 25));
	//
	walkingAnimationLeft.addFrame(sf::IntRect(246, 153, 20, 26));
	walkingAnimationLeft.addFrame(sf::IntRect(274, 153, 20, 26));
	walkingAnimationLeft.addFrame(sf::IntRect(304, 153, 20, 26));
	walkingAnimationLeft.addFrame(sf::IntRect(335, 153, 32, 32));
	//
	walkingAnimationRight.addFrame(sf::IntRect(32, 96, 32, 32));
	walkingAnimationRight.addFrame(sf::IntRect(64, 96, 28, 32));
	walkingAnimationRight.addFrame(sf::IntRect(32, 96, 32, 32));
	walkingAnimationRight.addFrame(sf::IntRect(0, 95, 32, 32));
	//
	walkingAnimationUp.addFrame(sf::IntRect(209, 90, 18, 28));
	walkingAnimationUp.addFrame(sf::IntRect(234, 90, 18, 28));
	walkingAnimationUp.addFrame(sf::IntRect(260, 90, 18, 28));
	walkingAnimationUp.addFrame(sf::IntRect(289, 90, 18, 28));

	currentAnimation = &walkingAnimationDown;

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
				_GameState = MENU;
			if (event.type == sf::Event::LostFocus)
				int foo = 1;
		}

		sf::Time frameTime = frameClock.restart();
		sf::Vector2f movement(0.f, 0.f);


		if (_GameState == CINEMATIC && _nextSlide)
		{
			fadeThread.terminate();
			_x++;
			RessourceManager.console("Changing Intro slide... ", 2);
			changeIntroSlide(std::to_string(_x) + ".png", _x, 20, 9, 90, 375, 300);
			_nextSlide = false;
		}

		if (_introDisableMove && _GameState == INTRO)
		{
			_speed = 60.f;
			_noKeyWasPressed = true;
			currentAnimation = &walkingAnimationUp;
			movement.y -= _speed;
			_automoveCounter++;

			if (_automoveCounter == 276)
			{
				RessourceManager.console("Introduction [Stopped]", 0);
				_introDisableMove = false;
			}
		}

		animatedSprite.play(*currentAnimation);
		animatedSprite.move(movement * frameTime.asSeconds());

		if (!_introDisableMove && _GameState == INTRO)
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

		if (beat.asSeconds() > 1 && _GameState == INTRO)
			render_window.draw(pressStart);
		if (beat.asSeconds() > 3 && _GameState == INTRO)
			clk.restart();

		if (_GameState == CINEMATIC)
		{
			if (clock.getElapsedTime().asMicroseconds() >= 2000) {
				auto delta = static_cast<float>(clock.getElapsedTime().asMicroseconds()) / 1000000.f;
				viewport->GetVerticalAdjustment()->SetValue(viewport->GetVerticalAdjustment()->GetValue() + delta * 13.f);
				clock.restart();
			}
		}
		switch (_GameState)
		{
		case INTRO:
			RessourceManager.invokeMusic("intro.ogg", 40, true);
			render_window.draw(SpriteLogoMain);
			render_window.draw(TriforceSprite);
			render_window.draw(Cp2Sprite);
			render_window.draw(Cp1Sprite);
			render_window.draw(animatedSprite);
			break;

		case MENU:
			RessourceManager.invokeMusic("fairyIntro.ogg", 40, true, 0);
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

			if (t > _x * 19 && t < (_x + 1) * 19.05 && _x < 6)
			{
				RessourceManager.console("[Changing Intro slide] -> Actual is " + std::to_string(_x), 2);
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



