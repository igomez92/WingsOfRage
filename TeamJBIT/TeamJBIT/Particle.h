#pragma once

#include <SFML/Graphics.hpp>

class Particle
{
	public:
		Particle(std::string file, sf::Vector2f pos, sf::Vector2f vel, sf::Color color, float lifeExpectancy);
		~Particle();
		void draw(sf::RenderWindow& window);
		void update(float deltaTime);
		sf::Vector2f pos;
		sf::Vector2f vel;
		sf::Vector2f startingPosition;
		sf::Vector2f getPosition();
		sf::Vector2f startPos();
		float lifeExpectancy;
		sf::Color particleColor;

	private:
		sf::Sprite sprite;

};