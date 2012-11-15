#ifndef CHARACTER_H
#define CHARACTER_H

#include "Animation.h"
#include <SFML/Graphics.hpp>

enum Direction
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NONE
};

// The various animation types so far
const Animation RUNNING_RIGHT_ANIMATION(RUNNING_RIGHT);
const Animation RUNNING_LEFT_ANIMATION(RUNNING_LEFT);
const Animation STANDING_RIGHT_ANIMATION(STANDING_RIGHT);
const Animation STANDING_LEFT_ANIMATION(STANDING_LEFT);

// The speed of motion
const float SPEED = 100.0f;

class Character
{
public:
	Character();
	
	Character(int xPos, int yPos, Direction startDir, Animation animationToUse, 
		unsigned int mHealth, unsigned int startAttack);
	
	Character(int savedX, int savedY, Direction savedDir, Animation savedAnimation, unsigned int savedCurrentHealth, 
		unsigned int savedMaxHealth, unsigned int savedAttack, unsigned int savedLevel);

	~Character();

	// These are for Key presses and Motion
	void move(sf::Time elapsed);
	void doPressedCommand(sf::Keyboard::Key keyCode);
	void doReleasedCommand(sf::Keyboard::Key keyCode);
	sf::Sprite getSprite();

	// Command Options
	void attackTarget(Character& being);

	unsigned int currentHealth;
	unsigned int maxHealth;
	unsigned int attackPower;
	unsigned int level;


private:
	// All the details necessary for the movement of the Character
	Animation animation;
	Direction dir;
	float x;
	float y;
	bool changeDirection;
	void setAnimation(Animation nextAnimation);
};

#endif