#pragma once

#include <string>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "UIElement.h"

class UIText : public UIElement
{
public:
    
    UIText(std::string text, sf::Color color, sf::Font* font, int fontsize, float _x, float _y,
           float _height, float _width);

    void update_rect() override;

    void draw(sf::RenderWindow& window) override;

private:

    sf::Text text;
    std::string strText;
    sf::Color textColor;
    sf::Font* font;
    int fontSize;
};
