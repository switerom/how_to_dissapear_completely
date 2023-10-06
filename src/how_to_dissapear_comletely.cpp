#include "stdafx.h"

#include "settings.h"
#include "timecontroller.h"
#include "windowsettings.h"
#include "explorer.h"
#include "collisiondetection.h"

int main()
{
    WindowSettings windowSettings;
    sf::RenderWindow window;
    windowSettings.initWindow(window);  
    TimeController timeController;
    Explorer explorer;
    
    while (window.isOpen())
    {
        timeController.restartDt();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if(timeController.isDoubleClick(window))
                    {
                        if(isColliding(sf::Mouse::getPosition(window), explorer.getTopBoxRect()))    // может быть переписать так, чтобы мышь была внутри isColliding функции
                        {
                            std::cout << "True" << "\n";
                            //explorer.toggleMaximize();
                        }
                    }
                }
            }
        }

        window.clear();

        //explorer.Update(dt.get());
        explorer.Draw(window);

        window.display();
    }

    return 0;
}