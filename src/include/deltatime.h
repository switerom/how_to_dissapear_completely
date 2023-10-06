#include "stdafx.h"

class DeltaTime
{
public:
    DeltaTime() : _clock(), _time() {}

    // Restart clock to get time of 1 frame in a loop
    void restart();

    // Get deltaTime as float
    float get() const;

private:
    sf::Clock _clock;
    sf::Time _time;
};