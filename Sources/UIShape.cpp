#include "../Headers/UIShape.h"

#include <SFML/Graphics/RectangleShape.hpp>

UIShape::UIShape(sf::Color color, const float x, const float y, const float height, float width){
    this->color = color;
    this->x = x;
    this->y = y;
    this->height = height;
    this->width = width;

    shape = new sf::RectangleShape(sf::Vector2f(width, height));
}

void UIShape::update_rect()
{
    UIElement::update_rect();
}

void UIShape::draw(sf::RenderWindow& window)
{
    shape->setFillColor(color);
    shape->setPosition(x, y);
    shape->setSize(sf::Vector2f(width, height));
    window.draw(*shape);
}
