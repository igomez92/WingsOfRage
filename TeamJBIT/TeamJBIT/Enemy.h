#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include "Bullet.h"

class Enemy
{
public:
	Enemy(std::string file, sf::Vector2f pos, int health = 100);
	~Enemy(void);

	void update(float deltaTime, std::list<Bullet*>& eList);
	void draw(sf::RenderWindow& window);
	void takeDam(int dam);
	bool isDead();
	sf::Vector2f pos;

	sf::Clock bulletClock;

private:
	int health;
	sf::Sprite sprite;
	sf::Texture image;
};

