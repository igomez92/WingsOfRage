#include "SliderEnemy.h"
#include "Utility.h"

SliderEnemy::SliderEnemy(std::string file, sf::Vector2f pos, int health)
	:Enemy(file,pos,health)
{
	bool goingup = true;
	float dir = -1;
}
void SliderEnemy::update(float deltaTime, std::list<Bullet*>& eList, sf::Vector2f player_pos)
{
	
	
	pos.x =  400 + (400*dir*sin(pos.y/100)) ;
	

	if(pos.y > 650 + sprite.getLocalBounds().height)
	{
		goingdown = false;
		
	}else if(pos.y < -50 + sprite.getLocalBounds().height)
	{
		goingdown =true;
	}

	if(pos.x > 800 + sprite.getLocalBounds().width)
	{
		
		dir = 1;
	}
	if(pos.x < 0 + sprite.getLocalBounds().width)
	{
		
		dir = -1;
	}

	if(!goingdown)
	{
		pos.y += -3;
	}
	else
	{
		pos.y += +3;
	}
	sprite.setPosition(pos);
	if (bulletClock.getElapsedTime().asSeconds() > .2)
	{
		/*
		if(!goingdown)
			eList.push_back(new Bullet("bullet.png", pos, sf::Vector2f(0, -400)));

		if(goingdown)
			eList.push_back(new Bullet("bullet.png", pos, sf::Vector2f(0, 400)));
			*/

		sf::Vector2f aiming;
		sf::Vector2f temp = (pos - player_pos);
			temp = normalize(temp);

			aiming.x = temp.x * -100;
			aiming.y = temp.y * -100;

		eList.push_back(new Bullet("bullet.png", pos, aiming, 5, sf::Color(255, 50, 50)));
		
		bulletClock.restart();
	}

}