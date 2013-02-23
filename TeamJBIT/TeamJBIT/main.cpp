#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>

#include "IScene.h"
#include "GameScene.h"
#include "EndGameScene.h"
#include "SceneManager.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(char argc, char* argv[]) 
{
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Team JBIT SFML Test");
	window.setFramerateLimit(60);

	IScene* endGameScene = new EndGameScene();
	IScene* gameScene = new GameScene();
	
	SceneManager::getInstance().addScene("start",gameScene);
	SceneManager::getInstance().addScene("end",endGameScene);
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
		SceneManager::getInstance().getCurrentScene()->update();

		//draw
		window.clear(sf::Color(50, 50, 50));
		SceneManager::getInstance().getCurrentScene()->draw(window);
	

		window.display();
    }

	return 0;
}
