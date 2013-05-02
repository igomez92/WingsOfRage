#include "ShotSword.h"


ShotSword::ShotSword(std::string file,float delay, sf::Vector2f dir, sf::Vector2f pos, float damage, float swingSpeed)
	:BeamSword(file, delay, dir, pos, damage, swingSpeed), shotDone(false)
{
}


ShotSword::~ShotSword(void)
{
}

void ShotSword::update(float deltaTime, sf::Vector2f pos, std::list<Bullet*>& playerBullets)
{
	// Calculate our new angle of swing
	currentAngle += swingSpeed*deltaTime;	

	sprite.setRotation(currentAngle + (-atan2f(dir.x, dir.y) * (180 / 3.1415926f))+90);

	// if the angle is above 120 degrees, end the attack
	if(currentAngle >= 60)
		endSwing = true;

	if(currentAngle >= 0 && shotDone == false)
	{
		sf::Vector2f vel(dir.x * 400, dir.y*400);
		playerBullets.push_back(new Bullet("media/bullet.png", pos, vel));
		shotDone = true;
	}

	sprite.setPosition(pos);
}
