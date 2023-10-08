#pragma once

#include "stdafx.h"

class TimeController
{
public:
    TimeController();

    // Restart clock to get time of 1 frame in a loop
    void restartDt();

    // Get deltaTime as float
    float getDt() const;

    bool isDoubleClick(sf::RenderWindow& window);

private:
    sf::Clock _dtClock;
    sf::Time _dtTime;

    sf::Vector2i _lastClickPos;
    //bool _isDoubleClick;
    sf::Time _lastClickTime;
    sf::Clock _lastClickClock;
};