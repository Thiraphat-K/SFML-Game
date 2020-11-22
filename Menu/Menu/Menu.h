#pragma once
#include<SFML/Graphics.hpp>
#define Max_Items 4 //Start HighScore Guide Quit
class Menu
{
public:
	Menu(float width, float height);
	~Menu();

	void draw(sf::RenderWindow& window);
	void Moveup();
	void Movedown();
	int GetPressedItem() { return selectedItem; }

private:
	int selectedItem = 0;
	sf::Font font;
	sf::Text menu[Max_Items];
};

