#pragma once

#include <SFML/Graphics.hpp>
#include "AnimSprite.h"
#include "Bullet.h"
#include "ShotType.h"
#include "SingleShot.h"
#include "TriCannonShot.h"
#include "MultiPhotonShot.h"
#include <list>

class Player
{
public:
	Player(std::string file, sf::Vector2f pos);
	~Player();

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	sf::Vector2f pos;
	void shoot(std::list<Bullet*>& playerBullets, sf::Vector2f dir);
	void switchShot();
	ShotType* getShotType();
	void mouseShot(std::list<Bullet*>& playerBullets, sf::RenderWindow& window);
	void powerUP();
	int currentWeaponLevel;
	int currentPlayerMode;
	int enemiesKilled;
	void damaged(int damagedealt);
	bool isDead();

private:
	unsigned int health;
	unsigned int level;
	bool playerSwitch;
	ShotType* shotType;
	bool powerUpFound;
	AnimSprite sprite;
};