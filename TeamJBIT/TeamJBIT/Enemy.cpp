#include "Enemy.h"


Enemy::Enemy(std::string file, int x, int y)
	:VisibleObject(file), continueDraw(true), xPos(x), yPos(y)
{
	setPosition(x,y);
	getSprite().setOrigin(getSprite().getLocalBounds().width/2, getSprite().getLocalBounds().height/2);
}


Enemy::~Enemy(void)
{
}

void Enemy::update()
{
	if(continueDraw == false)
	{
		setPosition(-100, -100);
	}
	else
	{
		yPos += 5;
		setPosition(xPos, yPos);
		if(yPos > 600 + getSprite().getLocalBounds().height)
		{
			yPos -= 600 + getSprite().getLocalBounds().height;
			setPosition(xPos, yPos);
		}
	}
}