#pragma once
#include<SFML/Graphics.hpp>
#include"Animation.h"
class compman
{
public:
	compman(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	~compman();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;
};

