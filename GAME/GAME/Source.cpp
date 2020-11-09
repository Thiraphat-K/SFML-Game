#include <SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<cmath>
#include<iostream>
#include<vector>
#include"compman.h"
#include"Collider.h"
#include"ObjColli.h"
#include"hitboxtest.h"

static const float VIEW_HEIGHT = 900.0f;
static const float boxes = 512.0f;
using namespace std;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 900), "Box Way", sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(1.0f, 1.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));

	//***Player**//
	sf::Texture CompmanTexture;
	CompmanTexture.loadFromFile("Object/compmanA1.png");
	compman Compman(&CompmanTexture, sf::Vector2u(8, 4), 0.2f, 400.0f, 200.0f);

	//***Background**//
	/*sf::Texture Bg;
	Bg.loadFromFile("Object/FezBg1.jpg");
	sf::Sprite bg(Bg);
	bg.setScale(1.5, 1.5);*/

	//***BoxStage**//
	sf::Texture box;
	box.loadFromFile("Object/box.png");
	std::vector<ObjColli>Objs1;
	Objs1.push_back(ObjColli(&box, sf::Vector2f(boxes, boxes), sf::Vector2f(400.0f, 1000.0f)));
	Objs1.push_back(ObjColli(&box, sf::Vector2f(boxes, boxes), sf::Vector2f(400.0f + boxes, 1000.0f)));
	Objs1.push_back(ObjColli(&box, sf::Vector2f(boxes, boxes), sf::Vector2f(400.0f + boxes * 2, 1000.0f)));
	Objs1.push_back(ObjColli(&box, sf::Vector2f(boxes, boxes), sf::Vector2f(400.0f + boxes * 3, 1000.0f)));
	Objs1.push_back(ObjColli(&box, sf::Vector2f(boxes, boxes), sf::Vector2f(400.0f + boxes * 4, 1000.0f)));
	Objs1.push_back(ObjColli(&box, sf::Vector2f(boxes, boxes), sf::Vector2f(400.0f + boxes * 5, 1000.0f)));
	Objs1.push_back(ObjColli(&box, sf::Vector2f(boxes, boxes), sf::Vector2f(400.0f + boxes * 6, 1000.0f)));
	Objs1.push_back(ObjColli(&box, sf::Vector2f(boxes, boxes), sf::Vector2f(400.0f + boxes * 7, 1000.0f)));
	Objs1.push_back(ObjColli(&box, sf::Vector2f(boxes, boxes), sf::Vector2f(400.0f + boxes * 8, 1000.0f)));
	Objs1.push_back(ObjColli(&box, sf::Vector2f(boxes, boxes), sf::Vector2f(400.0f + boxes * 9, 1000.0f)));
	Objs1.push_back(ObjColli(&box, sf::Vector2f(boxes, boxes), sf::Vector2f(400.0f + boxes * 10, 1000.0f)));
	Objs1.push_back(ObjColli(&box, sf::Vector2f(boxes, boxes), sf::Vector2f(400.0f + boxes * 11, 1000.0f)));
	//ObjColli box1(&box, sf::Vector2f(64.0f,64.0f), sf::Vector2f (750.0f, 800.0f));

	//----box--pick----//
	sf::Texture box2;
	//box2.loadFromFile("Object/box2.png");
	std::vector<ObjColli>Objs2;
	Objs2.push_back(ObjColli(&box2, sf::Vector2f(48.0f, 48.0f), sf::Vector2f(750.0f, 648.0f)));


	//----hitboxtest----//
	hitboxtest hitbox0(0, 0, Vector2f(55, Objs2[0].GetSize().x), Objs2[0].GetPosition());
	hitboxtest hitbox1(0, 0, Vector2f(55, Compman.GetSize().x), Compman.GetPosition());

	float deltaTime = 1500.0f;
	sf::Clock clock;
	float timeElasped = 0;

	while (window.isOpen())
	{
		timeElasped += deltaTime;
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.0f)
			deltaTime = 1.0f / 20.0f;
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
			cout << "Position x : " << Compman.getPosition().x << "\n" << "Position y : " << Compman.getPosition().y << "\n" << endl;
		}

		Compman.Update(deltaTime);
		sf::Vector2f direction;

		//--Collider Update--//
		Collider c = Compman.GetCollider();
		for (ObjColli& Obj : Objs1)
			if (Obj.GetCollider().CheckCollision(c, direction, 1.0f))
				Compman.OnCollision(direction);
		/*for (ObjColli& Obj : Objs2)
			if (Obj.GetCollider().CheckCollision(c, direction, 1.0f))
				Compman.OnCollision(direction);*/

				//--hitboxtest Update--//
		hitbox1.Update(-23.0, -34.0, Compman.GetPosition());
		hitbox0.Update(Objs2[0].GetSize().x, Objs2[0].GetSize().y, Objs2[0].GetPosition());

		//box1.GetCollider().CheckCollision(c, 1.0f);
		view.setCenter(Compman.GetPosition().x, Compman.GetPosition().y);
		/*if (view.getCenter().x - 450.0f <= 0.0f)
		{
			if (view.getCenter().y - 450.0f <= 0.0f)
			{
				view.setCenter(450.0f, 450.0f);
			}
			if (view.getCenter().y + 450.0f >= 3130.14f)
			{
				view.setCenter(450.0f, 2680.14f);
			}
			if (view.getCenter().y - 450.0f > 0.0f && view.getCenter().y + 450.0f < 2680.14f)
			{
				view.setCenter(450.0f, Compman.GetPosition().y);
			}
		}
		if (view.getCenter().x + 450.0f >= 2680.14f)
		{
			if (view.getCenter().y - 450.0f <= 0.0f)
			{
				view.setCenter(900.0f, 450.0f);
			}
			if (view.getCenter().y + 450.0f >= 900.0f)
			{
				view.setCenter(900.0f, 900.0f);
			}
			if (view.getCenter().y - 450.0f > 0.0f && view.getCenter().y + 450.0f < 900.0f)
			{
				view.setCenter(900.0f, Compman.GetPosition().y);
			}
		}*/

			window.clear(sf::Color(500, 500, 500));

		//--DrawEverythings--//
		//window.draw(bg);
		window.setView(view);
		Compman.Draw(window);
		for (ObjColli& Obj : Objs1)
			Obj.Draw(window);
		/*for (ObjColli& Obj : Objs2)
			Obj.Draw(window);*/
		hitbox0.Draw(window);
		hitbox1.Draw(window);
		//box1.Draw(window);
		window.display();
	}

	return 0;
}