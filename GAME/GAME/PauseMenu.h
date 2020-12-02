#pragma once
#include"Anyinclude.h"

class PauseMenu
{
public:
	PauseMenu(float width, float height);
	~PauseMenu();

	void draw(sf::RenderWindow& window);
	void Moveup();
	void Movedown();
	int GetPressedItem() { return PselectedItem; }

	int PselectedItem = 0;
private:
	sf::Texture PmenuTexture[PMax_Items];
	sf::Sprite Pmenupic[PMax_Items];

};

