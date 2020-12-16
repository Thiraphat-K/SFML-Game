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
static const float boxes2 = 513.0f;
static const float boxes2_2 = 229.5f;
static const float boxes3 = 463.0f;
static const float boxes3_3 = 320.0f;
using namespace std;
float max_spacebartimer = 450;
float spacebartimer = 0;
static const float eraseObj = 7000.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 900), "Box Way", sf::Style::Close /*| sf::Style::Resize*/);
	Menu menu(window.getSize().x, window.getSize().y);

	//--Obj Everythings--//

	Texture MNp;
	MNp.loadFromFile("Object/Menu/MenuP.png");
	Sprite BGmn;
	BGmn.setTexture(MNp);

	Texture Gp0;
	Gp0.loadFromFile("Object/Guide.png");
	Sprite BG_Gp;
	BG_Gp.setTexture(Gp0);

	Texture Guide_page;
	Guide_page.loadFromFile("Object/Guide.png");
	Sprite Gp;
	Gp.setTexture(Guide_page);

	Music stage1;
	Music menums;
	menums.openFromFile("Object/Menu/menusound.wav");
	menums.setVolume(50);
	menums.setLoop(true);
	menums.play();

	Texture BGpmn;
	BGpmn.loadFromFile("Object/BGpause.png");
	Sprite pause_bg;
	pause_bg.setTexture(BGpmn);

	sf::Texture CompmanTexture;
	CompmanTexture.loadFromFile("Object/compmanA1.png");
	compman Compman(&CompmanTexture, sf::Vector2u(8, 4), 0.2f, 350.0f, 150.0f);

	TextFont SDid;
	TextFont NameT;

	Font font;
	font.loadFromFile("Object/cour.ttf");

	//init state
	bool checkColli = false;
	bool checkGameOpen = false;
	bool p_Menu = false;
	bool Game = false;
	int Game_State = 0;
	int P_State = 0;
	float deltaTime = 1500.0f;
	float GameTime = 0;

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
						//menums.stop();
						Game_State = 4;
						checkGameOpen = true;
						break;
					case 2:
						cout << "HighScore has been pressed" << endl;
						//go to state
						Game_State = 6;
						checkGameOpen = true;
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

	if (Game_State == 4) //guide
	{
		sf::Clock deCLK = sf::Clock();
		double debounce;
		Texture Gp1;
		Gp1.loadFromFile("Object/Guide/Control.png");
		Sprite Gpo;
		Gpo.setTexture(Gp1);

		int Guide_State = 0;
		double deTime = 0;
		while (window.isOpen() && Game_State == 4)
		{

			deTime += deCLK.getElapsedTime().asSeconds();
			sf::Event event;
			if (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				}
				if (Guide_State == 0)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
					{
						Guide_State = 1;
						debounce = deTime;
					}
					window.clear();
					window.draw(BG_Gp);
					window.draw(Gpo);
					window.display();

				}

				if (Guide_State == 1)
				{
					Texture Gp2;
					Gp2.loadFromFile("Object/Guide/Obj.png");
					Sprite Gpo2;
					Gpo2.setTexture(Gp2);
					window.clear();
					window.draw(BG_Gp);
					window.draw(Gpo2);
					window.display();

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::N) && deTime - debounce >= 100.f)
					{
						Game_State = 1;
					}

				}
			}


		}
	}

	if (Game_State == 6)
	{
		cout << "in";
		sf::Clock deCLK = sf::Clock();
		double debounce;
		Texture hScore;
		hScore.loadFromFile("Object/HScore.png");
		Sprite HS;
		HS.setTexture(hScore);

		int HS_State = 0;
		double deTime = 0;
		bool scorenaja = false;

		int cnt = 0;

		vector<pair<int, string>> scoreboard;

		scoreboard.clear();
		ifstream loadFile;
		loadFile.open("HS.txt");
		if (!loadFile.eof()) {
			string tempName;
			int tempScore;
			loadFile >> tempName >> tempScore;
			scoreboard.push_back({ tempScore,tempName });
			cout << "xxx";
		}
		loadFile.close();

		sort(scoreboard.begin(), scoreboard.end(), greater<pair<int, string>>());
		while (window.isOpen() && Game_State == 6)
		{
			sf::Event event;
			if (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
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
			}
			if (HS_State == 0)
			{
				window.clear();
				window.draw(HS);
				for (vector<pair<int, string>>::iterator k = scoreboard.begin(); k != scoreboard.end(); ++k)
				{
					++cnt;
					if (cnt > 5)
						break;

					sf::Text hname, hscore;
					hscore.setString(to_string(k->first));
					cout << k->second;
					hscore.setFont(font);
					hscore.setCharacterSize(20);
					hscore.setPosition(100, 100 + (80 * cnt));
					hscore.setFillColor(sf::Color::Black);
					window.draw(hscore);
					hname.setString(k->second);
					hname.setFont(font);
					hname.setCharacterSize(20);
					hname.setPosition(100, 100 + (80 * cnt));
					hname.setFillColor(sf::Color::Black);
					window.draw(hname);
				}
				window.display();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
				{
					debounce = deTime;
					Game_State = 1;
				}

			}
		}
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

		//***Player**//


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
			Objs2.push_back(ObjColli(&box2, sf::Vector2f(54.0f, 54.0f), sf::Vector2f(rand() % (4000 - 1500) + 1500, 400.0f)));
		}

		//---Limit Stage---//
		sf::Texture box3;
		std::vector<ObjColli>Objs3;
		Objs3.push_back(ObjColli(&box3, sf::Vector2f(2.0f, 5000.0f), sf::Vector2f(-268.0f, 724.f)));
		Objs3.push_back(ObjColli(&box3, sf::Vector2f(2.0f, 5000.0f), sf::Vector2f(5890.f, 724.f)));

		//----item----//
		//ITEM_1
		Texture item11;
		item11.loadFromFile("Object/Item_stage1/1.png");
		Sprite bt;
		bt.setTexture(item11);
		bt.setScale(1.2, 1.2);
		bt.setPosition(2500.f, 50.0f);
		bt.setOrigin(bt.getScale().x / 2, bt.getScale().y / 2);
		//ITEM_2
		Texture item12;
		item12.loadFromFile("Object/Item_stage1/2.png");
		Sprite bt2;
		bt2.setTexture(item12);
		bt2.setScale(1.2, 1.2);
		bt2.setPosition(1800.f, 40.0f);
		bt2.setOrigin(bt2.getScale().x / 2, bt2.getScale().y / 2);
		//ITEM_3
		Texture item13;
		item13.loadFromFile("Object/Item_stage1/3.png");
		Sprite bt3;
		bt3.setTexture(item13);
		bt3.setScale(1.2, 1.2);
		bt3.setPosition(4200.f, 40.0f);
		bt3.setOrigin(bt3.getScale().x / 2, bt3.getScale().y / 2);

		Texture arr;
		arr.loadFromFile("Object/ArrRed.png");
		Sprite arr1;
		arr1.setTexture(arr);
		arr1.setScale(0.9, 0.9);
		arr1.setPosition(2500.f, 640.0f);
		arr1.setOrigin(arr1.getScale().x / 2, arr1.getScale().y / 2);

		Sprite arr2;
		arr2.setTexture(arr);
		arr2.setScale(0.9, 0.9);
		arr2.setPosition(1800.f, 640.0f);
		arr2.setOrigin(arr2.getScale().x / 2, arr2.getScale().y / 2);

		Sprite arr3;
		arr3.setTexture(arr);
		arr3.setScale(0.9, 0.9);
		arr3.setPosition(4200.f, 640.0f);
		arr3.setOrigin(arr3.getScale().x / 2, arr3.getScale().y / 2);


		//---Next-Arrow---//
		Texture Narr;
		Narr.loadFromFile("Object/NArrRed.png");
		Sprite Narr1;
		Narr1.setTexture(Narr);
		Narr1.setScale(1.2, 1.2);
		Narr1.setPosition(2300.f, 150.0f);
		Narr1.setRotation(135);
		Narr1.setOrigin(Narr1.getScale().x / 2, Narr1.getScale().y / 2);

		Texture Narr_2;
		Narr_2.loadFromFile("Object/NArrRed2.png");
		Sprite Narr2;
		Narr2.setTexture(Narr_2);
		Narr2.setScale(1.2, 1.2);
		Narr2.setPosition(2300.f, 150.0f);
		Narr2.setRotation(45);
		Narr2.setOrigin(Narr2.getScale().x / 2, Narr2.getScale().y / 2);

		Texture Darr_1;
		Darr_1.loadFromFile("Object/DoorArr.png");
		Sprite Darr1;
		Darr1.setTexture(Darr_1);
		Darr1.setScale(1.2, 1.2);
		Darr1.setPosition(4300.f, 150.0f);
		Darr1.setRotation(45);
		Darr1.setOrigin(Darr1.getScale().x / 2, Darr1.getScale().y / 2);

		Texture DGo;
		DGo.loadFromFile("Object/DoorArrGo.png");
		Sprite D_Go;
		D_Go.setTexture(DGo);
		D_Go.setScale(1.2, 1.2);
		D_Go.setPosition(4900.f, 690.0f);
		D_Go.setOrigin(D_Go.getScale().x / 2, D_Go.getScale().y / 2);

		sf::Texture Holl;
		Holl.loadFromFile("Object/Holl.png");
		sf::Sprite hell(Holl);
		hell.setScale(1.2, 1.2);
		hell.setPosition(5300.0f, 675.0f);
		hell.setOrigin(hell.getScale().x / 2, hell.getScale().y / 2);

		//----hitboxtest----//
		hitboxtest hitbox0(0, 0, Vector2f(54, Objs2[0].GetSize().x), Objs2[0].GetPosition());
		hitboxtest hitbox1(0, 0, Vector2f(50, Compman.GetSize().x), Compman.GetPosition());


		//--Text--//
		TextFont text1;
		TextFont text2;

		bool Nextarr = false; bool Nextarr1 = false; bool Nextarr2 = false; bool Nextarr3 = false;
		bool N_item2 = false; bool N_item3 = false;
		bool Door1 = false;
		sf::Clock clock;
		float timeElasped = 0;
		float PointTime = 100;

		while (window.isOpen())
		{
			timeElasped += deltaTime;
			deltaTime = clock.restart().asSeconds();
			if (deltaTime > 1.0f / 20.0f)
				deltaTime = 1.0f / 20.0f;
			/*if (GameTime > 0)*/
			/*if (GameTime <= 0)*/
			GameTime += deltaTime;
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

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				stage1.stop();
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
					if ((Keyboard::isKeyPressed(Keyboard::Space)) && spacebartimer >= max_spacebartimer && Compman.getHold() == false && Objs2[i].getPickObj() == false /*&& Compman.getPosition().y >= Objs2[i].getbody().getPosition().y - 20 && Compman.getPosition().y <= Objs2[i].getbody().getPosition().y + 20*/) {
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
						if (Objs2[j].GetCollider().CheckCollision(o, direction, 1.0f))
						{
							Objs2[i].Oncollision(direction);
						}
					}
				}
			}
			for (ObjColli& Obj : Objs3)
			{
				Collider b = Obj.GetCollider();
				if (Obj.GetCollider().CheckCollision(c, direction, 1.0f))
				{
					Compman.OnCollision(direction);
				}
				for (ObjColli& Obj2 : Objs2)
				{
					if (Obj2.GetCollider().CheckCollision(b, direction, 0.0f))
					{
						Obj2.Oncollision(direction);
					}
				}
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

			if (Compman.getGlobalbounds().intersects(bt.getGlobalBounds()))
			{
				bt.setPosition(eraseObj, eraseObj);
				arr1.setPosition(eraseObj, eraseObj);
				Nextarr = true;

			}	//ITEM_1
			if (Compman.getGlobalbounds().intersects(arr2.getGlobalBounds()))
			{
				Narr1.setPosition(eraseObj, eraseObj);
			}
			if (Compman.getGlobalbounds().intersects(bt2.getGlobalBounds()))
			{
				arr2.setPosition(eraseObj, eraseObj);
				bt2.setPosition(eraseObj, eraseObj);
				Nextarr1 = true;
			}
			if (Compman.getGlobalbounds().intersects(arr3.getGlobalBounds()))
			{
				Narr2.setPosition(eraseObj, eraseObj);
			}
			if (Compman.getGlobalbounds().intersects(bt3.getGlobalBounds()))
			{
				arr3.setPosition(eraseObj, eraseObj);
				bt3.setPosition(eraseObj, eraseObj);
				Nextarr2 = true;
			}
			if (Compman.getPosition().x == Darr1.getPosition().x)
			{
				Nextarr3 = true;
			}
			if (Compman.getGlobalbounds().intersects(D_Go.getGlobalBounds()) + 200.0f && Compman.getGlobalbounds().intersects(bt3.getGlobalBounds()))
			{
				Door1 = true;
			}
			if (Compman.getGlobalbounds().intersects(hell.getGlobalBounds()))
			{
				cout << "Go State 2";
				Game_State = 2;
				stage1.stop();
				window.clear();
				break;
			}
			if (Keyboard::isKeyPressed(Keyboard::End))
			{
				hell.setPosition(sf::Vector2f(Compman.getPosition().x + 50.0f, Compman.getPosition().y - 30.0f));
				Door1 = true;
			}

			window.clear(sf::Color(255, 255, 255));
			window.setView(view);
			window.draw(bt);
			window.draw(arr1);
			if (Nextarr == true)
			{
				window.draw(Narr1);
				N_item2 = true;
			}
			if (N_item2 == true)
			{
				window.draw(arr2);
				window.draw(bt2);
			}
			if (Nextarr1 == true)
			{
				window.draw(Narr2);
				N_item3 = true;
			}
			if (N_item3 == true)
			{
				window.draw(arr3);
				window.draw(bt3);
			}
			if (Nextarr2 == true)
			{
				window.draw(Darr1);
			}
			if (Nextarr3 == true)
			{
				window.draw(D_Go);
			}
			if (Door1 == true)
			{
				window.draw(hell);
			}
			Compman.Draw(window);
			for (ObjColli& Obj : Objs1)
				Obj.Draw(window);
			for (ObjColli& Obj : Objs2)
				Obj.Draw(window);
			for (ObjColli& Obj : Objs3)
				Obj.Draw(window);
			/*hitbox0.Draw(window);
			hitbox1.Draw(window);*/
			text1.drawtext((float)abs(GameTime), (string)"Time : ", (string)" s", sf::Vector2f(view.getCenter().x + (window.getSize().x / 2) - 250, view.getCenter().y - (window.getSize().y / 2) + 20), window, sf::Color(255, 0, 0));
			//text2.drawtext((int)abs(PointTime), (string)"Point : ", (string)"", sf::Vector2f(view.getCenter().x + (window.getSize().x / 2) - 200, view.getCenter().y - (window.getSize().y / 2) + 55), window, sf::Color(255, 150, 0));
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

		sf::Texture Holl;
		Holl.loadFromFile("Object/Holl.png");
		sf::Sprite hell(Holl);
		hell.setScale(1.2, 1.2);
		hell.setPosition(5300.0f, 675.0f);
		hell.setOrigin(hell.getScale().x / 2, hell.getScale().y / 2);

		//***BoxStage**//
		sf::Texture box12;
		box12.loadFromFile("Object/box23.png");
		std::vector<ObjColli>Objs12;
		Objs12.push_back(ObjColli(&box12, sf::Vector2f(boxes2, boxes2_2), sf::Vector2f(0.0f, 718.0f)));
		Objs12.push_back(ObjColli(&box12, sf::Vector2f(boxes2, boxes2_2), sf::Vector2f(0.0f + boxes2, 718.0f)));
		Objs12.push_back(ObjColli(&box12, sf::Vector2f(boxes2, boxes2_2), sf::Vector2f(0.0f + boxes2 * 2, 718.0f)));
		Objs12.push_back(ObjColli(&box12, sf::Vector2f(boxes2, boxes2_2), sf::Vector2f(0.0f + boxes2 * 3, 718.0f)));
		Objs12.push_back(ObjColli(&box12, sf::Vector2f(boxes2, boxes2_2), sf::Vector2f(0.0f + boxes2 * 4, 718.0f)));
		Objs12.push_back(ObjColli(&box12, sf::Vector2f(boxes2, boxes2_2), sf::Vector2f(0.0f + boxes2 * 5, 718.0f)));
		Objs12.push_back(ObjColli(&box12, sf::Vector2f(boxes2, boxes2_2), sf::Vector2f(0.0f + boxes2 * 6, 718.0f)));
		Objs12.push_back(ObjColli(&box12, sf::Vector2f(boxes2, boxes2_2), sf::Vector2f(0.0f + boxes2 * 7, 718.0f)));
		Objs12.push_back(ObjColli(&box12, sf::Vector2f(boxes2, boxes2_2), sf::Vector2f(0.0f + boxes2 * 8, 718.0f)));
		Objs12.push_back(ObjColli(&box12, sf::Vector2f(boxes2, boxes2_2), sf::Vector2f(0.0f + boxes2 * 9, 718.0f)));
		Objs12.push_back(ObjColli(&box12, sf::Vector2f(boxes2, boxes2_2), sf::Vector2f(0.0f + boxes2 * 10, 718.0f)));
		Objs12.push_back(ObjColli(&box12, sf::Vector2f(boxes2, boxes2_2), sf::Vector2f(0.0f + boxes2 * 11, 718.0f)));

		//----box--pick----//
		sf::Texture box22;
		box22.loadFromFile("Object/box3.png");
		std::vector<ObjColli>Objs22;
		for (size_t i = 0;i <= 30;i++)
		{
			Objs22.push_back(ObjColli(&box22, sf::Vector2f(54.0f, 54.0f), sf::Vector2f(rand() % (4300 - 1200) + 1500, 400.0f)));
		}

		//---Limit Stage---//
		sf::Texture box32;
		std::vector<ObjColli>Objs32;
		Objs32.push_back(ObjColli(&box32, sf::Vector2f(2.0f, 5000.0f), sf::Vector2f(-268.0f, 724.f)));
		Objs32.push_back(ObjColli(&box32, sf::Vector2f(2.0f, 5000.0f), sf::Vector2f(5890.f, 724.f)));

		//----hitboxtest----//
		hitboxtest hitbox0(0, 0, Vector2f(54, Objs22[0].GetSize().x), Objs22[0].GetPosition());
		hitboxtest hitbox1(0, 0, Vector2f(50, Compman.GetSize().x), Compman.GetPosition());

		TextFont text1;
		TextFont text2;

		bool Door1 = false;

		sf::Clock clock;
		float timeElasped = 0;
		float PointTime = 100;

		while (window.isOpen())
		{
			timeElasped += deltaTime;
			deltaTime = clock.restart().asSeconds();
			if (deltaTime > 1.0f / 20.0f)
				deltaTime = 1.0f / 20.0f;
			/*if (GameTime > 0)*/
			/*if (GameTime <= 0)*/
			GameTime += deltaTime;
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

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					stage2.stop();
				}
			}
			spacebartimer += 1;
			Compman.Update(deltaTime);
			sf::Vector2f direction;
			//--Collider_Update--//
			Collider c = Compman.GetCollider();
			for (ObjColli& Obj : Objs12)
			{
				Collider O = Obj.GetCollider();
				if (Obj.GetCollider().CheckCollision(c, direction, 1.0f))
				{
					Compman.OnCollision(direction);
				}
				for (ObjColli& Obj22 : Objs22)
				{
					if (Obj22.GetCollider().CheckCollision(O, direction, 0.0f))
					{
						Obj22.Oncollision(direction);
					}
				}
			}
			//---Hold_Obj---//
			for (int i = 0;i < Objs22.size();i++)
			{
				Objs22[i].Update(deltaTime, Compman.getPosition());
				if (Objs22[i].GetCollider().CheckCollision(c, direction, 0.0f))
				{
					if (Objs22[i].getPickObj() == false)
					{
						Compman.OnCollision(direction);
						//cout << "Collision" << endl;
					}
					if ((Keyboard::isKeyPressed(Keyboard::Space)) && spacebartimer >= max_spacebartimer && Compman.getHold() == false && Objs22[i].getPickObj() == false /*&& Compman.getPosition().y >= Objs2[i].getbody().getPosition().y - 20 && Compman.getPosition().y <= Objs2[i].getbody().getPosition().y + 20*/) {
						spacebartimer = 0;
						Objs22[i].setPickObj(true);
						Compman.setHold(true);
					}
					if (Objs22[i].getPickObj() == true && (Keyboard::isKeyPressed(Keyboard::Space)) && spacebartimer >= max_spacebartimer && Compman.getcanJump() == false)
					{
						spacebartimer = 0;
						Objs22[i].getbody().setPosition(Compman.getPosition().x, Compman.getPosition().y + 60);
						Compman.setHold(false);
						Objs22[i].setPickObj(false);
					}
				}
				Collider o = Objs22[i].GetCollider();
				for (int j = 0; j < Objs22.size();j++)
				{
					if (i != j)
					{
						if (Objs22[j].GetCollider().CheckCollision(o, direction, 1.0f))
						{
							Objs22[i].Oncollision(direction);
						}
					}
				}
			}
			for (ObjColli& Obj : Objs32)
			{
				Collider b = Obj.GetCollider();
				if (Obj.GetCollider().CheckCollision(c, direction, 1.0f))
				{
					Compman.OnCollision(direction);
				}
				for (ObjColli& Obj2 : Objs32)
				{
					if (Obj2.GetCollider().CheckCollision(b, direction, 0.0f))
					{
						Obj2.Oncollision(direction);
					}
				}
			}
			//--hitboxtest_Update--//
			hitbox1.Update(-21.5, -35.5, Compman.GetPosition());
			hitbox0.Update(-27, -27, Objs22[0].GetPosition());

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

			if (Keyboard::isKeyPressed(Keyboard::End))
			{
				hell.setPosition(sf::Vector2f(Compman.getPosition().x + 50.0f, Compman.getPosition().y - 30.0f));
				Door1 = true;
			}



			if (Compman.getGlobalbounds().intersects(hell.getGlobalBounds()))
			{
				cout << "Go State 3";
				Game_State = 3;
				stage2.stop();
				window.clear();
				break;
			}

			window.clear(sf::Color(255, 255, 255));
			//--DrawEverythings--//
			window.setView(view);
			if (Door1 == true)
			{
				window.draw(hell);
			}
			Compman.Draw(window);
			for (ObjColli& Obj : Objs12)
				Obj.Draw(window);
			for (ObjColli& Obj : Objs22)
				Obj.Draw(window);
			for (ObjColli& Obj : Objs32)
				Obj.Draw(window);
			text1.drawtext((float)abs(GameTime), (string)"Time : ", (string)" s", sf::Vector2f(view.getCenter().x + (window.getSize().x / 2) - 250, view.getCenter().y - (window.getSize().y / 2) + 20), window, sf::Color(255, 0, 0));
			window.display();
		}
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

		sf::Texture Holl;
		Holl.loadFromFile("Object/Holl.png");
		sf::Sprite hell(Holl);
		hell.setScale(1.2, 1.2);
		hell.setPosition(5300.0f, 675.0f);
		hell.setOrigin(hell.getScale().x / 2, hell.getScale().y / 2);

		//***BoxStage**//
		sf::Texture box12;
		box12.loadFromFile("Object/Christmas_box.png");
		std::vector<ObjColli>Objs12;
		Objs12.push_back(ObjColli(&box12, sf::Vector2f(boxes3, boxes3_3), sf::Vector2f(0.0f, 1000.0f)));
		Objs12.push_back(ObjColli(&box12, sf::Vector2f(boxes3, boxes3_3), sf::Vector2f(0.0f + boxes3, 1000.0f)));
		Objs12.push_back(ObjColli(&box12, sf::Vector2f(boxes3, boxes3_3), sf::Vector2f(0.0f + boxes3 * 2, 1000.0f)));
		Objs12.push_back(ObjColli(&box12, sf::Vector2f(boxes3, boxes3_3), sf::Vector2f(0.0f + boxes3 * 3, 1000.0f)));
		Objs12.push_back(ObjColli(&box12, sf::Vector2f(boxes3, boxes3_3), sf::Vector2f(0.0f + boxes3 * 4, 1000.0f)));
		Objs12.push_back(ObjColli(&box12, sf::Vector2f(boxes3, boxes3_3), sf::Vector2f(0.0f + boxes3 * 5, 1000.0f)));
		Objs12.push_back(ObjColli(&box12, sf::Vector2f(boxes3, boxes3_3), sf::Vector2f(0.0f + boxes3 * 6, 1000.0f)));
		Objs12.push_back(ObjColli(&box12, sf::Vector2f(boxes3, boxes3_3), sf::Vector2f(0.0f + boxes3 * 7, 1000.0f)));
		Objs12.push_back(ObjColli(&box12, sf::Vector2f(boxes3, boxes3_3), sf::Vector2f(0.0f + boxes3 * 8, 1000.0f)));
		Objs12.push_back(ObjColli(&box12, sf::Vector2f(boxes3, boxes3_3), sf::Vector2f(0.0f + boxes3 * 9, 1000.0f)));
		Objs12.push_back(ObjColli(&box12, sf::Vector2f(boxes3, boxes3_3), sf::Vector2f(0.0f + boxes3 * 10, 1000.0f)));
		Objs12.push_back(ObjColli(&box12, sf::Vector2f(boxes3, boxes3_3), sf::Vector2f(0.0f + boxes3 * 11, 1000.0f)));
		Objs12.push_back(ObjColli(&box12, sf::Vector2f(boxes3, boxes3_3), sf::Vector2f(0.0f + boxes3 * 12, 1000.0f)));
		Objs12.push_back(ObjColli(&box12, sf::Vector2f(boxes3, boxes3_3), sf::Vector2f(0.0f + boxes3 * 13, 1000.0f)));

		//----box--pick----//
		sf::Texture box22;
		box22.loadFromFile("Object/Christbox_pick.png");
		std::vector<ObjColli>Objs22;
		for (size_t i = 0;i <= 40;i++)
		{
			Objs22.push_back(ObjColli(&box22, sf::Vector2f(54.0f, 54.0f), sf::Vector2f(rand() % (5000 - 1000) + 1500, 400.0f)));
		}

		//---Limit Stage---//
		sf::Texture box32;
		std::vector<ObjColli>Objs32;
		Objs32.push_back(ObjColli(&box32, sf::Vector2f(2.0f, 5000.0f), sf::Vector2f(-268.0f, 724.f)));
		Objs32.push_back(ObjColli(&box32, sf::Vector2f(2.0f, 5000.0f), sf::Vector2f(5890.f, 724.f)));

		//----hitboxtest----//
		hitboxtest hitbox0(0, 0, Vector2f(54, Objs22[0].GetSize().x), Objs22[0].GetPosition());
		hitboxtest hitbox1(0, 0, Vector2f(50, Compman.GetSize().x), Compman.GetPosition());

		TextFont text1;
		TextFont text2;

		bool Door1 = false;

		sf::Clock clock;
		float timeElasped = 0;

		float PointTime = 100;

		while (window.isOpen())
		{
			timeElasped += deltaTime;
			deltaTime = clock.restart().asSeconds();
			if (deltaTime > 1.0f / 20.0f)
				deltaTime = 1.0f / 20.0f;
			/*if (GameTime > 0)*/
			/*if (GameTime <= 0)*/
			GameTime += deltaTime;
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

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					stage3.stop();
				}
			}
			spacebartimer += 1;
			Compman.Update(deltaTime);
			sf::Vector2f direction;
			//--Collider_Update--//
			Collider c = Compman.GetCollider();
			for (ObjColli& Obj : Objs12)
			{
				Collider O = Obj.GetCollider();
				if (Obj.GetCollider().CheckCollision(c, direction, 1.0f))
				{
					Compman.OnCollision(direction);
				}
				for (ObjColli& Obj22 : Objs22)
				{
					if (Obj22.GetCollider().CheckCollision(O, direction, 0.0f))
					{
						Obj22.Oncollision(direction);
					}
				}
			}
			//---Hold_Obj---//
			for (int i = 0;i < Objs22.size();i++)
			{
				Objs22[i].Update(deltaTime, Compman.getPosition());
				if (Objs22[i].GetCollider().CheckCollision(c, direction, 0.0f))
				{
					if (Objs22[i].getPickObj() == false)
					{
						Compman.OnCollision(direction);
						//cout << "Collision" << endl;
					}
					if ((Keyboard::isKeyPressed(Keyboard::Space)) && spacebartimer >= max_spacebartimer && Compman.getHold() == false && Objs22[i].getPickObj() == false /*&& Compman.getPosition().y >= Objs2[i].getbody().getPosition().y - 20 && Compman.getPosition().y <= Objs2[i].getbody().getPosition().y + 20*/) {
						spacebartimer = 0;
						Objs22[i].setPickObj(true);
						Compman.setHold(true);
					}
					if (Objs22[i].getPickObj() == true && (Keyboard::isKeyPressed(Keyboard::Space)) && spacebartimer >= max_spacebartimer && Compman.getcanJump() == false)
					{
						spacebartimer = 0;
						Objs22[i].getbody().setPosition(Compman.getPosition().x, Compman.getPosition().y + 60);
						Compman.setHold(false);
						Objs22[i].setPickObj(false);
					}
				}
				Collider o = Objs22[i].GetCollider();
				for (int j = 0; j < Objs22.size();j++)
				{
					if (i != j)
					{
						if (Objs22[j].GetCollider().CheckCollision(o, direction, 1.0f))
						{
							Objs22[i].Oncollision(direction);
						}
					}
				}
			}
			for (ObjColli& Obj : Objs32)
			{
				Collider b = Obj.GetCollider();
				if (Obj.GetCollider().CheckCollision(c, direction, 1.0f))
				{
					Compman.OnCollision(direction);
				}
				for (ObjColli& Obj2 : Objs32)
				{
					if (Obj2.GetCollider().CheckCollision(b, direction, 0.0f))
					{
						Obj2.Oncollision(direction);
					}
				}
			}
			//--hitboxtest_Update--//
			hitbox1.Update(-21.5, -35.5, Compman.GetPosition());
			hitbox0.Update(-27, -27, Objs22[0].GetPosition());

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

			if (Keyboard::isKeyPressed(Keyboard::End))
			{
				hell.setPosition(sf::Vector2f(Compman.getPosition().x + 50.0f, Compman.getPosition().y - 30.0f));
				Door1 = true;
			}

			if (Compman.getGlobalbounds().intersects(hell.getGlobalBounds()))
			{
				Game_State = 5;
				stage3.stop();
				window.clear();
				break;
			}

			window.clear(sf::Color(255, 255, 255));
			//--DrawEverythings--//
			window.setView(view);
			if (Door1 == true)
			{
				window.draw(hell);
			}
			Compman.Draw(window);
			for (ObjColli& Obj : Objs12)
				Obj.Draw(window);
			for (ObjColli& Obj : Objs22)
				Obj.Draw(window);
			for (ObjColli& Obj : Objs32)
				Obj.Draw(window);
			text1.drawtext((float)abs(GameTime), (string)"Time : ", (string)" s", sf::Vector2f(view.getCenter().x + (window.getSize().x / 2) - 250, view.getCenter().y - (window.getSize().y / 2) + 20), window, sf::Color(255, 0, 0));
			window.display();
		}
	}

	if (Game_State == 5)
	{
		cout << "Stage 5";
		sf::Clock deCLK = sf::Clock();
		double debounce;

		string name1;
		String name;
		Text yourname;

		Texture Mapname;
		Mapname.loadFromFile("Object/StageName.png");
		Sprite name_key;
		name_key.setTexture(Mapname);

		int Name_State = 0;
		double deTime = 0;
		bool enterinto = false;
		while (window.isOpen())
		{
			deTime += deCLK.getElapsedTime().asSeconds();
			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
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
				if (event.type == sf::Event::TextEntered)
				{
					enterinto = true;
					cout << "intoEnter";
					if (event.text.unicode == '\b' && (name.getSize() > 0))
					{
						name1.erase(name.getSize() - 1, 1);
						name.erase(name.getSize() - 1, 1);
					}
					else
					{
						if ((event.text.unicode < 128) && (name.getSize() < 8) && (event.text.unicode != '\b'))
						{
							name += static_cast<char>(event.text.unicode);
							name1 += static_cast<char>(event.text.unicode);
						}
					}
					yourname.setFont(font);
					yourname.setString(name);
					yourname.setFillColor(sf::Color::White);
					yourname.setCharacterSize(20);
					yourname.setPosition(window.getSize().x/2, window.getSize().y/2);
				}
				if (Keyboard::isKeyPressed(Keyboard::Enter))
				{
					window.close();
				}
			}
			window.clear();
			window.draw(name_key);
			window.draw(yourname);
			window.display();
		}

		//cout << "Position x : " << Compman.getPosition().x << "\n" << "Position y : " << Compman.getPosition().y << "\n" << endl;
		cout << "Go State Score";
		ofstream highscore;
		highscore.open("HS.txt", ios::out | ios::app);
		highscore << "\n" << name1 << " " << GameTime;
		highscore.close();
	}

	while (P_State == 1)
	{
		PauseMenu Pmenu(500.f, 500.f);
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					if (Pmenu.PselectedItem >= 0)
					{
						Pmenu.Moveup();
						break;

					}
				case sf::Keyboard::Down:
					if (Pmenu.PselectedItem < PMax_Items)
					{
						Pmenu.Movedown();
						break;
					}


				case sf::Keyboard::Return:
					switch (Pmenu.GetPressedItem())
					{
					case 0:
						cout << "Resume has been pressed" << endl;
						//go to state
						Game_State = 1;
						checkGameOpen = true;
						break;
					case 1:
						cout << "Main Menu has been pressed" << endl;
						//go to state
						break;
					case 2:
						cout << "Quit has been pressed" << endl;
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
		Pmenu.draw(window);
		window.draw(pause_bg);
		window.display();
		if (checkGameOpen == true)
			break;
	}

	return 0;
}

