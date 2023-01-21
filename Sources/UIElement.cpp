#include "../Headers/UIElement.h"

namespace sf
{
    class RenderWindow;
}

void UIElement::InitResources( float _x , float _y , float _height, float _width)
{
    this->x = _x;
    this->y = _y;
    this->height = _height;
    this->width = _width;
}

void UIElement::update(float DeltaTime) {}

void UIElement::update_rect() {}