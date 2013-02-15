#pragma once

#include "VisibleObject.h"
#include <SFML/Graphics.hpp>

class Bullet : public VisibleObject
{
public:
	Bullet(std::string file);
	~Bullet(void);

	void update(float time);
	sf::Vector2f getPosition();

private:
	sf::Vector2f velocity;
	sf::Vector2f position;
};

