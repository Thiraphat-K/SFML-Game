#include <SFML/Graphics.hpp>
#include<SFML/System.hpp>
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
	sf::Texture CompmanTexture;
	CompmanTexture.loadFromFile("Object/compmanA.png");

	
	//sf::Texture wall;
	//wall.loadFromFile("Wallpaper/wallpapertest03.jpg");
	//sf::Sprite wall2(wall);
	//wall2.setScale(1.7, 1.5);

	/*sf::Texture box;
	box.loadFromFile("Object/boxedit.png");
	sf::Sprite boxwaybox(box);
	sf::Vector2f boxPoint = { 800.f,550.f };*/

	compman Compman(&CompmanTexture, sf::Vector2u(8, 2), 0.2f, 100.0f);

	ObjColli objcolli1(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 200.0f));
	ObjColli objcolli2(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 0.0f));

	float deltaTime = 1500.0f;
	sf::Clock clock;
	
	//boxwaybox.setPosition(boxPoint);

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
			}
		}
		
		Compman.Update(deltaTime);
		objcolli1.GetCollider().CheckCollision(Compman.GetCollider(), 0.9f);
		objcolli2.GetCollider().CheckCollision(Compman.GetCollider(), 1.0f);
		view.setCenter(Compman.GetPosition());
		window.clear(sf::Color(500,500,500));
		//window.draw(wall2);
		window.setView(view);
		Compman.Draw(window);
		objcolli1.Draw(window);
		objcolli2.Draw(window);
		//window.draw(boxwaybox);
		window.display();
	}

	return 0;
}