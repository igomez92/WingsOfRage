#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>

#include "IScene.h"
#include "SceneManager.h"
#include "SplashScene.h"
#include "MenuScene.h"
#include "CreditsScene.h"
#include "GameScene.h"
#include "EndGameScene.h"
#include "PauseScene.h"
#include "WinScene.h"
#include "Utility.h"

int main(char argc, char* argv[]) 
{
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "The Wings of Rage");
	
	// Fullscreen Mode
	//sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "The Wings of Rage", sf::Style::Fullscreen);
	window.setFramerateLimit(60);

	//set up scenes
	SceneManager::getInstance().addScene("splash", new SplashScene());
	SceneManager::getInstance().addScene("menu", new MenuScene());
	SceneManager::getInstance().addScene("credits", new CreditsScene());
	SceneManager::getInstance().addScene("pause", new PauseScene());
	SceneManager::getInstance().addScene("end", new EndGameScene());

	SceneManager::getInstance().addScene("win", new WinScene());

	SceneManager::getInstance().changeScene("splash");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
			if (SceneManager::getInstance().getCurrentScene()->handleEvent(event)) continue;

            if (event.type == sf::Event::Closed)
                window.close();
        }

		//update
		SceneManager::getInstance().getCurrentScene()->update(window);

		//draw
		window.clear(sf::Color(50, 50, 50));
		SceneManager::getInstance().getCurrentScene()->draw(window);	

		window.display();
    }

	return 0;
}
