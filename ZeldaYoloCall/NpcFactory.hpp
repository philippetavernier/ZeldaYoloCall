#ifndef __NPCFACTORY_INCLUDE
#define __NPCFACTORY_INCLUDE

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
#include "Invokation.hpp"

/*! 
* \class NpcFactory
* \brief Fabrique a personnage
*
*  La classe construit et parametre un personnage/non jouable
*/

class NpcFactory
{
	public:
		enum Move{ UP, DOWN, LEFT, RIGHT, HIT, ROLL, SPECIAL };
		enum Type{ LINK, ZELDA, LIKELIKE, ANTIFAIRY, MOBLIN, ARMED_MODBLIN, STALFOS_KNIGHT, CHICKEN };

		/*!
		*  \brief Construceur
		*
		*  Constructeur de la classe NpcFactory
		*
		*  \param npcId : .......;;
		*/
		NpcFactory(Type npcId, AnimatedSprite &AS, NpcFactory::Move initialMove);

		/*!
		*  \brief Crée un dérivé d'un personnage
		*
		*  Permet de créer un NPC/PC personnalisé
		*
		*/
		void makeCustom();

		/*!
		*  \brief Virtualisation du personnage courant
		*
		*  Methode qui permet de virtualiser un NPC/PC dans le jeu
		*
		*  \param posX : La position horizontale du personnage, posY : La position verticale du personnage, Orientation : Orientation (Move) du personnage
		*/
		void virtualize(int posX, int posY, NpcFactory::Move Orientation=NpcFactory::Move::DOWN);

		/*!
		*  \brief Permet de déplacer un personnage vers un autre personnage / une entité déja positionnée
		*
		*  Methode qui permet dde déplacer le personnage courant vers un autre objet/personnage/tile de 
		*  la carte
		*
		*  \param subject : Le personnage a déplacer, to : ?, customSpeed : si la vitesse doit changer
		*/
		void goTo(NpcFactory subject, NpcFactory to, float customSpeed);

		/*!
		*  \brief Changement d'orientation personnage
		*
		*  Methode qui permet de changer l'orientation d'un personnage
		*
		*  \param movement : un element de l'enumeration Move de NpcFactory
		*  \return  La nouvelle orientation du personnage
		*/
		Animation* setOrientation(Move movement);

		/*!
		*  \brief Récupère le statut vital d'un personnage
		*
		*  Methode permetant de savoir si un personnage
		*  est déja mort ou vient de mourrir (ex: declanchement
		*  evenement, envoie au destructeur etc..)
		*
		*  \return true si le personnage est mort,
		*  false sinon
		*/
		bool isDead(void);

		/*!
		*  \brief Récupère le statut vital d'un personnage
		*
		*  Methode permetant de savoir si un personnage
		*  est déja mort ou vient de mourrir (ex: declanchement
		*  evenement, envoie au destructeur etc..)
		*
		*/
		float getDefaultSpeed(void);

		/*!
		*  \brief Récupère le statut vital d'un personnage
		*
		*  Methode permetant de savoir si un personnage
		*  est déja mort ou vient de mourrir (ex: declanchement
		*  evenement, envoie au destructeur etc..)
		*
		*/
		void setDefaultSpeed(void);

		/*!
		*  \brief Récupère le statut vital d'un personnage
		*
		*  Methode permetant de savoir si un personnage
		*  est déja mort ou vient de mourrir (ex: declanchement
		*  evenement, envoie au destructeur etc..)
		*
		*/
		void NpcFactory::setSpeed(float s);
      
		/*!
		*  \brief Récupère le statut vital d'un personnage
		*
		*  Methode permetant de savoir si un personnage
		*  est déja mort ou vient de mourrir (ex: declanchement
		*  evenement, envoie au destructeur etc..)
		*
		*/  
		float NpcFactory::getSpeed();

		/*!
		*  \brief Destructeur
		*
		*  Destructeur de la classe CPlayer
		*/
		virtual ~NpcFactory();
		
    private:
		Invokation RessourceManager;
		AnimatedSprite *_as;
		Animation _Right, _Left, _Top, _Bot, _Hit;
		
		float _speed, _defaultSpeed;
		unsigned int _life, _hitDamage;
		int _mobId;
		std::string _name;
		//Damageby

		sf::Texture _npcTexture;
};

#endif
