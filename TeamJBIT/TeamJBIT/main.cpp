#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>

int main(char argc, char* argv[]) {
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(800, 600), "Team JBIT SFML Test");
	window.setFramerateLimit(60);
	window.clear(sf::Color(50, 50, 50));
	window.display();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

	return 0;
}
