#include <iostream>
#include <string> 
#include "../Headers/GameData.h"
#include "../Headers/UIText.h"

GameData* GameData::Instance()
{
    if (pInstance == nullptr)
        pInstance = new GameData;

    return pInstance;
}

GameData *GameData::pInstance = nullptr;

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
                players[s_event.player]->apply_event(s_event);
                players[s_event.player]->print_data();

                s_event.triggered = true;
            }
        }
    }
    
    const int minutes = m_timeEvents / 60;
    const int seconds = m_timeEvents - minutes * 60;

	titre->strText = std::to_string(minutes) + " m : " + std::to_string(seconds) + "s";

}

void GameData::draw(sf::RenderWindow& window) const
{
    for (int i = 0 ; i < 2 ; i++)
        for(const auto& element : uiElementslist)
            element->draw(window);
}

void GameData::Init()
{
    constexpr int nb_events = 100;
 
    m_vEvents.clear();

    for (int i = 0; i < players.size(); i++)
    {
        players[i]->player_id = i;
        players[i]->f_health = players[i]->f_max_health;
        players[i]->f_mana = players[i]->f_max_mana;
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

	titre = new UIText("0 m : 0s", sf::Color::White, font, 20, m_widthWindow / 2, m_heightWindow / 10, 50, 100);
    uiElementslist.push_back(titre);
    
    std::sort(m_vEvents.begin(), m_vEvents.end(), [](const GameEvent& a, const GameEvent& b) { return a.time < b.time; });
}

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
