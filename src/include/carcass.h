#pragma once

#include "stdafx.h"

class Carcass
{
public:

	Carcass(sf::Time timeline);

	void Draw(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window, float dt);

	const sf::FloatRect& getBounds() const { return _background.getGlobalBounds(); };

private:
	sf::RectangleShape _background;
	sf::Time _timeline;
	
};