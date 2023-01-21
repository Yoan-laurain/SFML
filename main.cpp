#include <SFML/Graphics.hpp>
#include "Headers/GameData.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Game");

    GameData gameData;
    gameData.Init();
  
    while (window.isOpen())
    {
        sf::Event event{};
        
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();
        
        window.clear();
        gameData.draw(window);
        gameData.update();
        window.display();
    }
    return EXIT_SUCCESS;
}