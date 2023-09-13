#include "stdafx.h"
#include "settings.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), GAME_NAME, sf::Style::Default);

    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }

    return 0;
}