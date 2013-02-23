#pragma once

#include "IScene.h"
#include "AnimSprite.h"
class EndGameScene : public IScene {
	public:
		EndGameScene();
		~EndGameScene();

		virtual void update();
		virtual void draw(sf::RenderWindow& window);
		virtual bool handleEvent(sf::Event& event);

	private:
		sf::Texture animSpriteTexture;
		AnimSprite testSprite;

		sf::Font tempestaSevenFont;
		sf::Text gameOverMessage;
		
		sf::Clock clock;
		sf::Time lastFrameTime;
};