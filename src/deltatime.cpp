#include "deltatime.h"

void DeltaTime::restart()
{
    _time = _clock.restart();
}

float DeltaTime::get() const
{
    return _time.asSeconds();
}