#pragma once

#include <SFML/Graphics.hpp>

class IEntity
{
	public:
		virtual void update(float deltaTime) = 0;
		virtual void draw(sf::RenderWindow& window) = 0;
		virtual bool isDead() {return false;} //if true then entity will be removed
};
