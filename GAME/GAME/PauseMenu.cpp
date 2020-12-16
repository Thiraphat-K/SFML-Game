#include "PauseMenu.h"

PauseMenu::PauseMenu(float width, float height)
{
	this->PmenuTexture[0].loadFromFile("Object/PauseMenu/rs.png");
	this->Pmenupic[0].setTexture(this->PmenuTexture[0]);
	this->Pmenupic[0].setOrigin(this->PmenuTexture[0].getSize().x / static_cast<float>(4), this->PmenuTexture[0].getSize().y / static_cast<float>(2));
	this->Pmenupic[0].setPosition(500/2, 415);
	this->Pmenupic[0].setTextureRect(sf::IntRect(PmenuTexture[0].getSize().x / 2, 0, PmenuTexture[0].getSize().x / 2, PmenuTexture[0].getSize().y));

	this->PmenuTexture[1].loadFromFile("Object/PauseMenu/mm.png");
	this->Pmenupic[1].setTexture(this->PmenuTexture[1]);
	this->Pmenupic[1].setOrigin(this->PmenuTexture[1].getSize().x / static_cast<float>(4), this->PmenuTexture[1].getSize().y / static_cast<float>(2));
	this->Pmenupic[1].setPosition(500/2, 475);

	this->PmenuTexture[2].loadFromFile("Object/PauseMenu/Q.png");
	this->Pmenupic[2].setTexture(this->PmenuTexture[2]);
	this->Pmenupic[2].setOrigin(this->PmenuTexture[2].getSize().x / static_cast<float>(4), this->PmenuTexture[2].getSize().y / static_cast<float>(2));
	this->Pmenupic[2].setPosition(500/2, 520);


	for (int i = 1;i < PMax_Items;i++)
	{
		this->Pmenupic[i].setTextureRect(sf::IntRect(0, 0, this->PmenuTexture[i].getSize().x / 2, this->PmenuTexture[i].getSize().y));
	}
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::draw(sf::RenderWindow& window)
{

	for (int i = 0;i < PMax_Items;i++)
	{
		window.draw(this->Pmenupic[i]);
	}
	//std::cout << PselectedItem << std::endl;
}

void PauseMenu::Moveup()
{
	if (PselectedItem - 1 >= 0)
	{
		this->Pmenupic[PselectedItem].setTextureRect(sf::IntRect(0, 0, PmenuTexture[PselectedItem].getSize().x / 2, PmenuTexture[PselectedItem].getSize().y));
		this->PselectedItem--;
		this->Pmenupic[PselectedItem].setTextureRect(sf::IntRect(PmenuTexture[PselectedItem].getSize().x / 2, 0, PmenuTexture[PselectedItem].getSize().x / 2, PmenuTexture[PselectedItem].getSize().y));

	}
}

void PauseMenu::Movedown()
{
	if (PselectedItem + 1 < PMax_Items)
	{
		this->Pmenupic[PselectedItem].setTextureRect(sf::IntRect(0, 0, PmenuTexture[PselectedItem].getSize().x / 2, PmenuTexture[PselectedItem].getSize().y));
		this->PselectedItem++;
		this->Pmenupic[PselectedItem].setTextureRect(sf::IntRect(PmenuTexture[PselectedItem].getSize().x / 2, 0, PmenuTexture[PselectedItem].getSize().x / 2, PmenuTexture[PselectedItem].getSize().y));
	}
}
