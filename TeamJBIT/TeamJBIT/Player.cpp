#include "Player.h"
#include "Utility.h"
#include "TextureManager.h"

Player::Player(sf::Vector2f pos)
	:health(1000), totalHealth(1000), pos(pos), shotType(new TriCannonShot), laserShooting(false), laserShotDelay(3.0f), allowLaser(true),
	accumDelayTime(0.0f), swordSwinging(false), allowSword(true), energy(1000), totalEnergy(1000)
{
	planeImage = _getTexture("media/plane.png");
	gunnerImage = _getTexture("media/gunSuit.png");
	fighterImage = _getTexture("media/swordSuit.png");
	sprite.setTexture(*planeImage);
	sprite.setFrameSize(32,32);
	sprite.setScale(1.5,1.5);

	//framerate > game framerate makes it animation a little more irregular, which is desired here
	/*sprite.addAnim("L", 0, 43, 2, 1, 90);
	sprite.addAnim("F", 41, 43, 2, 1, 90);
	sprite.addAnim("R", 82, 43, 2, 1, 90);
	sprite.playAnim("F");

	sprite.addAnim("L2", 95, 36, 1, 1, 1);
	sprite.addAnim("F2", 63, 36, 1, 1, 1);
	sprite.addAnim("R2", (32*6 - 1), 36, 1, 1, 1);
	*/
	sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
	powerUpFound = false;
	playerSwitch = false;
	currentWeaponLevel = 1;
	currentPlayerMode = PLANE_MODE;
	Targetable = true;
	canBlink = true;
	isDoingABarrelRoll = false;
	shieldUp = false;
}


Player::~Player()
{
	 delete shotType;

	 if(laserShooting == true)
		 delete laser;
	 if(swordSwinging == true)
		 delete sword;
}


void Player::update(float deltaTime, std::list<Bullet*>& playerBullets)
{
	sprite.update(deltaTime);

	barrelRollSequence.update(deltaTime);
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		playerSwitch = true;
	}
	else if(playerSwitch)
	{
		currentPlayerMode++;
		
		if(currentPlayerMode == NO_MODE)
			currentPlayerMode = PLANE_MODE;
		if(currentPlayerMode == PLANE_MODE)
		{
			if(meleeType != NULL)
				allowSword = false;
				//delete meleeType;
			shotType = new TriCannonShot;
			sprite.setTexture(*planeImage);
			sprite.setFrameSize(32,32);
			sprite.setScale(1,1);
		}
		else if(currentPlayerMode == GUNNER_MODE)
		{
			delete shotType;
			shotType = new SingleShot(1.25f);
			sprite.setTexture(*gunnerImage);
			sprite.setFrameSize(32,32);
			//sprite.setScale(1.5,1.5);
		}
		else
		{
			//delete shotType;
			//meleeType = new SwordSlash(.75f);
			sprite.setTexture(*fighterImage);
			sprite.setFrameSize(32,32);
			sprite.setScale(1,1);
			allowSword = true;
		}

		playerSwitch = false;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		playerSwitchQ = true;
	}
	else if(playerSwitchQ == true)
	{
			currentPlayerMode--;
		
		if(currentPlayerMode < PLANE_MODE)
			currentPlayerMode = FIGHTER_MODE;
		if(currentPlayerMode == PLANE_MODE)
		{
			if(meleeType != NULL)
				allowSword = false;
				//delete meleeType;
			shotType = new TriCannonShot;
			sprite.setTexture(*planeImage);
			sprite.setFrameSize(32,32);
			sprite.setScale(1,1);
		}
		else if(currentPlayerMode == GUNNER_MODE)
		{
			delete shotType;
			shotType = new SingleShot(1.25f);
			sprite.setTexture(*gunnerImage);
			sprite.setFrameSize(32,32);
			sprite.setScale(1, 1);
			//sprite.setScale(1.5,1.5);
		}
		else
		{
			sprite.setTexture(*fighterImage);
			sprite.setFrameSize(32, 32);
			//delete shotType;
			//meleeType = new SwordSlash(.75f);
			allowSword = true;
		}
		playerSwitchQ = false;
	}
	
	sf::Vector2f movementVec(0, 0);
	if(laserShooting == false)
	{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		movementVec.y += 1;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		movementVec.y -= 1;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		movementVec.x -= 1;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		movementVec.x += 1;
	}

	if (isDoingABarrelRoll) movementVec = sf::Vector2f(); //zero it
	
	//play correct animation (if it isn't already playing)
	if(currentPlayerMode == PLANE_MODE)
	{
		/*if (abs(movementVec.x) < 0.5) {
			if (sprite.getCurrentAnim() != "F") sprite.playAnim("F");
		} else if (movementVec.x > 0.5) {
			if (sprite.getCurrentAnim() != "R") sprite.playAnim("R");
		} else {
			if (sprite.getCurrentAnim() != "L") sprite.playAnim("L");
		}*/
	}

	if(currentPlayerMode == GUNNER_MODE || currentPlayerMode == FIGHTER_MODE)
	{
		/*if (abs(movementVec.x) < 0.5) {
			if (sprite.getCurrentAnim() != "F2") sprite.playAnim("F2");
		} else if (movementVec.x > 0.5) {
			if (sprite.getCurrentAnim() != "R2") sprite.playAnim("R2");
		} else {
			if (sprite.getCurrentAnim() != "L2") sprite.playAnim("L2");
		}*/
	}
	//apply the movement
	pos += normalize(movementVec) * (300 * deltaTime);
	sprite.setPosition(pos);

	//Collide with borders
	}
	if(sprite.getGlobalBounds().top + sprite.getGlobalBounds().height > SCREEN_HEIGHT)
	{
		pos.y = SCREEN_HEIGHT - sprite.getGlobalBounds().height/2 - 0.01;
		sprite.setPosition(pos);
	}
	if(sprite.getGlobalBounds().top < 0)
	{
		pos.y = sprite.getGlobalBounds().height / 2;
		sprite.setPosition(pos);
	}
	if(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width > SCREEN_WIDTH)
	{
		pos.x = SCREEN_WIDTH - sprite.getGlobalBounds().width/2 - 0.01;
		sprite.setPosition(pos);
	}
	if(sprite.getGlobalBounds().left < 0)
	{
		pos.x = sprite.getGlobalBounds().width / 2;
		sprite.setPosition(pos);
	}
	
	switchShot();

	if(laserShooting == true)
	{

		laser->update(deltaTime);

		if(laser->continueDraw == false)
		{
			delete laser;
			laserShooting = false;
		}
	}

	if(allowLaser == false && laserShooting == false)
	{
		accumDelayTime += deltaTime;
		if(accumDelayTime >= laserShotDelay)
		{
			allowLaser = true;
			accumDelayTime = 0;
		}
	}

	if(swordSwinging == true)
	{
		sword->update(deltaTime, pos, playerBullets);

		if(sword->endSwing == true)
		{
			delete sword;
			swordSwinging = false;
		}
	}
}

void Player::draw(sf::RenderWindow& window)
{
	if(laserShooting == true)
	{
		laser->draw(window);
	}

	if(swordSwinging == true)
	{
		sword->draw(window);
	}

	window.draw(sprite);
}

void Player::shoot(std::list<Bullet*>& playerBullets, sf::Vector2f dir)
{
	shotType->doShot(playerBullets, pos, dir);
}

/*void Player::doMelee(sf::Vector2f pos, Melee* currentAtt)
{
    meleeType->doMeleeAttack(pos);
}
*/

void Player::switchShot()
{
	if(currentPlayerMode == GUNNER_MODE)
	{
		if(!powerUpFound)
		{
			delete shotType;
			shotType = new SingleShot(.7f);
		}
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

MeleeType* Player::getMeleeType()
{
	return meleeType;
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
	if(powerUpFound && currentPlayerMode == GUNNER_MODE)
	{
		laserShot(window);
	}
	else  if(currentPlayerMode == PLANE_MODE || currentPlayerMode == GUNNER_MODE)
		shoot(playerBullets, dir);
	else
	{
		//do the melee attack
			swordSwing(window);
	}
	//playerBullets.push_back(new Bullet("bullet.png", pos, sf::Vector2f(dir.x*400, dir.y*400)));

}

void Player::doABarrelRoll(bool isLeft)
{
	if (!barrelRollSequence.isEmpty()) return;

	barrelRollSequence.appendTween(new CDBTweener::CTween(&CDBTweener::TWEQ_SINUSOIDAL, CDBTweener::TWEA_INOUT, 0.9, &pos.x, pos.x + scaledXPos(250 * (isLeft ? -1 : 1))));
	barrelRollSequence.appendCue([&] {isDoingABarrelRoll = false;});
	isDoingABarrelRoll = true;
}

void Player::damaged(int damagedealt)
{
	//health -= damagedealt;
}

bool Player::isDead()
{
	return(health <= 0);
}

void Player::laserShot(sf::RenderWindow& window)
{
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

	laser = new LaserShot(pos, dir);
	laserShooting = true;	
	allowLaser = false;
}

signed int Player::getHealth()
{
	return health;
}

signed int Player::getTotalHealth()
{
	return totalHealth;
}

signed int Player::getEnergy()
{
	return energy;
}

signed int Player::getTotalEnergy()
{
	return totalEnergy;
}

void Player::setTargetable(bool targ)
{
	Targetable = targ;
}

bool Player::isTargetable()
{
	return Targetable;
}

void Player::swordSwing(sf::RenderWindow& window)
{
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

	sword = new BeamSword("media/newSword.png", 0, dir, pos, 30.f, 1000.f);
	swordSwinging = true;
}

sf::FloatRect Player::getSize()
{
	return sprite.getLocalBounds();
}


void Player::increaseHealth(int incrementation)
{
	health += incrementation;

	if(health > totalHealth)
		health = totalHealth;
}

void Player::decreaseEnergy(int decrementation)
{
	energy -= decrementation;

	if(energy <= 0)
		energy = 0;
}

void Player::increaseEnergy(int incrementation)
{
	energy += incrementation;

	if(energy > totalEnergy)
		energy = totalEnergy;
}

void Player::setShieldUp(bool b)
{
	shieldUp = b;
	
}

bool Player::isShieldUp()
{
	return shieldUp;
}

