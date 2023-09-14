#include "deltatime.h"

float DeltaTime::restart()
{
    sf::Time elapsed = _clock.restart();
    _time = elapsed;
    return elapsed.asSeconds();
}

float DeltaTime::get() const
{
    return _time.asSeconds();
}