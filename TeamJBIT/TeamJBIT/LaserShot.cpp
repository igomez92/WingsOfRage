#include "LaserShot.h"

LaserShot::LaserShot(sf::Vector2f pos, sf::Vector2f dir, float timeLim, int dam)
	:dam(dam), totalTime(timeLim)
{
	image.loadFromFile("greenLaserRay.png");
	sprite.setTexture(image);
	sprite.scale(sf::Vector2f(5, 1));
	sprite.setOrigin(0, sprite.getLocalBounds().height/2);
	sprite.setPosition(pos);
	// Rotate the laser based on our direction
	sprite.setRotation((-atan2f(dir.x, dir.y) * (180 / 3.1415926f)) + 90.f);

	continueDraw = true;
	accumTime = 0;
}

LaserShot::~LaserShot(void)
{
}

void LaserShot::update(float deltaTime)
{
	accumTime += deltaTime;
	
	if(accumTime > totalTime)
	{
		continueDraw = false;
	}
}

void LaserShot::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}