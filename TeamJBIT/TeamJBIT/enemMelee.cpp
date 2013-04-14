#include "enemMelee.h"
#include "TextureManager.h"

enemMelee::enemMelee(std::string file, float delay, sf::Vector2f dir, sf::Vector2f pos, float damage, float swingSpeed)
	:dir(dir), currentAngle(-60), swingSpeed(swingSpeed), dam(damage), pos(pos), endSwing(false)
{
	sf::Texture* image = _GETTEXTURE(file);
	sprite.setTexture(*image);
	sprite.setOrigin(0, sprite.getLocalBounds().height/2);
	sprite.setPosition(pos);
	//sprite.scale(2, 0.5);
	sprite.rotate((-atan2f(dir.x, dir.y) * (180 / 3.1415926f)));
}

enemMelee::~enemMelee(void)
{
}

bool enemMelee::collidesWith(Player& player)
{
	// Check points on player to see if within the sword swing

	// Center
	if(player.pos.x >= sprite.getGlobalBounds().left && 
		player.pos.x <= sprite.getGlobalBounds().left+sprite.getGlobalBounds().width &&
		player.pos.y >= sprite.getGlobalBounds().top &&
		player.pos.y <= sprite.getGlobalBounds().top + sprite.getGlobalBounds().height)
	{
		return true;
	}
	// Bottom left
	else if(player.pos.x - player.getSize().width/2 >= sprite.getGlobalBounds().left && 
		player.pos.x - player.getSize().width/2 <= sprite.getGlobalBounds().left+sprite.getGlobalBounds().width &&
		player.pos.y + player.getSize().height/2 >= sprite.getGlobalBounds().top &&
		player.pos.y + player.getSize().height/2 <= sprite.getGlobalBounds().top + sprite.getGlobalBounds().height)
	{
		return true;
	}
	// Top Left
	else if(player.pos.x - player.getSize().width/2 >= sprite.getGlobalBounds().left && 
		player.pos.x - player.getSize().width/2 <= sprite.getGlobalBounds().left+sprite.getGlobalBounds().width &&
		player.pos.y - player.getSize().height/2 >= sprite.getGlobalBounds().top &&
		player.pos.y - player.getSize().height/2 <= sprite.getGlobalBounds().top + sprite.getGlobalBounds().height)
	{
		return true;
	}
	// Bottom Right
	else if(player.pos.x + player.getSize().width/2 >= sprite.getGlobalBounds().left && 
		player.pos.x + player.getSize().width/2 <= sprite.getGlobalBounds().left+sprite.getGlobalBounds().width &&
		player.pos.y + player.getSize().height/2 >= sprite.getGlobalBounds().top &&
		player.pos.y + player.getSize().height/2 <= sprite.getGlobalBounds().top + sprite.getGlobalBounds().height)
	{
		return true;
	}
	// Top Right
	else if(player.pos.x + player.getSize().width/2 >= sprite.getGlobalBounds().left && 
		player.pos.x + player.getSize().width/2 <= sprite.getGlobalBounds().left+sprite.getGlobalBounds().width &&
		player.pos.y - player.getSize().height/2 >= sprite.getGlobalBounds().top &&
		player.pos.y - player.getSize().height/2 <= sprite.getGlobalBounds().top + sprite.getGlobalBounds().height)
	{
		return true;
	}
	// If we aren't within the position, return false
	return false;
}

void enemMelee::doDamage(Player& player)
{
	player.damaged(dam);
}

void enemMelee::update(float deltaTime, sf::Vector2f pos)
{
	// Calculate our new angle of swing
	currentAngle += swingSpeed*deltaTime;	

	sprite.setRotation(currentAngle + (-atan2f(dir.x, dir.y) * (180 / 3.1415926f))+90);

	// if the angle is above 120 degrees, end the attack
	if(currentAngle >= 60)
		endSwing = true;

	sprite.setPosition(pos);
}

void enemMelee::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}