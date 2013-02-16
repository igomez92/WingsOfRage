#pragma once

#include <SFML/Graphics.hpp>

class Enemy
{
public:
	Enemy(std::string file, sf::Vector2f pos);
	~Enemy(void);

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

	bool continueDraw;
	sf::Vector2f pos;

private:
	sf::Sprite sprite;
	sf::Texture image;
};

