#pragma once
#include"ObjColli.h"
using namespace sf;

class hitboxtest
{
public:
	RectangleShape hitbox;
	hitboxtest(float offset_x, float offset_y, Vector2f size, Vector2f compmposition);

	void Update(float offset_x, float offset_y, Vector2f compmposition);
	void Draw(RenderWindow& window);
	const Vector2f& getPosition() const;
	const FloatRect getGlobalbounds() const;
	bool intersects(const FloatRect& frect);
};

