#pragma once

#include <string>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include "UIElement.h"

namespace sf
{
    class RenderTarget;
    class RenderStates;
}

class UIImage : public UIElement
{
public:
    UIImage(sf::Texture* texture, const sf::Color& color,sf::Vector2f UV, float _x, float _y,
            float _height, float _width);

    void update_rect() override;

    void draw(sf::RenderWindow& window) override;

private:
 
    std::string m_imageUrl;
    sf::Color m_color;
    sf::Vector2f m_UV;
    sf::Texture* texture;
    sf::RectangleShape* sprite;
};
