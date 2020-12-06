#include "hitboxtest.h"

hitboxtest::hitboxtest(float offset_x, float offset_y, Vector2f size, Vector2f compmposition)
{
	hitbox.setSize(size);
	hitbox.setPosition(compmposition.x + offset_x, compmposition.y + offset_y);
	hitbox.setFillColor(Color::Transparent);
	hitbox.setOutlineThickness(1.5f);
	hitbox.setOutlineColor(Color::Red);
}

void hitboxtest::Update(float offset_x, float offset_y, Vector2f compmposition)
{
	hitbox.setPosition(compmposition.x + offset_x, compmposition.y + offset_y);
}

void hitboxtest::Draw(RenderWindow& window)
{
	window.draw(hitbox);
}

const Vector2f& hitboxtest::getPosition() const
{
	return this->hitbox.getPosition();
}

const FloatRect hitboxtest::getGlobalbounds() const
{
	return this->hitbox.getGlobalBounds();
}

bool hitboxtest::intersects(const FloatRect& frect)
{
	return this->hitbox.getGlobalBounds().intersects(frect);
}
