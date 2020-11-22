#include "Menu.h"

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("Object/JudPai.ttf"))
	{

	}
	menu[0].setFont(font);
	menu[0].setCharacterSize(40);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Start");
	menu[0].setOrigin(menu[0].getLocalBounds().width / 2, menu[0].getLocalBounds().height / 2);
	menu[0].setPosition(sf::Vector2f(width / 2, height / (Max_Items + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("HighScore");
	menu[1].setOrigin(menu[1].getLocalBounds().width / 2, menu[1].getLocalBounds().height / 2);
	menu[1].setPosition(sf::Vector2f(width / 2, height / (Max_Items + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Guide");
	menu[2].setOrigin(menu[2].getLocalBounds().width / 2, menu[2].getLocalBounds().height / 2);
	menu[2].setPosition(sf::Vector2f(width / 2, height / (Max_Items + 1) * 3));

	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::White);
	menu[3].setString("Quit");
	menu[3].setOrigin(menu[3].getLocalBounds().width / 2, menu[3].getLocalBounds().height / 2);
	menu[3].setPosition(sf::Vector2f(width / 2, height / (Max_Items + 1) * 4));
}

Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0;i < Max_Items;i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::Moveup()
{
	if (selectedItem - 1 >= 0)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		selectedItem--;
		menu[selectedItem].setFillColor(sf::Color::Red);
	}
}

void Menu::Movedown()
{
	if (selectedItem + 1 <= Max_Items)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		selectedItem++;
		menu[selectedItem].setFillColor(sf::Color::Red);
	}
}
