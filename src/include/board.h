#pragma once

#include "stdafx.h"
#include "area.h"
#include "timecontroller.h"
#include "carcass.h"
#include "videoplayer.h"

class Board: public Area
{
public:
	struct ViewCnotrol
	{
		sf::Vector2i prevMousePos;
		bool isMoving;
	};

	struct MoveControl
	{
		bool isCarcassMoving;
		//int selectedCarcass;
		const sfe::Movie* selectedCarcass;
		sf::Vector2f selectPosShift;
	};

	Board();
	~Board();
	void Init();
	virtual void Draw(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window, float dt);

	void moveView(sf::RenderWindow& window, float dt);
	void setViewMoving(sf::RenderWindow& window, bool isMoving);
	void zoomView(sf::RenderWindow& window, float dt_zoom, float dt);

	void createCarcass(const sfe::Movie* video);

	void setCarcassMoving(bool isCarcassMoving) { _movecontrol.isCarcassMoving = isCarcassMoving; };
	void moveCarcass(sf::RenderWindow& window);
	void selectCarcass(sf::RenderWindow& window);
	void addScreenshot(const Screenshot& screenshot);

private:
	sf::View _boardView;
	sf::RectangleShape _bigRect;
	ViewCnotrol _viewControl;

	std::map<const sfe::Movie*, Carcass*> _carcasses;
	std::list<const sfe::Movie*> _layers;

	MoveControl _movecontrol;
};