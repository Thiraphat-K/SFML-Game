#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include"Collider.h"

class ObjColli
{
public:
	ObjColli(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
	~ObjColli();

	void Draw(sf::RenderWindow& window);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	sf::FloatRect GetGlobalbound() { return body.getGlobalBounds(); }
	Collider GetCollider() { return Collider(body); }
	sf::Vector2f GetSize() { return body.getSize(); }

private:
	sf::RectangleShape body;
};

