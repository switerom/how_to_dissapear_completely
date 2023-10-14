#pragma once

#include "stdafx.h"
#include "area.h"

struct ViewCnotrol
{
	bool isMoving;
	sf::Vector2i prevMousePos;
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

	//void zoomView(float delta_zoom, sf::RenderWindow& window);

private:
	sf::View _boardView;
	sf::RectangleShape _bigRect;
	ViewCnotrol _viewControl;
};