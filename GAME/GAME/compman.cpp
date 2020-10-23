#include "compman.h"

compman::compman(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight)
	:animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(75.0f, 75.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(450.f, 800.f);
	body.setTexture(texture);
}

compman::~compman()
{
}

void compman::Update(float deltaTime)
{
	velocity.x = 0.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		velocity.x -= speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		velocity.x += speed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && canJump)
	{
		canJump = false;

		velocity.y = -sqrtf(2.0f * 980.0f * jumpHeight);
	}
	velocity.y += 980.0f * deltaTime;

	if (velocity.x == 0.0f)
	{
		row = 0;
	}
	else
	{
		row = 1;

		if (velocity.x > 0.0f) {
			faceRight = true;
		}
		else {
			faceRight = false;
		}
	}

	animation.Update(row, deltaTime, faceRight);
	
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);

}

void compman::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void compman::OnCollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f)
	{
		//Collision of the left.
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f)
	{
		//Collision of the right.
		velocity.x = 0.0f;
	}
	if (direction.y < 0.0f)
	{
		//Collision of the bottom.
		velocity.y = 0.0f;
		canJump = true;
	}
	else if (direction.y > 0.0f)
	{
		velocity.y = 0.0f;
	}
}
