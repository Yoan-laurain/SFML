#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include "UIElement.h"

class UIShape : public UIElement
{
public:

    UIShape(sf::Color color, float x , float y , float height, float width);

    void update_rect() override;
    
    void draw(sf::RenderWindow &window);
private :
    sf::Color color;
    sf::RectangleShape* shape;
};
