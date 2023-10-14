#pragma once

#include "stdafx.h"
#include "area.h"

class Board: public Area
{
public:
	Board();
	void Init();
	virtual void Draw(sf::RenderWindow& window);
	void Update(float dt);

private:
	sf::View _boardView;
	sf::RectangleShape _bigRect;
};