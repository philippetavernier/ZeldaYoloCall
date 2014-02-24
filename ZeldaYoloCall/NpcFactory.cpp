/**
* \file NpcFactory.cpp
* \brief Classe de création de personnages / non joueurs
* \author Paul Fasola	
* \version 0.1
* \date 22 Février 2014
*/

#include "NpcFactory.hpp"

NpcFactory::NpcFactory(Type npcId, AnimatedSprite &AS, NpcFactory::Move move) : _speed(_defaultSpeed){
	_as = &AS;
	 
	switch (npcId){

	case LINK:
		_name = "Link";
		RessourceManager.testAndLoad(_npcTexture.loadFromFile("src\\tilesets\\player.png"), "Link SpriteSheet");
		_defaultSpeed = 60.f; // Vitesse conseillée

		_Bot.addFrame(sf::IntRect(268, 15, 18, 25));
		_Bot.addFrame(sf::IntRect(0, 150, 18, 25));
		_Bot.addFrame(sf::IntRect(52, 150, 18, 25));
		_Bot.addFrame(sf::IntRect(80, 152, 18, 25));
		_Bot.addFrame(sf::IntRect(52, 150, 18, 25));
		_Left.addFrame(sf::IntRect(246, 153, 20, 26));
		_Left.addFrame(sf::IntRect(274, 153, 20, 26));
		_Left.addFrame(sf::IntRect(304, 153, 20, 26));
		_Left.addFrame(sf::IntRect(335, 153, 32, 32));
		_Right.addFrame(sf::IntRect(32, 96, 32, 32));
		_Right.addFrame(sf::IntRect(64, 96, 28, 32));
		_Right.addFrame(sf::IntRect(32, 96, 32, 32));
		_Right.addFrame(sf::IntRect(0, 95, 32, 32));
		_Top.addFrame(sf::IntRect(209, 90, 18, 28));
		_Top.addFrame(sf::IntRect(234, 90, 18, 28));
		_Top.addFrame(sf::IntRect(260, 90, 18, 28));
		_Top.addFrame(sf::IntRect(289, 90, 18, 28));
		break;
	case ZELDA:

		break;
	case STALFOS_KNIGHT:
		_name = "Stalfos Knight";
		RessourceManager.testAndLoad(_npcTexture.loadFromFile("src\\tilesets\\ennemies.png"), "Ennemie SpriteSheet");
		_defaultSpeed = 60.f; 

		_Right.addFrame(sf::IntRect(135, 406, 25, 16));
		_Right.addFrame(sf::IntRect(161, 407, 23, 15));
		 _Left.addFrame(sf::IntRect(136, 388, 24, 17));
		 _Left.addFrame(sf::IntRect(162, 390, 23, 15));
		  _Bot.addFrame(sf::IntRect(136, 363, 16, 24));
		  _Bot.addFrame(sf::IntRect(153, 363, 16, 24));
		  _Top.addFrame(sf::IntRect(136, 425, 16, 24));
		  _Top.addFrame(sf::IntRect(153, 425, 18, 28));
		RessourceManager.console("Stalfos Initilized !");
		break;
	case ANTIFAIRY:
		_name = "Anti Fairy";
		RessourceManager.testAndLoad(_npcTexture.loadFromFile("src\\tilesets\\ennemies.png"), "Ennemie SpriteSheet");
		_defaultSpeed = 57.f;

		_Right.addFrame(sf::IntRect(84, 359, 16, 16));
		_Right.addFrame(sf::IntRect(101, 359, 16, 16));
		_Left.addFrame(sf::IntRect(84, 359, 16, 16));
		_Left.addFrame(sf::IntRect(101, 359, 16, 16));
		_Bot.addFrame(sf::IntRect(84, 359, 16, 16));
		_Bot.addFrame(sf::IntRect(101, 359, 16, 16));
		_Top.addFrame(sf::IntRect(84, 359, 16, 16));
		_Top.addFrame(sf::IntRect(101, 359, 16, 16));
		break;
	case MOBLIN: 
		_name = "Moblin";
		RessourceManager.testAndLoad(_npcTexture.loadFromFile("src\\tilesets\\ennemies.png"), "Ennemie SpriteSheet");
		_defaultSpeed = 50.f;

		_Right.addFrame(sf::IntRect(6, 5, 16, 15));
		_Right.addFrame(sf::IntRect(24, 4, 16, 16));
		_Left.addFrame(sf::IntRect(6, 22, 16, 16));
		_Left.addFrame(sf::IntRect(24, 23, 16, 15));
		_Bot.addFrame(sf::IntRect(7, 57, 16, 16));
		_Bot.addFrame(sf::IntRect(24, 56, 16, 16));
		_Top.addFrame(sf::IntRect(7, 39, 16, 16));
		_Top.addFrame(sf::IntRect(24, 39, 16, 16));
		RessourceManager.console("Moblin Initilized !");
		break;
	case LIKELIKE:
		_name = "Like-Like";
		RessourceManager.testAndLoad(_npcTexture.loadFromFile("src\\tilesets\\ennemies.png"), "Ennemie SpriteSheet");
		_defaultSpeed = 40.f;

		_Right.addFrame(sf::IntRect(252, 105, 16, 15));
		_Right.addFrame(sf::IntRect(269, 104, 14, 16));
		_Left.addFrame(sf::IntRect(252, 105, 16, 15));
		_Left.addFrame(sf::IntRect(269, 104, 14, 16));
		_Bot.addFrame(sf::IntRect(252, 105, 16, 15));
		_Bot.addFrame(sf::IntRect(269, 104, 14, 16));
		_Top.addFrame(sf::IntRect(252, 105, 16, 15));
		_Top.addFrame(sf::IntRect(269, 104, 14, 16));
		RessourceManager.console("Like-Like Initilized !");
		break;

	case CHICKEN:
		_name = "Chicken";
		RessourceManager.testAndLoad(_npcTexture.loadFromFile("src\\tilesets\\allies.png"), "Allies SpriteSheet");
		_defaultSpeed = 30.f;

		_Right.addFrame(sf::IntRect(458, 219, 16, 15));
		_Right.addFrame(sf::IntRect(476, 218, 16, 16));
		_Left.addFrame(sf::IntRect(350, 218, 16, 16));
		_Left.addFrame(sf::IntRect(368, 219, 16, 15));
		_Bot.addFrame(sf::IntRect(404, 218, 16, 16));
		_Bot.addFrame(sf::IntRect(386, 219, 16, 15));
		_Top.addFrame(sf::IntRect(422, 218, 16, 16));
		_Top.addFrame(sf::IntRect(440, 220, 16, 14));
		RessourceManager.console("Like-Like Initilized !");
		break;

	}

	_Right.setSpriteSheet(_npcTexture);
	_Left.setSpriteSheet(_npcTexture);
	_Top.setSpriteSheet(_npcTexture);
	_Bot.setSpriteSheet(_npcTexture);
}


NpcFactory::~NpcFactory()
{}
 

void NpcFactory::virtualize(int posX, int posY, Move Orientation){
	RessourceManager.console("A new " + _name + " Spawned !");
	_as->setPosition(posX, posY);
}

Animation* NpcFactory::setOrientation(Move movement){
	switch (movement){
		case 0:
			return &_Top;
			break;
		case 1:
			return &_Bot;
			break;
		case 2:
			return &_Left;
			break;
		case 3:
			return &_Right;
			break;
		default:
			return &_Bot;
			break;
	}
}

void goTo(NpcFactory subject, NpcFactory to, float speed){

	//Récupérons d'abord les positions des deux éléments.
	
	

}



float NpcFactory::getDefaultSpeed(){
	return _defaultSpeed;
}

void  NpcFactory::setDefaultSpeed(){
	_speed = _defaultSpeed;
}

void NpcFactory::setSpeed(float newSpeed){
	_speed = newSpeed;
}

float  NpcFactory::getSpeed(){
	_speed = _defaultSpeed;
	return _speed;
}

bool NpcFactory::isDead(){
	return (_life == 0);
}

 