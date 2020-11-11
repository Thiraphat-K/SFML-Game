#include "compman.h"



compman::compman(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight)
	:animation(texture, imageCount, switchTime), canJump(0)
{
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	row = 0;
	faceRight = true;
	body.setSize(sf::Vector2f(75.0f, 75.0f));
	body.setOrigin(body.getSize() / 2.2f);
	body.setPosition(200.14f, 706.5f);
	//body.setPosition(3130.14f, 706.5f);
	body.setTexture(texture);
}

compman::~compman()
{
}

void compman::Update(float deltaTime)
{

	velocity.x = 0.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x -= speed;
		faceRight = false;
	}
		
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x += speed;
		faceRight = true;
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && canJump)
	{
		canJump = false;

		velocity.y = -sqrtf(2.0f * 980.0f * jumpHeight);
		//std::cout << "JUMP !!!" << std::endl;
	}
	velocity.y += 980.0f * deltaTime;
	//std::cout << velocity.y << std::endl;

	if (!canJump)
	{
		if (velocity.y < 0)
		{
			row = 2;
		}
		if (velocity.y > 0)
		{
			row = 3;
		}
	}
	
	else
	{
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

const Vector2f& compman::getPosition() const
{
	return this->body.getPosition();
}
