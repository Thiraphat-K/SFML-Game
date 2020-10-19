#include <SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<cmath>
#include<iostream>
#include"compman.h"
#include"ObjColli.h"

static const float VIEW_HEIGHT = 900.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT );
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(900, 900), "Box Way", sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(1.0f, 1.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
	
	//***Player**//
	sf::Texture CompmanTexture;
	CompmanTexture.loadFromFile("Object/compmanA.png");
	compman Compman(&CompmanTexture, sf::Vector2u(8, 2), 0.2f, 500.0f);

	//***Background**//
	sf::Texture Bg;
	Bg.loadFromFile("Object/FezBg1.jpg");
	sf::Sprite bg(Bg);
	bg.setScale(1.5, 1.5);

	//***Box**//
	sf::Texture box;
	box.loadFromFile("Object/box.png");
	ObjColli box1(&box, sf::Vector2f(64.0f,64.0f), sf::Vector2f (750.0f, 800.0f));

	float deltaTime = 1500.0f;
	sf::Clock clock;
	

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				ResizeView(window, view);
				break;
			case sf::Event::MouseButtonPressed:
				std::cout << "Mouse button has been pressed" << std::endl;
				switch (event.key.code)
				{
				case sf::Mouse::Left:
					std::cout << "LEFT KEY has been pressed" << std::endl;
					break;
				}
				break;
			case sf::Event::MouseButtonReleased:
				std::cout << "Mouse button has been released" << std::endl;
				break;		
			}
		}

		Compman.Update(deltaTime);
		Collider c = Compman.GetCollider();
		box1.GetCollider().CheckCollision(c, 1.0f);
		view.setCenter(Compman.GetPosition());
		window.clear(sf::Color(500,500,500));
		window.draw(bg);
		window.setView(view);
		Compman.Draw(window);
		box1.Draw(window);
		window.display();
	}

	return 0;
}