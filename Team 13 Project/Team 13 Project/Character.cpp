#include "Character.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>

Character::Character()
	:dir(NONE), changeDirection(false), x(25), y(25)
{
	setAnimation(STANDING_RIGHT_ANIMATION);
}

Character::Character(int xPos, int yPos, Direction startDir, Animation animationToUse, 
	unsigned int mHealth, unsigned int startAttack)
	:x(xPos), y(yPos), dir(startDir), changeDirection(false), currentHealth(mHealth), 
	maxHealth(mHealth), attackPower(startAttack), level(0)
{
	setAnimation(animationToUse);
}
	
Character::Character(int savedX, int savedY, Direction savedDir, Animation savedAnimation, unsigned int savedCurrentHealth, 
	unsigned int savedMaxHealth, unsigned int savedAttack, unsigned int savedLevel)
	:x(savedX), y(savedY), dir(savedDir), changeDirection(false), currentHealth(savedCurrentHealth), 
	maxHealth(savedMaxHealth), attackPower(savedAttack), level(savedLevel)
{
	setAnimation(savedAnimation);
}

Character::~Character()
{
}

void Character::move(sf::Time elapsed)
{
	//move character distance depending on time elapsed and speed constant
	float distance = SPEED * elapsed.asSeconds();
	if(dir == LEFT)
	{
		x -= distance;
	}
	else if(dir == RIGHT)
	{
		x += distance;
	}
	else if(dir == UP)
	{
		y -= distance;
	}
	else if(dir == DOWN)
	{
		y += distance;
	}
	animation.update(x, y);
}

void Character::doPressedCommand(sf::Keyboard::Key keyCode)
{
	switch(keyCode)
	{
	case sf::Keyboard::Right:
		//if you try to move right but are still moving left,
		//then inform the program that you want to immediately start
		//moving right when left is released
		if(dir == LEFT)
		{
			changeDirection = true;
			break;
		}
		//begin moving right, and flip the sprites so that they are facing right
		if(dir == NONE)
		{
			dir = RIGHT;
			setAnimation(RUNNING_RIGHT_ANIMATION);
		}
		break;
	case sf::Keyboard::Left:
		//if you try to move left but are still moving right,
		//then inform the program that you want to immediately start
		//moving left when right is released
		if(dir == RIGHT)
		{
			changeDirection = true;
			break;
		}
		//begin moving left, and flip the sprites so that they are facing left
		if(dir == NONE)
		{
			dir = LEFT;
			setAnimation(RUNNING_LEFT_ANIMATION);
		}
		break;
	case sf::Keyboard::Up:
		if(dir == DOWN)
		{
			changeDirection = true;
			break;
		}
		if(dir == NONE)
		{
			dir = UP;
			setAnimation(RUNNING_RIGHT_ANIMATION);
		}
		break;
	case sf::Keyboard::Down:
		if(dir == UP)
		{
			changeDirection = true;
			break;
		}
		if(dir == NONE)
		{
			dir = DOWN;
			setAnimation(RUNNING_RIGHT_ANIMATION);
		}
		break;
	default:
		break;
	}
}

void Character::doReleasedCommand(sf::Keyboard::Key keyCode)
{
	switch(keyCode)
	{
	case sf::Keyboard::Right:
		if(dir == RIGHT)
		{
			//if the player started to press left while still running right
			//then immediately begin the left movement. helps make things smoother
			//also, flip the sprites around depending on the direction
			if(changeDirection)
			{
				dir = LEFT;
				changeDirection = false;
				setAnimation(RUNNING_LEFT_ANIMATION);
			}
			else
			{
				//stop movement
				dir = NONE;
				setAnimation(STANDING_RIGHT_ANIMATION);
			}
		}
		else
		{
			//player changed their mind about changing direction
			changeDirection = false;
		}
		break;
	case sf::Keyboard::Left:
		if(dir == LEFT)
		{
			//if the player started to press right while still running left
			//then immediately begin the right movement. helps make things smoother
			//also, flip the sprites around depending on the direction
			if(changeDirection)
			{
				dir = RIGHT;
				changeDirection = false;
				setAnimation(RUNNING_RIGHT_ANIMATION);
			}
			else
			{
				//stop movement
				dir = NONE;
				setAnimation(STANDING_LEFT_ANIMATION);
			}
		}
		else
		{
			//player changed their mind about changing direction
			changeDirection = false;
		}
		break;
	case sf::Keyboard::Up:
		if(dir == UP)
		{
			//if the player started to press right while still running left
			//then immediately begin the right movement. helps make things smoother
			//also, flip the sprites around depending on the direction
			if(changeDirection)
			{
				dir = DOWN;
				changeDirection = false;
				setAnimation(RUNNING_RIGHT_ANIMATION);
			}
			else
			{
				//stop movement
				dir = NONE;
				setAnimation(STANDING_LEFT_ANIMATION);
			}
		}
		else
		{
			//player changed their mind about changing direction
			changeDirection = false;
		}
		break;
	case sf::Keyboard::Down:
		if(dir == DOWN)
		{
			//if the player started to press right while still running left
			//then immediately begin the right movement. helps make things smoother
			//also, flip the sprites around depending on the direction
			if(changeDirection)
			{
				dir = UP;
				changeDirection = false;
				setAnimation(RUNNING_RIGHT_ANIMATION);
			}
			else
			{
				//stop movement
				dir = NONE;
				setAnimation(STANDING_LEFT_ANIMATION);
			}
		}
		else
		{
			//player changed their mind about changing direction
			changeDirection = false;
		}
		break;
	}
}

void Character::setAnimation(Animation nextAnimation)
{
	animation = nextAnimation;
	animation.reset();
}

sf::Sprite Character::getSprite()
{
	return animation.getSprite();
}

// Does an attack on a target
void Character::attackTarget(Character& being)
{
	// If our attack won't kill the enemy
	if(being.currentHealth > this->attackPower)
	{
		// Do the damage
		being.currentHealth = being.currentHealth - this->attackPower;
	}
	// If our attack will kill the enemy
	else
	{
		// Say that the enemy has lost all of its health
		being.currentHealth = 0;
	}
}