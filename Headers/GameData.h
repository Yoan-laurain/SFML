#pragma once

#include <vector>
#include <SFML/System/Clock.hpp>
#include "PlayerInfos.h"
#include "UIElement.h"

namespace sf
{
    class Font;
}

struct GameEvent
{
    bool triggered = false;
    int player = 0;
    int score_delta = 0;
    int health_delta = 0;
    int mana_delta = 0;
    float time = 0;
        
    void print_event() const;
};

class GameData
{
public:
    
	void Init();
    void update();
    void draw(sf::RenderWindow& window ) const;
    sf::Clock get_ClockTime() { return m_clock; }

    static GameData *pInstance;
    static GameData* Instance();
    
	std::vector<PlayerInfos*> players;
    std::vector<UIElement*> uiElementslist;
    
    float heightBlock = 20;
    float width_block = 200;
    int font_size = 13;
    float m_heightWindow = 720;
    float m_widthWindow = 1280;

    sf::Font* font;
	
    bool endGame = false;

private:
    sf::Clock m_clock;
    float m_timeEvents = 0;
    std::vector<GameEvent> m_vEvents;
    UIText* titre;
};