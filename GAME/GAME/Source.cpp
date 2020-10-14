#include <SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<iostream>
#include"Animation.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1500, 700), "Box Way");
	//sf::Texture wall;
	//wall.loadFromFile("Wallpaper/wallpapertest03.jpg");
	//sf::Sprite wall2(wall);
	//wall2.setScale(1.7, 1.5);


	sf::Texture purpleman;
	purpleman.loadFromFile("Object/compman.png");
	sf::Sprite boxwayman(purpleman);
	/*int ppmanX = purpleman.getSize().x / 12;
	int ppmanY = purpleman.getSize().y / 15;
	boxwayman.setTextureRect(sf::IntRect(ppmanX * 0, ppmanY * 0, ppmanX, ppmanY));*/
	sf::Vector2f spawnPoint = { 750.f,550.f };

	sf::Texture box;
	box.loadFromFile("Object/boxedit.png");
	sf::Sprite boxwaybox(box);
	sf::Vector2f boxPoint = { 800.f,550.f };

	Animation animation(&purpleman, sf::Vector2u(9, 1), 0.3f);

	float deltaTime = 1500.0f;
	sf::Clock clock;
	
	
	boxwayman.setPosition(spawnPoint);
	boxwaybox.setPosition(boxPoint);

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
		/*boxwayman.setTextureRect(sf::IntRect(ppmanX * 0, ppmanY * 0, ppmanX, ppmanY));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			boxwayman.move(0.1f, 0.0f);
			boxwayman.setTextureRect(sf::IntRect(ppmanX * 0, ppmanY * 0, ppmanX, ppmanY));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			boxwayman.move(-0.1f, 0.f);
			boxwayman.setTextureRect(sf::IntRect(ppmanX * 0, ppmanY * 0, ppmanX, ppmanY));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			boxwayman.move(0.f, -0.1f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			boxwayman.move(0.f, 0.1f);
		}*/
	
		animation.Update(0, deltaTime);
		boxwayman.setTextureRect(animation.uvRect);
		window.clear();
		//window.draw(wall2);
		window.draw(boxwayman);
		window.draw(boxwaybox);
		window.display();
	}

	return 0;
}