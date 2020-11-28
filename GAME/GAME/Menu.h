#pragma once
#include"Anyinclude.h"

class Menu
{
public:
	Menu(float width, float height);
	~Menu();

	void draw(sf::RenderWindow& window);
	void Moveup();
	void Movedown();
	int GetPressedItem() { return selectedItem; }

	int selectedItem = 0;
private:
	sf::Font font;
	sf::Texture menuTexture[Max_Items];
	sf::Sprite menupic[Max_Items];

};

