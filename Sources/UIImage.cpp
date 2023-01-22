#include "../Headers/UIImage.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>

UIImage::UIImage(sf::Texture* texture, const sf::Color& color, sf::Vector2f UV, float _x, float _y,
                 float _height, float _width)
{
    this->m_imageUrl = m_imageUrl;
    this->m_color = color;
    this->m_UV = UV;
    this->x = _x;
    this->y = _y;
    this->height = _height;
    this->width = _width;

    sprite = new sf::RectangleShape(sf::Vector2f(width, height));
	sprite->setOrigin(width / 2, height / 2);

    this->texture = texture;
}

void UIImage::update_rect()
{
    UIElement::update_rect();
}

void UIImage::draw(sf::RenderWindow& window)
{
    sprite->setTexture(texture);
    sprite->setPosition(x, y);
    window.draw(*sprite);
}
