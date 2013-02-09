#include "VisibleObject.h"


VisibleObject::VisibleObject(std::string file)
	:filename(file)
{
	image.loadFromFile(file);
	sprite.setTexture(image);
}


VisibleObject::~VisibleObject(void)
{
}

void VisibleObject::setPosition(int x, int y)
{
	sprite.setPosition(sf::Vector2f(x, y));
}

int VisibleObject::getX()
{
	return sprite.getPosition().x;
}
int VisibleObject::getY()
{
	return sprite.getPosition().y;
}

sf::Sprite VisibleObject::getSprite()
{
	return sprite;
}

sf::Rect<float> VisibleObject::getBounds() const
{
	return sprite.getGlobalBounds();
}