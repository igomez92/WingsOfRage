#pragma once

#include <SFML/System.hpp>
#include "AnimSprite.h"
#include "IScene.h"
#include "Player.h"

#include "Enemy.h"
#include "TankEnemy.h"
#include "MTankEnemy.h"
#include "SliderEnemy.h"
#include "Boss1.h"
#include "Bullet.h"
#include "PowerUp.h"
#include "MeleeType.h"
#include "Utility.h"
#include "LevelLoader.h"

#include "ParticleManager.h"
#include "Particle.h"

#include <list>
#include <sstream>

class GameScene : public IScene
{
	public:
		GameScene();
		~GameScene();
	
		virtual void update(sf::RenderWindow& window);
		virtual void draw(sf::RenderWindow& window);
		virtual bool handleEvent(sf::Event& event);

	private:

		Player player;
		PowerUp testDummy;
		sf::Time shotTimer;
		int enemyDisplacement;

		std::queue<SpawnEntry> enemySpawnQueue;
		ParticleManager ptManager;

		std::list<Enemy*> enemyList;
		std::list<Bullet*> playerBullets;
		std::list<Bullet*> enemyBullets;
		std::list<Particle*> allParticles;
		MeleeType* currentMeleeAttack;

		sf::Clock clock;
		sf::Time lastFrameTime;
		sf::Time hitDelay;
		sf::Time blinkDelay;

		sf::Sprite backgroundSpriteLow;
		sf::Sprite backgroundSpriteMed;
		float backgroundOffsetLow;
		float backgroundOffsetMed;

		// Score stuff
		std::stringstream scoreStr;
		sf::Text score;
		sf::Font tempestaSevenFont;
		unsigned int scoreNum;

		//player health
		std::stringstream playerhealthStr;
		sf::Text health;

		unsigned int healthNum;

		// Time stuff
		std::stringstream timeStr;
		sf::Text timer;

		//boss stuff
		bool bossSpawned;

		void initializeScoreAndTime();
		void updateScoreAndTime();
		void printScoreAndTime(sf::RenderWindow& window);
		void updateplayershot(sf::RenderWindow& window);
		void updatePlayerBullets(float deltaTime);
		void updateLaser();
		void updateSword();
		void updateEnemies(float deltaTime);
		void bulletToPlayerCollision(float deltaTime);
		void enemyToPlayerCollision(float deltaTime);
		void updateUpgrade();
		void updateSpawnQueue();
		void updateParticleEffects(float deltaTime);
};
