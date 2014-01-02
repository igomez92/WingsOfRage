#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio//SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include "AnimSprite.h"
#include "Bullet.h"
#include "ShotType.h"
#include "SingleShot.h"
#include "TriCannonShot.h"
#include "MultiPhotonShot.h"
#include "MeleeType.h"
#include "SwordSlash.h"
#include "BeamSword.h"
#include "ShotSword.h"
#include <list>
#include "LaserShot.h"
#include "Sequence.h"

#include "LaserCharge.h"

enum currentMode {PLANE_MODE , GUNNER_MODE, FIGHTER_MODE, NO_MODE};
enum upgradeState {STAGE_ONE, STAGE_TWO, STAGE_THREE};

class Player
{
	public:
		Player(sf::Vector2f pos); 
		~Player();

		void update(float deltaTime, std::list<Bullet*>& playerBullets);
		void draw(sf::RenderWindow& window);
		sf::Vector2f pos;
		void shoot(std::list<Bullet*>& playerBullets, sf::Vector2f dir);
		void switchShot();
		ShotType* getShotType();
		MeleeType* getMeleeType();
		void mouseShot(std::list<Bullet*>& playerBullets, sf::RenderWindow& window, bool mousePressed);
		void powerUP();
		int currentWeaponLevel;
		int currentPlayerMode;
		int enemiesKilled;
		int lives;
		void damaged(int damagedealt);
		bool isDead();
		bool isTargetable();
		bool canBlink;
		float blinkDelay;
		void setTargetable(bool targetable);
		sf::FloatRect getSize();

		// For laser
		bool laserShooting;
		LaserShot* laser;
		void laserShot(sf::RenderWindow& window, sf::Vector2f dir);
		float laserShotDelay;
		bool allowLaser;
		float accumDelayTime;
		signed int getHealth();
		signed int getTotalHealth();
		signed int getEnergy();
		signed int getTotalEnergy();
		void setHealth(signed int newHealth);
		void setEnergy(signed int newEnergy);
		unsigned int getLevel();
		AnimSprite sprite;
		// For melee
		bool swordSwinging;
		float swordDelay;
		float currentSwordTime;
		BeamSword* sword;
		void swordSwing(sf::RenderWindow& window, sf::Vector2f dir);
		bool allowSword;
		bool powerUpFound;
		void increaseHealth(int incrementation);
		void decreaseEnergy(int decrementation);
		void increaseEnergy(int incrementation);
		void increaseLevel();
		void setLevelToZero();
		void setShieldUp(bool shieldUp);
		bool isShieldUp();

		Sequence barrelRollSequence;
		bool isDoingABarrelRoll;
		void doABarrelRoll(bool isLeft); //yes I did just do that
		void doBlink(float deltaTime, sf::Vector2i mousePos);

	private:
		signed int health;
		signed int totalHealth;
		signed int energy;
		signed int totalEnergy;
		unsigned int level;
		bool playerSwitch;
		bool playerSwitchQ;
		bool Targetable;
		bool shieldUp;

		ShotType* shotType;
		MeleeType* meleeType;
		
		sf::Texture* planeImage;
		sf::Texture* gunnerImage;
		sf::Texture* fighterImage;

		sf::Texture* chargeImage;

		sf::SoundBuffer buffer;
		sf::Sound sound;

};