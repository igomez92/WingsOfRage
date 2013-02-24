#pragma once

#include <SFML/Graphics.hpp>
#include "AnimSprite.h"
#include "Bullet.h"
#include "ShotType.h"
#include "SingleShot.h"
#include "TriCannonShot.h"
#include <list>

class Player
{
public:
	Player(std::string file, sf::Vector2f pos);
	~Player();

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	sf::Vector2f pos;
	void shoot(std::list<Bullet*>& playerBullets);
	void switchShot();
	ShotType* getShotType();

private:
	unsigned int health;
	unsigned int level;

	ShotType* shotType;

	AnimSprite sprite;
	sf::Texture image;
};