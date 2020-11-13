#include "TextFont.h"

TextFont::TextFont()
{
	font.loadFromFile("Object/JudPai.ttf");
	text.setFont(font);
	text.setCharacterSize(25);
	text.setFillColor(sf::Color(0, 0, 255));
	
}

TextFont::~TextFont()
{
}

void TextFont::drawtext(float judpai, string frontword ,string backword  , sf::Vector2f position, sf::RenderWindow& window)
{
	text.setPosition(position);
	stringstream num;
	num << frontword << fixed <<  setprecision(2) << judpai << backword;
	text.setString(num.str());
	window.draw(text);
}
