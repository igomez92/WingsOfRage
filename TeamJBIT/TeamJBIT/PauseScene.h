#pragma once

#include <SFML\Graphics.hpp>
#include "IScene.h"
#include "dbtweener.h"
#include "Button.h"

class PauseScene : public IScene {
	public:
		PauseScene();
		virtual void enter();
		virtual void leave();
		virtual void update(sf::RenderWindow& window);
		virtual void draw(sf::RenderWindow& window);
		virtual bool handleEvent(sf::Event& event);

	private:
		sf::Texture backgroundTexture;
		bool bgTextureUpdated;
		sf::Sprite backgroundSprite;

		sf::RectangleShape blackScreen;

		sf::Text pauseLabel;

		TextButton buttons [3];

		CDBTweener fadeTweener;
		
		sf::Clock clock;
		sf::Time lastFrameTime;
};
