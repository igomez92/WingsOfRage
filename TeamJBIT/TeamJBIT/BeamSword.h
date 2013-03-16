#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Enemy.h"

class BeamSword
{
public:
	BeamSword(std::string file,float delay, sf::Vector2f dir, sf::Vector2f pos, float damage = 30, float swingSpeed = 5000.f);
	~BeamSword();

	bool collidesWith(Enemy& enemy);
	void doDamage(Enemy& enemy);
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