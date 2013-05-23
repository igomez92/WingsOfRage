#include "WinScene.h"

#include "SceneManager.h"
#include "GameScene.h"
#include "TextureManager.h"
#include "Utility.h"
#include "FontManager.h"

WinScene::WinScene() : bgTextureUpdated(false) {

	//sf::Texture* animSpriteTexture = _getTexture("media/WinImagePlaceholder.jpg");
	//animSpriteTexture->setSmooth(true);

	//winSprite.setTexture(*animSpriteTexture);

	//winSprite.setFrameSize(200, 217);
	//centerOrigin(winSprite);
	//winSprite.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	//winSprite.setScale(SCREEN_WIDTH/200.f, SCREEN_HEIGHT/217.f);
	backgroundTexture.create(SCREEN_WIDTH, SCREEN_HEIGHT);
	backgroundSprite.setTexture(backgroundTexture);

	blackScreen.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));

	//setup credits text
	pauseLabel = sf::Text("LEVEL COMPLETED", *_getFont("media/kimberley bl.ttf"), scaledFontSize(50));
	centerOrigin(pauseLabel);
	pauseLabel.setPosition(SCREEN_WIDTH / 2, 200);
	pauseLabel.setColor(sf::Color(150, 150, 150));

	//buttons
	buttons[0] = TextButton(sf::FloatRect(scaledXPos(325), scaledYPos(250), scaledXPos(150), scaledYPos(50)), "Next Level", scaledFontSize(20), [] {SceneManager::getInstance().changeScene("start");});
	buttons[1] = TextButton(sf::FloatRect(scaledXPos(325), scaledYPos(300), scaledXPos(150), scaledYPos(50)), "Restart Level", scaledFontSize(20), [] {SceneManager::getInstance().deleteScene("start"); SceneManager::getInstance().addScene("start", new GameScene()); SceneManager::getInstance().changeScene("start");});
	buttons[2] = TextButton(sf::FloatRect(scaledXPos(325), scaledYPos(350), scaledXPos(150), scaledYPos(50)), "Quit to Menu", scaledFontSize(20), [] {SceneManager::getInstance().deleteScene("start"); SceneManager::getInstance().changeScene("menu");});
}

void WinScene::enter() {
	bgTextureUpdated = false;

	blackScreen.setFillColor(sf::Color(0,0,0,0));
	fadeTweener.addTween(&CDBTweener::TWEQ_QUADRATIC, CDBTweener::TWEA_INOUT, 0.3, 0, [&] (float alpha) {blackScreen.setFillColor(sf::Color(0, 0, 0, (sf::Uint8)alpha));}, 200);
}

void WinScene::leave() {
	for (CDBTweener::CTween* tween : fadeTweener.getTweens()) {
		fadeTweener.removeTween(tween);
		if (fadeTweener.getTweens().empty()) break;
	}
}

void WinScene::update(sf::RenderWindow& window) {
	float deltaTime = (clock.getElapsedTime() - lastFrameTime).asSeconds();
	lastFrameTime = clock.getElapsedTime();
	if(deltaTime >=.1f){ deltaTime = .1f;};

	if (!bgTextureUpdated) {
		backgroundTexture.update(window);
		bgTextureUpdated = true;
	}

	for(TextButton& button : buttons)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);

		// If the mouse is on the button
		if(button.boundsRect.contains(mousePos.x, mousePos.y))
			button.setSelected();
		else
			button.setUnselected();
	}

	fadeTweener.step(deltaTime);
}

void WinScene::draw(sf::RenderWindow& window) {


	for (TextButton& button : buttons) {
		window.draw(button.labelText);
	}

	window.draw(winSprite);
}

bool WinScene::handleEvent(sf::Event& e) {
	//check buttons
	if (e.type == sf::Event::MouseButtonPressed) {
		for (TextButton& button : buttons) {
			button.processClick(e);
		}
		return true;
	}

	//return to game if ESC pressed again
	if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) {
		SceneManager::getInstance().changeScene("start");
	}

	return false;
}
