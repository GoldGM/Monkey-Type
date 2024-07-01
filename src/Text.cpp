#include "Text.h"



Text::Text(const std::string& text,sf::Font& font,int characterSize,sf::Color color, sf::Text::Style style, sf::Text::Style style2, int x, int y) {

    this->text.setString(text);
    this->text.setFont(font);
    this->text.setCharacterSize(characterSize);
    this->text.setFillColor(color);
    this->text.setStyle(style | style2);
    this->text.setPosition(x,y);
}
