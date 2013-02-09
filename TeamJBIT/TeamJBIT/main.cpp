#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include "VisibleObject.h"
#include <iostream>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(char argc, char* argv[]) {
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Team JBIT SFML Test");
	window.setFramerateLimit(60);

	VisibleObject object("ball.png");
	VisibleObject object2("ball.png");
	object2.setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			object.setPosition(object.getX(), object.getY() + 5);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			object.setPosition(object.getX(), object.getY() - 5);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			object.setPosition(object.getX() - 5, object.getY());
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			object.setPosition(object.getX() + 5, object.getY());
		}

		if(object.getBounds().top + object.getBounds().height > SCREEN_HEIGHT)
		{
			object.setPosition(object.getX(), SCREEN_HEIGHT - object.getBounds().height);
		}
		if(object.getBounds().top < 0)
		{
			object.setPosition(object.getX(), 0.01);
		}
		if(object.getBounds().left + object.getBounds().width > SCREEN_WIDTH)
		{
			object.setPosition(SCREEN_WIDTH - object.getBounds().width, object.getY());
		}
		if(object.getBounds().left < 0)
		{
			object.setPosition(0.01, object.getY());
		}

		window.clear(sf::Color(50, 50, 50));

		window.draw(object.getSprite());

		if(clock.getElapsedTime().asSeconds() >= 2)
		{
			window.draw(object2.getSprite());
		}

		window.display();
    }

	return 0;
}
