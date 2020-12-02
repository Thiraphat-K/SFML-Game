#include "Menu.h"

Menu::Menu(float width, float height)
{
	this->menuTexture[0].loadFromFile("Object/Menu/Start.png");
	this->menupic[0].setTexture(this->menuTexture[0]);
	this->menupic[0].setOrigin(this->menuTexture[0].getSize().x / static_cast<float>(4), this->menuTexture[0].getSize().y / static_cast<float>(2));
	this->menupic[0].setPosition(455, 415);
	this->menupic[0].setTextureRect(sf::IntRect(menuTexture[0].getSize().x / 2, 0, menuTexture[0].getSize().x / 2, menuTexture[0].getSize().y));

	this->menuTexture[1].loadFromFile("Object/Menu/Guide1.png");
	this->menupic[1].setTexture(this->menuTexture[1]);
	this->menupic[1].setOrigin(this->menuTexture[1].getSize().x / static_cast<float>(4), this->menuTexture[1].getSize().y / static_cast<float>(2));
	this->menupic[1].setPosition(425, 590);

	this->menuTexture[2].loadFromFile("Object/Menu/HS1.png");
	this->menupic[2].setTexture(this->menuTexture[2]);
	this->menupic[2].setOrigin(this->menuTexture[2].getSize().x / static_cast<float>(4), this->menuTexture[2].getSize().y / static_cast<float>(2));
	this->menupic[2].setPosition(590, 550);

	this->menuTexture[3].loadFromFile("Object/Menu/Quit1.png");
	this->menupic[3].setTexture(this->menuTexture[3]);
	this->menupic[3].setOrigin(this->menuTexture[3].getSize().x / static_cast<float>(4), this->menuTexture[3].getSize().y / static_cast<float>(2));
	this->menupic[3].setPosition(870, 820);

	for (int i = 1;i < Max_Items;i++)
	{
		this->menupic[i].setTextureRect(sf::IntRect(0, 0, this->menuTexture[i].getSize().x / 2, this->menuTexture[i].getSize().y));
	}
}

Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow& window)
{

	for (int i = 0;i < Max_Items;i++)
	{
		window.draw(this->menupic[i]);
	}
	//std::cout << selectedItem << std::endl;
}

void Menu::Moveup()
{
	if (selectedItem - 1 >= 0)
	{
		this->menupic[selectedItem].setTextureRect(sf::IntRect(0, 0, menuTexture[selectedItem].getSize().x / 2, menuTexture[selectedItem].getSize().y));
		this->selectedItem--;
		this->menupic[selectedItem].setTextureRect(sf::IntRect(menuTexture[selectedItem].getSize().x / 2, 0, menuTexture[selectedItem].getSize().x / 2, menuTexture[selectedItem].getSize().y));

	}
}

void Menu::Movedown()
{
	if (selectedItem + 1 < Max_Items)
	{
		this->menupic[selectedItem].setTextureRect(sf::IntRect(0, 0, menuTexture[selectedItem].getSize().x / 2, menuTexture[selectedItem].getSize().y));
		this->selectedItem++;
		this->menupic[selectedItem].setTextureRect(sf::IntRect(menuTexture[selectedItem].getSize().x / 2, 0, menuTexture[selectedItem].getSize().x / 2, menuTexture[selectedItem].getSize().y));
	}
}
