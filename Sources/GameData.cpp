#include <iostream>
#include <string> 
#include "../Headers/GameData.h"
#include "../Headers/UIImage.h"
#include "../Headers/UIShape.h"
#include "../Headers/UIText.h"

void GameEvent::print_event() const
{
    std::cout << "At time [" << time << "] On Player " << player << " --> ";
    if (score_delta != 0)
        std::cout << "Score delta [" << score_delta << "] ";

    if (health_delta != 0)
        std::cout << "Health delta [" << health_delta << "] ";

    if (mana_delta != 0)
        std::cout << "Mana delta [" << mana_delta << "] ";

    std::cout << std::endl;
}

void GameData::Init()
{
    constexpr int nb_events = 100;

    m_widthWindow = 1280;
    m_heightWindow = 720;
    
    m_vEvents.clear();

    this->font = new sf::Font();
    font->loadFromFile("Resources/Roboto-Black.ttf");

    m_texture = new sf::Texture();
    m_texture2 = new sf::Texture();
    
    if (!m_texture->loadFromFile("Resources/avatar1.png"))
        return;

    if (!m_texture2->loadFromFile("Resources/avatar2.png"))
        return;

    for (int i = 0; i < nbPlayers; i++)
    {
        players[i].player_id = i;
        players[i].f_health = players[i].f_max_health;
        players[i].f_mana = players[i].f_max_mana;
    }
    
    for (int i = 0; i < nb_events; i++)
    {
        GameEvent s_event;
        s_event.time = static_cast<float>(rand() % 100);
        s_event.player = rand() % 2;
        s_event.health_delta = (rand() % 10) - 8;
        s_event.mana_delta = (rand() % 10) - 8;
        s_event.score_delta = (rand() % 10) - 5;

        m_vEvents.push_back(s_event);
    }

    create_hud();

    std::sort(m_vEvents.begin(), m_vEvents.end(), [](const GameEvent& a, const GameEvent& b) { return a.time < b.time; });
    float timeEvents = 0;
}

void clamp_val(float& val, float min, float max) {}

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

void GameData::update()
{
    const sf::Time elapsed = m_clock.restart();

    m_timeEvents += elapsed.asSeconds();

    for (GameEvent& s_event : m_vEvents)
    {
        if (!s_event.triggered)
        {
            if (s_event.time < m_timeEvents)
            {
                players[s_event.player].apply_event(s_event);
                players[s_event.player].print_data();

                s_event.triggered = true;
            }
        }
    }
    create_hud();
}

void GameData::create_hud()
{
    if ( endGame ) return ;
    
    uiElementslist.clear();

    const int minutes = m_timeEvents / 60;
    const int seconds = m_timeEvents - minutes * 60;

    const std::string time_string = std::to_string(minutes) + " m : " + std::to_string(seconds) + "s";
    
    auto* p_titre = new UIText(time_string,sf::Color::White,font, 20, m_widthWindow / 2, m_heightWindow / 10, 100,200);
    uiElementslist.push_back(p_titre);

    int cmp = 0;
    for (auto& player : players)
    {
        constexpr float heightBlock = 30;
        constexpr float width_block = 200;
        if ( player.f_health <= 0 )
        {
            player.f_health = 0;
            endGame = true;
        }
        
        auto* player1_image = new UIImage(cmp == 0 ? m_texture : m_texture2 ,sf::Color::Red,sf::Vector2f(100, 100),cmp == 0 ? m_widthWindow / 20 : m_widthWindow - m_widthWindow / 20 - 100,100,100,100);
        uiElementslist.push_back(player1_image);

        const float position_x = cmp == 0 ? m_widthWindow / 7 : m_widthWindow - m_widthWindow/7 - 200;
        constexpr int font_size = 13;

        const sf::Color grey(128, 128, 128);
        
        auto* p_shape_bg = new UIShape( grey, position_x,100,heightBlock,width_block );
        auto* p_shape_bg2 = new UIShape( grey , position_x,100 + heightBlock,heightBlock,width_block );
        
        uiElementslist.push_back(p_shape_bg);
        uiElementslist.push_back(p_shape_bg2);

        float widthPercentage = player.f_health / player.f_max_health;

        auto* p_shape = new UIShape( sf::Color::Green , position_x,100,heightBlock,width_block * widthPercentage );
        widthPercentage = player.f_mana / player.f_max_mana;
        
        auto* p_shape2 = new UIShape( sf::Color::Yellow , position_x,100 + heightBlock,heightBlock,width_block * widthPercentage );
        auto* p_shape3 = new UIShape( sf::Color::Blue , position_x,100 + 2*heightBlock,heightBlock,width_block );
        
        uiElementslist.push_back(p_shape);
        uiElementslist.push_back(p_shape2);
        uiElementslist.push_back(p_shape3);
        
        auto* p_text = new UIText(std::to_string(static_cast<int>(player.f_health)),sf::Color::Red,font, font_size, position_x + 90, 108, 200,200);
        auto* p_text2 = new UIText(std::to_string(static_cast<int>(player.f_mana)),sf::Color::Red,font, font_size, position_x + 90, 108 + heightBlock, 200,200);
        auto* p_text3 = new UIText(std::to_string(static_cast<int>(player.f_score)),sf::Color::Red,font, font_size, position_x + 90, 108 + 2 * heightBlock, 200,200);
        
        uiElementslist.push_back(p_text);
        uiElementslist.push_back(p_text2);
        uiElementslist.push_back(p_text3);

        cmp++;
    }
}

void GameData::draw(sf::RenderWindow& window) const
{
    for (int i = 0 ; i < 2 ; i++)
        for(const auto& element : uiElementslist)
            element->draw(window);
}
