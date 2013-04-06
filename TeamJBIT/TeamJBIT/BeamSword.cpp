#include "BeamSword.h"
#include "TextureManager.h"
#include "Enemy.h"

BeamSword::BeamSword(std::string file, float delay, sf::Vector2f dir, sf::Vector2f pos, float damage, float swingSpeed)
	:dir(dir), currentAngle(-60), swingSpeed(swingSpeed), dam(damage), pos(pos)
{
	sf::Texture* image = TextureManager::getInstance().getTexture(file);
	sprite.setTexture(*image);
	sprite.setOrigin(0, sprite.getLocalBounds().height/2);
	sprite.setPosition(pos);
	//sprite.scale(2, 0.5);
	sprite.rotate((-atan2f(dir.x, dir.y) * (180 / 3.1415926f)));
}

BeamSword::~BeamSword(void)
{
}

bool BeamSword::collidesWith(Enemy& enemy)
{
	// Check points on enemy to see if within the sword swing

	// Center
	if(enemy.pos.x >= sprite.getGlobalBounds().left && 
		enemy.pos.x <= sprite.getGlobalBounds().left+sprite.getGlobalBounds().width &&
		enemy.pos.y >= sprite.getGlobalBounds().top &&
		enemy.pos.y <= sprite.getGlobalBounds().top + sprite.getGlobalBounds().height)
	{
		return true;
	}
	// Bottom left
	else if(enemy.pos.x - enemy.getSize().width/2 >= sprite.getGlobalBounds().left && 
		enemy.pos.x - enemy.getSize().width/2 <= sprite.getGlobalBounds().left+sprite.getGlobalBounds().width &&
		enemy.pos.y + enemy.getSize().height/2 >= sprite.getGlobalBounds().top &&
		enemy.pos.y + enemy.getSize().height/2 <= sprite.getGlobalBounds().top + sprite.getGlobalBounds().height)
	{
		return true;
	}
	// Top Left
	else if(enemy.pos.x - enemy.getSize().width/2 >= sprite.getGlobalBounds().left && 
		enemy.pos.x - enemy.getSize().width/2 <= sprite.getGlobalBounds().left+sprite.getGlobalBounds().width &&
		enemy.pos.y - enemy.getSize().height/2 >= sprite.getGlobalBounds().top &&
		enemy.pos.y - enemy.getSize().height/2 <= sprite.getGlobalBounds().top + sprite.getGlobalBounds().height)
	{
		return true;
	}
	// Bottom Right
	else if(enemy.pos.x + enemy.getSize().width/2 >= sprite.getGlobalBounds().left && 
		enemy.pos.x + enemy.getSize().width/2 <= sprite.getGlobalBounds().left+sprite.getGlobalBounds().width &&
		enemy.pos.y + enemy.getSize().height/2 >= sprite.getGlobalBounds().top &&
		enemy.pos.y + enemy.getSize().height/2 <= sprite.getGlobalBounds().top + sprite.getGlobalBounds().height)
	{
		return true;
	}
	// Top Right
	else if(enemy.pos.x + enemy.getSize().width/2 >= sprite.getGlobalBounds().left && 
		enemy.pos.x + enemy.getSize().width/2 <= sprite.getGlobalBounds().left+sprite.getGlobalBounds().width &&
		enemy.pos.y - enemy.getSize().height/2 >= sprite.getGlobalBounds().top &&
		enemy.pos.y - enemy.getSize().height/2 <= sprite.getGlobalBounds().top + sprite.getGlobalBounds().height)
	{
		return true;
	}
	// If we aren't within the position, return false
	return false;
}

void BeamSword::doDamage(Enemy& enemy)
{
	enemy.takeDam(dam);
}

void BeamSword::update(float deltaTime, sf::Vector2f pos)
{
	// Calculate our new angle of swing
	currentAngle += swingSpeed*deltaTime;	

	sprite.setRotation(currentAngle + (-atan2f(dir.x, dir.y) * (180 / 3.1415926f))+90);

	// if the angle is above 120 degrees, end the attack
	if(currentAngle >= 60)
		endSwing = true;

	sprite.setPosition(pos);
}

void BeamSword::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}