#pragma once

#include <SFML/Graphics.hpp>

class Bullet
{
public:
	Bullet(std::string file, sf::Vector2f pos, sf::Vector2f vel, int dam = 20, sf::Color bulletColor = sf::Color::White);
	~Bullet(void);

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	sf::Vector2f getPosition();

	sf::Vector2f vel;
	sf::Vector2f pos;
	
	int dam;

private:
	sf::Sprite sprite;
};
