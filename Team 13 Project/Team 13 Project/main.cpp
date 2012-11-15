#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Character.h"
/*
#include "Commander.h"
#include "Enemy.h"
#include "NPC.h"
#include "Assassin.h"
#include "Soldier.h"
*/
sf::Clock timer;

// Our games "Main" Function
// It loads the window that updates at every frame
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Dystopia");
	window.setVerticalSyncEnabled(true);

	//create player sprite
	Character player;

	//run main loop
	bool running = true;
	while(running)
	{
		//handle events
		sf::Event event;
		while(window.pollEvent(event))
		{
			switch(event.type)
			{
			case sf::Event::Closed:
				//end the program
				running = false;
				break;
			case sf::Event::Resized:
				//adjust viewport when resizing

				break;
			case sf::Event::KeyPressed:
				//do something based on key pressed
				player.doPressedCommand(event.key.code);
				break;
			case sf::Event::KeyReleased:
				//do something based on key released
				player.doReleasedCommand(event.key.code);
				break;
			default:
				break;
			}
		}

		//update objects
		player.move(timer.getElapsedTime());
		timer.restart();

		//clear the frame
		window.clear(sf::Color(0, 255, 255));

		//draw stuff
		window.draw(player.getSprite());

		//end the current frame
		window.display();
	}

	window.close();

	return 0;
}