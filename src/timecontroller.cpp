#include "collisiondetection.h"
#include "timecontroller.h"
#include "settings.h"
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

    // Needed to make double click work even if mouse moved a little
    float dx = clickPos.x - _lastClickPos.x;
    float dy = clickPos.y - _lastClickPos.y;
    float clickRange = std::sqrt(dx * dx + dy * dy);

    if (_lastClickTime.asSeconds() < 0.5 && clickRange < DOUBLE_CLICK_RANGE)
        isDoubleClick = true;
    else 
        isDoubleClick = false;

    _lastClickPos = clickPos;

    return isDoubleClick;
}
