#include "SliderEnemy.h"
#include "Utility.h"

SliderEnemy::SliderEnemy(std::string file, sf::Vector2f pos, int health)
	:Enemy(file,pos,health)
{
	goingdown = true;
	dir = -1;
	initial_pos = pos.x;
}
void SliderEnemy::update(float deltaTime, std::list<Bullet*>& eList, sf::Vector2f player_pos)
{
	pos.x = initial_pos + (400*dir*sin(pos.y/100)) ;

	if(pos.y > 610 + sprite.getLocalBounds().height)
	{
		goingdown = false;
	} 
	else if(pos.y < -20)
	{
		goingdown =true;
	}

	if(initial_pos >  400)
	{
		dir = 1;
	}
	if(initial_pos <= 400 )
	{
		dir = -1;
	}

	if(pos.x > 810)
	{
		pos.x = 810;
	}
	if(pos.x < -10)
	{
		pos.x = -10;
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
	if (bulletClock.getElapsedTime().asSeconds() > .1)
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

			aiming.x = temp.x * -400;
			aiming.y = temp.y * -400;

		eList.push_back(new Bullet("media/bullet.png", pos, aiming, 5, sf::Color(255, 50, 50)));
		
		bulletClock.restart();
	}

}
