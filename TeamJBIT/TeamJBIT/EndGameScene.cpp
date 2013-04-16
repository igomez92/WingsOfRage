#include "EndGameScene.h"
#include <cmath>
#include <SFML\System.hpp>
#include "SceneManager.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "Utility.h"

EndGameScene::EndGameScene() {
	sf::Texture* animSpriteTexture = _getTexture("media/yeah.jpg");
	animSpriteTexture->setSmooth(true);

	testSprite.setTexture(*animSpriteTexture);
	testSprite.addAnim("yeah", 0, 0, 95, 10, 30, true);
	testSprite.setFrameSize(200, 217);
	testSprite.playAnim("yeah");
	centerOrigin(testSprite);
	testSprite.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	testSprite.setScale(SCREEN_WIDTH/200.f, SCREEN_HEIGHT/217.f);

	gameOverMessage = sf::Text("GAME OVER", *_getFont("media/pf_tempesta_seven.ttf"), scaledFontSize(100));
	centerOrigin(gameOverMessage);
	gameOverMessage.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}

EndGameScene::~EndGameScene() {

}

void EndGameScene::enter() {
	clock.restart();
	lastFrameTime = sf::Time::Zero;
	testSprite.playAnim("yeah");
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
	if ((event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed) && clock.getElapsedTime().asSeconds() > 1) {
		SceneManager::getInstance().deleteScene("start");
		SceneManager::getInstance().changeScene("menu");

		return true;
	}

	return false;
}