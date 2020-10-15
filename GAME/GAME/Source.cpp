#include <SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<iostream>
#include"compman.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1500, 700), "Box Way", sf::Style::Close | sf::Style::Resize);
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
	
		
		window.clear();
		//window.draw(wall2);
		Compman.Update(deltaTime);
		Compman.Draw(window);
		//window.draw(boxwaybox);
		window.display();
	}

	return 0;
}