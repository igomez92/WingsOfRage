#include "GameScene.h"

GameScene::GameScene() : player("ball.png", sf::Vector2f(400, 300)), enemy("ball.png", sf::Vector2f(300, 50)) {

	//TEST STUFF
	animSpriteTexture.loadFromFile("yeah.jpg");
	animSpriteTexture.setSmooth(true);
	testSprite.setTexture(animSpriteTexture);
	testSprite.addAnim("yeah", 0, 0, 95, 10, 30, true);
	testSprite.setFrameSize(200, 217);
	testSprite.playAnim("yeah");
	testSprite.setOrigin(100, 108);
	testSprite.setPosition(400, 300);
	testSprite.setScale(800.f/200, 600.f/217);
}

GameScene::~GameScene() {

}
	
void GameScene::update() {
	float deltaTime = (clock.getElapsedTime() - lastFrameTime).asSeconds();
	lastFrameTime = clock.getElapsedTime();


	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		playerBullets.push_back(new Bullet("ball.png", player.pos, sf::Vector2f(0,-400)));
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

		it++;
	}

	enemy.update(deltaTime);
	player.update(deltaTime);
	testSprite.update(deltaTime);
}

void GameScene::draw(sf::RenderWindow& window) {
	window.draw(testSprite);

	//draw bullets
	for (auto it = playerBullets.begin(); it != playerBullets.end(); it++) {
		(**it).draw(window);
	}	

	enemy.draw(window);
	player.draw(window);	
}

bool GameScene::handleEvent(sf::Event& event) {
	return false;
}