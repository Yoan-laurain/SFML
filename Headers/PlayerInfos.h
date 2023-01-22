#pragma once

#include "UIShape.h"
#include <SFML/Graphics/Texture.hpp>
#include "UIImage.h"


class UIText;
class GameEvent;


class PlayerInfos
{
public:

    PlayerInfos();
    
    float f_health = 0;
    float f_mana = 0;
    float f_score = 0;
    float f_max_health = 100;
    float f_max_mana = 100;
    int player_id = -1;
    
    UIShape* bg1;
    UIShape* bg2;

    UIShape* fill1;
    UIShape* fill2;
    UIShape* fill3;

    UIText* text1;
    UIText* text2;
    UIText* text3;

	sf::Texture* m_texture;

	UIImage* player_image;
    
    void apply_event(const GameEvent& event);
    void print_data() const;
    void update();
};