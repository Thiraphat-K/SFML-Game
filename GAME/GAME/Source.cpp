#include"Anyinclude.h"
#include"compman.h"
#include"Collider.h"
#include"ObjColli.h"
#include"hitboxtest.h"
#include"TextFont.h"
#include"Menu.h"
#include"PauseMenu.h"

static const float VIEW_HEIGHT = 900.0f;
static const float boxes = 512.0f;
using namespace std;
float max_spacebartimer = 500;
float spacebartimer = 0;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 900), "Box Way", sf::Style::Close /*| sf::Style::Resize*/);
	Menu menu(window.getSize().x, window.getSize().y);

	sf::Texture MNp;
	MNp.loadFromFile("Object/Menu/MenuP.png");

	sf::Music stage1;
	sf::Music menums;
	menums.openFromFile("Object/Menu/menusound.wav");
	menums.setVolume(50);
	menums.setLoop(true);
	menums.play();

	sf::Sprite BGmn;
	BGmn.setTexture(MNp);

	TextFont SDid;
	TextFont NameT;

	//init state
	bool checkColli = false;
	bool checkGameOpen = false;
	bool p_Menu = false;
	int Game_State = 0;
	int P_State = 0;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					if (menu.selectedItem >= 0)
					{
						menu.Moveup();
						break;

					}
				case sf::Keyboard::Down:
					if (menu.selectedItem < Max_Items)
					{
						menu.Movedown();
						break;
					}


				case sf::Keyboard::Return:
					switch (menu.GetPressedItem())
					{
					case 0:
						cout << "Start has been pressed" << endl;
						//go to state
						menums.stop();
						Game_State = 1;
						checkGameOpen = true;
						break;
					case 1:
						cout << "Guide has been pressed" << endl;
						//go to state
						break;
					case 2:
						cout << "HighScore has been pressed" << endl;
						//go to state
						break;
					case 3:
						window.close();
						menums.stop();
						break;
					}
					break;
				}
				break;
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
		window.clear();
		window.draw(BGmn);
		menu.draw(window);
		SDid.drawtext(63010467, (string)"", (string)"  THIRAPHAT KETSINGNOI", sf::Vector2f(610, 865), window, sf::Color(0, 120, 255));
		window.display();
		if (checkGameOpen == true)
			break;
	}

	//-----------------Loop Game Stage------------------//

		//--Stage 1--//
	if (Game_State == 1)
	{
		sf::View view(sf::Vector2f(1.0f, 1.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));

		stage1.openFromFile("Object/stage1.wav");
		stage1.setVolume(50);
		stage1.setLoop(true);
		stage1.play();

		sf::Texture Holl;
		Holl.loadFromFile("Object/Holl.png");
		sf::Sprite hell(Holl);
		hell.setScale(1.2, 1.2);
		hell.setPosition(5000.0f, 675.0f);

		//***Player**//
		sf::Texture CompmanTexture;
		CompmanTexture.loadFromFile("Object/compmanA1.png");
		compman Compman(&CompmanTexture, sf::Vector2u(8, 4), 0.2f, 350.0f, 200.0f);

		//***BoxStage**//
		sf::Texture box;
		box.loadFromFile("Object/box.png");
		std::vector<ObjColli>Objs1;
		Objs1.push_back(ObjColli(&box, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f, 1000.0f)));
		Objs1.push_back(ObjColli(&box, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes, 1000.0f)));
		Objs1.push_back(ObjColli(&box, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 2, 1000.0f)));
		Objs1.push_back(ObjColli(&box, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 3, 1000.0f)));
		Objs1.push_back(ObjColli(&box, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 4, 1000.0f)));
		Objs1.push_back(ObjColli(&box, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 5, 1000.0f)));
		Objs1.push_back(ObjColli(&box, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 6, 1000.0f)));
		Objs1.push_back(ObjColli(&box, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 7, 1000.0f)));
		Objs1.push_back(ObjColli(&box, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 8, 1000.0f)));
		Objs1.push_back(ObjColli(&box, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 9, 1000.0f)));
		Objs1.push_back(ObjColli(&box, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 10, 1000.0f)));
		Objs1.push_back(ObjColli(&box, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 11, 1000.0f)));

		//----box--pick----//
		sf::Texture box2;
		box2.loadFromFile("Object/box2.png");
		std::vector<ObjColli>Objs2;
		for (size_t i = 0;i <= 20;i++)
		{
			Objs2.push_back(ObjColli(&box2, sf::Vector2f(54.0f, 54.0f), sf::Vector2f(rand() % (4500 - 1500) + 1500, 400.0f)));
		}

		//---Limit Stage---//
		sf::Texture box3;
		std::vector<ObjColli>Objs3;
		Objs3.push_back(ObjColli(&box3, sf::Vector2f(2.0f, 5000.0f), sf::Vector2f(-268.0f, 724.f)));
		Objs3.push_back(ObjColli(&box3, sf::Vector2f(2.0f, 5000.0f), sf::Vector2f(5890.f, 724.f)));


		//----hitboxtest----//
		hitboxtest hitbox0(0, 0, Vector2f(54, Objs2[0].GetSize().x), Objs2[0].GetPosition());
		hitboxtest hitbox1(0, 0, Vector2f(50, Compman.GetSize().x), Compman.GetPosition());


		//--Text--//
		TextFont text1;
		TextFont text2;

		float deltaTime = 1500.0f;
		sf::Clock clock;
		float timeElasped = 0;
		float GameTime = 0;
		float PointTime = 100;

		while (window.isOpen())
		{
			timeElasped += deltaTime;
			deltaTime = clock.restart().asSeconds();
			if (deltaTime > 1.0f / 20.0f)
				deltaTime = 1.0f / 20.0f;
			/*if (GameTime > 0)*/
			GameTime += deltaTime;
			/*if (GameTime <= 0)*/
				/*PointTime -= deltaTime;*/
			/*if (PointTime <= 0)
				PointTime = 0;*/
			sf::Event event;
			if (window.pollEvent(event))
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
					cout << "Mouse button has been pressed" << endl;
					switch (event.key.code)
					{
					case sf::Mouse::Left:
						cout << "LEFT KEY has been pressed" << endl;
						break;
					}
					break;
				case sf::Event::MouseButtonReleased:
					cout << "Mouse button has been released" << endl;
					break;
				}
				//cout << "Position x : " << Compman.getPosition().x << "\n" << "Position y : " << Compman.getPosition().y << "\n" << endl;
				sf::Vector2f Posi = Compman.getPosition();

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					window.close();
					stage1.stop();
				}
			}

			spacebartimer += 1;
			Compman.Update(deltaTime);
			sf::Vector2f direction;
			//--Collider_Update--//
			Collider c = Compman.GetCollider();
			for (ObjColli& Obj : Objs1)
			{
				Collider O = Obj.GetCollider();
				if (Obj.GetCollider().CheckCollision(c, direction, 1.0f))
				{
					Compman.OnCollision(direction);
				}
				for (ObjColli& Obj2 : Objs2)
				{
					if (Obj2.GetCollider().CheckCollision(O, direction, 0.0f))
					{
						Obj2.Oncollision(direction);
					}
				}
			}
			//---Hold_Obj---//
			for (int i = 0;i < Objs2.size();i++)
			{
				Objs2[i].Update(deltaTime, Compman.getPosition());
				if (Objs2[i].GetCollider().CheckCollision(c, direction, 0.0f))
				{
					if (Objs2[i].getPickObj() == false)
					{
						Compman.OnCollision(direction);
						//cout << "Collision" << endl;
					}
					if ((Keyboard::isKeyPressed(Keyboard::Space)) && spacebartimer >= max_spacebartimer && Compman.getHold() == false && Objs2[i].getPickObj() == false && Compman.getPosition().y >= Objs2[i].getbody().getPosition().y - 20 && Compman.getPosition().y <= Objs2[i].getbody().getPosition().y + 20) {
						spacebartimer = 0;
						Objs2[i].setPickObj(true);
						Compman.setHold(true);
					}
					if (Objs2[i].getPickObj() == true && (Keyboard::isKeyPressed(Keyboard::Space)) && spacebartimer >= max_spacebartimer && Compman.getcanJump() == false)
					{
						spacebartimer = 0;
						Objs2[i].getbody().setPosition(Compman.getPosition().x, Compman.getPosition().y + 60);
						Compman.setHold(false);
						Objs2[i].setPickObj(false);
					}
				}
				Collider o = Objs2[i].GetCollider();
				for (int j = 0; j < Objs2.size();j++)
				{
					if (i != j)
					{
						if (Objs2[j].GetCollider().CheckCollision(o, direction, 0.0f))
						{
							Objs2[i].Oncollision(direction);
						}
					}
				}
			}
			for (ObjColli& Obj : Objs3)
			{
				if (Obj.GetCollider().CheckCollision(c, direction, 1.0f))
					Compman.OnCollision(direction);
			}

			//--hitboxtest_Update--//
			hitbox1.Update(-21.5, -35.5, Compman.GetPosition());
			hitbox0.Update(-27, -27, Objs2[0].GetPosition());

			//----------Set_View----------//
			view.setCenter(Compman.GetPosition().x, Compman.GetPosition().y);
			if (view.getCenter().x - 195.0f <= 0.0f)
			{
				if (view.getCenter().y - 450.0f <= 0.0f)
				{
					view.setCenter(195.f, Compman.GetPosition().y);
				}
				if (view.getCenter().y + 450.0f >= 900.0f)
				{
					view.setCenter(195.f, Compman.GetPosition().y);
				}
				if (view.getCenter().y - 450.0f > 0.0f && view.getCenter().y + 450.0f < 900.0f)
				{
					view.setCenter(195.f, Compman.GetPosition().y);
				}
			}
			if (view.getCenter().x + 415.0f >= 5850.f)
			{
				if (view.getCenter().y - 450.0f <= 0.0f)
				{
					view.setCenter(5435.f, Compman.GetPosition().y);
				}
				if (view.getCenter().y + 450.0f >= 900.0f)
				{
					view.setCenter(5435.f, Compman.GetPosition().y);
				}
				if (view.getCenter().y - 450.0f > 0.0f && view.getCenter().y + 450.0f < 900.0f)
				{
					view.setCenter(5435.f, Compman.GetPosition().y);
				}
			}
			//cout << view.getCenter().x << "\t" << view.getCenter().y << endl ;

			window.clear(sf::Color(255, 255, 255));
			window.setView(view);
			Compman.Draw(window);
			for (ObjColli& Obj : Objs1)
				Obj.Draw(window);
			for (ObjColli& Obj : Objs2)
				Obj.Draw(window);
			for (ObjColli& Obj : Objs3)
				Obj.Draw(window);
			/*hitbox0.Draw(window);
			hitbox1.Draw(window);*/
			text1.drawtext((float)abs(GameTime), (string)"Time : ", (string)" s", sf::Vector2f(view.getCenter().x + (window.getSize().x / 2) - 200, view.getCenter().y - (window.getSize().y / 2) + 20), window, sf::Color(255, 0, 0));
			text2.drawtext((int)abs(PointTime), (string)"Point : ", (string)"", sf::Vector2f(view.getCenter().x + (window.getSize().x / 2) - 200, view.getCenter().y - (window.getSize().y / 2) + 55), window, sf::Color(255, 150, 0));
			window.draw(hell);
			window.display();
		}

	}


	//--Stage 2--//
	if (Game_State == 2)
	{
		sf::View view(sf::Vector2f(1.0f, 1.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));

		sf::Music stage2;
		stage2.openFromFile("Object/stage2.wav");
		stage2.setVolume(50);
		stage2.setLoop(true);
		stage2.play();

		//***BoxStage**//
		sf::Texture box21;
		box21.loadFromFile("Object/box2.png");
		std::vector<ObjColli>Objs21;
		Objs21.push_back(ObjColli(&box21, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f, 1000.0f)));
		Objs21.push_back(ObjColli(&box21, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes, 1000.0f)));
		Objs21.push_back(ObjColli(&box21, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 2, 1000.0f)));
		Objs21.push_back(ObjColli(&box21, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 3, 1000.0f)));
		Objs21.push_back(ObjColli(&box21, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 4, 1000.0f)));
		Objs21.push_back(ObjColli(&box21, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 5, 1000.0f)));
		Objs21.push_back(ObjColli(&box21, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 6, 1000.0f)));
		Objs21.push_back(ObjColli(&box21, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 7, 1000.0f)));
		Objs21.push_back(ObjColli(&box21, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 8, 1000.0f)));
		Objs21.push_back(ObjColli(&box21, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 9, 1000.0f)));
		Objs21.push_back(ObjColli(&box21, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 10, 1000.0f)));
		Objs21.push_back(ObjColli(&box21, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 11, 1000.0f)));

		//---Limit Stage---//
		sf::Texture box32;
		box32.loadFromFile("Object/box3.png");
		std::vector<ObjColli>Objs32;
		for (size_t i = 0;i <= 30;i++)
		{
			Objs32.push_back(ObjColli(&box32, sf::Vector2f(54.0f, 54.0f), sf::Vector2f(rand() % (4500 - 1500) + 1500, 400.0f)));
		}

		float deltaTime = 1500.0f;
		sf::Clock clock;
		float timeElasped = 0;
		float GameTime = 10;
		float PointTime = 100;

		while (window.isOpen())
		{
			timeElasped += deltaTime;
			deltaTime = clock.restart().asSeconds();
			if (deltaTime > 1.0f / 20.0f)
				deltaTime = 1.0f / 20.0f;
			if (GameTime > 0)
				GameTime -= deltaTime;
			if (GameTime <= 0)
				PointTime -= deltaTime;
			if (PointTime <= 0)
				PointTime = 0;
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
					cout << "Mouse button has been pressed" << endl;
					switch (event.key.code)
					{
					case sf::Mouse::Left:
						cout << "LEFT KEY has been pressed" << endl;
						break;
					}
					break;
				case sf::Event::MouseButtonReleased:
					cout << "Mouse button has been released" << endl;
					break;
				}
				//cout << "Position x : " << Compman.getPosition().x << "\n" << "Position y : " << Compman.getPosition().y << "\n" << endl;

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
				{
					window.close();
				}
			}
			sf::Vector2f direction;

			//--Collider Update--//
			//Collider c = Compman.GetCollider();
			//for (ObjColli& Obj : Objs1)
			//	if (Obj.GetCollider().CheckCollision(c, direction, 1.0f))
			//		Compman.OnCollision(direction);
			//for (ObjColli& Obj : Objs3)
			//	if (Obj.GetCollider().CheckCollision(c, direction, 1.0f))
			//		Compman.OnCollision(direction);
			////----------Set_View----------//
			//view.setCenter(Compman.GetPosition().x, Compman.GetPosition().y);
			//if (view.getCenter().x - 195.0f <= 0.0f)
			//{
			//	if (view.getCenter().y - 450.0f <= 0.0f)
			//	{
			//		view.setCenter(195.f, Compman.GetPosition().y);
			//	}
			//	if (view.getCenter().y + 450.0f >= 900.0f)
			//	{
			//		view.setCenter(195.f, Compman.GetPosition().y);
			//	}
			//	if (view.getCenter().y - 450.0f > 0.0f && view.getCenter().y + 450.0f < 900.0f)
			//	{
			//		view.setCenter(195.f, Compman.GetPosition().y);
			//	}
			//}
			//if (view.getCenter().x + 415.0f >= 5850.f)
			//{
			//	if (view.getCenter().y - 450.0f <= 0.0f)
			//	{
			//		view.setCenter(5435.f, Compman.GetPosition().y);
			//	}
			//	if (view.getCenter().y + 450.0f >= 900.0f)
			//	{
			//		view.setCenter(5435.f, Compman.GetPosition().y);
			//	}
			//	if (view.getCenter().y - 450.0f > 0.0f && view.getCenter().y + 450.0f < 900.0f)
			//	{
			//		view.setCenter(5435.f, Compman.GetPosition().y);
			//	}
			//}
			//cout << view.getCenter().x << "\t" << view.getCenter().y << endl ;

			window.clear(sf::Color(255, 255, 255));
			//--DrawEverythings--//
			window.setView(view);
			//Compman.Draw(window);
			for (ObjColli& Obj : Objs21)
				Obj.Draw(window);
			for (ObjColli& Obj : Objs32)
				Obj.Draw(window);
			window.display();
		}

		////--Stage 3--//
		if (Game_State == 3)
		{
			sf::View view(sf::Vector2f(1.0f, 1.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));

			sf::Music stage3;
			stage3.openFromFile("Object/stage3.wav");
			stage3.setVolume(50);
			stage3.setLoop(true);
			stage3.play();

			//***BoxStage**//
			sf::Texture box23;
			box23.loadFromFile("Object/Christmas_box.png");
			std::vector<ObjColli>Objs23;
			Objs23.push_back(ObjColli(&box23, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f, 1000.0f)));
			Objs23.push_back(ObjColli(&box23, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes, 1000.0f)));
			Objs23.push_back(ObjColli(&box23, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 2, 1000.0f)));
			Objs23.push_back(ObjColli(&box23, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 3, 1000.0f)));
			Objs23.push_back(ObjColli(&box23, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 4, 1000.0f)));
			Objs23.push_back(ObjColli(&box21, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 5, 1000.0f)));
			Objs23.push_back(ObjColli(&box23, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 6, 1000.0f)));
			Objs23.push_back(ObjColli(&box23, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 7, 1000.0f)));
			Objs23.push_back(ObjColli(&box23, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 8, 1000.0f)));
			Objs23.push_back(ObjColli(&box23, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 9, 1000.0f)));
			Objs23.push_back(ObjColli(&box23, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 10, 1000.0f)));
			Objs23.push_back(ObjColli(&box23, sf::Vector2f(boxes, boxes), sf::Vector2f(0.0f + boxes * 11, 1000.0f)));

			//---Limit Stage---//
			sf::Texture box33;
			box33.loadFromFile("Object/Christbox_pick.png");
			std::vector<ObjColli>Objs33;
			for (size_t i = 0;i <= 40;i++)
			{
				Objs33.push_back(ObjColli(&box33, sf::Vector2f(54.0f, 54.0f), sf::Vector2f(rand() % (4500 - 1500) + 1500, 400.0f)));
			}

			float deltaTime = 1500.0f;
			sf::Clock clock;
			float timeElasped = 0;
			float GameTime = 10;
			float PointTime = 100;

			while (window.isOpen())
			{
				timeElasped += deltaTime;
				deltaTime = clock.restart().asSeconds();
				if (deltaTime > 1.0f / 20.0f)
					deltaTime = 1.0f / 20.0f;
				if (GameTime > 0)
					GameTime -= deltaTime;
				if (GameTime <= 0)
					PointTime -= deltaTime;
				if (PointTime <= 0)
					PointTime = 0;
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
						cout << "Mouse button has been pressed" << endl;
						switch (event.key.code)
						{
						case sf::Mouse::Left:
							cout << "LEFT KEY has been pressed" << endl;
							break;
						}
						break;
					case sf::Event::MouseButtonReleased:
						cout << "Mouse button has been released" << endl;
						break;
					}
					//cout << "Position x : " << Compman.getPosition().x << "\n" << "Position y : " << Compman.getPosition().y << "\n" << endl;

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
					{
						window.close();
					}
				}
				sf::Vector2f direction;

				//--Collider Update--//
				//Collider c = Compman.GetCollider();
				//for (ObjColli& Obj : Objs1)
				//	if (Obj.GetCollider().CheckCollision(c, direction, 1.0f))
				//		Compman.OnCollision(direction);
				//for (ObjColli& Obj : Objs3)
				//	if (Obj.GetCollider().CheckCollision(c, direction, 1.0f))
				//		Compman.OnCollision(direction);
				////----------Set_View----------//
				//view.setCenter(Compman.GetPosition().x, Compman.GetPosition().y);
				//if (view.getCenter().x - 195.0f <= 0.0f)
				//{
				//	if (view.getCenter().y - 450.0f <= 0.0f)
				//	{
				//		view.setCenter(195.f, Compman.GetPosition().y);
				//	}
				//	if (view.getCenter().y + 450.0f >= 900.0f)
				//	{
				//		view.setCenter(195.f, Compman.GetPosition().y);
				//	}
				//	if (view.getCenter().y - 450.0f > 0.0f && view.getCenter().y + 450.0f < 900.0f)
				//	{
				//		view.setCenter(195.f, Compman.GetPosition().y);
				//	}
				//}
				//if (view.getCenter().x + 415.0f >= 5850.f)
				//{
				//	if (view.getCenter().y - 450.0f <= 0.0f)
				//	{
				//		view.setCenter(5435.f, Compman.GetPosition().y);
				//	}
				//	if (view.getCenter().y + 450.0f >= 900.0f)
				//	{
				//		view.setCenter(5435.f, Compman.GetPosition().y);
				//	}
				//	if (view.getCenter().y - 450.0f > 0.0f && view.getCenter().y + 450.0f < 900.0f)
				//	{
				//		view.setCenter(5435.f, Compman.GetPosition().y);
				//	}
				//}
				//cout << view.getCenter().x << "\t" << view.getCenter().y << endl ;

				window.clear(sf::Color(255, 255, 255));
				//--DrawEverythings--//
				window.setView(view);
				//Compman.Draw(window);
				for (ObjColli& Obj : Objs23)
					Obj.Draw(window);
				for (ObjColli& Obj : Objs33)
					Obj.Draw(window);
				window.display();
			}

			/*if (P_State == 0)
			{
				PauseMenu Pmenu(300.f, 500.f);
			}*/


			return 0;
		}
	}