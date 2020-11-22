#pragma once
#include"Anyinclude.h"
#include"Animation.h"
#include"Collider.h"
using namespace std;
using namespace sf;
class compman
{
public:
	compman(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight);
	~compman();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void OnCollision(sf::Vector2f direction);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }
	sf::Vector2f GetSize() { return body.getSize(); }

	const Vector2f& getPosition() const;

private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;

	sf::Vector2f velocity;
	bool canJump;
	float jumpHeight;
};

