//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include"checkbox.h"
//#include <vector>
//
//using namespace sf;
//using namespace std;
//
//
//int main()
//{
//	bool frag = true;
//	int counteiei = 1;
//	sf::RenderWindow window(sf::VideoMode(1080, 720), "CHECK POSITION FROM PLATFORM", sf::Style::Resize | sf::Style::Close);
//	//--Player--//
//	sf::RectangleShape Rshape(sf::Vector2f(40.f, 40.f));
//	Rshape.setFillColor(sf::Color::Magenta);
//	Rshape.setPosition(20, 20);
//	Rshape.setOrigin(Rshape.getSize().x / 2, Rshape.getSize().y / 2);
//	//--checkbox--//
//	vector<checkbox>checkboxs;
//	checkboxs.push_back(checkbox(Rshape.getSize(), sf::Vector2f(rand() % window.getSize().x, rand() % window.getSize().y)));
//
//	//text-position//
//	Vector2f checkp;
//
//	while (window.isOpen())
//	{
//
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				window.close();
//			break;
//		}
//
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) and Rshape.getPosition().x > 0)
//		{
//			Rshape.move(-0.2f, 0.f);
//		}
//
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) and Rshape.getPosition().x < 1080)
//		{
//			Rshape.move(0.2f, 0.f);
//		}
//
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) and Rshape.getPosition().y > 0)
//		{
//			Rshape.move(0.f, -0.2f);
//		}
//
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) and Rshape.getPosition().y < 720)
//		{
//			Rshape.move(0.f, 0.2f);
//		}
//
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
//		{
//			window.close();
//		}
//		for (int i = 0; i < checkboxs.size(); i++)
//		{
//			checkboxs[i].Update(checkboxs[i].getPosition());
//		}
//		for (int i = 0; i < checkboxs.size(); i++)
//		{
//			if (Rshape.getGlobalBounds().intersects(checkboxs[i].getGlobalbounds()))
//			{
//				checkboxs.pop_back();
//				checkboxs.push_back(checkbox(Rshape.getSize(), sf::Vector2f(rand() % window.getSize().x, rand() % window.getSize().y)));
//				checkp = checkboxs[i].getPosition();
//				cout << "Position x : " << checkp.x << "\n" << "Position y : " << checkp.y << "\n" << endl;
//			}
//
//		}
//
//		window.clear();
//		window.draw(Rshape);
//		for (int i = 0; i < checkboxs.size(); i++)
//		{
//			checkboxs[i].Draw(window);
//
//		}
//		window.display();
//	}
//	return 0;
//}