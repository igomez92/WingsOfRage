#include "MenuScene.h"
#include "SceneManager.h"
#include "TextureManager.h"
#include "Utility.h"
#include "GameScene.h"

MenuScene::MenuScene() : shouldQuit(false), backgroundScroll(0) {
	sf::Texture* gameLogoTexture = _getTexture("media/UI/GameLogo.png");
	gameLogoSprite.setTexture(*gameLogoTexture);
	centerOrigin(gameLogoSprite);
	gameLogoSprite.setPosition(SCREEN_WIDTH / 2, scaledYPos(130));

	sf::Texture* backgroundTexture = _getTexture("media/backgrounds/starsLow.png");
	backgroundTexture->setRepeated(true);
	backgroundTexture->setSmooth(true);
	backgroundSprite.setTexture(*backgroundTexture);
	backgroundSprite.setTextureRect(sf::IntRect(0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2));

	blackScreen.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));

	//buttons
	buttons[0] = new TextButton(sf::FloatRect(scaledXPos(200), scaledYPos(300), scaledXPos(400), scaledYPos(50)), "Play", scaledFontSize(40), [] {SceneManager::getInstance().addScene("start", new GameScene());; SceneManager::getInstance().changeScene("start");});
	buttons[1] = new TextButton(sf::FloatRect(scaledXPos(200), scaledYPos(365), scaledXPos(400), scaledYPos(50)), "Credits", scaledFontSize(40), [] {SceneManager::getInstance().changeScene("credits");});
	buttons[2] = new TextButton(sf::FloatRect(scaledXPos(200), scaledYPos(430), scaledXPos(400), scaledYPos(50)), "Quit", scaledFontSize(40), [&] {shouldQuit = true;});
}

MenuScene::~MenuScene() {
	for (TextButton* button : buttons) {
		delete button;
	}
}

void MenuScene::enter() {
	blackScreen.setFillColor(sf::Color::Black);
	fadeTweener.addTween(&CDBTweener::TWEQ_QUADRATIC, CDBTweener::TWEA_INOUT, 0.5, 255, [&] (float alpha) {blackScreen.setFillColor(sf::Color(0, 0, 0, (sf::Uint8)alpha));}, 0);
}

void MenuScene::leave() {
	for (CDBTweener::CTween* tween : fadeTweener.getTweens()) {
		fadeTweener.removeTween(tween);
		if (fadeTweener.getTweens().empty()) break;
	}
}

void MenuScene::update(sf::RenderWindow& window) {
	float deltaTime = (clock.getElapsedTime() - lastFrameTime).asSeconds();
	lastFrameTime = clock.getElapsedTime();
	if(deltaTime >=.1f){ deltaTime = .1f;};

	backgroundScroll += 50 * deltaTime;
	if (backgroundScroll >= 512)
		backgroundScroll -= 512;
	backgroundSprite.setPosition(-backgroundScroll, -backgroundScroll);

	fadeTweener.step(deltaTime);

	if (shouldQuit)
		window.close();
}

void MenuScene::draw(sf::RenderWindow& window) {
	window.clear(sf::Color::Black);
	window.draw(backgroundSprite);
	window.draw(gameLogoSprite);

	for (TextButton* button : buttons) {
		window.draw(button->labelText);
	}

	window.draw(blackScreen);
}

bool MenuScene::handleEvent(sf::Event& e) {
	//check buttons
	if (e.type == sf::Event::MouseButtonPressed) {
		for (TextButton* button : buttons) {
			button->processClick(e);
		}
		return true;
	}

	return false;
}
