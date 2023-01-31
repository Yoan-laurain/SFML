#include "../Headers/PlayerInfos.h"
#include <iostream>
#include "../Headers/UIImage.h"
#include "../Headers/UIText.h"
#include "../Headers/GameData.h"

void clamp_val(float& val, float min, float max) {}

PlayerInfos::PlayerInfos()
{
    player_id = GameData::Instance()->players.size();
    f_health = f_max_health;
	f_mana = f_max_mana;

    m_texture = new sf::Texture();

    switch (player_id)
    {
        case 0:
            if (!m_texture->loadFromFile("Resources/avatar1.png"))
                return;
            break;

        case 1:
            if (!m_texture->loadFromFile("Resources/avatar2.png"))
                return;
            break;

        case 2:
            if (!m_texture->loadFromFile("Resources/avatar1.png"))
                return;
            break;

        case 3:
            if (!m_texture->loadFromFile("Resources/avatar1.png"))
                return;
            break;
        default:
            break;
    }

    const sf::Color grey(128, 128, 128);

    float position_x{};
	float position_y{};

    switch (player_id)
    {
        case 0 :
			position_x = GameData::Instance()->m_widthWindow / 4;
			position_y = GameData::Instance()->m_heightWindow / 4;
			break;

        case 1 :
			position_x = GameData::Instance()->m_widthWindow / 4 * 3;
			position_y = GameData::Instance()->m_heightWindow / 4;
            break;

		case 2 :
			position_x = GameData::Instance()->m_widthWindow / 4;
			position_y = GameData::Instance()->m_heightWindow / 4 * 3;
            break;
               
        case 3 :
			position_x = GameData::Instance()->m_widthWindow / 4 * 3;
			position_y = GameData::Instance()->m_heightWindow / 4 * 3;
            break;
        default:
            break;
    }

    float imageWidth = 100.f;
	
    player_image = new UIImage(m_texture, sf::Color::Red, sf::Vector2f(100, 100), position_x, position_y, imageWidth, imageWidth);
    GameData::Instance()->uiElementslist.push_back(player_image);
	
    bg1 = new UIShape(grey, position_x, position_y + imageWidth, GameData::Instance()->heightBlock, GameData::Instance()->width_block);
    bg2 = new UIShape(grey, position_x, position_y + imageWidth + GameData::Instance()->heightBlock, GameData::Instance()->heightBlock, GameData::Instance()->width_block);

    GameData::Instance()->uiElementslist.push_back(bg1);
    GameData::Instance()->uiElementslist.push_back(bg2);
	
    fill1 = new UIShape(sf::Color::Green, position_x, position_y  + imageWidth, GameData::Instance()->heightBlock, GameData::Instance()->width_block * f_health / f_max_health);
    fill2 = new UIShape(sf::Color::Yellow, position_x, position_y + imageWidth +  GameData::Instance()->heightBlock, GameData::Instance()->heightBlock, GameData::Instance()->width_block * f_mana / f_max_mana);
    fill3 = new UIShape(sf::Color::Blue, position_x, position_y + imageWidth + 2 * GameData::Instance()->heightBlock, GameData::Instance()->heightBlock, GameData::Instance()->width_block);

    GameData::Instance()->uiElementslist.push_back(fill1);
    GameData::Instance()->uiElementslist.push_back(fill2);
    GameData::Instance()->uiElementslist.push_back(fill3);
	
    text1 = new UIText(std::to_string(static_cast<int>(f_health)), sf::Color::Red, GameData::Instance()->font, GameData::Instance()->font_size, position_x,position_y + imageWidth, 20, 20);
    text2 = new UIText(std::to_string(static_cast<int>(f_mana)), sf::Color::Red, GameData::Instance()->font, GameData::Instance()->font_size, position_x, position_y + imageWidth + GameData::Instance()->heightBlock, 20, 20);
    text3 = new UIText(std::to_string(static_cast<int>(f_score)), sf::Color::Red, GameData::Instance()->font, GameData::Instance()->font_size, position_x, position_y + imageWidth + 2 * GameData::Instance()->heightBlock, 20, 20);

    GameData::Instance()->uiElementslist.push_back(text1);
    GameData::Instance()->uiElementslist.push_back(text2);
    GameData::Instance()->uiElementslist.push_back(text3);

	GameData::Instance()->players.push_back(this);
}

void PlayerInfos::apply_event(const GameEvent& event)
{
    f_health += event.health_delta;
    f_mana += event.mana_delta;
    f_score += event.score_delta;

    clamp_val(f_health, 0, f_max_health);
    clamp_val(f_mana, 0, f_max_mana);
}

void PlayerInfos::print_data() const
{
    std::cout << "Player " << player_id << "[Health] : " << f_health << "[Mana] : " << f_mana << " [Score] : " << f_score << std::endl;
}

void PlayerInfos::update()
{
	fill1->shape->setScale(f_health / f_max_health, 1);
	fill2->shape->setScale(f_mana / f_max_mana, 1);
       
	text1->strText = std::to_string(static_cast<int>(f_health));
	text2->strText = std::to_string(static_cast<int>(f_mana));
	text3->strText = std::to_string(static_cast<int>(f_score));
}