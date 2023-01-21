#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

class UIElement
{
    public:
    
    void InitResources(float _x, float _y, float _height, float _width);
    virtual void update(float DeltaTime);
    virtual void update_rect();
    virtual void draw( sf::RenderWindow& window) = 0;

protected:
    float x;
    float y;
    float width;
    float height;
};