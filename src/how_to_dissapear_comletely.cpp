﻿#include "stdafx.h"

#include "settings.h"
#include "timecontroller.h"
#include "windowsettings.h"
#include "explorer.h"
#include "collisiondetection.h"
#include "assetmanager.h"
#include "videoplayer.h"
#include "area.h"
#include "areacontroller.h"
#include "board.h"
#include "keygen.h"

int main()
{
    WindowSettings windowSettings;
    sf::RenderWindow window;
    windowSettings.initWindow(window);  
    TimeController timeController;
    Explorer explorer;
    VideoPlayer videoplayer;
    Board board;
    AreaController areacontroller ( explorer, videoplayer, board );
    AssetManager assetmanager;

    while (window.isOpen())
    {
        timeController.restartDt();
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            areacontroller.EventControl(event, window, timeController);
        }

        areacontroller.Update(window, timeController.getDt());

        window.clear();
        areacontroller.Draw(window);
        window.display();
    }

    return 0;
}