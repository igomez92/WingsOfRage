#include "CreditsScene.h"

#include "SceneManager.h"
#include "TextureManager.h"
#include "Utility.h"
#include "FontManager.h"

CreditsScene::CreditsScene() : backgroundScroll(0) {

	sf::Texture* backgroundTexture = _getTexture("media/backgrounds/starsLow.png");
	backgroundTexture->setRepeated(true);
	backgroundTexture->setSmooth(true);
	backgroundSprite.setTexture(*backgroundTexture);
	backgroundSprite.setTextureRect(sf::IntRect(0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2));

	blackScreen.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	blackScreen.setFillColor(sf::Color::Black);
	//fade in
	fadeTweener.addTween(&CDBTweener::TWEQ_QUADRATIC, CDBTweener::TWEA_INOUT, 1, 255, [&] (float alpha) {blackScreen.setFillColor(sf::Color(0, 0, 0, (sf::Uint8)alpha));}, 0);

	//setup credits text
	teamLabel = sf::Text("Team JBIT", *_getFont("media/kimberley bl.ttf"), 50);
	centerOrigin(teamLabel);
	teamLabel.setPosition(400, 150);
	teamLabel.setColor(sf::Color(150, 150, 150));

	teamList = sf::Text("Jonathan Wendorf \n    Brian Charles \n    Isidro Gomez  \n     Tommy Tran  ", *_getFont("media/kimberley bl.ttf"), 40);
	teamList.setOrigin((int)teamList.getLocalBounds().width / 2, 0);
	teamList.setPosition(400, 200);

	backButton = TextButton(sf::FloatRect(200, 500, 400, 50), "Back to Menu", 30, [] {SceneManager::getInstance().changeScene("menu");});
}

CreditsScene::~CreditsScene() {
}

void CreditsScene::update(sf::RenderWindow& window) {
	float deltaTime = (clock.getElapsedTime() - lastFrameTime).asSeconds();
	lastFrameTime = clock.getElapsedTime();
	if(deltaTime >=.1f){ deltaTime = .1f;};

	backgroundScroll += 50 * deltaTime;
	if (backgroundScroll >= 512)
		backgroundScroll -= 512;
	backgroundSprite.setPosition(-backgroundScroll, -backgroundScroll);

	fadeTweener.step(deltaTime);
}

void CreditsScene::draw(sf::RenderWindow& window) {
	window.clear(sf::Color::Black);
	window.draw(backgroundSprite);

	window.draw(teamLabel);
	window.draw(teamList);

	window.draw(backButton.labelText);

	window.draw(blackScreen);
}

bool CreditsScene::handleEvent(sf::Event& e) {
	//check button
	if (e.type == sf::Event::MouseButtonPressed) {
		backButton.processClick(e);
		return true;
	}

	return false;
}
