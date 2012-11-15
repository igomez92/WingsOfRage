#include "Animation.h"
#include <SFML/Graphics.hpp>
#include <iostream>

AnimationType animationType;
sf::Sprite sprite;
sf::Texture texture;
sf::Clock animationClock;
std::vector<sf::IntRect> spriteRects;
int animationTime; //milliseconds
int spriteIndex;

Animation::Animation() {}

Animation::Animation(AnimationType type)
{
	bool didReadFile = false;
	animationType = type;
	switch(animationType)
	{
	case RUNNING_RIGHT:
		didReadFile = texture.loadFromFile("runningSprites.png");
		animationTime = 50;
		break;
	case RUNNING_LEFT:
		didReadFile = texture.loadFromFile("runningSprites.png");
		animationTime = 50;
		sprite.scale(-1.f, 1.f);
		break;
	case STANDING_RIGHT:
		didReadFile = texture.loadFromFile("runningSprites.png");
		animationTime = 100;
		break;
	case STANDING_LEFT:
		didReadFile = texture.loadFromFile("runningSprites.png");
		animationTime = 100;
		sprite.scale(-1.f, 1.f);
		break;
	}
	if(didReadFile)
	{
		sprite.setTexture(texture);
		sprite.setOrigin(21.3f, 25.6f);
	}
	else
	{
		std::cout << "Could not read image file" << std::endl;
	}
	createRects();
	spriteIndex = 0;
}

Animation::~Animation()
{
}

void Animation::createRects()
{
	switch(animationType)
	{
		//set up running animation sprite rectangles
	case RUNNING_RIGHT:
		for(int r=0; r<5; r++)
		{
			for(int c=0; c<6; c++)
			{
				spriteRects.push_back(sf::IntRect(42.6*c, 51.2*r, 40, 50));
			}
		}
		break;
	case RUNNING_LEFT:
		for(int r=0; r<5; r++)
		{
			for(int c=0; c<6; c++)
			{
				spriteRects.push_back(sf::IntRect(42.6*c, 51.2*r, 40, 50));
			}
		}
		break;
	case STANDING_RIGHT:
		spriteRects.push_back(sf::IntRect(0, 0, 40, 50));
		break;
	case STANDING_LEFT:
		spriteRects.push_back(sf::IntRect(0, 0, 40, 50));
		break;
	}
}

void Animation::update(int x, int y)
{
	//use animation timer to iterate through the sprite rectangles
	if(animationClock.getElapsedTime().asMilliseconds() > animationTime)
	{
		spriteIndex++;
		animationClock.restart();
	}
	//if it reaches the last sprite rectangle, go back to the first one
	if(spriteIndex == spriteRects.size())
		spriteIndex = 0;
	//set the next sprite rectangle
	sprite.setTextureRect(spriteRects.at(spriteIndex));
	sprite.setPosition(x, y);
}

sf::Sprite Animation::getSprite()
{
	return sprite;
}

void Animation::reset()
{
	spriteIndex = 0;
	animationClock.restart();
}