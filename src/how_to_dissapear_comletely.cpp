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
    //VideoPlayer videoplayer;
    AssetManager assetmanager;
    //Area area;

    //sfe::Movie _currentVideo;
    //_currentVideo.openFromFile("rsc/vid/2.mp4");
    //_currentVideo.play();

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
                        if(timeController.isDoubleClick(window) && isColliding(window, explorer, explorer.getTopBoxRect()))
                        {
                            explorer.toggleMaximize();
                        }
                        
                        explorer.selectItem(window);
                    }
                    //else if (isColliding(window, area))
                    //{
                    //    if (timeController.isDoubleClick(window) && isColliding(window, area, area.getTopBoxRect()))
                    //    {
                    //        area.toggleMaximize();
                    //    }
                    //}
                }
            }
            else if (event.type == sf::Event::MouseWheelScrolled) 
            {
                explorer.scrollView(event.mouseWheelScroll.delta, timeController.getDt());
            }
        }

        window.clear();

        explorer.Draw(window);
        //_currentVideo.update();
        //window.draw(_currentVideo);
        window.display();
    }

    return 0;
}