#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"

class enemMelee
{
public:
	enemMelee(std::string file, float delay, sf::Vector2f dir, sf::Vector2f pos, float damage, float swingSpeed);
	~enemMelee(void);

	bool collidesWith(Player& player);
	void doDamage(Player& player);
	void update(float deltaTime, sf::Vector2f pos);
	void draw(sf::RenderWindow& window);
	bool endSwing;
	float dam;

private:
	float swingSpeed;
	float currentAngle;
	sf::Vector2f pos;
	sf::Vector2f dir;
	sf::Vector2f targetPos;
	sf::Sprite sprite;
};

