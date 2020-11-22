//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include "Menu.h"
//#include"Anyinclude.h"
//#include"compman.h"
//#include"Collider.h"
//#include"ObjColli.h"
//#include"hitboxtest.h"
//#include"TextFont.h"
//#include"Menu.h"
//using namespace std;
//
//
//static const float VIEW_HEIGHT = 900.0f;
//static const float boxes = 512.0f;
//
//
//void ResizeView(const sf::RenderWindow& window, sf::View& view)
//{
//	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
//	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
//}
//
//
//int main()
//{
//	sf::RenderWindow window(sf::VideoMode(1000, 900), "Menu Test");
//
//	Menu menu(window.getSize().x, window.getSize().y);
//	//init state
//	bool checkGameOpen = false;
//	int Gamestate;
//	while (window.isOpen())
//	{
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			switch (event.type)
//			{
//			case sf::Event::KeyReleased:
//				switch (event.key.code)
//				{
//				case sf::Keyboard::Up:
//					menu.Moveup();
//					break;
//				case sf::Keyboard::Down:
//					menu.Movedown();
//					break;
//				case sf::Keyboard::Return:
//					switch (menu.GetPressedItem())
//					{
//					case 0:
//						cout << "Start has been pressed" << endl;
//						//go to state
//						Gamestate = 1;
//						checkGameOpen = true;
//						break;
//					case 1:
//						cout << "HighScore has been pressed" << endl;
//						//go to state
//						break;
//					case 2:
//						cout << "Guide has been pressed" << endl;
//						//go to state
//						break;
//					case 3:
//						window.close();
//						break;
//					}
//					break;
//				}
//				break;
//			case sf::Event::Closed:
//				window.close();
//				break;
//			}
//		}
//		window.clear();
//		menu.draw(window);
//		window.display();
//		if (checkGameOpen == true)
//			break;
//	}
//
//	while (true)
//	{
//		if (Gamestate == 1)
//		{
//			sf::View view(sf::Vector2f(1.0f, 1.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
//
//
//			//***Player**//
//			sf::Texture CompmanTexture;
//			CompmanTexture.loadFromFile("Object/compmanA1.png");
//			compman Compman(&CompmanTexture, sf::Vector2u(8, 4), 0.2f, 400.0f, 200.0f);
//
//			//***Background**//
//			sf::Texture Bg;
//			Bg.loadFromFile("Object/grid.png");
//			sf::Sprite bg(Bg);
//			bg.setScale(1.2, 1.2);
//			bg.setPosition(2048.f, -55.f);
//
//			//***BoxStage**//
//			sf::Texture box;
//			box.loadFromFile("Object/box.png");
//			std::vector<ObjColli>Objs1;
//			Objs1.push_back(ObjColli(&box, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f, 1000.0f)));
//			Objs1.push_back(ObjColli(&box, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes, 1000.0f)));
//			Objs1.push_back(ObjColli(&box, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 2, 1000.0f)));
//			Objs1.push_back(ObjColli(&box, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 3, 1000.0f)));
//			Objs1.push_back(ObjColli(&box, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 4, 1000.0f)));
//			Objs1.push_back(ObjColli(&box, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 5, 1000.0f)));
//			Objs1.push_back(ObjColli(&box, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 6, 1000.0f)));
//			Objs1.push_back(ObjColli(&box, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 7, 1000.0f)));
//			Objs1.push_back(ObjColli(&box, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 8, 1000.0f)));
//			Objs1.push_back(ObjColli(&box, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 9, 1000.0f)));
//			Objs1.push_back(ObjColli(&box, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 10, 1000.0f)));
//			Objs1.push_back(ObjColli(&box, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 11, 1000.0f)));
//
//			//----box--pick----//
//			sf::Texture box2;
//			std::vector<ObjColli>Objs2, Objs3;
//			Objs2.push_back(ObjColli(&box2, sf::Vector2f(48.0f, 48.0f), sf::Vector2f(750.0f, 648.0f)));
//			Objs3.push_back(ObjColli(&box2, sf::Vector2f(2.0f, 5000.0f), sf::Vector2f(-268.0f, 724.f)));
//			Objs3.push_back(ObjColli(&box2, sf::Vector2f(2.0f, 5000.0f), sf::Vector2f(5890.f, 724.f)));
//
//
//			//----hitboxtest----//
//			hitboxtest hitbox0(0, 0, Vector2f(55, Objs2[0].GetSize().x), Objs2[0].GetPosition());
//			hitboxtest hitbox1(0, 0, Vector2f(50, Compman.GetSize().x), Compman.GetPosition());
//
//			//--Text--//
//			TextFont text1;
//			TextFont text2;
//
//			float deltaTime = 1500.0f;
//			sf::Clock clock;
//			float timeElasped = 0;
//			float GameTime = 10;
//			float PointTime = 100;
//
//			while (window.isOpen())
//			{
//				timeElasped += deltaTime;
//				deltaTime = clock.restart().asSeconds();
//				if (deltaTime > 1.0f / 20.0f)
//					deltaTime = 1.0f / 20.0f;
//				if (GameTime > 0)
//					GameTime -= deltaTime;
//				if (GameTime <= 0)
//					PointTime -= deltaTime;
//				if (PointTime <= 0)
//					PointTime = 0;
//				sf::Event event;
//				while (window.pollEvent(event))
//				{
//					switch (event.type)
//					{
//					case sf::Event::Closed:
//						window.close();
//						break;
//					case sf::Event::Resized:
//						ResizeView(window, view);
//						break;
//					case sf::Event::MouseButtonPressed:
//						cout << "Mouse button has been pressed" << endl;
//						switch (event.key.code)
//						{
//						case sf::Mouse::Left:
//							cout << "LEFT KEY has been pressed" << endl;
//							break;
//						}
//						break;
//					case sf::Event::MouseButtonReleased:
//						cout << "Mouse button has been released" << endl;
//						break;
//					}
//					//cout << "Position x : " << Compman.getPosition().x << "\n" << "Position y : " << Compman.getPosition().y << "\n" << endl;
//
//					if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
//					{
//						window.close();
//					}
//				}
//
//				Compman.Update(deltaTime);
//				sf::Vector2f direction;
//
//				//--Collider Update--//
//				Collider c = Compman.GetCollider();
//				for (ObjColli& Obj : Objs1)
//					if (Obj.GetCollider().CheckCollision(c, direction, 1.0f))
//						Compman.OnCollision(direction);
//				for (ObjColli& Obj : Objs3)
//					if (Obj.GetCollider().CheckCollision(c, direction, 1.0f))
//						Compman.OnCollision(direction);
//
//				//--hitboxtest Update--//
//				hitbox1.Update(-22.0, -37.0, Compman.GetPosition());
//				hitbox0.Update(Objs2[0].GetSize().x, Objs2[0].GetSize().y, Objs2[0].GetPosition());
//
//				view.setCenter(Compman.GetPosition().x, Compman.GetPosition().y);
//				if (view.getCenter().x - 195.0f <= 0.0f)
//				{
//					if (view.getCenter().y - 450.0f <= 0.0f)
//					{
//						view.setCenter(195.f, Compman.GetPosition().y);
//					}
//					if (view.getCenter().y + 450.0f >= 900.0f)
//					{
//						view.setCenter(195.f, Compman.GetPosition().y);
//					}
//					if (view.getCenter().y - 450.0f > 0.0f && view.getCenter().y + 450.0f < 900.0f)
//					{
//						view.setCenter(195.f, Compman.GetPosition().y);
//					}
//				}
//				if (view.getCenter().x + 415.0f >= 5850.f)
//				{
//					if (view.getCenter().y - 450.0f <= 0.0f)
//					{
//						view.setCenter(5435.f, Compman.GetPosition().y);
//					}
//					if (view.getCenter().y + 450.0f >= 900.0f)
//					{
//						view.setCenter(5435.f, Compman.GetPosition().y);
//					}
//					if (view.getCenter().y - 450.0f > 0.0f && view.getCenter().y + 450.0f < 900.0f)
//					{
//						view.setCenter(5435.f, Compman.GetPosition().y);
//					}
//				}
//				//cout << view.getCenter().x << "\t" << view.getCenter().y << endl ;
//
//				/*if (Compman.GetCollider().CheckCollision(Collider &Objs3[3],0,0.f)
//				{
//					state = 2;
//					goto statechange;
//				}*/
//				window.clear(sf::Color(255, 255, 255));
//				//--DrawEverythings--//
//				window.draw(bg);
//				window.setView(view);
//				Compman.Draw(window);
//				for (ObjColli& Obj : Objs1)
//					Obj.Draw(window);
//				for (ObjColli& Obj : Objs3)
//					Obj.Draw(window);
//				hitbox0.Draw(window);
//				hitbox1.Draw(window);
//				text1.drawtext((float)abs(GameTime), (string)"Time : ", (string)" s", sf::Vector2f(view.getCenter().x + (window.getSize().x / 2) - 200, view.getCenter().y - (window.getSize().y / 2) + 20), window, sf::Color(255, 0, 0));
//				text1.drawtext((int)abs(PointTime), (string)"Point : ", (string)"", sf::Vector2f(view.getCenter().x + (window.getSize().x / 2) - 200, view.getCenter().y - (window.getSize().y / 2) + 55), window, sf::Color(255, 150, 0));
//				//window.clear();
//				//menu.draw(window);
//				window.display();
//
//			}
//
//		}
//	}
//	return 0;
//}