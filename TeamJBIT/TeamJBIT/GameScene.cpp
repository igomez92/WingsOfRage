#include "GameScene.h"
#include "SceneManager.h"
#include <SFML/Graphics.hpp>

GameScene::GameScene() : player("ship.png", sf::Vector2f(400, 300)), scoreNum(0) , testDummy("ball.png", sf::Vector2f(500,500))
{
	// Initialize score info
	initializeScoreAndTime();
	
	

	enemyDisplacement = 0;
	enemyList.push_back(new Enemy("ball.png", sf::Vector2f(500, 100)));
	enemyList.push_back(new TankEnemy("ball.png", sf::Vector2f(500,100)));
	enemyList.push_back(new SliderEnemy("ball.png", sf::Vector2f(300,100)));

}

GameScene::~GameScene() 
{
	
	for(auto it = enemyList.begin(); it != enemyList.end(); it++)
		delete (*it);
	for(auto it = playerBullets.begin(); it != playerBullets.end(); it++)
		delete (*it);
	for (auto it = enemyBullets.begin(); it != enemyBullets.end(); it++) 
		delete (*it);
}
	
void GameScene::update(sf::RenderWindow& window) {
	float deltaTime = (clock.getElapsedTime() - lastFrameTime).asSeconds();
	lastFrameTime = clock.getElapsedTime();
	if(deltaTime >=.1f){ deltaTime = .1f;};

	//if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && player.laserShooting == false){
		if((clock.getElapsedTime() - shotTimer).asSeconds() > player.getShotType()->shotTime()){
		//playerBullets.push_back(new Bullet("ball.png", player.pos, sf::Vector2f(0,-400)));
		player.mouseShot(playerBullets, window);
		shotTimer = clock.getElapsedTime();
		}
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player.allowLaser == true)
	{
		if(player.laserShooting == false)
			player.laserShot(window);
	}

	//update bullets
	for (auto it = playerBullets.begin(); it != playerBullets.end();) {
		(**it).update(deltaTime);

		//offscreen check
		if ((**it).getPosition().y < -100) {
			auto itToErase = it;
			it++;
			delete (*itToErase);
			playerBullets.erase(itToErase);
			continue;
		}

		bool removeBullet = false;
		for (auto enemyIt = enemyList.begin(); enemyIt != enemyList.end(); enemyIt++)
		{
			float thresholdX = abs((**enemyIt).pos.x - (**it).pos.x);
			float thresholdY = abs((**enemyIt).pos.y - (**it).pos.y);
			if(thresholdX < 22.f && thresholdY < 22.f)
			{
				(**enemyIt).takeDam((**it).dam);
				removeBullet = true;
				break;
			}
		}

		if (removeBullet)
		{
			auto itToErase = it;
			it++;
			delete (*itToErase);
			playerBullets.erase(itToErase);
			continue;
		}


		it++;
	}
	if(player.laserShooting == true)
	{
		for (auto it = enemyList.begin(); it != enemyList.end(); it++)
		{
			if(player.laser->collidesWith(**it))
			{
				(**it).takeDam(player.laser->dam);
			}
		}
	}
	for (auto it = enemyList.begin(); it != enemyList.end();) 
	{
		if((**it).isDead())
		{
			scoreNum += 100;

			auto itToErase = it;
			it++;
			delete (*itToErase);
			enemyList.erase(itToErase);
			continue;
		}
		
		(**it).update(deltaTime, enemyBullets,player.pos);
		
		it++;
	}

	if(enemyList.empty())
		{
			if(enemyDisplacement >= 600)
			{
				enemyDisplacement = 0;
			}else
			{
   				enemyDisplacement += 100;
			}
			enemyList.push_back(new Enemy("ball.png", sf::Vector2f(enemyDisplacement , 0)));
			enemyList.push_back(new Enemy("ball.png", sf::Vector2f(enemyDisplacement+100, 0)));
			
		}

	for (auto it = enemyBullets.begin(); it != enemyBullets.end();) {
		(**it).update(deltaTime);
		//threshholds for enemy bullet to player collision
		float thresholdX = abs(player.pos.x - (**it).pos.x);
		float thresholdY = abs(player.pos.y - (**it).pos.y);

		//offscreen check
		if ((**it).getPosition().y > 700) {
			auto itToErase = it;
			it++;
			delete (*itToErase);
			enemyBullets.erase(itToErase);
			continue;

			//check for collision
		} else if ( thresholdX < 22 && thresholdY < 22) {
			auto itToErase = it;
			player.damaged((**it).dam);
			it++;
			delete *itToErase;
			enemyBullets.erase(itToErase);

			if(player.isDead())
				SceneManager::getInstance().changeScene("end");

			continue;
		}
		

		it++;
	}
	if(abs(player.pos.x - testDummy.pos.x) < 22 && abs(player.pos.y - testDummy.pos.y) < 22)
	{
		player.powerUP();
		
	}


	updateScoreAndTime();
	player.update(deltaTime);
}

void GameScene::draw(sf::RenderWindow& window) {
	//draw our bullets
	for (auto it = playerBullets.begin(); it != playerBullets.end(); it++) {
		(**it).draw(window);
	}	

	//draw enemy bullets
	for (auto it = enemyBullets.begin(); it != enemyBullets.end(); it++) {
		(**it).draw(window);
	}

	//draw enemies
	for (auto it = enemyList.begin(); it != enemyList.end(); it++) 
	{
		(**it).draw(window);
	}
	player.draw(window);
	testDummy.draw(window);
	printScoreAndTime(window);
}

bool GameScene::handleEvent(sf::Event& event) {
	return false;
}

void GameScene::initializeScoreAndTime()
{
	tempestaSevenFont.loadFromFile("pf_tempesta_seven.ttf");

	timer = sf::Text("0:00", tempestaSevenFont, 20);
	//timer.setOrigin(timer.getLocalBounds().width / 2.f, timer.getLocalBounds().height / 2.f);
	timer.setPosition(5, 10);

	scoreStr << scoreNum;
	score = sf::Text(scoreStr.str(), tempestaSevenFont, 20);
	//score.setOrigin(score.getLocalBounds().width / 2.f, score.getLocalBounds().height / 2.f);
	score.setPosition(5, 35);
	scoreStr.str("");
	scoreStr.clear();
}

void GameScene::updateScoreAndTime()
{
	int time = clock.getElapsedTime().asSeconds();
	timeStr << "Time: ";
	if(time/60 == 0)
		timeStr << "0:";
	else
	{
		timeStr << time/60 << ":";
		// Get Seconds
		time = time%60;
	}
	if(time < 10)
		timeStr << "0" <<time;
	else
		timeStr << time;

	timer.setString(timeStr.str());
	timeStr.str("");
	timeStr.clear();

	scoreStr << "Score: " << scoreNum;
	score.setString(scoreStr.str());
	scoreStr.str("");
	scoreStr.clear();
}

void GameScene::printScoreAndTime(sf::RenderWindow& window)
{
	window.draw(timer);
	window.draw(score);
}