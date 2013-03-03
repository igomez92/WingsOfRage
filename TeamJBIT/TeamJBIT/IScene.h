#pragma once

#include <SFML/Graphics.hpp>

class IScene
{
public:
	virtual void update(sf::RenderWindow& window) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual bool handleEvent(sf::Event& event) = 0;
};

