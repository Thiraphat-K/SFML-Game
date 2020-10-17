#pragma once
#include<SFML/Graphics.hpp>
#include"Collider.h"

class ObjColli
{
public:
	ObjColli(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
	~ObjColli();

	void Draw(sf::RenderWindow& window);
	Collider GetCollider() { return Collider(body); }

private:
	sf::RectangleShape body;
};

