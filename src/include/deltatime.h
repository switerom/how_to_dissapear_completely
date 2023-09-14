#include "stdafx.h"

class DeltaTime
{
public:
    DeltaTime() : _clock(), _time() {}

    float restart();

    float get() const;

private:
    sf::Clock _clock;
    sf::Time _time;
};