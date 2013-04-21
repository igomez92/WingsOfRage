#pragma once

#include "Enemy.h"
#include "Sequence.h"

class SliderEnemy : public Enemy
{
	public:
		SliderEnemy(std::string file, sf::Vector2f pos, int health = 10);
		~SliderEnemy(void);

		void update(float deltaTime, std::list<Bullet*>& eList, std::list<Bullet*>& pList, Player& player);

	private:
		Sequence sliderSequenceX;
		Sequence sliderSequenceY;
		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();
};