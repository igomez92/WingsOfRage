#pragma once

#include <SFML/Graphics.hpp>

class Enemy
{
public:
	Enemy(std::string file, sf::Vector2f pos, int health = 100);
	~Enemy(void);

	void update(float deltaTime);
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

