//
// Created by Miyav on 30-May-24.
//

#ifndef KAHRAMAN_TEXT_H
#define KAHRAMAN_TEXT_H


#include <string>
#include <SFML/Graphics.hpp>

class Text {

public:
    sf::Text text;
    Text(const std::string& text,sf::Font& font,int characterSize,sf::Color color,sf::Text::Style style,sf::Text::Style style2, int x,int y);




};


#endif
