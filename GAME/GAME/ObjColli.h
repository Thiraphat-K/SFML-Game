#pragma once
#include"Anyinclude.h"
#include"Collider.h"
using namespace sf;

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
	const Vector2f& getPosition() const;
	const FloatRect getGlobalbounds() const;
	bool intersects(const sf::FloatRect& frect);
	void Update(float deltaTime, Vector2f CompmanPosition);
	void Oncollision(Vector2f direction);
	bool getPickObj();
	void setPickObj(bool Pick);
	RectangleShape& getbody();

private:
	sf::RectangleShape body;
	sf::Vector2f velocity;
	bool PickObj;
};

