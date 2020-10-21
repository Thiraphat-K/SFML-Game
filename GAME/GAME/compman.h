#pragma once
#include<SFML/Graphics.hpp>
#include"Animation.h"
#include"Collider.h"

class compman
{
public:
	compman(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	~compman();

	void Update(float deltaTime, sf::Vector2u compmanposition);
	void Draw(sf::RenderWindow& window);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }

private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;
};

