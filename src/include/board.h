#pragma once

#include "stdafx.h"
#include "area.h"
#include "timecontroller.h"

struct ViewCnotrol
{
	bool isMoving;
	sf::Vector2i prevMousePos;

	bool isZooming;
};

class Board: public Area
{
public:
	Board();
	void Init();
	virtual void Draw(sf::RenderWindow& window);

	void Update(sf::RenderWindow& window, float dt);
	void moveView(sf::RenderWindow& window, float dt);
	void setViewMoving(sf::RenderWindow& window, bool isMoving);
	void zoomView(sf::RenderWindow& window, float dt_zoom, float dt);

private:
	sf::View _boardView;
	sf::RectangleShape _bigRect;
	ViewCnotrol _viewControl;
};