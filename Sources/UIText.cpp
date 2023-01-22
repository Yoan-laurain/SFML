#include "../Headers/UIText.h"
#include <SFML/Graphics/Text.hpp>
#include <utility>

UIText::UIText(std::string text, sf::Color color, sf::Font* font,int size, float _x, float _y,
               float _height, float _width)
{
    this->strText = std::move(text);
    this->textColor = color;
    this->font = font;
    this->fontSize = size;
    this->x = _x;
    this->y = _y;
    this->height = _height;
    this->width = _width;
}

void UIText::update_rect()
{
    UIElement::update_rect();
}

void UIText::draw( sf::RenderWindow &window )
{
    text.setString(strText);
    text.setFillColor(textColor);
	text.setOrigin(width / 2, height / 2);
    text.setFont(*font);
    text.setCharacterSize(fontSize);
    text.setPosition(x, y);
    window.draw(text);
}
