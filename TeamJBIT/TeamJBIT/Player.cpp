#include "Player.h"
Player::Player(std::string file, sf::Vector2f pos)
	:health(15), pos(pos), shotType(new TriCannonShot)
{
	image.loadFromFile(file);
	sprite.setTexture(image);
	sprite.setFrameSize(42,43);
	sprite.addAnim("ship", 0, 0, 9, 3, -1);
	sprite.playAnim("ship");
	sprite.showFrame(4);
	sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
	powerUpFound = false;
	playerSwitch = false;
	currentWeaponLevel = 1;
	currentPlayerMode = 0;
}


Player::~Player()
{
	 delete shotType;
}


void Player::update(float deltaTime)
{
	sprite.update(deltaTime);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		playerSwitch = true;
	}
	else if(playerSwitch)
	{
		currentPlayerMode++;
		
		if(currentPlayerMode == 3)
			currentPlayerMode = 0;
		if(currentPlayerMode == 0)
		{
			delete shotType;
			shotType = new TriCannonShot;
		}
		else if(currentPlayerMode == 1)
		{
			delete shotType;
			shotType = new SingleShot(1.25f);
		}
		playerSwitch = false;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		pos.y += 300 * deltaTime;
		sprite.setPosition(pos);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		pos.y -= 300 * deltaTime;
		sprite.setPosition(pos);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		pos.x -= 300 * deltaTime;
		sprite.setPosition(pos);
		sprite.showFrame(3);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		pos.x += 300 * deltaTime;
		sprite.setPosition(pos);
		sprite.showFrame(5);
	}
	else
	{
		sprite.showFrame(4);
	}
	
	if(sprite.getGlobalBounds().top + sprite.getGlobalBounds().height > 600)
	{
		pos.y = 600 - sprite.getGlobalBounds().height/2 - 0.01;
		sprite.setPosition(pos);
	}
	if(sprite.getGlobalBounds().top < 0)
	{
		pos.y = sprite.getGlobalBounds().height / 2;
		sprite.setPosition(pos);
	}
	if(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width > 800)
	{
		pos.x = 800 - sprite.getGlobalBounds().width/2 - 0.01;
		sprite.setPosition(pos);
	}
	if(sprite.getGlobalBounds().left < 0)
	{
		pos.x = sprite.getGlobalBounds().width / 2;
		sprite.setPosition(pos);
	}
	
	switchShot();
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void Player::shoot(std::list<Bullet*>& playerBullets, sf::Vector2f dir)
{
	shotType->doShot(playerBullets, pos, dir);
}

void Player::switchShot()
{
	if(currentPlayerMode == 1)
	{
		delete shotType;
		shotType = new SingleShot(1.25f);
	}
	
	else if(powerUpFound && currentWeaponLevel == 1)
	{
		delete shotType;
		shotType = new MultiPhotonShot;
	}
}

void Player::powerUP()
{
	powerUpFound = true;
}

ShotType* Player::getShotType()
{
	return shotType;
}

void Player::mouseShot(std::list<Bullet*>& playerBullets, sf::RenderWindow& window)
{

// Get the Position of the mouse
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	
	// Get the Direction of the shot
	sf::Vector2f dir;
	dir.x = (float)mousePos.x - pos.x;
	dir.y = (float)mousePos.y - pos.y;
	float norm = sqrt((dir.x*dir.x)+(dir.y*dir.y));
	
	// Compute the direction of our shot
	if(norm != 0.f)
	{
		dir.x = dir.x/norm;
		dir.y = dir.y/norm;
	}
	if(currentPlayerMode == 0 || currentPlayerMode == 1)
		shoot(playerBullets, dir);
	//else
		//do the melee attack 

	//playerBullets.push_back(new Bullet("bullet.png", pos, sf::Vector2f(dir.x*400, dir.y*400)));

}

void Player::damaged(int damagedealt)
{
	health -= damagedealt;
}

bool Player::isDead()
{
	if(health <= 0)
		return true;

	return false;
}