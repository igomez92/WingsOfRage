#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>

#include "VisibleObject.h"
#include "Player.h"
#include "Enemy.h"
#include <iostream>
#include <vector>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(char argc, char* argv[]) {
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Team JBIT SFML Test");
	window.setFramerateLimit(60);

	Player p1("ball.png", 0, 0);

	Enemy e0("ball.png", 100, 100);
	Enemy e1("ball.png", 300, 100);
	Enemy e2("ball.png", 500, 100);
	Enemy e3("ball.png", 700, 100);

	std::vector<Enemy> enemyVec;
	enemyVec.push_back(e0);
	enemyVec.push_back(e1);
	enemyVec.push_back(e2);
	enemyVec.push_back(e3);
	sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		window.clear(sf::Color(50, 50, 50));

		p1.update();
		window.draw(p1.getSprite());

	/*	if(clock.getElapsedTime().asSeconds() >= 2)
		{
			e1.update();
			window.draw(e1.getSprite());
		}*/

		for(int i = 0; i < enemyVec.size(); i++)
		{
			int thresholdX = abs(enemyVec.at(i).xPos - p1.xPos);
			int thresholdY = abs(enemyVec.at(i).yPos - p1.yPos);
			if(thresholdX < 22 && thresholdY < 22)
			{
				enemyVec.at(i).continueDraw = false;
			}
			enemyVec.at(i).update();
			window.draw(enemyVec.at(i).getSprite());
		}

		window.display();
    }

	return 0;
}
