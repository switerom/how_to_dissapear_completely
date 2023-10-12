#include "collisiondetection.h"
#include "timecontroller.h"
#include "stdafx.h"

TimeController::TimeController()
{
}

void TimeController::restartDt()
{
    _dtTime = _dtClock.restart();
}

float TimeController::getDt() const
{
    return _dtTime.asSeconds();
}

bool TimeController::isDoubleClick(sf::RenderWindow& window)
{
    sf::Vector2i clickPos = sf::Mouse::getPosition(window);

    bool isDoubleClick{};

    _lastClickTime = _lastClickClock.restart();

    if (_lastClickTime.asSeconds() < 0.5 && clickPos == _lastClickPos)
        isDoubleClick = true;
    else 
        isDoubleClick = false;

    _lastClickPos = clickPos;

    return isDoubleClick;
}
