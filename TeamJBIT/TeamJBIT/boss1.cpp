#include "Boss1.h"
#include "Utility.h"

Boss1::Boss1(std::string file, sf::Vector2f pos, int health):Enemy(file,pos,health)
{
	collisiondmg = 100;
	type = Boss;
	attackswitchtimer = 0;
	sprite.rotate(180);
}


void Boss1::update(float deltaTime, std::list<Bullet*>& eList, std::list<Bullet*>& pList, Player& player)
{
	attackswitchtimer += deltaTime;
	if(attackswitchtimer < 10)
	{
		attackPattern1(deltaTime,eList,pList,player.pos);
	}else if(attackswitchtimer >= 10 && attackswitchtimer < 15)
	{
		attackPattern2(deltaTime,eList,pList,player.pos);
	}else if(attackswitchtimer >= 15 && attackswitchtimer < 20)
	{
		attackPattern3(deltaTime,eList,pList,player.pos);
	}else if(attackswitchtimer >=20)
	{
		attackPattern1(deltaTime,eList,pList,player.pos);
		attackswitchtimer = 0;
	}
}


void Boss1::attackPattern1(float deltaTime, std::list<Bullet*>& eList, std::list<Bullet*>& pList, sf::Vector2f player_pos)
{
	pos.x = 400;
	pos.y = 100;
	sprite.setPosition(pos);

	sf::Vector2f shootingpoints[5];
	for(int i = 0; i < 5; i++)
	{
		sf::Vector2f vectorToAdd;
		vectorToAdd.x = ((int)((SCREEN_WIDTH/5.0f)*i))+100;
		vectorToAdd.y = 100;
		shootingpoints[i] = vectorToAdd;
	}
	
		if (bulletClock.getElapsedTime().asSeconds() > .1)
		{
			for(int i = 0 ; i < 5; i++)
			{
				sf::Vector2f aiming;
				sf::Vector2f temp = (shootingpoints[i] - player_pos);
					temp = normalize(temp);

					aiming.x = temp.x * -300;
					aiming.y = temp.y * -300;

				eList.push_back(new Bullet("media/bullet.png", shootingpoints[i], aiming, 5, sf::Color(255, 50, 50)));
				
			}
			bulletClock.restart();
		}
		

}

void Boss1::attackPattern2(float deltaTime, std::list<Bullet*>& eList, std::list<Bullet*>& pList, sf::Vector2f player_pos)
{
	pos.x = SCREEN_WIDTH - 100;
	pos.y = 100;
	sprite.setPosition(pos);



	sf::Vector2f shootingpoints[8];
	for(int i = 0; i < 8; i++)
	{
		sf::Vector2f vectorToAdd;
		vectorToAdd.x = SCREEN_WIDTH;
		vectorToAdd.y = ((SCREEN_HEIGHT/8)*i)+100;;
		shootingpoints[i] = vectorToAdd;
	}

	
		if (bulletClock.getElapsedTime().asSeconds() > .1)
			{

				eList.push_back(new Bullet("media/bullet.png", shootingpoints[0], sf::Vector2f(-400, 0), 10, sf::Color(255, 50, 250)));
				eList.push_back(new Bullet("media/bullet.png", shootingpoints[1], sf::Vector2f(-400, 0), 10, sf::Color(255, 50, 250)));
				eList.push_back(new Bullet("media/bullet.png", shootingpoints[2], sf::Vector2f(-400, 0), 10, sf::Color(255, 50, 250)));
				eList.push_back(new Bullet("media/bullet.png", shootingpoints[3], sf::Vector2f(-400, 0), 10, sf::Color(255, 50, 250)));
				eList.push_back(new Bullet("media/bullet.png", shootingpoints[4], sf::Vector2f(-400, 0), 10, sf::Color(255, 50, 250)));
				eList.push_back(new Bullet("media/bullet.png", shootingpoints[5], sf::Vector2f(-400, 0), 10, sf::Color(255, 50, 250)));
				eList.push_back(new Bullet("media/bullet.png", shootingpoints[6], sf::Vector2f(-400, 0), 10, sf::Color(255, 50, 250)));
				eList.push_back(new Bullet("media/bullet.png", shootingpoints[7], sf::Vector2f(-400, 0), 10, sf::Color(255, 50, 250)));
				
				bulletClock.restart();
			}
	
}

void Boss1::attackPattern3(float deltaTime, std::list<Bullet*>& eList, std::list<Bullet*>& pList, sf::Vector2f player_pos)
{
	pos.x = 100;
	pos.y = 100;
	sprite.setPosition(pos);



	sf::Vector2f shootingpoints[8];
	for(int i = 0; i < 8; i++)
	{
		sf::Vector2f vectorToAdd;
		vectorToAdd.x = 0;
		vectorToAdd.y = ((SCREEN_HEIGHT/8)*i) +50;;
		shootingpoints[i] = vectorToAdd;
	}

	for(int i = 0; i < 8; i++)
	{
		if (bulletClock.getElapsedTime().asSeconds() > .1)
			{

				eList.push_back(new Bullet("media/bullet.png", shootingpoints[0], sf::Vector2f(400, 0), 10, sf::Color(255, 250, 50)));
				eList.push_back(new Bullet("media/bullet.png", shootingpoints[1], sf::Vector2f(400, 0), 10, sf::Color(255, 250, 50)));
				eList.push_back(new Bullet("media/bullet.png", shootingpoints[2], sf::Vector2f(400, 0), 10, sf::Color(255, 250, 50)));
				eList.push_back(new Bullet("media/bullet.png", shootingpoints[3], sf::Vector2f(400, 0), 10, sf::Color(255, 250, 50)));
				eList.push_back(new Bullet("media/bullet.png", shootingpoints[4], sf::Vector2f(400, 0), 10, sf::Color(255, 250, 50)));
				eList.push_back(new Bullet("media/bullet.png", shootingpoints[5], sf::Vector2f(400, 0), 10, sf::Color(255, 250, 50)));
				eList.push_back(new Bullet("media/bullet.png", shootingpoints[6], sf::Vector2f(400, 0), 10, sf::Color(255, 250, 50)));
				eList.push_back(new Bullet("media/bullet.png", shootingpoints[7], sf::Vector2f(400, 0), 10, sf::Color(255, 250, 50)));
				
				bulletClock.restart();
			}
	}
}