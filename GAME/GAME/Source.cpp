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
static const float arr_point = 640.0f;
static const float arr_point2 = 640.0f - 100.0f;
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
	
	bool Game_run = true;
	
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

	if (Game_run == true)
	{
		Menu menu(window.getSize().x, window.getSize().y);
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
			SDid.drawtext(63010467, (string)".", (string)"  THIRAPHAT KETSINGNOI", sf::Vector2f(600, 865), window, sf::Color(0, 120, 255));
			window.display();
			if (checkGameOpen == true)
				break;
		}
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
						menums.stop();
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
				window.clear();
				window.draw(HS);
				for (vector<pair<int, string>>::iterator k = scoreboard.begin(); k != scoreboard.end(); ++k)
				{
					++cnt;
					if (cnt > 5)
						break;
					sf::Text hname, hscore;
					hscore.setString(to_string(k->first));
					hscore.setFont(font);
					hscore.setCharacterSize(20);
					hscore.setOrigin(HS.getLocalBounds().width / 2, HS.getLocalBounds().height / 2);
					hscore.setPosition(window.getSize().x / 2, window.getSize().y + (80 * cnt));
					hscore.setFillColor(sf::Color::Blue);
					window.draw(hscore);
					hname.setString(k->second);
					hname.setFont(font);
					hname.setCharacterSize(20);
					hname.setOrigin(HS.getLocalBounds().width / 2, HS.getLocalBounds().height / 2);
					hname.setPosition(window.getSize().x / 2, window.getSize().y + (80 * cnt));
					hname.setFillColor(sf::Color::Blue);
					window.draw(hname);
				}
				window.display();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
				{
					debounce = deTime;
					menums.stop();
					Game_State = 1;
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
		bt.setPosition(eraseObj, eraseObj);
		bt.setOrigin(bt.getScale().x / 2, bt.getScale().y / 2);
		//ITEM_2
		Texture item12;
		item12.loadFromFile("Object/Item_stage1/2.png");
		Sprite bt2;
		bt2.setTexture(item12);
		bt2.setScale(1.2, 1.2);
		bt2.setPosition(eraseObj, eraseObj);
		bt2.setOrigin(bt2.getScale().x / 2, bt2.getScale().y / 2);
		//ITEM_3
		Texture item13;
		item13.loadFromFile("Object/Item_stage1/3.png");
		Sprite bt3;
		bt3.setTexture(item13);
		bt3.setScale(1.2, 1.2);
		bt3.setPosition(eraseObj, eraseObj);
		bt3.setOrigin(bt3.getScale().x / 2, bt3.getScale().y / 2);

		Texture arr;
		arr.loadFromFile("Object/ArrRed.png");
		Sprite arr1;
		arr1.setTexture(arr);
		arr1.setScale(0.9, 0.9);
		arr1.setPosition(2700.0f, arr_point);
		arr1.setOrigin(arr1.getScale().x / 2, arr1.getScale().y / 2);

		Sprite arr2;
		arr2.setTexture(arr);
		arr2.setScale(0.9, 0.9);
		arr2.setPosition(eraseObj, eraseObj);
		arr2.setOrigin(arr2.getScale().x / 2, arr2.getScale().y / 2);

		Sprite arr3;
		arr3.setTexture(arr);
		arr3.setScale(0.9, 0.9);
		arr3.setPosition(eraseObj, eraseObj);
		arr3.setOrigin(arr3.getScale().x / 2, arr3.getScale().y / 2);


		//---Next-Arrow---//
		Texture Narr_s;
		Narr_s.loadFromFile("Object/NArrS2.png");
		Sprite Narr_is;
		Narr_is.setTexture(Narr_s);
		Narr_is.setScale(1.2, 1.2);
		Narr_is.setPosition(eraseObj, eraseObj);
		//Narr_i1.setRotation(135);
		Narr_is.setOrigin(Narr_is.getScale().x / 2, Narr_is.getScale().y / 2);
		Narr_is.setPosition(Compman.getPosition().x + 200.f, arr_point);

		Texture Narr;
		Narr.loadFromFile("Object/NArrRed.png");
		Sprite Narr1;
		Narr1.setTexture(Narr);
		Narr1.setScale(1.2, 1.2);
		Narr1.setPosition(eraseObj, eraseObj);
		Narr1.setOrigin(Narr1.getScale().x / 2, Narr1.getScale().y / 2);

		Texture Narr_2;
		Narr_2.loadFromFile("Object/NArrRed2.png");
		Sprite Narr2;
		Narr2.setTexture(Narr_2);
		Narr2.setScale(1.2, 1.2);
		Narr2.setPosition(eraseObj, eraseObj);
		Narr2.setOrigin(Narr2.getScale().x / 2, Narr2.getScale().y / 2);

		Texture Darr_1;
		Darr_1.loadFromFile("Object/DoorArr.png");
		Sprite Darr1;
		Darr1.setTexture(Darr_1);
		Darr1.setScale(1.2, 1.2);
		Darr1.setPosition(eraseObj, eraseObj);
		Darr1.setOrigin(Darr1.getScale().x / 2, Darr1.getScale().y / 2);

		Texture DGo;
		DGo.loadFromFile("Object/DoorArrGo.png");
		Sprite D_Go;
		D_Go.setTexture(DGo);
		D_Go.setScale(1.2, 1.2);
		D_Go.setPosition(eraseObj, eraseObj);
		D_Go.setOrigin(D_Go.getScale().x / 2, D_Go.getScale().y / 2);

		sf::Texture Holl;
		Holl.loadFromFile("Object/Holl.png");
		sf::Sprite hell(Holl);
		hell.setScale(1.2, 1.2);
		hell.setPosition(eraseObj, eraseObj
		);
		hell.setOrigin(hell.getScale().x / 2, hell.getScale().y / 2);

		//----hitboxtest----//
		hitboxtest hitbox0(0, 0, Vector2f(54, Objs2[0].GetSize().x), Objs2[0].GetPosition());
		hitboxtest hitbox1(0, 0, Vector2f(50, Compman.GetSize().x), Compman.GetPosition());


		//--Text--//
		TextFont text1;
		TextFont text2;

		//----bool for if rand y position item----//
		bool item_s11 = true;
		bool item_s12 = true;
		bool item_s13 = true;
		
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

			//---loop pick item---//
			for (size_t i = 0;i < Objs2.size(); i++)
			{
				if ((Objs2[i].getGlobalbounds().intersects(arr1.getGlobalBounds()) or Compman.getGlobalbounds().intersects(arr1.getGlobalBounds())) and item_s11 == true)
				{
					Narr_is.setPosition(eraseObj, eraseObj);
					bt.setPosition(arr1.getPosition().x, rand() % (150 - 40) + 40);
					item_s11 = false;
				}
				if (Compman.getGlobalbounds().intersects(bt.getGlobalBounds()))
				{
					arr1.setPosition(eraseObj, eraseObj);
					bt.setPosition(eraseObj, eraseObj);
					Narr1.setPosition(Compman.getPosition().x - 200.0f, 200.0f);
					Narr1.setRotation(135);
					arr2.setPosition(Narr1.getPosition().x - 900.0f, arr_point);
				}
				if ((Compman.getGlobalbounds().intersects(arr2.getGlobalBounds()) or Objs2[i].getGlobalbounds().intersects(arr2.getGlobalBounds())) and item_s12 == true)
				{
					bt2.setPosition(arr2.getPosition().x, rand() % (150 - 40) + 40);
					item_s12 = false;
					Narr1.setPosition(eraseObj, eraseObj);
				}
				if(Compman.getGlobalbounds().intersects(bt2.getGlobalBounds()))
				{
					arr2.setPosition(eraseObj, eraseObj);
					bt2.setPosition(eraseObj, eraseObj);
					Narr2.setPosition(Compman.getPosition().x + 200.0f, 200.0f);
					Narr2.setRotation(45);
					arr3.setPosition(Narr2.getPosition().x + (900.0f*2), arr_point);
				}
				if ((Compman.getGlobalbounds().intersects(arr3.getGlobalBounds()) or Objs2[i].getGlobalbounds().intersects(arr3.getGlobalBounds())) and item_s13 == true)
				{
					bt3.setPosition(arr3.getPosition().x, rand() % (150 - 40) + 40);
					item_s13 = false;
					Narr2.setPosition(eraseObj, eraseObj);
				}
				if (Compman.getGlobalbounds().intersects(bt3.getGlobalBounds()))
				{
					arr3.setPosition(eraseObj, eraseObj);
					bt3.setPosition(eraseObj, eraseObj);
					Darr1.setPosition(Compman.getPosition().x + 200.0f, 200.0f);
					Darr1.setRotation(45);
					D_Go.setPosition(Darr1.getPosition().x + 600.0f, arr_point+50.0f);
				}
				if (Compman.getGlobalbounds().intersects(D_Go.getGlobalBounds()))
				{
					Darr1.setPosition(eraseObj, eraseObj);
					hell.setPosition(D_Go.getPosition().x + 300.0f, arr_point+30.0f);
				}

			}

			if (Compman.getGlobalbounds().intersects(hell.getGlobalBounds()))
			{
				cout << "Go State 2" << endl;
				Game_State = 2;
				stage1.stop();
				window.clear();
				break;
			}
			if (Keyboard::isKeyPressed(Keyboard::End))
			{
				hell.setPosition(sf::Vector2f(Compman.getPosition().x + 50.0f, Compman.getPosition().y - 30.0f));
			}

			window.clear(sf::Color(255, 255, 255));
			window.setView(view);
			window.draw(bt);
			window.draw(arr1);
			window.draw(Narr1);
			window.draw(arr2);
			window.draw(bt2);
			window.draw(Narr2);
			window.draw(arr3);
			window.draw(bt3);
			window.draw(Darr1);
			window.draw(D_Go);
			window.draw(Narr_is);
			Compman.Draw(window);
			for (ObjColli& Obj : Objs1)
				Obj.Draw(window);
			for (ObjColli& Obj : Objs2)
				Obj.Draw(window);
			for (ObjColli& Obj : Objs3)
				Obj.Draw(window);
			/*hitbox0.Draw(window);
			hitbox1.Draw(window);*/
			window.draw(hell);
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
		hell.setPosition(eraseObj, eraseObj);
		hell.setOrigin(hell.getScale().x / 2, hell.getScale().y / 2);
		//---------Item---------//
		Texture WFt;
		WFt.loadFromFile("Object/Item_stage2/1.png");
		Sprite WFs;
		WFs.setTexture(WFt);
		WFs.setScale(1.2, 1.2);
		WFs.setPosition(eraseObj, eraseObj);
		WFs.setOrigin(WFs.getScale().x / 2, WFs.getScale().y / 2);

		Texture ELt;
		ELt.loadFromFile("Object/Item_stage2/2.png");
		Sprite ELs;
		ELs.setTexture(ELt);
		ELs.setScale(1.2, 1.2);
		ELs.setPosition(eraseObj, eraseObj);
		ELs.setOrigin(ELs.getScale().x / 2, ELs.getScale().y / 2);

		Texture LKt;
		LKt.loadFromFile("Object/Item_stage2/3.png");
		Sprite LKs;
		LKs.setTexture(LKt);
		LKs.setScale(1.2, 1.2);
		LKs.setPosition(eraseObj, eraseObj);
		LKs.setOrigin(LKs.getScale().x / 2, LKs.getScale().y / 2);

		Texture LCt;
		LCt.loadFromFile("Object/Item_stage2/4.png");
		Sprite LCs;
		LCs.setTexture(LCt);
		LCs.setScale(1.2, 1.2);
		LCs.setPosition(eraseObj, eraseObj);
		LCs.setOrigin(LCs.getScale().x / 2, LCs.getScale().y / 2);
		//--------------------------------------------------------------------

		//--Arrow point Item--//
		Texture ArrR;
		ArrR.loadFromFile("Object/ArrRed.png");
		Sprite ArrR_i1;
		ArrR_i1.setTexture(ArrR);
		ArrR_i1.setScale(0.9, 0.9);
		ArrR_i1.setPosition(3900.0f, arr_point2);
		ArrR_i1.setOrigin(ArrR_i1.getScale().x / 2, ArrR_i1.getScale().y / 2);

		Sprite ArrR_i2;
		ArrR_i2.setTexture(ArrR);
		ArrR_i2.setScale(0.9, 0.9);
		ArrR_i2.setPosition(eraseObj, eraseObj);
		ArrR_i2.setOrigin(ArrR_i2.getScale().x / 2, ArrR_i2.getScale().y / 2);

		Sprite ArrR_i3;
		ArrR_i3.setTexture(ArrR);
		ArrR_i3.setScale(0.9, 0.9);
		ArrR_i3.setPosition(eraseObj, eraseObj);
		ArrR_i3.setOrigin(ArrR_i3.getScale().x / 2, ArrR_i3.getScale().y / 2);
		
		Sprite ArrR_i4;
		ArrR_i4.setTexture(ArrR);
		ArrR_i4.setScale(0.9, 0.9);
		ArrR_i4.setPosition(eraseObj, eraseObj);
		ArrR_i4.setOrigin(ArrR_i4.getScale().x / 2, ArrR_i4.getScale().y / 2);
		//------------------------------------------------------------------------

		//----Arrow guide Item----//
		Texture Narr_s;
		Narr_s.loadFromFile("Object/NArrS2.png");
		Sprite Narr_is;
		Narr_is.setTexture(Narr_s);
		Narr_is.setScale(1.2, 1.2);
		Narr_is.setPosition(eraseObj, eraseObj);
		//Narr_i1.setRotation(135);
		Narr_is.setOrigin(Narr_is.getScale().x / 2, Narr_is.getScale().y / 2);
		Narr_is.setPosition(ArrR_i1.getPosition().x + 200.f, arr_point2);
		
		Texture Narr;
		Narr.loadFromFile("Object/NArrRed.png");
		Sprite Narr_i1;
		Narr_i1.setTexture(Narr);
		Narr_i1.setScale(1.2, 1.2);
		Narr_i1.setPosition(eraseObj, eraseObj);
		//Narr_i1.setRotation(135);
		Narr_i1.setOrigin(Narr_i1.getScale().x / 2, Narr_i1.getScale().y / 2);

		Texture Narr2;
		Narr2.loadFromFile("Object/NArrRed2.png");
		Sprite Narr_i2;
		Narr_i2.setTexture(Narr);
		Narr_i2.setScale(1.2, 1.2);
		Narr_i2.setPosition(eraseObj, eraseObj);
		//Narr_i2.setRotation(45);
		Narr_i2.setOrigin(Narr_i2.getScale().x / 2, Narr_i2.getScale().y / 2);

		Sprite Narr_i3;
		Narr_i3.setTexture(Narr2);
		Narr_i3.setScale(1.2, 1.2);
		Narr_i3.setPosition(eraseObj, eraseObj);
		//Narr_i3.setRotation(135);
		Narr_i3.setOrigin(Narr_i3.getScale().x / 2, Narr_i3.getScale().y / 2);

		Texture Darr_1;
		Darr_1.loadFromFile("Object/DoorArr.png");
		Sprite Darr1;
		Darr1.setTexture(Darr_1);
		Darr1.setScale(1.2, 1.2);
		Darr1.setPosition(eraseObj, eraseObj);
		//Darr1.setRotation(45);
		Darr1.setOrigin(Darr1.getScale().x / 2, Darr1.getScale().y / 2);

		Texture DGo;
		DGo.loadFromFile("Object/DoorArrGo.png");
		Sprite D_Go;
		D_Go.setTexture(DGo);
		D_Go.setScale(1.2, 1.2);
		D_Go.setPosition(eraseObj, eraseObj);
		D_Go.setOrigin(D_Go.getScale().x / 2, D_Go.getScale().y / 2);

		//***BoxStage**//
		sf::Texture box12;
		box12.loadFromFile("Object/box23.png");
		std::vector<ObjColli>Objs12;
		Objs12.push_back(ObjColli(&box12, sf::Vector2f(boxes2, boxes2_2), sf::Vector2f(0.0f, 770.0f)));
		Objs12.push_back(ObjColli(&box12, sf::Vector2f(boxes2, boxes2_2), sf::Vector2f(0.0f + boxes2, 770.0f)));
		Objs12.push_back(ObjColli(&box12, sf::Vector2f(boxes2, boxes2_2), sf::Vector2f(0.0f + boxes2 * 2, 770.0f)));
		Objs12.push_back(ObjColli(&box12, sf::Vector2f(boxes2, boxes2_2), sf::Vector2f(0.0f + boxes2 * 3, 770.0f)));
		Objs12.push_back(ObjColli(&box12, sf::Vector2f(boxes2, boxes2_2), sf::Vector2f(0.0f + boxes2 * 4, 770.0f)));
		Objs12.push_back(ObjColli(&box12, sf::Vector2f(boxes2, boxes2_2), sf::Vector2f(0.0f + boxes2 * 5, 770.0f)));
		Objs12.push_back(ObjColli(&box12, sf::Vector2f(boxes2, boxes2_2), sf::Vector2f(0.0f + boxes2 * 6, 770.0f)));
		Objs12.push_back(ObjColli(&box12, sf::Vector2f(boxes2, boxes2_2), sf::Vector2f(0.0f + boxes2 * 7, 770.0f)));
		Objs12.push_back(ObjColli(&box12, sf::Vector2f(boxes2, boxes2_2), sf::Vector2f(0.0f + boxes2 * 8, 770.0f)));
		Objs12.push_back(ObjColli(&box12, sf::Vector2f(boxes2, boxes2_2), sf::Vector2f(0.0f + boxes2 * 9, 770.0f)));
		Objs12.push_back(ObjColli(&box12, sf::Vector2f(boxes2, boxes2_2), sf::Vector2f(0.0f + boxes2 * 10, 770.0f)));
		Objs12.push_back(ObjColli(&box12, sf::Vector2f(boxes2, boxes2_2), sf::Vector2f(0.0f + boxes2 * 11, 770.0f)));

		//----box--pick----//
		sf::Texture box22;
		box22.loadFromFile("Object/box3.png");
		std::vector<ObjColli>Objs22;
		for (size_t i = 0;i <= 30;i++)
		{
			Objs22.push_back(ObjColli(&box22, sf::Vector2f(54.0f, 54.0f), sf::Vector2f(rand() % (4300 - 1200) + 1200, 400.0f)));
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

		bool item_s21 = true;
		bool item_s22 = true;
		bool item_s23 = true;
		bool item_s24 = true;

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

			for (size_t i = 0;i < Objs22.size(); i++)
			{
				if ((Objs22[i].getGlobalbounds().intersects(ArrR_i1.getGlobalBounds()) or Compman.getGlobalbounds().intersects(ArrR_i1.getGlobalBounds())) and item_s21 == true)
				{
					WFs.setPosition(ArrR_i1.getPosition().x, rand() % (50 - 10) + 10);
					item_s21 = false;
				}
				if (Compman.getGlobalbounds().intersects(WFs.getGlobalBounds()))
				{
					Narr_is.setPosition(eraseObj, eraseObj);
					ArrR_i1.setPosition(eraseObj, eraseObj);
					WFs.setPosition(eraseObj, eraseObj);
					Narr_i1.setPosition(Compman.getPosition().x - 200.0f, 100.0f);
					Narr_i1.setRotation(135);
					ArrR_i2.setPosition(Narr_i1.getPosition().x - 900.0f, arr_point2);
					cout << ArrR_i2.getPosition().x << endl;
				}
				if ((Compman.getGlobalbounds().intersects(ArrR_i2.getGlobalBounds()) or Objs22[i].getGlobalbounds().intersects(ArrR_i2.getGlobalBounds())) and item_s22 == true)
				{
					LKs.setPosition(ArrR_i2.getPosition().x, rand() % (50 - 10) + 10);
					item_s22 = false;
				}
				if (Compman.getGlobalbounds().intersects(LKs.getGlobalBounds()))
				{
					Narr_i1.setPosition(eraseObj, eraseObj);
					ArrR_i2.setPosition(eraseObj, eraseObj);
					LKs.setPosition(eraseObj, eraseObj);
					Narr_i2.setPosition(Compman.getPosition().x - 200.0f, 100.0f);
					Narr_i2.setRotation(135);
					ArrR_i3.setPosition(Narr_i2.getPosition().x - (900.0f * 2), arr_point2);
				}
				if ((Compman.getGlobalbounds().intersects(ArrR_i3.getGlobalBounds()) or Objs22[i].getGlobalbounds().intersects(ArrR_i3.getGlobalBounds())) and item_s23 == true)
				{
					LCs.setPosition(ArrR_i3.getPosition().x, rand() % (50 - 10) + 10);
					item_s23 = false;
				}
				if (Compman.getGlobalbounds().intersects(LCs.getGlobalBounds()))
				{
					Narr_i2.setPosition(eraseObj, eraseObj);
					ArrR_i3.setPosition(eraseObj, eraseObj);
					LCs.setPosition(eraseObj, eraseObj);
					Narr_i3.setPosition(Compman.getPosition().x + 200.0f, 100.0f);
					Narr_i3.setRotation(45);
					ArrR_i4.setPosition(Narr_i3.getPosition().x + (900.0f *2), arr_point2);
				}
				if ((Compman.getGlobalbounds().intersects(ArrR_i4.getGlobalBounds()) or Objs22[i].getGlobalbounds().intersects(ArrR_i4.getGlobalBounds())) and item_s24 == true)
				{
					ELs.setPosition(ArrR_i4.getPosition().x, rand() % (60 - 20) + 20);
					item_s24 = false;
				}
				if (Compman.getGlobalbounds().intersects(ELs.getGlobalBounds()))
				{
					Narr_i3.setPosition(eraseObj, eraseObj);
					ArrR_i4.setPosition(eraseObj, eraseObj);
					ELs.setPosition(eraseObj, eraseObj);
					Darr1.setPosition(Compman.getPosition().x + 200.0f, Compman.getPosition().y);
					cout << Darr1.getPosition().x << "\t" << Darr1.getPosition().y << endl;
					Darr1.setRotation(45);
					D_Go.setPosition(Darr1.getPosition().x + 600.0f, arr_point2 + 50.0f);
				}
				if (Compman.getGlobalbounds().intersects(D_Go.getGlobalBounds()))
				{
					Darr1.setPosition(eraseObj, eraseObj);
					hell.setPosition(D_Go.getPosition().x + 300.0f, arr_point2 + 30.0f);
				}

			}

			if (Keyboard::isKeyPressed(Keyboard::End))
			{
				hell.setPosition(sf::Vector2f(Compman.getPosition().x + 50.0f, Compman.getPosition().y - 30.0f));
			}

			if (Compman.getGlobalbounds().intersects(hell.getGlobalBounds()))
			{
				cout << "Go State 3" << endl;
				Game_State = 3;
				stage2.stop();
				window.clear();
				break;
			}

			window.clear(sf::Color(255, 255, 255));
			//--DrawEverythings--//
			window.setView(view);
			window.draw(WFs);
			window.draw(LKs);
			window.draw(LCs);
			window.draw(ELs);
			window.draw(ArrR_i1);
			window.draw(ArrR_i2);
			window.draw(ArrR_i3);
			window.draw(ArrR_i4);
			window.draw(Narr_i1);
			window.draw(Narr_i2);
			window.draw(Narr_i3);
			window.draw(Darr1);
			window.draw(D_Go);
			window.draw(Narr_is);
			Compman.Draw(window);
			for (ObjColli& Obj : Objs12)
				Obj.Draw(window);
			for (ObjColli& Obj : Objs22)
				Obj.Draw(window);
			for (ObjColli& Obj : Objs32)
				Obj.Draw(window);
			window.draw(hell);
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
		hell.setPosition(eraseObj, eraseObj);
		hell.setOrigin(hell.getScale().x / 2, hell.getScale().y / 2);

		Texture Gt;
		Gt.loadFromFile("Object/Item_stage3/1.png");
		Sprite Gs;
		Gs.setTexture(Gt);
		Gs.setScale(0.7, 0.7);
		Gs.setPosition(eraseObj, eraseObj);
		Gs.setOrigin(Gs.getScale().x / 2, Gs.getScale().y / 2);

		Texture ArrR;
		ArrR.loadFromFile("Object/ArrRed.png");
		Sprite ArrR_i1;
		ArrR_i1.setTexture(ArrR);
		ArrR_i1.setScale(0.9, 0.9);
		ArrR_i1.setPosition(2400.0f, arr_point2);
		ArrR_i1.setOrigin(ArrR_i1.getScale().x / 2, ArrR_i1.getScale().y / 2);

		Texture Narr_s;
		Narr_s.loadFromFile("Object/NArrS.png");
		Sprite Narr_is;
		Narr_is.setTexture(Narr_s);
		Narr_is.setScale(1.2, 1.2);
		Narr_is.setPosition(eraseObj, eraseObj);
		//Narr_i1.setRotation(135);
		Narr_is.setOrigin(Narr_is.getScale().x / 2, Narr_is.getScale().y / 2);
		Narr_is.setPosition(ArrR_i1.getPosition().x - 200.f, arr_point2);

		Texture Darr_1;
		Darr_1.loadFromFile("Object/DoorArr.png");
		Sprite Darr1;
		Darr1.setTexture(Darr_1);
		Darr1.setScale(1.2, 1.2);
		Darr1.setPosition(eraseObj, eraseObj);
		//Darr1.setRotation(45);
		Darr1.setOrigin(Darr1.getScale().x / 2, Darr1.getScale().y / 2);

		Texture DGo;
		DGo.loadFromFile("Object/DoorArrGo.png");
		Sprite D_Go;
		D_Go.setTexture(DGo);
		D_Go.setScale(1.2, 1.2);
		D_Go.setPosition(eraseObj, eraseObj);
		D_Go.setOrigin(D_Go.getScale().x / 2, D_Go.getScale().y / 2);

		bool item_s31 = true;

		//***BoxStage**//
		sf::Texture box31;
		box31.loadFromFile("Object/Christmas_box.png");
		std::vector<ObjColli>Objs12;
		Objs12.push_back(ObjColli(&box31, sf::Vector2f(boxes3, boxes3_3), sf::Vector2f(0.0f, 1000-192.0f)));
		Objs12.push_back(ObjColli(&box31, sf::Vector2f(boxes3, boxes3_3), sf::Vector2f(0.0f + boxes3, 1000-192.0f)));
		Objs12.push_back(ObjColli(&box31, sf::Vector2f(boxes3, boxes3_3), sf::Vector2f(0.0f + boxes3 * 2, 1000-192.0f)));
		Objs12.push_back(ObjColli(&box31, sf::Vector2f(boxes3, boxes3_3), sf::Vector2f(0.0f + boxes3 * 3, 1000-192.0f)));
		Objs12.push_back(ObjColli(&box31, sf::Vector2f(boxes3, boxes3_3), sf::Vector2f(0.0f + boxes3 * 4, 1000-192.0f)));
		Objs12.push_back(ObjColli(&box31, sf::Vector2f(boxes3, boxes3_3), sf::Vector2f(0.0f + boxes3 * 5, 1000-192.0f)));
		Objs12.push_back(ObjColli(&box31, sf::Vector2f(boxes3, boxes3_3), sf::Vector2f(0.0f + boxes3 * 6, 1000-192.0f)));
		Objs12.push_back(ObjColli(&box31, sf::Vector2f(boxes3, boxes3_3), sf::Vector2f(0.0f + boxes3 * 7, 1000-192.0f)));
		Objs12.push_back(ObjColli(&box31, sf::Vector2f(boxes3, boxes3_3), sf::Vector2f(0.0f + boxes3 * 8, 1000-192.0f)));
		Objs12.push_back(ObjColli(&box31, sf::Vector2f(boxes3, boxes3_3), sf::Vector2f(0.0f + boxes3 * 9, 1000-192.0f)));
		Objs12.push_back(ObjColli(&box31, sf::Vector2f(boxes3, boxes3_3), sf::Vector2f(0.0f + boxes3 * 10, 1000-192.0f)));
		Objs12.push_back(ObjColli(&box31, sf::Vector2f(boxes3, boxes3_3), sf::Vector2f(0.0f + boxes3 * 11, 1000-192.0f)));
		Objs12.push_back(ObjColli(&box31, sf::Vector2f(boxes3, boxes3_3), sf::Vector2f(0.0f + boxes3 * 12, 1000-192.0f)));
		Objs12.push_back(ObjColli(&box31, sf::Vector2f(boxes3, boxes3_3), sf::Vector2f(0.0f + boxes3 * 13, 1000-192.0f)));

		//----box--pick----//
		sf::Texture box32;
		box32.loadFromFile("Object/Christbox_pick.png");
		std::vector<ObjColli>Objs32;
		for (size_t i = 0;i <= 40;i++)
		{
			Objs32.push_back(ObjColli(&box32, sf::Vector2f(54.0f, 54.0f), sf::Vector2f(rand() % (5000 - 1000) + 1000, 400.0f)));
		}

		//---Limit Stage---//
		sf::Texture box33;
		std::vector<ObjColli>Objs33;
		Objs33.push_back(ObjColli(&box33, sf::Vector2f(2.0f, 5000.0f), sf::Vector2f(-268.0f, 724.f)));
		Objs33.push_back(ObjColli(&box33, sf::Vector2f(2.0f, 5000.0f), sf::Vector2f(5890.f, 724.f)));

		//----hitboxtest----//
		hitboxtest hitbox0(0, 0, Vector2f(54, Objs32[0].GetSize().x), Objs32[0].GetPosition());
		hitboxtest hitbox1(0, 0, Vector2f(50, Compman.GetSize().x), Compman.GetPosition());

		TextFont text1;
		TextFont text2;


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
				for (ObjColli& Obj32 : Objs32)
				{
					if (Obj32.GetCollider().CheckCollision(O, direction, 0.0f))
					{
						Obj32.Oncollision(direction);
					}
				}
			}
			//---Hold_Obj---//
			for (int i = 0;i < Objs32.size();i++)
			{
				Objs32[i].Update(deltaTime, Compman.getPosition());
				if (Objs32[i].GetCollider().CheckCollision(c, direction, 0.0f))
				{
					if (Objs32[i].getPickObj() == false)
					{
						Compman.OnCollision(direction);
						//cout << "Collision" << endl;
					}
					if ((Keyboard::isKeyPressed(Keyboard::Space)) && spacebartimer >= max_spacebartimer && Compman.getHold() == false && Objs32[i].getPickObj() == false /*&& Compman.getPosition().y >= Objs2[i].getbody().getPosition().y - 20 && Compman.getPosition().y <= Objs2[i].getbody().getPosition().y + 20*/) {
						spacebartimer = 0;
						Objs32[i].setPickObj(true);
						Compman.setHold(true);
					}
					if (Objs32[i].getPickObj() == true && (Keyboard::isKeyPressed(Keyboard::Space)) && spacebartimer >= max_spacebartimer && Compman.getcanJump() == false)
					{
						spacebartimer = 0;
						Objs32[i].getbody().setPosition(Compman.getPosition().x, Compman.getPosition().y + 60);
						Compman.setHold(false);
						Objs32[i].setPickObj(false);
					}
				}
				Collider o = Objs32[i].GetCollider();
				for (int j = 0; j < Objs32.size();j++)
				{
					if (i != j)
					{
						if (Objs32[j].GetCollider().CheckCollision(o, direction, 1.0f))
						{
							Objs32[i].Oncollision(direction);
						}
					}
				}
			}
			for (ObjColli& Obj : Objs33)
			{
				Collider b = Obj.GetCollider();
				if (Obj.GetCollider().CheckCollision(c, direction, 1.0f))
				{
					Compman.OnCollision(direction);
				}
				for (ObjColli& Obj2 : Objs33)
				{
					if (Obj2.GetCollider().CheckCollision(b, direction, 0.0f))
					{
						Obj2.Oncollision(direction);
					}
				}
			}
			//--hitboxtest_Update--//
			hitbox1.Update(-21.5, -35.5, Compman.GetPosition());
			hitbox0.Update(-27, -27, Objs32[0].GetPosition());

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

			for (size_t i = 0;i < Objs32.size(); i++)
			{
				if ((Objs32[i].getGlobalbounds().intersects(ArrR_i1.getGlobalBounds()) or Compman.getGlobalbounds().intersects(ArrR_i1.getGlobalBounds())) and item_s31 == true)
				{
					Gs.setPosition(ArrR_i1.getPosition().x, -100.0f);
					item_s31 = false;
				}
				if (Compman.getGlobalbounds().intersects(Gs.getGlobalBounds()))
				{
					Narr_is.setPosition(eraseObj, eraseObj);
					ArrR_i1.setPosition(eraseObj, eraseObj);
					Gs.setPosition(eraseObj, eraseObj);
					Darr1.setPosition(Compman.getPosition().x + 200.0f, Compman.getPosition().y);
					cout << Darr1.getPosition().x << "\t" << Darr1.getPosition().y << endl;
					Darr1.setRotation(45);
					D_Go.setPosition(Darr1.getPosition().x + 600.0f, arr_point2 + 50.0f);
				}
				
				if (Compman.getGlobalbounds().intersects(D_Go.getGlobalBounds()))
				{
					Darr1.setPosition(eraseObj, eraseObj);
					hell.setPosition(D_Go.getPosition().x + 300.0f, arr_point2 + 30.0f);
				}

			}

			if (Keyboard::isKeyPressed(Keyboard::End))
			{
				hell.setPosition(sf::Vector2f(Compman.getPosition().x + 50.0f, Compman.getPosition().y - 30.0f));
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
			window.draw(Gs);
			window.draw(Narr_is);
			window.draw(ArrR_i1);
			window.draw(Darr1);
			window.draw(D_Go);
			Compman.Draw(window);
			for (ObjColli& Obj : Objs12)
				Obj.Draw(window);
			for (ObjColli& Obj : Objs32)
				Obj.Draw(window);
			for (ObjColli& Obj : Objs33)
				Obj.Draw(window);
			window.draw(hell);
			text1.drawtext((float)abs(GameTime), (string)"Time : ", (string)" s", sf::Vector2f(view.getCenter().x + (window.getSize().x / 2) - 250, view.getCenter().y - (window.getSize().y / 2) + 20), window, sf::Color(255, 0, 0));
			window.display();
		}
	}

	if (Game_State == 5)
	{
		//cout << "Stage 5";
		sf::View view(sf::Vector2f(500.0f, 450.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
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
					if (event.text.unicode == '\b' && (name.getSize() > 0))
					{
						name1.erase(name.getSize() - 1, 1);
						name.erase(name.getSize() - 1, 1);
					}
					else
					{
						if ((event.text.unicode < 128) && (name.getSize() < 10) && (event.text.unicode != '\b'))
						{
							name += static_cast<char>(event.text.unicode);
							name1 += static_cast<char>(event.text.unicode);
						}
					}
					yourname.setFont(font);
					yourname.setString(name);
					yourname.setFillColor(sf::Color(240,200,0));
					yourname.setCharacterSize(60);
					yourname.setOrigin(yourname.getLocalBounds().width / 2, yourname.getLocalBounds().height / 2);
					yourname.setPosition(window.getSize().x/2, window.getSize().y/2 + 280);
				}
				if (Keyboard::isKeyPressed(Keyboard::Enter))
				{
					window.close();
				}
			}
			window.clear(Color(255,255,255));
			window.setView(view);
			window.draw(name_key);
			window.draw(yourname);
			window.display();
		}

		//cout << "Position x : " << Compman.getPosition().x << "\n" << "Position y : " << Compman.getPosition().y << "\n" << endl;
		//cout << "Go State Score";
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

