#include "carcass.h"
#include "settings.h"

Carcass::Carcass(sf::Time timeline)
{
	_timeline = timeline;

	float width = _timeline.asSeconds() * TIMELINE_WIDTH_FACTOR;

	_background.setFillColor(CARCASS_COLOR);
	_background.setSize(sf::Vector2f(width, CARCASS_HEIGHT));
}

void Carcass::Draw(sf::RenderWindow& window)
{
	window.draw(_background);
}

void Carcass::Update(sf::RenderWindow& window, float dt)
{

}

