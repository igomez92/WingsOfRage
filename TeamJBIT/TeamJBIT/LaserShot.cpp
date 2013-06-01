#include "LaserShot.h"
#include "TextureManager.h"
#include "Enemy.h"

#include "Player.h"
#include "LaserCharge.h"

LaserShot::LaserShot(sf::Vector2f pos, sf::Vector2f dir, float timeLim, int dam)
	:dam(dam), totalTime(timeLim), pos(pos), dir(dir)
{
	sf::Texture* image = _getTexture("media/greenLaserRay.png");
	image->setSmooth(true);
	laserSprite.setTexture(*image);
	//sprite.scale(sf::Vector2f(3.5, 1));
	laserSprite.setScale(sf::Vector2f(5, 1));  
	laserSprite.setOrigin(0, laserSprite.getLocalBounds().height/2);
	laserSprite.setPosition(pos);
	// Rotate the laser based on our direction
	laserSprite.setRotation((-atan2f(dir.x, dir.y) * (180 / 3.1415926f)) + 90.f);

	continueDraw = true;
	accumTime = 0;


	sf::Texture* image2 = _getTexture("media/charge.png");
	image2->setSmooth(true);
	chargingSprite.setTexture(*image2);
	//sprite.scale(sf::Vector2f(3.5, 1));
	chargingSprite.setScale(sf::Vector2f(3, 3));  
	chargingSprite.setOrigin(0, chargingSprite.getLocalBounds().height/2);
	chargingSprite.setPosition(pos);
	// Rotate the laser based on our direction
	chargingSprite.setRotation((-atan2f(dir.x, dir.y) * (180 / 3.1415926f)) + 90.f);

	chargeTime = 3.0f;
	continueCharging = true;
}

LaserShot::~LaserShot(void)
{

}

void LaserShot::update(float deltaTime)
{
	accumTime += deltaTime;
	
	if(accumTime > chargeTime && continueCharging)
	{
		continueCharging = false;
		accumTime = 0.0f;
	}
	else if(accumTime > totalTime && continueCharging == false)
	{
		continueDraw = false;
	}
}

void LaserShot::draw(sf::RenderWindow& window)
{
	// if charging
	if(continueCharging == true)
	{
		window.draw(chargingSprite);
	}
	else
	{
		window.draw(laserSprite);
	}
}

bool LaserShot::collidesWith(Enemy& enemy)
{
	// If the enemy is within the bounds of our laser, check if we collide
	if(continueCharging == false)
	{
		if(enemy.pos.x >= laserSprite.getGlobalBounds().left && 
			enemy.pos.x <= laserSprite.getGlobalBounds().left+laserSprite.getGlobalBounds().width &&
			enemy.pos.y >= laserSprite.getGlobalBounds().top &&
			enemy.pos.y <= laserSprite.getGlobalBounds().top + laserSprite.getGlobalBounds().height)
		{
			// If the laser is vertical
			if(dir.x == 0)
			{
				// If the distance from the center of the enemy is within the laser, return true
				sf::Vector2f posToCheck;
				posToCheck.x = pos.x;
				posToCheck.y = enemy.pos.y;
				float distance = sqrt(pow(enemy.pos.x - posToCheck.x,2)+pow(enemy.pos.y-posToCheck.y,2));
			
				if(distance < laserSprite.getLocalBounds().height/2)
				{
					return true;
				}
			}
			// If the laser is in the negative direction, calculate the point closest to the enemy
			else
			{
				// Get two lines in point-slope form
				// Find the slope of original line as well as the "b"
				float origSlope = (dir.y-0)/(dir.x-0);
				float point1 = pos.y - (origSlope)*pos.x;
				// Find the slope of the new line(slope is perpendicular to the original) as well as the "b"
				float newSlope = -pow(origSlope,-1);
				float point2 = enemy.pos.y - (newSlope)*enemy.pos.x;

				// Calculate the closest x and y values
				float x = (point1 - point2)/(-origSlope + newSlope);
				float y = origSlope*x + point1;

				// Check the distance
				float distance = sqrt(pow(enemy.pos.x - x, 2)+pow(enemy.pos.y - y, 2));
				if(distance < laserSprite.getLocalBounds().height/2)
				{
					return true;
				}
			}
		}
	}
	// If we aren't within the position, return false
	return false;
}