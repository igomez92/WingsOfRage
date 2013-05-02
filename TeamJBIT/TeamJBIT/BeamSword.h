#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <list>
#include "Bullet.h"

class Enemy;

class BeamSword
{
public:
	BeamSword(std::string file,float delay, sf::Vector2f dir, sf::Vector2f pos, float damage = 30.f, float swingSpeed = 5000.f);
	~BeamSword();

	virtual bool collidesWith(Enemy& enemy);
	virtual void doDamage(Enemy& enemy);
	virtual void update(float deltaTime, sf::Vector2f pos, std::list<Bullet*>& playerBullets);
	virtual void draw(sf::RenderWindow& window);
	bool endSwing;
	float dam;

	float swingSpeed;
	float currentAngle;
	sf::Vector2f pos;
	sf::Vector2f dir;
	sf::Vector2f targetPos;
	sf::Sprite sprite;
};