#include "Particle.h"
#include "TextureManager.h"

Particle::Particle(std::string file, sf::Vector2f pos, sf::Vector2f vel, sf::Color particleColor, float lifeExpectancy)
	:startingPosition(pos), pos(pos), vel(vel), lifeExpectancy(lifeExpectancy), particleColor(particleColor)
{
	sf::Texture* image = _GETTEXTURE(file);
	image->setSmooth(true);
	sprite.setTexture(*image);
	sprite.setColor(particleColor);
	sprite.setPosition(pos);
	sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
}

Particle::~Particle()
{

}

void Particle::update(float deltaTime)
{
	pos += vel * deltaTime;
	sprite.setColor(sf::Color::Color(particleColor.r, particleColor.g, particleColor.b, particleColor.a -= 50));
	sprite.setPosition(pos);
}

void Particle::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

sf::Vector2f Particle::getPosition()
{
	return pos;
}

sf::Vector2f Particle::startPos()
{
	return startingPosition;
}