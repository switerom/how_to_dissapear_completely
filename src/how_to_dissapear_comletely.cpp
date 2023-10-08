#include "stdafx.h"

#include "settings.h"
#include "timecontroller.h"
#include "windowsettings.h"
#include "explorer.h"
#include "collisiondetection.h"
#include "assetmanager.h"
#include "videoplayer.h"
#include "area.h"

int main()
{
    WindowSettings windowSettings;
    sf::RenderWindow window;
    windowSettings.initWindow(window);  
    TimeController timeController;
    Explorer explorer;
    VideoPlayer videoplayer;
    AssetManager assetmanager;

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
                    if (isColliding(window, explorer))
                    {
                        explorer.selectItem(window);

                        if(timeController.isDoubleClick(window))
                        {
                            if (isColliding(window, explorer, explorer.getTopBoxRect()))
                            {
                                explorer.toggleMaximize();
                            }
                            else
                            {
                                videoplayer.toggleVideoPlayback(explorer.getCurrentVideo());
                            }
                        }
                    }
                    else if (isColliding(window, videoplayer))
                    {
                        if (timeController.isDoubleClick(window))
                        {
                            videoplayer.toggleMaximize();
                        }

                        videoplayer.toggleVideoPlayback();
                    }
                }
            }
            else if (event.type == sf::Event::MouseWheelScrolled) 
            {
                explorer.scrollView(event.mouseWheelScroll.delta, timeController.getDt());
            }
        }

        // возможно добавить условие
            videoplayer.Update(timeController.getDt());

        window.clear();

        explorer.Draw(window);
        videoplayer.Draw(window);
        window.display();
    }

    return 0;
}