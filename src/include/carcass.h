#pragma once

#include "stdafx.h"


class Carcass
{
public:
	struct Interface
	{
		sf::RectangleShape background;
		sf::RectangleShape timeline;
		sf::RectangleShape delimiter;
		int delimiter_amt;
		sf::Vector2f delimiter_pos;
	};

	Carcass(sf::Time timeline);

	void Draw(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window, float dt);

	sf::FloatRect getBounds() const { return _interface.background.getGlobalBounds(); };
	void setPosition(const sf::Vector2f& pos);

private:
	sf::Time _timeline;
	Interface _interface;
};