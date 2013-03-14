#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>

#include "IScene.h"
#include "SceneManager.h"
#include "SplashScene.h"
#include "GameScene.h"
#include "EndGameScene.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(char argc, char* argv[]) 
{
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "The Wings of Rage");
	window.setFramerateLimit(60);

	//set up scenes
	SceneManager::getInstance().addScene("splash", new SplashScene());
	SceneManager::getInstance().addScene("start", new GameScene());
	SceneManager::getInstance().addScene("end", new EndGameScene());
	SceneManager::getInstance().changeScene("start");

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
