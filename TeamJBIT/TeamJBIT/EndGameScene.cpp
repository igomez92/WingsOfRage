#include "EndGameScene.h"
#include <cmath>
#include <SFML\System.hpp>
#include "SceneManager.h"
#include "TextureManager.h"
#include "FontManager.h"

EndGameScene::EndGameScene()  {
	sf::Texture* animSpriteTexture = _getTexture("media/yeah.jpg");
	animSpriteTexture->setSmooth(true);

	testSprite.setTexture(*animSpriteTexture);
	testSprite.addAnim("yeah", 0, 0, 95, 10, 30, true);
	testSprite.setFrameSize(200, 217);
	testSprite.playAnim("yeah");
	testSprite.setOrigin(100, 108);
	testSprite.setPosition(400, 300);
	testSprite.setScale(800.f/200, 600.f/217);

	gameOverMessage = sf::Text("GAME OVER", *_getFont("media/pf_tempesta_seven.ttf"), 100);
	gameOverMessage.setOrigin(gameOverMessage.getLocalBounds().width / 2.f, gameOverMessage.getLocalBounds().height / 2.f);
	gameOverMessage.setPosition(400, 300);
}

EndGameScene::~EndGameScene() {

}

void EndGameScene::update(sf::RenderWindow& window) {
	float deltaTime = (clock.getElapsedTime() - lastFrameTime).asSeconds();
	lastFrameTime = clock.getElapsedTime();
	if(deltaTime >=.1){ deltaTime = .1;};

	gameOverMessage.setRotation(std::sinf(clock.getElapsedTime().asSeconds()));

	testSprite.update(deltaTime);
}

void EndGameScene::draw(sf::RenderWindow& window) {
	window.draw(testSprite);
	window.draw(gameOverMessage);
}

bool EndGameScene::handleEvent(sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		SceneManager::getInstance().deleteScene("start");
		SceneManager::getInstance().changeScene("menu");

		return true;
	}

	return false;
}