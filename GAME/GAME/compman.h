#ifndef compman_H
#define compman_H

#include"Anyinclude.h"
#include"Animation.h"
#include"Collider.h"
using namespace std;
using namespace sf;


class compman 
{
private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;

	sf::Vector2f velocity;
	bool canJump;
	float jumpHeight;
	bool Hold;

public:
	compman(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight);
	~compman();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void OnCollision(sf::Vector2f direction);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }
	sf::Vector2f GetSize() { return body.getSize(); }
	const FloatRect getGlobalbounds() const;
	bool intersects(const sf::FloatRect& frect);
	const Vector2f& getPosition() const;

	bool getHold();
	void setHold(bool nHold);

	bool getcanJump();
};
#endif

