#include <SFML/Graphics.hpp>
#include "Headers/GameData.h"

int main()
{
    GameData::Instance()->font = new sf::Font();
    if (!GameData::Instance()->font->loadFromFile("Resources/Roboto-Black.ttf")) return 0 ;
	
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Game");

	PlayerInfos* player1 = new PlayerInfos();
    PlayerInfos* player2 = new PlayerInfos();

    GameData::Instance()->Init();
  
    while (window.isOpen())
    {
        sf::Event event{};
        
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();
        
        window.clear();
        GameData::Instance()->update();
        player1->update();
		player2->update();
        GameData::Instance()->draw(window);
        window.display();
    }
    return EXIT_SUCCESS;
}