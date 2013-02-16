#pragma once

#include <SFML/Graphics.hpp>

class Bullet
{
public:
	Bullet(std::string file, sf::Vector2f pos, sf::Vector2f vel);
	~Bullet(void);

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	sf::Vector2f getPosition();

private:
	sf::Vector2f vel;
	sf::Vector2f pos;

	sf::Sprite sprite;
	sf::Texture image;
};

