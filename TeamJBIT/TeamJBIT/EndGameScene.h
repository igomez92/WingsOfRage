#pragma once

#include "IScene.h"
#include "AnimSprite.h"

class EndGameScene : public IScene {
	public:
		EndGameScene();
		~EndGameScene();

		virtual void update(sf::RenderWindow& window);
		virtual void draw(sf::RenderWindow& window);
		virtual bool handleEvent(sf::Event& event);

	private:
		AnimSprite testSprite;

		sf::Text gameOverMessage;
		
		sf::Clock clock;
		sf::Time lastFrameTime;
};