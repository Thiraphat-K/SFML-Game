#include "TextFont.h"

TextFont::TextFont()
{
	font.loadFromFile("Object/JudPai.ttf");
	text.setFont(font);
	text.setCharacterSize(25);
	
}

TextFont::~TextFont()
{
}

void TextFont::drawtext(float judpai, string frontword ,string backword  , sf::Vector2f position, sf::RenderWindow& window, sf::Color color)
{
	text.setFillColor(color);
	text.setPosition(position);
	stringstream num,life;
	num << frontword << fixed <<  setprecision(0) << judpai << backword;
	text.setString(num.str());
	window.draw(text);
}
