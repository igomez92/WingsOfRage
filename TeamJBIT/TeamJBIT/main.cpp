#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>

#include "IScene.h"
#include "GameScene.h"
#include <vector>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(char argc, char* argv[]) 
{
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Team JBIT SFML Test");
	window.setFramerateLimit(60);

	std::vector<IScene*> sceneList;
	IScene* currentScene = nullptr;

	GameScene gameScene = GameScene();
	sceneList.push_back(&gameScene);
	currentScene = &gameScene;


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
			if (currentScene->handleEvent(event)) continue;

            if (event.type == sf::Event::Closed)
                window.close();
        }

		//update
		currentScene->update();

		//draw
		window.clear(sf::Color(50, 50, 50));
		currentScene->draw(window);
	

		window.display();
    }

	return 0;
}
