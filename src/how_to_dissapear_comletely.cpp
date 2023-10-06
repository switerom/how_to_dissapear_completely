#include "stdafx.h"

#include "settings.h"
#include "deltatime.h"
#include "windowsettings.h"
#include "explorer.h"

int main()
{
    WindowSettings windowSettings;
    sf::RenderWindow window;
    windowSettings.initWindow(window);  
    DeltaTime dt;
    Explorer explorer;
    
    while (window.isOpen())
    {
        dt.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        //explorer.Update(dt.get());
        explorer.Draw(window);

        window.display();
    }

    return 0;
}