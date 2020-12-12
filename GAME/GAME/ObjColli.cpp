#include "ObjColli.h"

ObjColli::ObjColli(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);
}

ObjColli::~ObjColli()
{
}

void ObjColli::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

const Vector2f& ObjColli::getPosition() const
{
	return this->body.getPosition();
}

const FloatRect ObjColli::getGlobalbounds() const
{
	return this->body.getGlobalBounds();
}

bool ObjColli::intersects(const sf::FloatRect& frect)
{
	return this->body.getGlobalBounds().intersects(frect);
}
