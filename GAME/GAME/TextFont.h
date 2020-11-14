#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<sstream>
#include <iomanip>
#include <string.h>
using namespace std;

class TextFont
{
public:
	TextFont();
	~TextFont();
	void drawtext(float judpai, string frontword, string word, sf::Vector2f position, sf::RenderWindow& window, sf::Color color);
private:
	sf::Font font;
	sf::Text text;
};

