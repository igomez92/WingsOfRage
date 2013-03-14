#pragma once

#include <SFML/Graphics.hpp>
#include "AnimSprite.h"
#include "Bullet.h"
#include "ShotType.h"
#include "SingleShot.h"
#include "TriCannonShot.h"
#include "MultiPhotonShot.h"
#include "MeleeType.h"
#include "SwordSlash.h"
#include <list>
#include "LaserShot.h"


enum currentMode {PLANE_MODE , GUNNER_MODE, FIGHTER_MODE, NO_MODE};





class Player
{
public:
	Player(sf::Vector2f pos);
	~Player();

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	sf::Vector2f pos;
	void shoot(std::list<Bullet*>& playerBullets, sf::Vector2f dir);
	void switchShot();
	ShotType* getShotType();
	MeleeType* getMeleeType();
	void mouseShot(std::list<Bullet*>& playerBullets, sf::RenderWindow& window);
	void powerUP();
	int currentWeaponLevel;
	int currentPlayerMode;
	int enemiesKilled;
	void damaged(int damagedealt);
	bool isDead();

	// For laser
	bool laserShooting;
	LaserShot* laser;
	void laserShot(sf::RenderWindow& window);
	float laserShotDelay;
	bool allowLaser;
	float accumDelayTime;

private:
	unsigned int health;
	unsigned int level;
	bool playerSwitch;
	ShotType* shotType;
	MeleeType* meleeType;
	bool powerUpFound;
	AnimSprite sprite;
	sf::Texture* planeImage;
	sf::Texture* gunnerImage;
	sf::Texture* fighterImage;
};