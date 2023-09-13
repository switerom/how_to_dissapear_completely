#include "stdafx.h"
#include "settings.h"

#include "windowsettings.h"

int main()
{
    WindowSettings windowSettings;
    sf::RenderWindow window;
    windowSettings.initWindow(window);

    
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