#pragma once

#include <SFML/Graphics.hpp>

class VisibleObject
{
public:
	VisibleObject(std::string file);
	~VisibleObject();

	void setPosition(int x, int y);
	int getX();
	int getY();
	sf::Sprite getSprite();
	sf::Rect<float> getBounds() const;

private:
	sf::Sprite sprite;
	sf::Texture image;
	std::string filename;
};

