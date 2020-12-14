#include "ObjColli.h"

ObjColli::ObjColli(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);
	PickObj = false;
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

void ObjColli::Update(float deltaTime, Vector2f CompmanPosition)
{
	if (PickObj == false)
	{
		velocity.x = 0.0f;

		velocity.y += 980.0f * deltaTime;

		body.move(velocity * deltaTime);
	}
	else
	{
		body.setPosition(CompmanPosition.x+2.5, CompmanPosition.y-56);
	}
}

void ObjColli::Oncollision(Vector2f direction)
{
	if (direction.x < 0.0f)
	{
		//Collision of the left.
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f)
	{
		//Collision of the right.
		velocity.x = 0.0f;
	}
	if (direction.y < 0.0f)
	{
		//Collision of the bottom.
		velocity.y = 0.0f;
	}
	else if (direction.y > 0.0f)
	{
		velocity.y = 0.0f;
	}
}

bool ObjColli::getPickObj()
{
	return PickObj;
}

void ObjColli::setPickObj(bool Pick)
{
	PickObj = Pick;
}

RectangleShape& ObjColli::getbody()
{
	return body;
}
