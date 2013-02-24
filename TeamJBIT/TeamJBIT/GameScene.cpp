#include "GameScene.h"
#include "SceneManager.h"
GameScene::GameScene() : player("ball.png", sf::Vector2f(400, 300)), scoreNum(0) {

	//TEST STUFF
	/*animSpriteTexture.loadFromFile("yeah.jpg");
	animSpriteTexture.setSmooth(true);
	testSprite.setTexture(animSpriteTexture);
	testSprite.addAnim("yeah", 0, 0, 95, 10, 30, true);
	testSprite.setFrameSize(200, 217);
	testSprite.playAnim("yeah");
	testSprite.setOrigin(100, 108);
	testSprite.setPosition(400, 300);
	testSprite.setScale(800.f/200, 600.f/217);*/

	// Initialize score info
	initializeScoreAndTime();

	enemyDisplacement = 0;
	enemyList.push_back(new Enemy("ball.png", sf::Vector2f(400, 100)));
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
	
void GameScene::update() {
	float deltaTime = (clock.getElapsedTime() - lastFrameTime).asSeconds();
	lastFrameTime = clock.getElapsedTime();
	if(deltaTime >=.1f){ deltaTime = .1f;};

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		if((clock.getElapsedTime() - shotTimer).asSeconds() > player.getShotType()->shotTime()){
		//playerBullets.push_back(new Bullet("ball.png", player.pos, sf::Vector2f(0,-400)));
		player.shoot(playerBullets);
		shotTimer = clock.getElapsedTime();
		}
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
		
		(**it).update(deltaTime, enemyBullets);
		
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
			int thresholdX = abs(player.pos.x - (**it).pos.x);
			int thresholdY = abs(player.pos.y - (**it).pos.y);
		//offscreen check
		if ((**it).getPosition().y > 700) {
			auto itToErase = it;
			it++;
			delete (*itToErase);
			enemyBullets.erase(itToErase);
			continue;

			//check for collision
		}else if( thresholdX < 22 && thresholdY < 22)
		{
			auto itToErase = it;
			it++;
			delete *itToErase;
			enemyBullets.erase(itToErase);
			SceneManager::getInstance().changeScene("end");
			continue;
		}
		

		it++;
	}
	updateScoreAndTime();
	player.update(deltaTime);
	//testSprite.update(deltaTime);
}

void GameScene::draw(sf::RenderWindow& window) {
	//window.draw(testSprite);

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