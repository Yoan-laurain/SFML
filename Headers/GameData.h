#pragma once

#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include "UIElement.h"
#include "UIImage.h"
#include "UIShape.h"
#include "UIText.h"

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

class PlayerInfos
{
public:
	float f_health = 0;
    float f_mana = 0;
	float f_score = 0;
    const float f_max_health = 100;
    const float f_max_mana = 100;

    int player_id = -1;

    void apply_event(const GameEvent& event);
    void print_data() const;
};

class GameData
{
public:
    
	void Init();
    void update();
    void draw(sf::RenderWindow& window ) const;
    sf::Clock get_ClockTime() { return m_clock; }

    static const int nbPlayers = 2;
	PlayerInfos players[nbPlayers];
    std::vector<UIElement*> uiElementslist;

    void create_hud();

private:

    sf::Clock m_clock;
    float m_timeEvents = 0;
    std::vector<GameEvent> m_vEvents;

    bool endGame = false;

    float m_heightWindow;
    float m_widthWindow;

    sf::Texture* m_texture;
    sf::Texture* m_texture2;
    
    
    sf::Font* font;
};

