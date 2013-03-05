#pragma once
#include <SFML/Graphics.hpp>

class LaserShot
{
public:
	LaserShot(sf::Vector2f pos, sf::Vector2f dir, float timeLim = 5, int dam = 1000);
	~LaserShot(void);

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

	float totalTime;
	float accumTime;
	int dam;
	bool continueDraw;

private:
	sf::Sprite sprite;
	sf::Texture image;
};

