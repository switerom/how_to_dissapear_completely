#pragma once

#include "stdafx.h"

class Carcass
{
public:

	Carcass(sf::Time timeline);

	void Draw(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window, float dt);

	sf::FloatRect getBounds() const { return _background.getGlobalBounds(); };
	void setPosition(const sf::Vector2f& pos);

private:
	sf::RectangleShape _background;
	sf::Time _timeline;
};