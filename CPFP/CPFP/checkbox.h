#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;

class checkbox
{
public:
	checkbox(sf::Vector2f size, sf::Vector2f Rsposition);
	~checkbox();
	RectangleShape checkboxtest;
	void Update(Vector2f Rsposition);
	void Draw(RenderWindow& window);
	const Vector2f& getPosition() const;
	const FloatRect getGlobalbounds() const;
	bool intersects(const FloatRect& frect);
};

