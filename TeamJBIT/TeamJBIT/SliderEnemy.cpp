#include "SliderEnemy.h"
#include "Utility.h"
#include <math.h>

#define SLIDER_MOVETIME 1.5

SliderEnemy::SliderEnemy(std::string file, sf::Vector2f pos, int health)
	:Enemy(file,pos,health)
{
	//most of the following code is to start already moving across screen at same speed as it will be moving on a regular pass, but at the desired x location
	if (pos.x > SCREEN_WIDTH / 2) {
		this->pos.x = SCREEN_WIDTH + 50;
		moveLeft();
	} else {
		this->pos.x = -50;
		moveRight();
	}

	//figure out how many seconds into the move we're supposed to be
	pos.x = clamp(pos.x, -50, SCREEN_WIDTH + 50);
	float posPercent = (pos.x + 50) / (SCREEN_WIDTH + 100);
	float time = std::acosf((-posPercent * 2) + 1) / M_PI;
	time *= SLIDER_MOVETIME;
	if (pos.x > SCREEN_WIDTH / 2)
		time = SLIDER_MOVETIME - time;

	//update with that time to get desired x pos
	sliderSequenceX.update(time);
	sprite.setPosition(this->pos);

	moveDown();

	type = Normal;
}

void SliderEnemy::update(float deltaTime, std::list<Bullet*>& eList, std::list<Bullet*>& pList, Player& player)
{
	sliderSequenceX.update(deltaTime);
	sliderSequenceY.update(deltaTime);
	sprite.setPosition(pos);

	if (bulletClock.getElapsedTime().asSeconds() > .1)
	{
		sf::Vector2f aiming;
		sf::Vector2f temp = (pos - player.pos);
			temp = normalize(temp);

			aiming.x = temp.x * -400;
			aiming.y = temp.y * -400;

		eList.push_back(new Bullet("media/bullet.png", pos, aiming, 5, sf::Color(255, 50, 50)));
		
		bulletClock.restart();
	}

}

void SliderEnemy::moveUp() 
{
	sliderSequenceY.appendTween( new CDBTweener::CTween(&CDBTweener::TWEQ_LINEAR, CDBTweener::TWEA_INOUT, 3.5, &pos.y, 0) );
	sliderSequenceY.appendCue([&] {this->moveDown();});
}

void SliderEnemy::moveDown()
{
	sliderSequenceY.appendTween( new CDBTweener::CTween(&CDBTweener::TWEQ_LINEAR, CDBTweener::TWEA_INOUT, 3.5, &pos.y, SCREEN_HEIGHT) );
	sliderSequenceY.appendCue([&] {this->moveUp();});
}

void SliderEnemy::moveLeft() 
{
	sliderSequenceX.appendTween( new CDBTweener::CTween(&CDBTweener::TWEQ_SINUSOIDAL, CDBTweener::TWEA_INOUT, SLIDER_MOVETIME, &pos.x, 50) );
	sliderSequenceX.appendCue([&] {this->moveRight();});
}

void SliderEnemy::moveRight() 
{
	sliderSequenceX.appendTween( new CDBTweener::CTween(&CDBTweener::TWEQ_SINUSOIDAL, CDBTweener::TWEA_INOUT, SLIDER_MOVETIME, &pos.x, (SCREEN_WIDTH - 50)) );
	sliderSequenceX.appendCue([&] {this->moveLeft();});
}
